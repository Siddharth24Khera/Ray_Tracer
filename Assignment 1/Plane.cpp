#include "Plane.h"

Plane::Plane()
{
	point = Vect(0, 0, 0);
	normal = Vect(1, 0, 0);
	col = Color(0, 0, 0);
	mat = Material();
}

Plane::Plane(const Plane & p)
{
	point = p.point;
	normal = p.normal;
	col = p.col;
	mat = p.mat;
}

Plane::Plane(Vect v1, Vect v2, Vect v3, Color c,Material m)
{
	point = v1;
	normal = ((v1.minus(v2)).cross(v2.minus(v3))).unitVector();
	col = c;
	mat = m;
}

Plane::Plane(Vect poi, Vect norm, Color c, Material m)
{
	point = poi;
	normal = norm.unitVector();
	col = c;
	mat = m;
}

Material Plane::getMaterial()
{
	return mat;
}

Color Plane::getColor()
{
	return col;
}

Vect Plane::getIntersect(Ray r)
{
	double x = r.getDir().dot(normal);
	if (x == 0) return Vect(-1, -1, -1);
	/*if (x > 0) normal = normal.opposite();
	x = -x;*/
	double d = -normal.dot(point);
	double t = -(normal.dot(r.getStart()) + d) / x;
	if (t < 0)return Vect(-1, -1, -1);
	return r.getStart().add(r.getDir().scalarMult(t));
}

double Plane::getT(Ray r)
{
	double x = r.getDir().dot(normal);
	if (x == 0) return -1;
	/*if (x > 0) normal = normal.opposite();
	x = -x;*/
	double d = -normal.dot(point);
	double t = -(normal.dot(r.getStart()) + d) / x;
	if (t < 0) return -1;
	return t;
}

Vect Plane::getNormal(Vect intersect)
{
	return normal;
}

Vect Plane::getTransmitRayDirection(Ray incidentRay, Vect intersection)
{
	return incidentRay.getDir();
}

