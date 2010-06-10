/**
    \brief Genetic alogirthms
    \todo cleanup and document
*/
module siege.ai.genetics;

private
{
	import siege.util.random;
}

// TODO: get the things below into classes
float CROSSOVER_RATE = 0.8;
float MUTATION_RATE = 0.05;

int NUM_ELITE = 10;
int NUM_COPIES_ELITE = 2;

int POP_SIZE = 150;


int GENE_LENGTH = 10;
int CHROMO_LENGTH;

int NUM_TIDDLYWINKS = 50;
int MIN_RAD = 10;
int MAX_RAD = 30;


class SGenome
{
public:
	int[] vecBits;

	double dFitness_;

	//how many bits per gene
  	int iGeneLength;

	this()
	{
		dFitness_ = 0.0;
		iGeneLength = GENE_LENGTH;
		CHROMO_LENGTH = 3 * GENE_LENGTH;
	}
	this(int num_bits, int gene_size)
	{
		dFitness_ = 0.0;
		iGeneLength = gene_size;
		for (int i=0; i<num_bits; ++i)
		{
			vecBits.length = vecBits.length + 1;
			vecBits[ vecBits.length -1 ] = rand(0, 1);
		}
	}
	int[] Decode()
	{
		int[] decoded;
		for (int gene=0; gene < vecBits.length; gene += iGeneLength)
		{
			//get the gene at this position
			int[] ThisGene;

			for (int biti = 0; biti < iGeneLength; biti++)
			{
				ThisGene.length = ThisGene.length + 1;
				ThisGene[ ThisGene.length - 1 ] = vecBits[gene+biti];
			}

			//convert to decimal and add to list of decoded
			decoded.length = decoded.length + 1;
			decoded[ decoded.length - 1 ] = BinToInt(ThisGene);
		}
		return decoded;
	}
	int BinToInt(int[] vec)
	{
		int val = 0;
		int multiplier = 1;

		for (int cBit=vec.length; cBit>0; cBit--)
		{
			val += vec[cBit-1] * multiplier;

			multiplier *= 2;
		}

		return val;
	}
	int opCmp(Object O)
	{
		double a = dFitness_ - (cast(SGenome)O).dFitness_;
		if (a == 0)
			return 0;
		if (a < 0)
			return 1;
		if (a > 0)
			return -1;
	}
	public double dFitness()
	{
		return dFitness_;
	}
	public void dFitness(double a)
	{
		dFitness_ = a;
	}
}

class Cga
{
public:
	//our population of genomes
	SGenome[] m_vecGenomes;

	int m_iPopSize;

	double m_dCrossoverRate;

	double m_dMutationRate;

	//how many bits per chromosome
	int m_iChromoLength;

	//how many bits per gene
	int m_iGeneLength;

	double m_dTotalFitnessScore;

	int m_iGeneration;
	void Mutate(inout int[] vecBits)
	{
		for (int curBit=0; curBit<vecBits.length; curBit++)
		{
			//do we flip this bit?
			if (frand() < m_dMutationRate)
			{
				//flip the bit
				if (vecBits[curBit]==1)
					vecBits[curBit] = 0;
				else
					vecBits[curBit] = 1;
			}
		}//next bit
	}
	void Crossover(int[] mum,int[] dad,inout int[] baby1,inout int[] baby2)
	{
		//just return parents as offspring dependent on the rate
		//or if parents are the same
		if ( (frand() > m_dCrossoverRate) || (mum == dad))
		{
			baby1 = mum;
			baby2 = dad;

			return;
		}
		//determine a crossover point
		int cp = rand(0, m_iChromoLength - 1);
		//swap the bits
		baby1.length = 0;
		baby2.length = 0;
		for (int i=0; i<cp; i++)
		{
			baby1.length = baby1.length + 1;
			baby1[ baby1.length - 1 ] = mum[i];
			baby2.length = baby2.length + 1;
			baby2[ baby2.length - 1 ] = dad[i];
		}

		for (int i=cp; i<mum.length; i++)
		{
			baby1.length = baby1.length + 1;
			baby1[ baby1.length - 1 ] = dad[i];
			baby2.length = baby2.length + 1;
			baby2[ baby2.length - 1 ] = mum[i];
		}
	}
	SGenome RouletteWheelSelection()
	{
		double fSlice = frand() * m_dTotalFitnessScore;
		double cfTotal = 0.0;
		int SelectedGenome = 0;
		for (int i=0; i<m_vecGenomes.length; i++)
		{
			cfTotal = cfTotal + cast(double)(m_vecGenomes[i].dFitness());
			if (cfTotal > fSlice)
			{
				SelectedGenome = i;
				break;
			}
		}
		return m_vecGenomes[SelectedGenome];
	}
	void GrabNBest(int NBest,int NumCopies,SGenome[] vecNewPop)
	{
		m_vecGenomes.sort;
		//now add the required amount of copies of the n most fittest
		//to the supplied vector
		int count = NBest;
		while(count--)
		{
			for (int i=0; i<NumCopies; ++i)
			{
				vecNewPop.length = vecNewPop.length + 1;
				vecNewPop[ vecNewPop.length - 1 ] = m_vecGenomes[NBest-count-1];
			}
		}
	}
	void CreateStartPopulation()
	{
		//clear existing population
		m_vecGenomes.length=0;

		for (int i=0; i<m_iPopSize; i++)
		{
			m_vecGenomes.length = m_vecGenomes.length + 1;
			SGenome s = new SGenome(m_iChromoLength, m_iGeneLength);
			m_vecGenomes[ m_vecGenomes.length - 1 ] = s;
		}

		//reset all variables
		m_iGeneration = 0;
		m_dTotalFitnessScore = 0;
	}
	void CalculateTotalFitness()
	{
		m_dTotalFitnessScore = 0.0;
		int i;
		for (i=0; i<m_vecGenomes.length; i++)
		{
			m_dTotalFitnessScore=m_dTotalFitnessScore + (cast(double)m_vecGenomes[i].dFitness());
		}
	}
	this(double cross_rat,double mut_rat,int pop_size,int num_bits,int gene_len)
	{
		m_dCrossoverRate = cross_rat;
                m_dMutationRate = mut_rat;
                m_iPopSize = pop_size;
                m_iChromoLength = num_bits;
		m_dTotalFitnessScore = 0.0;
		m_iGeneration = 0;
		m_iGeneLength = gene_len;
		CreateStartPopulation();
	}
	SGenome[] GrabGenomes()
	{
		return m_vecGenomes;
	}
	void PutGenomes(inout SGenome[] gen)
	{
		m_vecGenomes = gen.dup;
	}
	void Epoch()
	{
		//Now to create a new population
		int NewBabies = 0;
		CalculateTotalFitness();
		//create some storage for the baby genomes
		SGenome[] vecBabyGenomes;

		//Now to add a little elitism we shall add in some copies of the
		//fittest genomes

		//make sure we add an EVEN number or the roulette wheel
		//sampling will crash
		if (!(NUM_COPIES_ELITE  * NUM_ELITE % 2))
		{
			GrabNBest(NUM_ELITE, NUM_COPIES_ELITE, vecBabyGenomes);
		}
		while (vecBabyGenomes.length < m_vecGenomes.length)
		{
			//select 2 parents
			SGenome mum = RouletteWheelSelection();
			SGenome dad = RouletteWheelSelection();
			//operator - crossover
			SGenome baby1, baby2;
			baby1 = new SGenome(m_iChromoLength, m_iGeneLength);
			baby2 = new SGenome(m_iChromoLength, m_iGeneLength);
			Crossover(mum.vecBits, dad.vecBits, baby1.vecBits, baby2.vecBits);
			//operator - mutate
			Mutate(baby1.vecBits);
			Mutate(baby2.vecBits);
			//add to new population
			vecBabyGenomes.length = vecBabyGenomes.length + 1;
			vecBabyGenomes[ vecBabyGenomes.length - 1 ] = baby1;
			vecBabyGenomes.length = vecBabyGenomes.length + 1;
			vecBabyGenomes[ vecBabyGenomes.length - 1 ] = baby2;

			NewBabies += 2;
		}
		//copy babies back into starter population

		int count;
		m_vecGenomes.length = 0;
		for(count=0; count< vecBabyGenomes.length;count++)
		{
			m_vecGenomes.length = m_vecGenomes.length + 1;
			m_vecGenomes[count] = vecBabyGenomes[count];
		}


		//increment the generation counter
		++m_iGeneration;
	}

	int getGeneration()
	{
		return m_iGeneration;
	}
}


