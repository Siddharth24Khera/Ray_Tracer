#pragma once
#include "WorldObject.h"
class Plane :
	public WorldObject
{
public:
	Plane();
	Plane(const Plane &p);
	Plane(Vect v1, Vect v2, Vect v3,Color c,Material m);
	Plane(Vect poi, Vect norm,Color c ,Material m);
	Material getMaterial();
	Color getColor();
	Vect getIntersect(Ray r);
	double getT(Ray r);
	Vect getNormal(Vect intersect);
	Vect getTransmitRayDirection(Ray incidentRay, Vect intersection);

private:
	Vect point;
	Vect normal;
	Color col;
	Material mat;
};

