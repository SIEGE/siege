module siege.util.interp;

private
{
    import std.math;
    import siege.util.sort;
    import siege.util.vector;
    import std.stdio;
}

float nearest(float pos, float[] points ...)
{
    assert(points.length > 0);

    if(pos < 0)
        return points[0];
    if(pos > points.length)
        return points[$-1];

    uint nearest = cast(uint)round(pos);
    return points[nearest];
}
float linear(float pos, float[] points)
{
    assert(points.length > 0);

    if(pos < 0)
    {
        return points[0];
    }
    if(pos > points.length)
    {
        return points[$-1];
    }

    uint min = cast(uint)floor(pos);
    uint max = cast(uint)ceil(pos);
    if(min == max)
        return points[min];
    pos = pos % 1;

    return points[min] * (1 - pos) + points[max] * pos;
}
/*
unittest
{
	float i=2.9;
	float[] a;
	a.length = 6;
	a[0..length] = [cast(float)1,cast(float)2,cast(float)9,cast(float)28,cast(float)65,cast(float)126];
	float ret = cubic(i, a);
	writefln("-----------------------");
	writefln("interpolation unittest:");
	writefln("-----------------------");
	writefln(ret);
	writefln("-----------------------");
	writefln("");
}
*/

/**
1D
**/

float cubic(float pos, float[] points)
{
    assert(points.length > 0);
    Vector[] p_vector;
    p_vector.length = points.length;
    int m_partition = 0;
    int w = 0;
    foreach(float f; points)
    {
	    p_vector[m_partition].x = m_partition;
	    p_vector[m_partition].y = points[m_partition];
	    if (pos>=m_partition && pos<=m_partition+1)
	    {
		    w = m_partition;
	    }
	    m_partition++;
    }
    /*P1--P2--P3--P4*/
    assert(w>=1 && w<p_vector.length-2);

    float a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t;
    a = p_vector[w].x * p_vector[w].x * p_vector[w].x;
    b = p_vector[w].x * p_vector[w].x;
    c = p_vector[w].x;
    d = 1;
    e = p_vector[w].y;
    f = p_vector[w+1].x * p_vector[w+1].x * p_vector[w+1].x;
    g = p_vector[w+1].x * p_vector[w+1].x;
    h = p_vector[w+1].x;
    i = 1;
    j = p_vector[w+1].y;
    k = p_vector[w+2].x * p_vector[w+2].x * p_vector[w+2].x;
    l = p_vector[w+2].x * p_vector[w+2].x;
    m = p_vector[w+2].x;
    n = 1;
    o = p_vector[w+2].y;
    p = p_vector[w+3].x * p_vector[w+3].x * p_vector[w+3].x;
    q = p_vector[w+3].x * p_vector[w+3].x;
    r = p_vector[w+3].x;
    s = 1;
    t = p_vector[w+3].y;

    float delta = (a*g*m*s)+(a*h*n*q)+(a*i*l*r)-(a*i*m*q)-(a*g*n*r)-(a*h*l*s)-(f*b*m*s)-(f*c*n*q)-(f*d*l*r)+(f*d*m*q)+(f*b*n*r)+(f*c*l*s)+(k*b*h*s)+(k*c*i*q)+(k*d*g*r)-(k*d*h*q)-(k*b*i*r)-(k*c*g*s)-(p*b*h*n)-(p*c*i*l)-(p*d*g*m)+(p*d*h*l)+(p*b*i*m)+(p*c*g*n);

    float wnum = (e*g*m*s)+(e*h*n*q)+(e*i*l*r)-(e*i*m*q)-(e*g*n*r)-(e*h*l*s)-(j*b*m*s)-(j*c*n*q)-(j*d*l*r)+(j*d*m*q)+(j*b*n*r)+(j*c*l*s)+(o*b*h*s)+(o*c*i*q)+(o*d*g*r)-(o*d*h*q)-(o*b*i*r)-(o*c*g*s)-(t*b*h*n)-(t*c*i*l)-(t*d*g*m)+(t*d*h*l)+(t*b*i*m)+(t*c*g*n);

    float wans = (wnum/delta);

    float xnum = (a*j*m*s)+(a*h*n*t)+(a*i*o*r)-(a*i*m*t)-(a*j*n*r)-(a*h*o*s)-(f*e*m*s)-(f*c*n*t)-(f*d*o*r)+(f*d*m*t)+(f*e*n*r)+(f*c*o*s)+(k*e*h*s)+(k*c*i*t)+(k*d*j*r)-(k*d*h*t)-(k*e*i*r)-(k*c*j*s)-(p*e*h*n)-(p*c*i*o)-(p*d*j*m)+(p*d*h*o)+(p*e*i*m)+(p*c*j*n);

    float xans = (xnum/delta);

    float ynum = (a*g*o*s)+(a*j*n*q)+(a*i*l*t)-(a*i*o*q)-(a*g*n*t)-(a*j*l*s)-(f*b*o*s)-(f*e*n*q)-(f*d*l*t)+(f*d*o*q)+(f*b*n*t)+(f*e*l*s)+(k*b*j*s)+(k*e*i*q)+(k*d*g*t)-(k*d*j*q)-(k*b*i*t)-(k*e*g*s)-(p*b*j*n)-(p*e*i*l)-(p*d*g*o)+(p*d*j*l)+(p*b*i*o)+(p*e*g*n);

    float yans = (ynum/delta);

    float znum = (a*g*m*t)+(a*h*o*q)+(a*j*l*r)-(a*j*m*q)-(a*g*o*r)-(a*h*l*t)-(f*b*m*t)-(f*c*o*q)-(f*e*l*r)+(f*e*m*q)+(f*b*o*r)+(f*c*l*t)+(k*b*h*t)+(k*c*j*q)+(k*e*g*r)-(k*e*h*q)-(k*b*j*r)-(k*c*g*t)-(p*b*h*o)-(p*c*j*l)-(p*e*g*m)+(p*e*h*l)+(p*b*j*m)+(p*c*g*o);

    float zans = (znum/delta);


    /* Y = wans*X^3 + xans*X^2 + yans*X + zans */

    return (cast(float)(wans*pos*pos*pos + xans*pos*pos + yans*pos + zans));
}
//Lagrange polynomial
float polynomial(float pos, float[] points)
{
    assert(points.length > 1);
    Vector[] p;
    p.length = points.length;
    int m = 0;
    int w = 0;
    foreach(float f; points)
    {
	    p[m].x = m;
	    p[m].y = points[m];
	    if (pos>=m && pos<=m+1)
	    {
		    w = m;
	    }
	    m++;
    }
    float retVal = 0;
    for (int i = 0; i < points.length; ++i)
    {
      float weight = 1;
      for (int j = 0; j < points.length; ++j)
      {
         //the i-th term has to be skipped
         if (j != i)
         {
            weight *= (pos - p[j].x) / (p[i].x - p[j].x);
         }
      }
      retVal += weight * p[i].y;
    }
    return (cast(float)retVal);
}
float spline(float pos, float[] points)
{
    assert(points.length > 2);
    assert(pos>=0 && pos<=(points.length-1));
    Vector[] p;
    p.length = points.length;
    int i = 0;
    int w = 0;
    foreach(float f; points)
    {
	    p[i].x = cast(float)i;
	    p[i].y = f;
	    if (pos>=i && pos<=i+1)
	    {
		    w = i;
	    }
	    i++;
    }
    return (cast(float)(p[w].y + (p[w+1].y - p[w].y) / (w+1-w) * ( pos - w)));
}

/**
2D
**/

private
{
	uint []indexesX(Vector[] array,float x)
	{
		uint i = 0;
		uint j = 0;
		uint []tmp;
		foreach(Vector a; array)
		{
			if (a.x == x)
			{
				tmp.length = tmp.length + 1;
				tmp[j] = i;
				j++;
			}
			i++;
		}
		return tmp;
	}
	bool existsX(Vector[] array,float x)
	{
		foreach(Vector a; array)
		{
			if (a.x == x)
				return true;
		}
		return false;
	}
	Vector[] sortX(Vector[] array)
	{
		float []x;
		x.length = array.length;
		uint i =0;
		foreach(Vector a; array)
		{
			if (!existsX(array,a.x))
			{
				x[i] = a.x;
				i++;
			}
		}
		BSort!(float) sortlist = new BSort!(float)(7,x.length);

		sortlist.Sort(x.ptr,x.length);

		Vector[] tmp;
		tmp.length = array.length;
		uint u = 0;
		foreach(float a; x)
		{
			uint []tmp2 = indexesX(array,a);
			for (uint m = 0; m<tmp2.length; m++)
			{
				tmp.length = tmp.length + 1;
				tmp[u] = array[tmp2[m]];
				u++;
			}
		}
		//delete sortlist;
		return tmp;
	}
	uint []indexesY(Vector[] array,float y)
	{
		uint i = 0;
		uint j = 0;
		uint []tmp;
		foreach(Vector a; array)
		{
			if (a.y == y)
			{
				tmp.length = tmp.length + 1;
				tmp[j] = i;
				j++;
			}
			i++;
		}
		return tmp;
	}
	bool existsY(Vector[] array,float y)
	{
		foreach(Vector a; array)
		{
			if (a.y == y)
				return true;
		}
		return false;
	}
	Vector[] sortY(Vector[] array)
	{
		float []y;
		y.length = array.length;
		uint i =0;
		foreach(Vector a; array)
		{
			if (!existsY(array,a.y))
			{
				y[i] = a.y;
				i++;
			}
		}
		BSort!(float) sortlist = new BSort!(float)(7,y.length);

		sortlist.Sort(y.ptr,y.length);

		Vector[] tmp;
		tmp.length = array.length;
		uint u = 0;
		foreach(float a; y)
		{
			uint []tmp2 = indexesY(array,a);
			for (uint m = 0; m<tmp2.length; m++)
			{
				tmp.length = tmp.length + 1;
				tmp[u] = array[tmp2[m]];
				u++;
			}
		}
		//delete sortlist;
		return tmp;
	}
	uint []indexesZ(Vector[] array,float z)
	{
		uint i = 0;
		uint j = 0;
		uint []tmp;
		foreach(Vector a; array)
		{
			if (a.z == z)
			{
				tmp.length = tmp.length + 1;
				tmp[j] = i;
				j++;
			}
			i++;
		}
		return tmp;
	}
	bool existsZ(Vector[] array,float z)
	{
		foreach(Vector a; array)
		{
			if (a.z == z)
				return true;
		}
		return false;
	}
	Vector[] sortZ(Vector[] array)
	{
		float []z;
		z.length = array.length;
		uint i =0;
		foreach(Vector a; array)
		{
			if (!existsZ(array,a.z))
			{
				z[i] = a.z;
				i++;
			}
		}
		BSort!(float) sortlist = new BSort!(float)(7,z.length);

		sortlist.Sort(z.ptr,z.length);

		Vector[] tmp;
		tmp.length = array.length;
		uint u = 0;
		foreach(float a; z)
		{
			uint []tmp2 = indexesZ(array,a);
			for (uint m = 0; m<tmp2.length; m++)
			{
				tmp.length = tmp.length + 1;
				tmp[u] = array[tmp2[m]];
				u++;
			}
		}
		//delete sortlist;
		return tmp;
	}
}

float cubic(float pos, Vector[] points)
{
	assert(points.length > 0);
	Vector[] p_vector;
	p_vector.length = points.length;
	p_vector = sortX(points);
	int w = 0;
	for(uint k=0; k < p_vector.length - 1; k++)
	{
		if (pos>=p_vector[k].x && pos<=p_vector[k+1].x)
		{
		    w = k;
		    break;
		}
	}
	assert(w>=1 && w<p_vector.length-2);

	float a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t;
	a = p_vector[w].x * p_vector[w].x * p_vector[w].x;
	b = p_vector[w].x * p_vector[w].x;
	c = p_vector[w].x;
	d = 1;
	e = p_vector[w].y;
	f = p_vector[w+1].x * p_vector[w+1].x * p_vector[w+1].x;
	g = p_vector[w+1].x * p_vector[w+1].x;
	h = p_vector[w+1].x;
	i = 1;
	j = p_vector[w+1].y;
	k = p_vector[w+2].x * p_vector[w+2].x * p_vector[w+2].x;
	l = p_vector[w+2].x * p_vector[w+2].x;
	m = p_vector[w+2].x;
	n = 1;
	o = p_vector[w+2].y;
	p = p_vector[w+3].x * p_vector[w+3].x * p_vector[w+3].x;
	q = p_vector[w+3].x * p_vector[w+3].x;
	r = p_vector[w+3].x;
	s = 1;
	t = p_vector[w+3].y;

	float delta = (a*g*m*s)+(a*h*n*q)+(a*i*l*r)-(a*i*m*q)-(a*g*n*r)-(a*h*l*s)-(f*b*m*s)-(f*c*n*q)-(f*d*l*r)+(f*d*m*q)+(f*b*n*r)+(f*c*l*s)+(k*b*h*s)+(k*c*i*q)+(k*d*g*r)-(k*d*h*q)-(k*b*i*r)-(k*c*g*s)-(p*b*h*n)-(p*c*i*l)-(p*d*g*m)+(p*d*h*l)+(p*b*i*m)+(p*c*g*n);

	float wnum = (e*g*m*s)+(e*h*n*q)+(e*i*l*r)-(e*i*m*q)-(e*g*n*r)-(e*h*l*s)-(j*b*m*s)-(j*c*n*q)-(j*d*l*r)+(j*d*m*q)+(j*b*n*r)+(j*c*l*s)+(o*b*h*s)+(o*c*i*q)+(o*d*g*r)-(o*d*h*q)-(o*b*i*r)-(o*c*g*s)-(t*b*h*n)-(t*c*i*l)-(t*d*g*m)+(t*d*h*l)+(t*b*i*m)+(t*c*g*n);

	float wans = (wnum/delta);

	float xnum = (a*j*m*s)+(a*h*n*t)+(a*i*o*r)-(a*i*m*t)-(a*j*n*r)-(a*h*o*s)-(f*e*m*s)-(f*c*n*t)-(f*d*o*r)+(f*d*m*t)+(f*e*n*r)+(f*c*o*s)+(k*e*h*s)+(k*c*i*t)+(k*d*j*r)-(k*d*h*t)-(k*e*i*r)-(k*c*j*s)-(p*e*h*n)-(p*c*i*o)-(p*d*j*m)+(p*d*h*o)+(p*e*i*m)+(p*c*j*n);

	float xans = (xnum/delta);

	float ynum = (a*g*o*s)+(a*j*n*q)+(a*i*l*t)-(a*i*o*q)-(a*g*n*t)-(a*j*l*s)-(f*b*o*s)-(f*e*n*q)-(f*d*l*t)+(f*d*o*q)+(f*b*n*t)+(f*e*l*s)+(k*b*j*s)+(k*e*i*q)+(k*d*g*t)-(k*d*j*q)-(k*b*i*t)-(k*e*g*s)-(p*b*j*n)-(p*e*i*l)-(p*d*g*o)+(p*d*j*l)+(p*b*i*o)+(p*e*g*n);

	float yans = (ynum/delta);

	float znum = (a*g*m*t)+(a*h*o*q)+(a*j*l*r)-(a*j*m*q)-(a*g*o*r)-(a*h*l*t)-(f*b*m*t)-(f*c*o*q)-(f*e*l*r)+(f*e*m*q)+(f*b*o*r)+(f*c*l*t)+(k*b*h*t)+(k*c*j*q)+(k*e*g*r)-(k*e*h*q)-(k*b*j*r)-(k*c*g*t)-(p*b*h*o)-(p*c*j*l)-(p*e*g*m)+(p*e*h*l)+(p*b*j*m)+(p*c*g*o);

	float zans = (znum/delta);

	/* Y = wans*X^3 + xans*X^2 + yans*X + zans */

	return (cast(float)(wans*pos*pos*pos + xans*pos*pos + yans*pos + zans));
}


float spline(float pos, Vector[] points)
{
	assert(points.length > 2);

	Vector[] p_vector;
	p_vector.length = points.length;
	p_vector = sortX(points);
	int w = 0;
	for(uint k=0; k < p_vector.length - 1; k++)
	{
		if (pos>=p_vector[k].x && pos<=p_vector[k+1].x)
		{
		    w = k;
		    break;
		}
	}
	return (cast(float)(p_vector[w].y + (p_vector[w+1].y - p_vector[w].y) / (p_vector[w+1].x-p_vector[w].x) * ( pos - p_vector[w].x)));
}

//Lagrange polynomial
float polynomial(float pos, Vector[] points)
{
	assert(points.length > 1);

	Vector[] p_vector;
	p_vector.length = points.length;
	p_vector = sortX(points);
	float retVal = 0;
	for (int i = 0; i < p_vector.length; ++i)
	{
		float weight = 1;
		for (int j = 0; j < p_vector.length; ++j)
		{
		 //the i-th term has to be skipped
		 if (j != i)
		 {
		    weight *= (pos - p_vector[j].x) / (p_vector[i].x - p_vector[j].x);
		 }
		}
		retVal += weight * p_vector[i].y;
	}
	return (cast(float)retVal);
}
