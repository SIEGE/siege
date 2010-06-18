/**
    \brief Artificial neural networks
    \todo cleanup and document
*/
module siege.ai.neural;

private
{
    import std.string;
    import std.math;
	import siege.util.random;
    import std.stream;
}

float error = 0.025; // 2.5% error
float kapa = 1;
float learningRate = 0.25;
double nepper = 2.718281828;
double activationFunc(double sum)
{
	double y = (1 / (1 + pow(nepper, -1 * kapa * sum)));
	return y;
}
/* f'(u) = f(u) * (1 - f(u)) */
double derivateactivationFunc(double sum)
{
	double y = activationFunc(sum)*(1-activationFunc(sum));
	return y;
}

enum type
{
	input,
	hidden,
	output,
	bias
}

struct trainSet
{
	double[] i;
	double[] o;
}

class Neuron
{
	this(char[] name_, type t_, double s=0)
	{
		name = name_;
		t = t_;
		state = s;
	}
	char[] getName()
	{
		return name;
	}
	void setName(char[] name_)
	{
		name = name_;
	}
	type getType()
	{
		return t;
	}
	void setType(type t_)
	{
		t = t_;
	}
	double getState()
	{
		return state;
	}
	void setState(double s)
	{
		state = s;
	}
private:
	type t;
	char[] name;
	double state;
}


class Connection
{
	this(char[] l,  char[] r)
	{
		leftNeuronId=l;
		rightNeuronId=r;
	}
	void setWeight(double w)
	{
		weight = w;
	}
	double getWeight()
	{
		return weight;
	}
	char[] getleftNeuronId()
	{
		return leftNeuronId;
	}
	char[] getrightNeuronId()
        {
                return rightNeuronId;
        }
private:
	double weight;
	char[] leftNeuronId;
	char[] rightNeuronId;
}

class Network
{
	this(char[] fname)
	{
		load(fname);
	}
	this(int i, int h1, int h2, int o)
	{
		li_.length = 0;
		lh1_.length = 0;
		lh2_.length = 0;
		lo_.length = 0;
		lc_.length = 0;
		int count, count2;
		/*Add Neurons*/
		for (count=0; count<i; count++)
		{
			Neuron n = new Neuron(cast(char[])"i_Neuron" ~ std.string.toString(count),type.input);
			li_.length = li_.length + 1;
			li_[li_.length - 1] = n;
		}
		for (count=0; count<h1; count++)
		{
			Neuron n = new Neuron(cast(char[])"h1_Neuron" ~ std.string.toString(count),type.hidden);
			lh1_.length = lh1_.length + 1;
			lh1_[lh1_.length - 1] = n;
		}
		/*Add bias*/
		Neuron n1 = new Neuron(cast(char[])"bh1_Neuron",type.bias);
		n1.setState(1.0);
		lh1_.length = lh1_.length + 1;
		lh1_[lh1_.length - 1] = n1;
		for (count=0; count<h2; count++)
		{
			Neuron n = new Neuron(cast(char[])"h2_Neuron" ~ std.string.toString(count),type.hidden);
			lh2_.length = lh2_.length + 1;
			lh2_[lh2_.length - 1] = n;
		}
		/*Add bias*/
		Neuron n2 = new Neuron(cast(char[])"bh2_Neuron",type.bias);
		n2.setState(1.0);
		lh2_.length = lh2_.length + 1;
		lh2_[lh2_.length - 1] = n2;
		for (count=0; count<o; count++)
		{
			Neuron n = new Neuron(cast(char[])"o_Neuron" ~ std.string.toString(count),type.output);
			lo_.length = lo_.length + 1;
			lo_[lo_.length - 1] = n;
		}
		/*Add bias*/
		Neuron n3 = new Neuron(cast(char[])"bo_Neuron",type.bias);
		n3.setState(1.0);
		lo_.length = lo_.length + 1;
		lo_[lo_.length - 1] = n3;
		/*Add Connections*/
		for (count=0; count<h1; count++)
		{
			for (count2=0; count2<i; count2++)
			{
				double weight;
				weight = drand(1,0);
				lc_.length = lc_.length + 1;
				Connection c = new Connection(li_[count2].getName(),lh1_[count].getName());
				c.setWeight(weight);
				lc_[lc_.length - 1] = c;
			}
			double weight1;
			weight1 = drand(1,0);
			lc_.length = lc_.length + 1;
			Connection c1 = new Connection("bh1_Neuron",lh1_[count].getName());
			c1.setWeight(weight1);
			lc_[lc_.length - 1] = c1;
		}
		for (count=0; count<h2; count++)
		{
			for (count2=0; count2<h1; count2++)
			{
				double weight;
				weight = drand(1,0);
				lc_.length = lc_.length + 1;
				Connection c = new Connection(lh1_[count2].getName(),lh2_[count].getName());
				c.setWeight(weight);
				lc_[lc_.length - 1] = c;
			}
			double weight1;
			weight1 = drand(1,0);
			lc_.length = lc_.length + 1;
			Connection c1 = new Connection("bh2_Neuron",lh2_[count].getName());
			c1.setWeight(weight1);
			lc_[lc_.length - 1] = c1;
		}
		for (count=0; count<o; count++)
		{
			for (count2=0; count2<h2; count2++)
			{
				double weight;
				weight = drand(1,0);
				lc_.length = lc_.length + 1;
				Connection c = new Connection(lh2_[count2].getName(),lo_[count].getName());
				c.setWeight(weight);
				lc_[lc_.length - 1] = c;
			}
			double weight1;
			weight1 = drand(1,0);
			lc_.length = lc_.length + 1;
			Connection c1 = new Connection("bo_Neuron",lo_[count].getName());
			c1.setWeight(weight1);
			lc_[lc_.length - 1] = c1;
		}
	}
	double getStateByName(char[] name)
	{
		int count;
		for (count=0; count<li_.length; count++)
                {
			if (li_[count].getName() == name)
			{
				return li_[count].getState();
			}
		}
		for (count=0; count<lh1_.length; count++)
                {
			if (lh1_[count].getName() == name)
			{
				return lh1_[count].getState();
			}
		}
		for (count=0; count<lh2_.length; count++)
                {
			if (lh2_[count].getName() == name)
			{
				return lh2_[count].getState();
			}
		}
		for (count=0; count<lo_.length; count++)
                {
			if (lo_[count].getName() == name)
			{
				return lo_[count].getState();
			}
		}
	}
	Neuron getNeuronByName(char[] name)
	{
		int count;
		for (count=0; count<li_.length; count++)
                {
			if (li_[count].getName() == name)
			{
				return li_[count];
			}
		}
		for (count=0; count<lh1_.length; count++)
                {
			if (lh1_[count].getName() == name)
			{
				return lh1_[count];
			}
		}
		for (count=0; count<lh2_.length; count++)
                {
			if (lh2_[count].getName() == name)
			{
				return lh2_[count];
			}
		}
		for (count=0; count<lo_.length; count++)
                {
			if (lo_[count].getName() == name)
			{
				return lo_[count];
			}
		}
	}
	double sumInput(Neuron n)
	{
		double sum = 0;
		int count;
		for (count=0; count<lc_.length; count++)
		{
			if (lc_[count].getrightNeuronId() == n.getName())
			{
				sum = sum + getStateByName(lc_[count].getleftNeuronId()) * lc_[count].getWeight();
			}
		}
		return sum;
	}

	double []output(double[] i)
	{
		int count, count2;
		if (i.length != li_.length)
			throw new Exception("Input length and input Neuron length does not match!");
		for (count=0; count<li_.length; count++)
		{
			li_[count].setState(i[count]);
		}
		for (count=0; count<lh1_.length; count++)
		{
			if (lh1_[count].getType() != type.bias)
				lh1_[count].setState(activationFunc(sumInput(lh1_[count])));
		}
		for (count=0; count<lh2_.length; count++)
		{
			if (lh2_[count].getType() != type.bias)
				lh2_[count].setState(activationFunc(sumInput(lh2_[count])));
		}
		for (count=0; count<lo_.length; count++)
		{
			if (lo_[count].getType() != type.bias)
				lo_[count].setState(activationFunc(sumInput(lo_[count])));
		}
		double []o_;
		o_.length = lo_.length - 1;
		for (count=0; count<lo_.length; count++)
		{
			if (lo_[count].getType() != type.bias)
				o_[count] = lo_[count].getState();
		}
		return o_;
	}
	void insertTrainSet(double[] i, double[] o)
	{
		int count;
		for (count=0; count<i.length; count++)
		{
			if (i[count] > 1 || i[count] < 0)
				throw new Exception(" 0<= inputs <=1 ");
		}
		ts.length = ts.length + 1;
		ts[ts.length - 1].i = i;
		ts[ts.length - 1].o = o;
	}
	private double errorOutput(double[] o, double[] d)
	{
		int count;
		double sum = 0;
		for (count=0; count<o.length; count++)
		{
			sum = sum + (d[count] - o[count]);
		}
		return sum;
	}
	private double errorNet(double[] e)
	{
		int count;
		double sum = 0;
		for (count=0; count<e.length; count++)
		{
			sum = sum + fabs(e[count]);
		}
		return (sum);
	}
	private double backpropagation(double[] o, double[] d)
	{
		int count,count2;
		double e_t = errorOutput(o,d);
		double e;
		for (count=0; count<lo_.length; count++)
		{
			for (count2=0; count2<lc_.length; count2++)
			{
				if (lc_[count2].getrightNeuronId() == lo_[count].getName())
				{
					double cweight = 0;
					cweight = cweight + (learningRate * e_t * getStateByName(lc_[count2].getleftNeuronId()) * getStateByName(lc_[count2].getrightNeuronId()) * (1 - getStateByName(lc_[count2].getrightNeuronId())));
					lc_[count2].setWeight(lc_[count2].getWeight() + cweight);
				}
			}
		}
		for (count=0; count<lh2_.length; count++)
		{
			for (count2=0; count2<lc_.length; count2++)
			{
				if (lc_[count2].getrightNeuronId() == lh2_[count].getName())
				{
					double cweight = 0;
					cweight = cweight + (learningRate * e_t * getStateByName(lc_[count2].getleftNeuronId()) * getStateByName(lc_[count2].getrightNeuronId()) * (1 - getStateByName(lc_[count2].getrightNeuronId())));
					lc_[count2].setWeight(lc_[count2].getWeight() + cweight);
				}
			}
		}
		for (count=0; count<lh1_.length; count++)
		{
			for (count2=0; count2<lc_.length; count2++)
			{
				if (lc_[count2].getrightNeuronId() == lh1_[count].getName())
				{
					double cweight = 0;
					cweight = cweight + (learningRate * e_t * getStateByName(lc_[count2].getleftNeuronId()) * getStateByName(lc_[count2].getrightNeuronId()) * (1 - getStateByName(lc_[count2].getrightNeuronId())));
					lc_[count2].setWeight(lc_[count2].getWeight() + cweight);
				}
			}
		}
		return e_t;
	}
	void train()
	{
		int count;
		double e = 1;
		while(e>error)
		{
			double[] e1;
			for (count=0; count<ts.length;count++)
			{
				double[] dout = output(ts[count].i);
				e1.length = e1.length + 1;
				e1[e1.length - 1] = backpropagation(dout, ts[count].o);
			}
			e = errorNet(e1);
		}
	}
	void save(char[] fname)
	{

		File f = new File(fname,FileMode.Out);
		f.writefln("---------------------------------------");
		f.writefln("%d,%d,%d,%d,%d,%d",li_.length,lh1_.length,lh2_.length,lo_.length,lc_.length,ts.length);
		f.writefln("---------------------------------------");
		int count, count2;
		for (count=0; count<ts.length; count++)
		{
			for (count2=0; count2<ts[count].i.length; count2++)
			{
				if (count2 == ts[count].i.length - 1)
					f.writef("%f",ts[count].i[count2]);
				else
					f.writef("%f,",ts[count].i[count2]);
			}
			f.writef("#");
			for (count2=0; count2<ts[count].o.length; count2++)
			{
				if (count2 == ts[count].o.length - 1)
					f.writef("%f",ts[count].o[count2]);
				else
					f.writef("%f,",ts[count].o[count2]);
			}
			f.writefln("");
		}
		for (count=0; count<li_.length; count++)
		{
			f.writefln("%d,%s,%f",li_[count].getType(),li_[count].getName(),li_[count].getState());
		}
                for (count=0; count<lh1_.length; count++)
		{
			f.writefln("%d,%s,%f",lh1_[count].getType(),lh1_[count].getName(),lh1_[count].getState());
		}
		for (count=0; count<lh2_.length; count++)
		{
			f.writefln("%d,%s,%f",lh2_[count].getType(),lh2_[count].getName(),lh2_[count].getState());
		}
		for (count=0; count<lo_.length; count++)
		{
			f.writefln("%d,%s,%f",lo_[count].getType(),lo_[count].getName(),lo_[count].getState());
		}
		for (count=0; count<lc_.length; count++)
		{
			f.writefln("%f,%s,%s",lc_[count].getWeight(),lc_[count].getleftNeuronId(),lc_[count].getrightNeuronId());
		}
		f.close();
	}
	private void load(char[] fname)
	{
		File f = new File(fname,FileMode.In);
		char[] buf = f.readLine();
		buf = f.readLine();
		char[][] tmp;
		tmp = split(buf,",");
		int ninput = atoi(tmp[0]);
		int nhidden1 = atoi(tmp[1]);
		int nhidden2 = atoi(tmp[2]);
		int noutput = atoi(tmp[3]);
		int nConnections = atoi(tmp[4]);
		int nts = atoi(tmp[5]);
		li_.length = 0;
		lh1_.length = 0;
		lh2_.length = 0;
		lo_.length = 0;
		lc_.length = 0;
		int count, count2;
		buf = f.readLine();
		for (count=0; count<nts; count++)
		{
			ts.length = ts.length + 1;
			buf = f.readLine();
			tmp = split(buf,"#");
			char[][] tmp2;
			char[][] tmp3;
			tmp2 =  split(tmp[0],",");
			tmp3 =  split(tmp[1],",");
			ts[count].i.length = tmp2.length;
			ts[count].o.length = tmp3.length;
			for (count2=0; count2<tmp2.length; count2++)
			{
				ts[count].i[count2] = atof(tmp2[count2]);
			}
			for (count2=0; count2<tmp3.length; count2++)
			{
				ts[count].o[count2] = atof(tmp3[count2]);
			}
		}
		//Add Neurons
		for (count=0; count<ninput; count++)
		{
			buf = f.readLine();
			type t;
			int ti;
			char[] i;
			double state;
			tmp = split(buf,",");
			ti = atoi(tmp[0]);
			i = tmp[1];
			state = atof(tmp[2]);
			if (ti == 0)
			{
				t = type.input;
			}
			if (ti == 1)
			{
				t = type.hidden;
			}
			if (ti == 2)
			{
				t = type.output;
			}
			Neuron n = new Neuron(i,t,state);
			li_.length = li_.length + 1;
			li_[li_.length - 1] = n;
		}

		for (count=0; count<nhidden1; count++)
		{
			buf = f.readLine();
			type t;
			int ti;
			char[] i;
			double state;
			tmp = split(buf,",");
			ti = atoi(tmp[0]);
			i = tmp[1];
			state = atof(tmp[2]);
			if (ti == 0)
			{
				t = type.input;
			}
			if (ti == 1)
			{
				t = type.hidden;
			}
			if (ti == 2)
			{
				t = type.output;
			}
			if (ti == 3)
			{
				t = type.bias;
			}
			Neuron n = new Neuron(i,t,state);
			lh1_.length = lh1_.length + 1;
			lh1_[lh1_.length - 1] = n;
		}

		for (count=0; count<nhidden2; count++)
		{
			buf = f.readLine();
			type t;
			int ti;
			char[] i;
			double state;
			tmp = split(buf,",");
			ti = atoi(tmp[0]);
			i = tmp[1];
			state = atof(tmp[2]);
			if (ti == 0)
			{
				t = type.input;
			}
			if (ti == 1)
			{
				t = type.hidden;
			}
			if (ti == 2)
			{
				t = type.output;
			}
			if (ti == 3)
			{
				t = type.bias;
			}
			Neuron n = new Neuron(i,t,state);
			lh2_.length = lh2_.length + 1;
			lh2_[lh2_.length - 1] = n;
		}

		for (count=0; count<noutput; count++)
		{
			buf = f.readLine();
			type t;
			int ti;
			char[] i;
			double state;
			tmp = split(buf,",");
			ti = atoi(tmp[0]);
			i = tmp[1];
			state = atof(tmp[2]);
			if (ti == 0)
			{
				t = type.input;
			}
			if (ti == 1)
			{
				t = type.hidden;
			}
			if (ti == 2)
			{
				t = type.output;
			}
			if (ti == 3)
			{
				t = type.bias;
			}
			Neuron n = new Neuron(i,t,state);
			lo_.length = lo_.length + 1;
			lo_[lo_.length - 1] = n;
		}
		//Add Connections
		for (count=0; count<nConnections; count++)
		{
			buf = f.readLine();
			tmp = split(buf,",");
			double weight;
			char[] l,r;
			weight = atof(tmp[0]);
			l = tmp[1];
			r = tmp[2];
			lc_.length = lc_.length + 1;
			Connection c = new Connection(l,r);
			c.setWeight(weight);
			lc_[lc_.length - 1] = c;
		}
		f.close();
	}
private:
	Neuron[] li_;
	Neuron[] lh1_;
	Neuron[] lh2_;
	Neuron[] lo_;
	Connection[] lc_;
	trainSet[] ts;
}
