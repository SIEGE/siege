/**
    \brief Sorting functions
    \todo cleanup and document
*/
module siege.util.sort;

private
{
    import std.math;
    import std.stdio;
}

/*
unittest
{
	int n = 7*12;
	float numbers[] = [
	 17.0, 18.0, 0.0, 0.0, 5.0, 6.0, 21.0, 21.0, 12.0, 16.0, -9.0, 20.0,
	 17.1, 18.1, 0.1, 0.1, 5.1, 6.0, 21.1, 21.0, 12.1, 16.0, 9.1, 20.1,
	 17.2, 18.0, 0.2, 0.0, 5.2, 6.0, 21.2, 21.0, 12.2, 16.2, 9.0, 20.2,
	 17.3, 18.3, 0.3, 0.0, 5.3, 6.0, 21.3, 21.0, 12.3, 16.0, 9.3, 20.0,
	 17.4, 18.0, 0.4, 0.3, 5.4, 6.3, 21.0, 21.4, 12.0, 16.4, 9.3, 20.0,
	 17.5, 18.0, 0.0, 0.0, 5.0, -6.0, 21.5, 21.0, 12.0, 16.5, 9.0, 20.0,
	 17.6, 18.0, 0.5, 0.0, 5.5, 6.0, 21.0, 21.0, 12.5, 16.0, 9.0, 20.5
	];
	BSort!(float) sortlist = new BSort!(float)(7,n);

	sortlist.Sort(numbers.ptr,n);
	writefln("-----------------------");
	writefln("BSort unittest:");
	writefln("-----------------------");
	for ( uint i = 0; i < n; i++ )
	{
		writefln(numbers[i]);
	}
	writefln("-----------------------");
	writefln("");

	delete sortlist;
}
*/

/**
Bucket sort template
**/

class BSort(T)
{
	///*
	this(uint N_Bucketss, ulong max_n)
	{
		buckets = null;
		element_heap = null;

		N_Buckets = N_Bucketss;
		N = max_n;
		has_bounds = false;
		lower_b = new T();
		*lower_b = 0.0;
		upper_b = new T();
		*upper_b = 0.0;

		BucketInit();
	}
	this(uint N_Bucketss, ulong max_n, T lb, T ub)
	{
		buckets = null;
		element_heap = null;

		N_Buckets = N_Buckets;
		N = max_n;
		has_bounds = false;
		*lower_b = lb;
		*upper_b = ub;

		BucketInit();
	}
	~this()
	{
		if ( buckets !is null ) delete buckets;
		if ( element_heap !is null ) delete element_heap;
	}

protected:
	struct SListConstant
	{
		SListConstant	*next;
		T		data;
	}
	struct CListHeader
	{
		SListConstant	*first;
		SListConstant	*last;
		CListHeader	*next;
		T		min;
		T		max;
	}
	struct bucket_info
	{
		T		*section;
		T		min;
		T		max;
	}
	CListHeader	[]buckets;
	SListConstant	[]element_heap;

	uint	N_Buckets;
	ulong	N;

	bool	has_bounds;
	T	*lower_b;
	T	*upper_b;
	T	bucket_delta;
	void BucketInit()
	{
		SListConstant	*heap_ptr;
		CListHeader	*prev_bucket_class = null;
		N_Buckets++;
		// make a list of pointers to the category elements.
		buckets = new CListHeader[N_Buckets];
		//memset(buckets,0,sizeof(CListHeader)*(N_Buckets));
		//
		element_heap = new  SListConstant[N + N_Buckets];
		//memset(element_heap,0,sizeof(SListConstant)*(N + N_Buckets));
		// make a heap for element allocation.
		heap_ptr = element_heap.ptr;
		{ // Initialize a set of category elements. { One element for each category. }
			ulong i;
			for ( i = 0; i < N_Buckets; i++ )
			{
				// Each class is a list. The heap element
				buckets[i].last = buckets[i].first = heap_ptr;
				InitMinMax(buckets[i].min,buckets[i].max);
				if ( prev_bucket_class !is null )
				{
					prev_bucket_class.next = &buckets[i];
				}
				prev_bucket_class = &buckets[i];
				heap_ptr++;
			}
		}
	}
	void InitMinMax(inout T c_min, inout T c_max)
	{
		c_min = T.max;
		c_max = -T.max;
	}
	ulong TShift(double d)
	{
		ulong i;

		i = cast(ulong)( fabs((d - (*lower_b))/bucket_delta) );
		return(i);
	}
	void SmallSectionSort2(T *buf_start)
	{
		T first, second;
		first = buf_start[0];
		second = buf_start[1];

		if ( first > second )  // First is bigger than second, so swap
		{
			buf_start[0] = second;
			buf_start[1] = first;
		}
	}
	void SmallSectionSort3(T *buf_start)
	{
		T first, second, third;
		first = buf_start[0];
		second = buf_start[1];
		third = buf_start[2];

		if ( first > second ) // First is bigger than second, so swap
		{
			buf_start[0] = second;
			buf_start[1] = first;
			first = buf_start[0]; // Reassign for next comparison.
			second = buf_start[1];
		}

		if ( second > third ) // First is bigger than second, so swap
		{
			buf_start[1] = third;
			buf_start[2] = second;
			second = third;
			if ( first > second )
			{
				buf_start[0] = second;
				buf_start[1] = first;
			}
		}
	}

	void SmallSectionSort4(T *buf_start)
	{
		SmallSectionSort2(buf_start);
		SmallSectionSort2(buf_start + 2);
		{
			T second, third;

			second = buf_start[1];
			third = buf_start[2];

			if ( second <= third ) return;

			buf_start[1] = third;
			buf_start[2] = second;
			SmallSectionSort4(buf_start);
		}
	}

	void BucketSort(T *buf_start, T *buf_end, int depth)
	{
		ulong sect_size = cast(ulong)(buf_end) - cast(ulong)(buf_start);
		{
			// For example, word size is 4 bytes. So, divide sect_size by 4.
			// That yield the # of pointers from the amount of space storing the pointers.
			// >> 2 = /4. So, shift by 1/2 word size.
			sect_size = sect_size / T.sizeof; // Compiler optimizes second term.
		}
		{
			bucket_delta = ((*upper_b) - (*lower_b))/(N_Buckets-1);
			if ( bucket_delta == 0 ) bucket_delta = 1;
		}
		{
			// SORT SHORT SECTIONS IN A BRUTE FORCE WAY.

			if (  sect_size <= 4 ) // This is a stopping condition.
			{

				if ( sect_size == 2 )
				{
					SmallSectionSort2(buf_start);
				} else if ( sect_size == 3 )
				{
					SmallSectionSort3(buf_start);
				} else if ( sect_size == 4 )
				{
					SmallSectionSort4(buf_start);
				}
				return;
			}
		}
		T lb = *lower_b;
		T ub = *upper_b;
		// OTHERWISE
		SListConstant	*heap_ptr;
		T		*b_start = buf_start;
		// Sectbuf stores the end points of the sections of data which
		// arise from the classes being reassembled. Only sections with
		// data are stored, but sectbuf is made large enough to handle
		// the eventuality of all the characters being represented.
		bucket_info	[]sectbuf = new bucket_info[(N_Buckets + 1)];
		bucket_info	*sectbufptr;
		bucket_info	*endsects;
		sectbufptr = sectbuf.ptr;
		// Always start the heap at the end of the list headers.
		// The first max_bucket elements are already allocated, ready
		// to receive the first element in the class.
		heap_ptr = element_heap.ptr + N_Buckets;
		{	// Build the list of pointers.
			T c;
			SListConstant *el;
			CListHeader *bucket;
			ulong ith_bucket;
			while ( buf_start < buf_end )
			{
				c = *buf_start++;  // Pointer data string.
				ith_bucket = TShift(c);

				// Get the last element of the class, which is allocated
				// for receipt of the next data element.
				bucket = &buckets[ith_bucket];
				el = bucket.last;		// This is a preparatory pointer.
				el.data = c;			// add data point to class.

				// Append to where the next element will go.
				el.next = heap_ptr++;	// Append only.
				bucket.last = el.next;
				// find max and min so that buckets may be resized in a recursive step;
				if ( c < bucket.min ) bucket.min = c;
				if ( c > bucket.max ) bucket.max = c;
			}
		}
		buf_start = b_start; // reset buf_start;

		{	// Reassemble the list.
			CListHeader *h;
			h = buckets.ptr; // First of classes.
			// Walk list of classes.
			while ( h )
			{
				SListConstant *el = h.first;
				SListConstant *last_el = h.last;
				if ( el != last_el ) // Not an empty class
				{
					h.last = h.first; // Empty the class for reuse.
					sectbufptr.min = h.min;
					sectbufptr.max = h.max;
					InitMinMax(h.min,h.max);
					sectbufptr.section = buf_start;
					sectbufptr++; // Prepare next level

					while ( el != last_el )
					{
						*buf_start++ = el.data; // Write element into its new location.
						el = el.next;
					}
				}
				h = h.next; // Next class
			}
		}
		sectbufptr.section = buf_start; // Get last pointer.
		endsects = sectbufptr-1;
		sectbufptr = sectbuf.ptr;
		/*
			RECURSE RIGHT HERE.
		*/
		while ( sectbufptr < endsects )
		{
			// Notice that end point pairs are formed from two first of sections
			// until the last pointer is used.
			buf_start = sectbufptr.section;
			*upper_b = sectbufptr.max;
			*lower_b = sectbufptr.min;
			sectbufptr++;
			buf_end = sectbufptr.section;

			if ( ( cast(ulong)(buf_end) - cast(ulong)(buf_start) ) == T.sizeof ) continue;

			if ( (*upper_b) == (*lower_b) ) continue;
			// two or more elements.
			BucketSort(buf_start, buf_end, (depth + 1));
		}
		*lower_b = lb;
		*upper_b = ub;
		delete sectbuf;
	}
	void GetMinMax(inout T *buf_start, inout T *lower_b, inout T *upper_b, ulong n)
	{
		T *el = buf_start;
		T *end = el + n;
		T dmin, dmax;
		InitMinMax(dmin,dmax);

		while ( el < end )
		{
			T d = *el++;
			if ( d < dmin ) dmin = d;
			if ( d > dmax ) dmax = d;
		}
		*lower_b = dmin;
		*upper_b = dmax;
	}
public:
	void Sort(T *x, ulong n)
	{
		T *buf_start;
		T *buf_end;
		// x is the list of data to be sorted. The list is a list of character
		// arrays.
		if ( !has_bounds )
		{
			GetMinMax(x,lower_b,upper_b,n);
		}
		buf_start = x; buf_end = x + n;
		BucketSort(buf_start, buf_end, 0);
	}
	//*/
}
