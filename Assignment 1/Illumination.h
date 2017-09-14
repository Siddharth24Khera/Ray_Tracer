#pragma once
#include "WorldObject.h"
#include"Vect.h"
#include"Sphere.h"
#include"Plane.h"
#include"Poly.h"

class Illumination

{
public:
	Illumination();
	Illumination(Vect v,double i);
	double getIntensityAtIntersectSphere(Sphere obj, Vect intPoint, Vect viewer);
	double getIntensityAtIntersectPlane(Plane obj, Vect intPoint, Vect viewer);
	double getIntensityAtIntersectPolygon(Poly obj, Vect intPoint, Vect viewer);
	Vect getPos();
	double getIntensity();
private:
	Vect pos;
	double intensity;
};

