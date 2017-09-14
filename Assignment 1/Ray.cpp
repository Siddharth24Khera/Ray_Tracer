#include "Ray.h"
#include "Vect.h"

using namespace std;

Ray::Ray(Vect v1, Vect v2, double i)
{
	start = v1;
	dir = v2.unitVector();
	intense = i;
}

Ray::Ray()
{
	start = Vect(0, 0, 0);
	dir = Vect(1, 0, 0);
	intense = 0;
}

Vect Ray::getStart()
{
	return start;
}

Vect Ray::getDir()
{
	return dir;
}

double Ray::getIntense()
{
	return intense;
}

void Ray::setStart(Vect v)
{
	start = v;
}

void Ray::setDir(Vect v)
{
	dir = v.unitVector();
}

void Ray::setIntense(double i)
{
	intense = i;
}
