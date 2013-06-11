//lets assume the polygons are defined as a array of points (anti-clock)
//the algo needs to be tested
Vect v = [p1,p2,p3,p4];

struct Polygon
{
    Vect []v;
}

static Polygon p.v = v;

// Returns the intersection point
Point IntersectLines(Point p1, Point p2, Point p3, Point p4, inout bool inter)
{
    ...
}

Polygon[] SlicePolygon(Polygon p, Point p1, Point p2)
{
    int count;
    Polygon tmp;
    Point intersect1=0, intersect2=0;
    //iterate anti clock
    for(count=0; count<p.length; count=count+2)
    {
        bool inter=false;
        if (count+1>=p.length)
            break;
        Point pt = IntersectLines(..., inter);
        if (inter)
        {
            tmp.length = tmp.length + 1;
            tmp[ tmp.length - 1 ] = p[count];
            tmp.length = tmp.length + 1;
            tmp[ tmp.length - 1 ] = pt;
            if (intersect1==0)
                intersect1 = pt;
            else
                intersect2 = pt;
            tmp.length = tmp.length + 1;
            tmp[ tmp.length - 1 ] = p[count+1];
        }
        else
        {
            tmp.length = tmp.length + 1;
            tmp[ tmp.length - 1 ] = p[count];
            tmp.length = tmp.length + 1;
            tmp[ tmp.length - 1 ] = p[count+1];
        }
    }
    //check btw last point and first point
    bool inter=false;
    Point pt = IntersectLines(..., inter);
    if (inter)
    {
        tmp.length = tmp.length + 1;
        tmp[ tmp.length - 1 ] = pt;
        if (intersect1==0)
            intersect1 = pt;
        else
            intersect2 = pt;
    }
    bool a=false, b=false;
    Polygon[2] ret;
    if (intersect1==0 || intersect2==0)
        return ret;
    for(count=0; count<tmp.length; count++)
    {
        if (!a && !b)
        {
            ret[0].v.length = ret[0].v.length + 1;
            ret[0].v[ ret[0].v.length - 1 ] = tmp[count];
        }
        else
        {
            if ((a && b) || (tmp[count]==intersect2))
            {
                ret[0].v.length = ret[0].v.length + 1;
                ret[0].v[ ret[0].v.length - 1 ] = tmp[count];
            }
        }
        if ((a && !b) || (tmp[count]==intersect1))
        {
            ret[1].v.length = ret[1].v.length + 1;
            ret[1].v[ ret[1].v.length - 1 ] = tmp[count];
        }
        if (tmp[count]==intersect1)
            a = true;
        if (tmp[count]==intersect2)
            b = true;
    }
    return ret;

}


