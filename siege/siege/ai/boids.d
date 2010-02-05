module siege.ai.boids;

private
{
	import siege.util.vector;
	import std.random;
	import siege.util.random;
	import std.date;
	import std.math;

}



float distance(Vector p1, Vector p2)
{
	double val = pow(cast(real)(p1.x - p2.x), 2) + pow(cast(real)(p1.y - p2.y), 2);
        return cast(float)sqrt(val);
}
class Boid
{
	this(bool zombie_, uint boundary_, uint minp, uint maxp )
	{
		position_ = Vector.rand(cast(float)minp,cast(float)maxp);
        	boundary = cast(float)boundary_;
        	zombie = zombie_;
		rand_seed(cast(uint)getUTCtime(),0);
                rnd = siege.util.random.rand(uint.max);
	}
	void position(Vector v)
	{
		position_ = v;
	}
	Vector position()
	{
		return position_;
	}
	void move(Boid[] list)
	{
		if (!zombie) flock(list);
                else hunt(list);
                checkBounds();
                checkSpeed();
                position_.x += dX;
                position_.y += dY;
	}
	void flock(Boid[] list)
	{
		foreach (Boid b; list)
                {
                        float distance_ = distance(position_, b.position_);
			if (b != this && !zombie)
			{
				if (distance_ < space)
                		{
                    			// Create space.
					dX += position_.x - b.position_.x;
                    			dY += position_.y - b.position_.y;
                		}
                		else
				if (distance_ < sight)
                		{
                    			// Flock together.
                    			dX += (b.position_.x - position_.x) * 0.05f;
                    			dY += (b.position_.y - position_.y) * 0.05f;
                		}
                		if (distance_ < sight)
                		{
                    			// Align movement.
                    			dX += b.dX * 0.5f;
                    			dY += b.dY * 0.5f;
                		}
			}
			if (b.zombie && distance_ < sight)
            		{
                		// Avoid zombies.
                		dX += position_.x - b.position_.x;
                		dY += position_.y - b.position_.y;
            		}
	        }
	}
	void hunt(Boid[] list)
	{
		float range = float.max;
        	Boid prey = null;
        	foreach (Boid b; list)
        	{
			if (!b.zombie)
            		{
                		float distance_ = distance(position_, b.position_);
                		if (distance_ < sight && distance_ < range)
                		{
                    			range = distance_;
                    			prey = b;
                		}

            		}
		}
		if (prey !is null)
        	{
            		// Move towards closest prey.
            		dX += prey.position_.x - position_.x;
            		dY += prey.position_.y - position_.y;
        	}
	}
	void checkBounds()
	{
		float val = boundary - border;
        	if (position_.x < border) dX += border - position_.x;
        	if (position_.y < border) dY += border - position_.y;
        	if (position_.x > val) dX += val - position_.x;
        	if (position_.y > val) dY += val - position_.y;
	}
	void checkSpeed()
	{
		float s;
        	if (!zombie) s = speed;
        	else
		s = speed / 4f;
        	float val = distance(Vector(0f, 0f, 0f), Vector(dX, dY, 0f));
        	if (val > s)
        	{
            		dX = dX * s / val;
            		dY = dY * s / val;
        	}
	}
private:
	Vector position_;
	static uint rnd;
	float border = 100f;
	float sight = 75f;
	float space = 30f;
	float speed = 12f;
	float boundary;
	float dX = 0f;
	float dY = 0f;
	bool zombie;
}

class Swarm
{
	this(uint boundary, uint min, uint max, uint p=100,bool useZombie=false)
	{
		population = p;
		for (int i = 0; i < population; i++)
        	{
			listPopulation.length = listPopulation.length + 1;
			Boid b;
			if (useZombie)
				b = new Boid((i>population-population/3),boundary,min,max);
			else
				b = new Boid(false,boundary,min,max);
			listPopulation[ listPopulation.length - 1] = b;
        	}
	}
	void population(uint p)
	{
		population_ = p;
	}
	uint population()
	{
		return population_;
	}
	void moveSwarm()
    	{
        	foreach (Boid b; listPopulation)
        	{
            		b.move(listPopulation);
        	}
    	}
	Boid[] getList()
        {
                return listPopulation;
        }
private:
	uint population_;
	Boid[] listPopulation;
}
