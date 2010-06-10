/**
    \brief Fuzzy logic
    \todo cleanup and document
*/
module siege.ai.fuzzy;

class Fuzzy
{
	this()
	{
		num = 0;
		defuzzed = false;
		evaluated = false;
	}
	this(float f)
	{
		num = f;
		defuzzed = false;
		evaluated = false;
	}
	this(float f, char[] n)
	{
		num=f;
		defuzzed=false;
		evaluated=false;
		name = n;
	}
	this(double f, char[] n)
	{
		num=cast(float)f;
		defuzzed=false;
		evaluated=false;
		name = n;
	}
	this(char[] n)
	{
		num=0;
		defuzzed=false;
		evaluated=false;
		name = cast(char[])n;
	}
	void setName(char[] n)
	{
		name = n;
	}
	void setNumber(double n)
	{
        	num=cast(float)n;
	}
	char[] getName()
	{
		return name;
	}
	double getNumber()
	{
		return cast(double)num;
	}
	bool contained(double f)
	{
		if (num < f)
			return true;
		else
			return false;
	}
	char[] show()
	{
			assert(getName()=="");
			return name;
	}
	void setDefuzzed()
	{
		defuzzed = true;
	}
	bool getDefuzzed()
	{
		return defuzzed;
	}
	void setEvaluated()
	{
		evaluated = true;
	}
	bool getEvaluated()
	{
		return evaluated;
	}
private:
	double	num;
	char[] name;
	bool defuzzed;
	bool evaluated;
}

class FuzzySet
{
	~this()
	{
		//delete mFuzzy;
		clear();
	}
	void clear()
	{
		mFuzzy.length=0;
	}
	void add(Fuzzy f)
	{
		assert(f.getNumber()>=0);
		assert(f.getNumber()<=1);
                if (mFuzzy.length == 0)
                {
                        mFuzzy.length =  mFuzzy.length + 1;
			mFuzzy[0]=f;
			return;
                }
		else
		{
			for(int i=0; i<mFuzzy.length; i++)
			{
				if (mFuzzy[i].contained(f.getNumber()))
				{
                                	mFuzzy.length = mFuzzy.length + 1;
					mFuzzy[mFuzzy.length-1] = f;
					break;
				}
			}
		}
	}
	void eval(Fuzzy f)
	{
		for(int i=0; i<mFuzzy.length; i++)
		{
			if (f.contained(mFuzzy[i].getNumber()))
			{
				f.setName(mFuzzy[i].getName());
				f.setNumber(mFuzzy[i].getNumber());
				f.setEvaluated();
				return;
			}
		}
	}
	void defuzzy(Fuzzy f)
	{
		if (f.getName()=="")
			eval(f);
		for(int i=0; i<mFuzzy.length; i++)
		{
			if ((mFuzzy[i].getName()==f.getName()) || (mFuzzy[i].getNumber()==f.getNumber()))
			{
				f.setName(mFuzzy[i].getName());
				f.setNumber(mFuzzy[i].getNumber());
				f.setDefuzzed();
				return;
			}
		}
	}
	Fuzzy getMember(int p)
	{
		return mFuzzy[p];
	}
	Fuzzy getMember(char[] name)
	{
		for(int i=0; i<mFuzzy.length; i++)
		{
			if (mFuzzy[i].getName()==name)
			{
				return mFuzzy[i];
			}
		}
	}
private:
	Fuzzy[] mFuzzy;
}


class FuzzyEngine: FuzzySet
{
	this()
	{
		hasList = false;
	}
	Fuzzy not(Fuzzy f)
	{
		defuzzy(f);
		f.setNumber(1-f.getNumber());
		eval(f);
		return f;
	}
	Fuzzy or(Fuzzy a, Fuzzy b)
	{
		defuzzy(a);
		defuzzy(b);
		if (a.getNumber() > b.getNumber())
		{
		    return a;
		}
        	return b;
	}
	Fuzzy and(Fuzzy a, Fuzzy b)
	{
		defuzzy(a);
		defuzzy(b);
		if (a.getNumber() < b.getNumber())
		{
		    return a;
		}
       		return b;
	}
	void addList(char[][] m, int n)
	{
		hasList = true;
		int i;
		assert(n!=0);
		double step = cast(double)(1/(cast(double)n));
		double stepi = step;
		for (i=0;i<n;i++)
		{
			char[] s;
			s = m[i];
			Fuzzy f = new Fuzzy(stepi,s);
			stepi = cast(double)(step+stepi);
			add(f);
		}
	}
	void defuzzy(Fuzzy f)
	{
		assert(hasList);
		if (f.getName()=="")
			eval(f);
		for(int i=0; i<mFuzzy.length; i++)
		{
			if ((mFuzzy[i].getName()==f.getName()) || (mFuzzy[i].getNumber()==f.getNumber()))
			{
				f.setName(mFuzzy[i].getName());
				f.setNumber(mFuzzy[i].getNumber());
				f.setDefuzzed();
				return;
			}
		}
	}
	void eval(Fuzzy f)
	{
		assert(hasList);
		for(int i=0; i<mFuzzy.length; i++)
		{
			if (f.contained(mFuzzy[i].getNumber()))
			{
				f.setName(mFuzzy[i].getName());
				f.setNumber(mFuzzy[i].getNumber());
				f.setEvaluated();
				return;
			}
		}
	}
	bool isE(Fuzzy f, char[] c)
	{
		assert(hasList);
		if (!f.getDefuzzed())
		{
			defuzzy(f);
		}
		if (!f.getEvaluated())
		{
			eval(f);
		}
		if (f.getName()==c)
			return true;
        	return false;
	}
	bool isE(Fuzzy f, double c)
	{
		assert(hasList);
		if (!f.getDefuzzed())
		{
			defuzzy(f);
		}
		if (!f.getEvaluated())
		{
			eval(f);
		}
		if (f.getNumber()==c)
			return true;
        	return false;
	}
private:
	bool hasList;
}
