#pragma once
#include "Vect.h"
#include"Color.h"
#include"Ray.h"
#include"Material.h"
#include"WorldObject.h"


class Sphere : public WorldObject
{
private:
	Vect centre;
	double rad;
	Color color;
	Material mat;

	
public:
	Sphere();
	Sphere(Vect c, double r, Color col,Material m);
	Sphere(const Sphere &s);

	Vect getCentre();
	double getRad();
	Color getColor();
	Vect getIntersect(Ray r);
	double getT(Ray r);
	Vect getNormal(Vect intersect);
	Material getMaterial();
	Vect getTransmitRayDirection(Ray incidentRay, Vect intersection);

};

