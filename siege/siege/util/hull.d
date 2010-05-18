module siege.util.hull;

private
{
    import std.math;

    import siege.graphics.draw;

    import siege.util.misc;
    import siege.util.color;
    import siege.util.vector;
    import siege.util.stack;
}

/**
Transform a set o points (Vectors) on a convex hull
**/

class Edge
{
	Vector start, end, centre;
	uint index;
	this(Vector s, Vector e)
	{
    		start = s;
    		end = e;
    		centre = start;
  	}
	this(Vector s, Vector e, uint i)
        {
                start = s;
                end = e;
                centre = start;
		index = i;
        }
	bool inside(Vector x)
	{
    		HalfSpace h = new HalfSpace(start,end);
    		return h.inside(x);
  	}
	void render()
	{
		draw.begin(Primitive.Lines);
		draw.color(1.0, 0.0, 0.0);
		draw.vertex(start.x,start.y);
		draw.color(0.0, 1.0, 0.0);
		draw.vertex(end.x,end.y);
		draw.end();
	}
}

Vector subtract(Vector dest, Vector src)
{
	dest.x-=src.x;
	dest.y-=src.y;
	dest.z-=src.z;
	return dest;
}

Vector cross(Vector a, Vector b)
{
	Vector p;
	p.x = a.y * b.z - b.y * a.z;
	p.y = a.z * b.x - b.z * a.x;
	p.z = a.x * b.y - b.x * a.y;
	return p;
}
double dot(Vector a, Vector b)
{
	return (cast(double)((a.x * b.x) + (a.y * b.y) + (a.z * b.z)));
}
bool sameside(Vector p1,Vector p2, Vector a, Vector b)
{
    Vector cp1 = cross(subtract(b, a), subtract(p1, a));
    Vector cp2 = cross(subtract(b, a), subtract(p2, a));
    if (dot(cp1, cp2) >= 0)
	    return true;
    else
	    return false;
}

bool pointintriangle(Vector p, Vector a, Vector b, Vector c)
{
    if (sameside(p,a, b,c) && sameside(p,b, a,c) && sameside(p,c, a,b))
	    return true;
    else
	    return false;
}

class HalfSpace
{
	Vector normal;
	double d;
	this(Vector a, Vector b, Vector c)
	{
		normal = cross(subtract(b,a),subtract(c,a)).normalize();
		d = dot(normal, a);
	}

	this(Vector a, Vector b)
	{
		Vector k = Vector(0,0,1);
		normal = cross(subtract(b,a),k).normalize();
	}
	bool inside(Vector x)
	{
		return (dot(normal,x) > d);
	}
	double zint(Vector p)
	{
		return(cast(double)((d - normal.x*p.x - normal.y*p.y) / normal.z));
	}
}

class Triangle
{
	Vector p1,p2,p3;
	uint index;
	this(Vector a, Vector b, Vector c, uint i)
	{
		p1 = a;
		p2 = b;
		p3 = c;
		index = i;
	}
	void render()
	{
		draw.begin(Primitive.Triangles);
                draw.color(1.0, 0.0, 0.0);
                draw.vertex(p1.x, p1.y);

                draw.color(0.0, 1.0, 0.0);
                draw.vertex(p2.x, p2.x);

                draw.color(0.0, 0.0, 1.0);
                draw.vertex(p3.x, p3.y);
            	draw.end();
	}
}


class HullEntity
{
	Vector o1;
	Edge e1;
	Triangle t1;
	string type;
	this(Vector x, string t)
	{
		o1 = x;
		type = t;
	}
	this(Edge x, string t)
        {
                e1 = x;
                type = t;
        }
	this(Triangle x, string t)
        {
                t1 = x;
                type = t;
        }
	void render()
	{
		if (type == "Edge")
			e1.render();
		if (type == "Vector")
		{
			draw.begin(Primitive.Points);
                	draw.color(1.0, 0.0, 0.0);
                	draw.vertex(o1.x, o1.y);
                	draw.end();
		}
		if (type == "Triangle")
                        t1.render();
	}
}

class GiftWrap
{
	this(Vector []p1)
	{
		p = p1.dup;
		tcount = 0;
	}
	~this()
	{
	}
	int index(Vector p1)
	{
    		for(int i=0; i<p.length; i++)
		{
      			if (p1==p[i])
			{
				return i;
      			}
    		}
    		return -1;
  	}
	Vector search2d(Vector p1)
	{
      		int i;
      		//i = p[0] == p1?1:0;
		if (p[0]==p1)
			i = 1;
		else
			i = 0;
      		Vector cand = p[i];
      		HalfSpace candh = new HalfSpace(p1,cand);
      		for(i=i+1; i < p.length; i++)
		{
			if (p[i]!=p1 && candh.inside(p[i]))
			{
	  			cand = p[i];
	  			candh = new HalfSpace(p1,cand);
			}
      		}
      		return cand;
	}
    	Vector bottom()
    	{
		Vector bot = p[0];
    		for (int i = 1; i < p.length; i++)
		{
      			if (p[i].y < bot.y)
			{
				bot = p[i];
      			}
    		}
    		return bot;
     	}
	void AppendPtr(Vector []p1)
	{
		p = p1.dup;
	}
	Vector search(Edge e)
	{
      		int i;
		for(i = 0; p[i] == e.start || p[i] == e.end; i++)
		{
			/* nothing */
      		}
      		Vector cand = p[i];
      		HalfSpace candh = new HalfSpace(e.start,e.end,cand);
      		for(i=i+1; i < p.length; i++)
		{
			if (p[i] != e.start && p[i] != e.end && candh.inside(p[i]))
			{
	  			cand = p[i];
	  			candh = new HalfSpace(e.start,e.end,cand);
			}
      		}
      		return cand;
	}
	bool compare2D(Vector a, Vector b)
	{
		if (a.x==b.x && a.y==b.y)
			return true;
		return false;
	}
	bool compare3D(Vector a, Vector b)
        {
                if (a.x==b.x && a.y==b.y && a.z==b.z)
                        return true;
                return false;
        }
	/**
	2D
	**/
	HullEntity []build2D()
	{
		Vector p1;
		Vector bot = bottom();

		HullEntity []faces;
		faces.length = faces.length + 1;
		HullEntity tmp = new HullEntity(bot,"Vector");
		faces[0] = tmp;
		p1 = bot;
		int i = 1;
		do
		{
			Vector cand = search2d(p1);
			faces.length = faces.length + 1;
			HullEntity	tmp2 = new HullEntity(new Edge(p1,cand,i),"Edge");
                	faces[i] = tmp2;
			p1 = cand;
			i++;
		}
		while(p1!=bot);
		tcount = i;
		return faces;
	}
	int indexOf(Stack!(Edge) s, Edge e)
	{
		assert(0,"DUNNO IF ITS REVERSE");
		Edge tmp = s.pop();
		int i = 0;
		bool found = false;
		while(s.length != 0)
		{
			if (e is tmp)
			{
				found = true;
				break;
			}
			else
			{
				tmp = s.pop();
				i++;
			}

		}
		if (!found)
			return -1;
		else
			return i;
	}
	void removeat(inout Stack!(Edge) s, uint index)
	{
		assert(0,"TODO");
	}
	void putp(inout Stack!(Edge) s, Vector a, Vector b)
	{
		Edge e = new Edge(a,b);
		int ind = indexOf(s,e);
		if (ind == -1)
		{
			s.push(e);
		}
		else
		{
			removeat(s,ind);
		}
	}
	/**
	3D
	**/
	HullEntity []build()
	{
		Vector bot, bot2;
		bot = bottom();
   		bot2 = search2d(bot);

		Stack!(Edge) es;
		Edge tmp1 = new Edge(bot,bot2);
		Edge tmp2 = new Edge(bot2,bot);

		es.push(tmp1);
		es.push(tmp2);

		int i = 1;
		HullEntity  []faces;
		Edge e = new Edge(bot,bot2,i);
		tcount=i++;
		faces.length = faces.length + 1;
		HullEntity  tmp3 = new HullEntity(e,"Edge");
		faces[0] = tmp3;
		while(es.length != 0)
		{
			Edge tmp4 = es.pop();
			Vector cand = search(tmp4);
			faces.length = faces.length + 1;
			HullEntity  tmp5 = new HullEntity(new Triangle(e.start,e.end,cand,i),"Triangle");
			faces[i-1] = tmp5;
			putp(es,e.start,cand);
			putp(es,cand,e.end);
			i++;
		}
		tcount = i;
                return faces;
	}
protected:
	Vector []p;
	uint tcount;
}

enum PolygonType
{
	CONVEX	= 0b100000,
	CONCAVE = 0b010000,
        INVALID = 0b001000
}

enum PolygonPath
{
	CLOCKWISE = 0b000100,
	COUNTERCLOCKWISE = 0b000010,
	INVALID = 0b000001
}

char[][] PolygonDict(PolygonType type, PolygonPath path)
{
    char[][] str;
    if(type & PolygonType.INVALID)
        str ~= "Invalidtype";
    if(type & PolygonType.CONVEX)
	str ~= "Convex";
    if(type & PolygonType.CONCAVE)
	str ~= "Concave";
    str ~= " - ";
    if(path & PolygonPath.CLOCKWISE)
        str ~= "Clockwise";
    if(path & PolygonPath.COUNTERCLOCKWISE)
        str ~= "Counterclockwise";
    if(path & PolygonPath.INVALID)
        str ~= "Invalidpath";
    return str;
}

interface Hull
{
    Hull dup();
    void drawDBG(Vector location, float angle = 0, Color c = Color(1.0, 1.0, 1.0, 1.0));
}

class Polygon: Hull
{
    Vector[] points;

    this(Vector[] points ...)
    {
        this.points = points;
    }
    bool clockwise()
    {
	if (path==PolygonPath.CLOCKWISE)
		return true;
	else
		return false;
    }
    bool counterclockwise()
    {
	if (path==PolygonPath.COUNTERCLOCKWISE)
		return true;
	else
		return false;
    }
    bool convex()
    {
	if (type==PolygonType.CONVEX)
		return true;
	else
		return false;
    }
    bool concave()
    {
	if (type==PolygonType.CONCAVE)
		return true;
	else
		return false;
    }
    void toClockWise()
    {
	    if (clockwise)
		    return;
	    Vector[] p = points.dup;
	    p.reverse;
	    points = p.dup;

    }
    void toCounterClockWise()
    {
	    if (counterclockwise)
		    return;
	    Vector[] p = points.dup;
	    p.reverse;
	    points = p.dup;
    }
    /**
    Maybe use mesh techniques
    **/
    Vector triangleCenter(Vector a, Vector b, Vector c)
    {
	    Vector ret;
	    ret.x = (a.x + b.x + c.x)/3;
	    ret.y = (a.y + b.y + c.y)/3;
	    ret.z = (a.z + b.z + c.z)/3;

	    return ret;
    }
    /**
    Need testing more testing
    **/
    void toConcave()
    {
	    if (concave)
		    return;
	    Polygon[] p = toMesh();
	    foreach(Polygon f; p)
	    {
		    points.length = points.length + 1;
		    points[points.length - 1] = triangleCenter(f.points[0],f.points[1],f.points[2]);
		    int i = evalconvex();
		    if (i==-1)
			    break;
	    }
    }
    /**
    Need testing more testing
    NOTE: the Y axis is increasing at opposite... this must be solved or change all the code
    **/
    void toConvex()
    {
	    if (convex)
		    return;
	    GiftWrap gw = new GiftWrap(points);
	    HullEntity []e = gw.build2D();
	    Vector[] p;
	    foreach(HullEntity h; e)
	    {
		    if (h.type=="Triangle")
		    {
			    p.length = p.length + 1;
			    p[p.length - 1] = h.t1.p1;
			    p.length = p.length + 1;
			    p[p.length - 1] = h.t1.p2;
			    p.length = p.length + 1;
			    p[p.length - 1] = h.t1.p3;
		    }
		    if (h.type=="Vector")
		    {
			    p.length = p.length + 1;
			    p[p.length - 1] = h.o1;
		    }
		    if (h.type=="Edge")
		    {
			    p.length = p.length + 1;
			    p[p.length - 1] = h.e1.start;
			    p.length = p.length + 1;
			    p[p.length - 1] = h.e1.end;
		    }
	    }
	    delete gw;
	    points = p.dup;
    }
    /**
    Mesh - Convert polygon to a set of triangles
    **/
    Vector[] removeVectorFromPolygon(Vector[] p, uint index)
    {
	    Vector[] ret;
	    ret.length = 0;
	    uint i = 0;
	    foreach(Vector f; p)
	    {
		    if (i!=index)
		    {
			    ret.length = ret.length + 1;
			    ret[ret.length-1] = f;
		    }
		    i+=1;
	    }
	    return ret;
    }
    uint leftMostVector(Vector[] p)
    {
	    uint index = 0;
	    uint i = 0;
	    float minx = float.max;
	    foreach(Vector point; p)
	    {
		    if (point.x<=minx)
		    {
			    minx = point.x;
			    index = i;
		    }
		    i+=1;
	    }
	    return index;
    }
    Vector[] pointsInsideTriangle(Vector a, Vector b, Vector c, Vector[]  p)
    {
	    Vector[] ret;
	    ret.length = 0;
	    foreach(Vector f; p)
	    {
		    if (f!=a && f!=b && f!=c)
		    {
			    if (pointintriangle(f,a,b,c))
			    {
				    ret.length = ret.length + 1;
				    ret[ret.length-1] = f;
			    }
		    }
	    }
	    return ret;
    }
    Vector[] orderPolygonStartingLeftmostVector(Vector[] p1)
    {
	    uint index = leftMostVector(p1);
	    Vector[] p;
	    p = p1[index..$];
	    p = p ~ p1[0..index];
	    return p;
    }
    Vector[] twoAdjacentVectors(uint index, Vector[] p1)
    {
	    float[] dist;
	    uint i=0;
	    foreach(Vector f; p1)
	    {
		    dist.length = dist.length + 1;
		    dist[dist.length - 1] = sqrt((f.x-p1[index].x)*(f.x-p1[index].x) + (f.y-p1[index].y)*(f.y-p1[index].y) + (f.z-p1[index].z)*(f.z-p1[index].z));
	    }
	    float[] dist2 = dist.dup;
	    dist2.sort;
	    uint k = 0;
	    uint v,b;
	    foreach(float m; dist)
	    {
		    if (m==dist2[1])
		    {
			    v = k;
		    }
		    if (m==dist2[2])
		    {
			    b = k;
		    }
		    k+=1;
	    }
	    return([p1[v],p1[b]]);
    }
    bool vectorInPolygon(Polygon p, Vector a)
    {
	    foreach(Vector f; p.points)
	    {
		    if (f.x == a.x && f.y == a.y && f.z == a.z)
			    return true;
	    }
	    return false;
    }
    /**
    Convert the polygon to mesh (triangles)
    Working - :)
    **/
    Polygon[] toMesh()
    {
	    Polygon[] p;
	    p.length = 0;
	    if (points.length < 3)
		    return(p);
	    Vector[] tmp = points.dup;
	    while(tmp.length != 0)
	    {
		    if (tmp.length>=3)
		    {
			    Vector[] adjacents = twoAdjacentVectors(leftMostVector(tmp),tmp);
			    p.length = p.length + 1;
			    p[p.length - 1] = new Polygon([tmp[leftMostVector(tmp)],adjacents[0],adjacents[1]]);
			    tmp = removeVectorFromPolygon(tmp,leftMostVector(tmp));
		    }
		    else
		    {
			    int j = 1;
			    while(tmp.length!=0)
			    {
				    Polygon f = p[p.length-j];
				    Vector[] tmp3 = pointsInsideTriangle(f.points[0],f.points[1],tmp[0],points);
				    if (tmp3.length == 0)
				    {
					    p.length = p.length + 1;
					    p[p.length - 1] = new Polygon([f.points[0],f.points[1],tmp[0]]);
					    tmp = removeVectorFromPolygon(tmp,0);
				    }
				    else
				    {
					    tmp3 = pointsInsideTriangle(f.points[0],tmp[0],f.points[2],points);
					    if (tmp3.length == 0)
					    {
						    p.length = p.length + 1;
						    p[p.length - 1] = new Polygon([f.points[0],tmp[0],f.points[2]]);
						    tmp = removeVectorFromPolygon(tmp,0);
					    }
					    else
					    {
						    tmp3 = pointsInsideTriangle(tmp[0],f.points[1],f.points[2],points);
						    if (tmp3.length == 0)
						    {
							    p.length = p.length + 1;
							    p[p.length - 1] = new Polygon([tmp[0],f.points[1],f.points[2]]);
							    tmp = removeVectorFromPolygon(tmp,0);
						    }
					    }
				    }
				    j++;
			    }
		    }
	    }
	    return p;
    }
    /**
    Working +-
    **/
    Polygon toDeMesh(Polygon[] p)
    {
	    uint i = 0;
	    Polygon tmp;
	    Polygon tmp2;
	    tmp2 = new Polygon(cast(Vector[])[]);
	    tmp = new Polygon(cast(Vector[])[]);
	    while(i < p.length)
	    {
		    //assert(p[i].points.length!=3,"No meshed polygon");
		    //writefln(p[i].points.length);
		    foreach(Vector f; p[i].points)
		    {
			    if (!vectorInPolygon(tmp, f))
			    {
				    tmp.points.length = tmp.points.length + 1;
				    tmp.points[tmp.points.length - 1] = f;
			    }
		    }
		    i++;
	    }
	    /*
	    while(tmp.points.length != 0)
	    {
		    //tmp.points = orderPolygonStartingLeftmostVector(tmp.points);
		    tmp2.points.length = tmp2.points.length + 1;
		    tmp2.points[tmp2.points.length - 1] = tmp.points[0];
		    tmp.points = removeVectorFromPolygon(tmp.points,0);
	    }
	    return tmp2;
	    */
	    return tmp;
    }
    /**
    0  - invalid
    1  - convex
    -1 - concave
    **/
    int evalconvex()
    {
   	int i,j,k;
   	int flag = 0;
   	double z;

   	if (points.length < 3)
      		return(0);

   	for (i=0;i<points.length;i++)
	{
      		j = (i + 1) % points.length;
      		k = (i + 2) % points.length;
      		z  = (points[j].x - points[i].x) * (points[k].y - points[j].y);
      		z -= (points[j].y - points[i].y) * (points[k].x - points[j].x);
      		if (z < 0)
         		flag |= 1;
      		else if (z > 0)
         		flag |= 2;
      		if (flag == 3)
         		return(-1);
   	}
   	if (flag != 0)
      		return(1);
	else
      		return(0);
    }
    /**
    0  - invalid
    1  - clockwise
    -1 - counterclockwise
    **/
    int evalclockwise()
    {
	    int i,j,k;
	    int count = 0;
	    double z;

	    if (points.length < 3)
		return(0);

	    for (i=0;i<points.length;i++)
	    {
		    j = (i + 1) % points.length;
		    k = (i + 2) % points.length;
		    z  = (points[j].x - points[i].x) * (points[k].y - points[j].y);
		    z -= (points[j].y - points[i].y) * (points[k].x - points[j].x);
		    if (z < 0)
			    count--;
		    else if (z > 0)
			    count++;
			}
		    if (count > 0)
			    return(-1);
		    else if (count < 0)
			    return(1);
		    else
			    return(0);
    }


    PolygonType type()
    {
	int e = evalconvex();
	if (e == 0)
		return cast(PolygonType)(PolygonType.INVALID);
	if (e == 1)
		return cast(PolygonType)(PolygonType.CONVEX);
	if (e == -1)
                return cast(PolygonType)(PolygonType.CONCAVE);
    }
    PolygonPath path()
    {
	int e = evalclockwise();
	if (e == 0)
		return cast(PolygonPath)(PolygonPath.INVALID);
	if (e == 1)
		return cast(PolygonPath)(PolygonPath.CLOCKWISE);
	if (e == -1)
                return cast(PolygonPath)(PolygonPath.COUNTERCLOCKWISE);
    }
    /// TODO: ANGLE
    void drawDBG(Vector location = Vector(0.0, 0.0), float angle = 0, Color c = Color(1.0, 1.0, 1.0, 1.0))
    {
        draw.color(c);
        draw.begin(Primitive.LineLoop);
        foreach(p; points)
        {
            draw.vertex(p + location);
        }
        draw.end();
    }

    Polygon dup()
    {
        //if(convex)
        //    return new ConvexPolygon(points.dup);
        return new Polygon(points.dup);
    }
}

class ConvexPolygon: Polygon
{
    this(Vector[] points ...)
    {
        super(points);
    }
/*
    override ConvexPolygon[] toConvex()
    {
        return [cast(ConvexPolygon)dup];
    }

*/
    override bool convex()
    {
        return true;
    }
    override Polygon dup()
    {
        return new ConvexPolygon(points.dup);
    }
}

class Circle: Hull
{
    float radius;

    this(float r)
    {
        radius = r;
    }

    void drawDBG(Vector location = Vector(0.0, 0.0), float angle = 0, Color c = Color(1.0, 1.0, 1.0, 1.0))
    {
        uint sides = max(cast(uint)(radius * 1.4f), 3);
        cfloat[] circleData;
        uint circle;
        {
            float r = 2 * PI / sides;

            circleData = new cfloat[sides];
            for(circle = 0; circle < sides; circle++)
            {
                circleData[circle] = expi(circle * r);
            }
        }

        draw.color(c);
        draw.begin(Primitive.LineLoop);
        for(circle = 0; circle < sides; circle++)
        {
            draw.vertex(location.x + circleData[circle].re * radius, location.y + circleData[circle].im * radius);
        }
        draw.end();
    }

    Circle dup()
    {
        return new Circle(radius);
    }
}
