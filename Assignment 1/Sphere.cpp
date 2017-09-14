#include "Sphere.h"
#include "Vect.h"
#include"Color.h"
#include"Ray.h"
#include"Material.h"
#include"WorldObject.h"
#include <cmath>

using namespace std;

Sphere::Sphere()
{
	centre = Vect();
	rad = 1.0;
	color = Color();
	mat = Material();
}

Sphere::Sphere(Vect c, double r, Color col,Material m)
{
	centre = c;
	rad = r;
	color = col;
	mat = m;
}

Sphere::Sphere(const Sphere & s)
{
	centre = s.centre;
	rad = s.rad;
	color = s.color;
	mat = s.mat;
}

Vect Sphere::getCentre()
{
	return centre;
}

double Sphere::getRad()
{
	return rad;
}

Color Sphere::getColor()
{
	return color;
}

Vect Sphere::getIntersect(Ray r)
{
	double a = 1.0;
	double b = 2.0 * ( r.getDir().getX() * (r.getStart().getX() - centre.getX()) + 
					r.getDir().getY()*(r.getStart().getY() - centre.getY()) + r.getDir().getZ() * (r.getStart().getZ() - centre.getZ()) );
	double c = (r.getStart().getX() - centre.getX())*(r.getStart().getX() - centre.getX()) +
				(r.getStart().getY() - centre.getY())*(r.getStart().getY() - centre.getY()) + (r.getStart().getZ() - centre.getZ())*(r.getStart().getZ() - centre.getZ()) - rad*rad;
	double d = b*b - 4*a*c;
	if (d < 0)	return Vect(-1,-1,-1);
	double t1 = (-b + sqrt(d)) / 2.0;
	double t2 = (-b - sqrt(d)) / 2.0;
	if ((t1 < t2 && t1>0) || (t1>0 && t2<0))
		return Vect(r.getStart().getX() + t1*(r.getDir().getX()), r.getStart().getY() + t1*(r.getDir().getY()), r.getStart().getZ() + t1*(r.getDir().getZ()));
	else if ((t2 <= t1 && t2 > 0) || (t2 > 0 && t1 < 0)) {
		Vect vec = Vect(r.getStart().getX() + t2*(r.getDir().getX()), r.getStart().getY() + t2*(r.getDir().getY()), r.getStart().getZ() + t2*(r.getDir().getZ()));
		return vec;
	}
	else return Vect(-1, -1, -1);
}

double Sphere::getT(Ray r)
{
	double a = 1.0;
	double b = 2.0 * (r.getDir().getX() * (r.getStart().getX() - centre.getX()) +
		r.getDir().getY()*(r.getStart().getY() - centre.getY()) + r.getDir().getZ() * (r.getStart().getZ() - centre.getZ()));
	double c = (r.getStart().getX() - centre.getX())*(r.getStart().getX() - centre.getX()) +
		(r.getStart().getY() - centre.getY())*(r.getStart().getY() - centre.getY()) + (r.getStart().getZ() - centre.getZ())*(r.getStart().getZ() - centre.getZ()) - rad*rad;
	double d = b*b - 4 * a*c;
	if (d < 0)	return -1;
	double t1 = (-b + sqrt(d)) / 2.0;
	double t2 = (-b - sqrt(d)) / 2.0;
	if (t1 < 0 && t2 < 0) return -1;
	if ((t1 < t2 && t1>0) || (t1>0 && t2<0))
		return t1;
	else if ((t2 <= t1 && t2 > 0) || (t2 > 0 && t1 < 0)) {
		return t2;
	}
	
}


Vect Sphere::getNormal(Vect intersect)
{
	return Vect((intersect.getX() - centre.getX()) * 1.0 / rad, (intersect.getY() - centre.getY())*(1.0) / rad, (intersect.getZ() - centre.getZ())*(1.0) / rad).unitVector();
}

Material Sphere::getMaterial()
{
	return mat;
}

Vect Sphere::getTransmitRayDirection(Ray incidentRay, Vect intersection)
{
	Vect n = getNormal(intersection);
	double angleOfIncidence = acos((-1)*incidentRay.getDir().dot(n));
	double angleOfRefracton = asin(sin(angleOfIncidence) / mat.getRefractiveIndex());
	return Vect();
}

