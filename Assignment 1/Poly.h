#pragma once
#include "Vect.h"
#include "WorldObject.h"
#include <list>
#include "Plane.h"

using namespace std;

class Poly : public WorldObject
{
public:
	Poly();
	Poly(list<Vect> lPoints,Color c,Material m);
	Poly(const Poly &p);

	Color getColor();
	Material getMaterial();
	int getVerticeNo();
	list<Vect> getListOfPoints();

	Vect getNormal(Vect v);
	Vect getIntersect(Ray r);
	double getT(Ray r);
	Vect getTransmitRayDirection(Ray incidentRay, Vect intersection);

private:
	Material mat;
	Color col;
	int verticesNo;
	list<Vect> listOfPoints;
	Plane containingPlane;
	bool containment(Vect v);

};

