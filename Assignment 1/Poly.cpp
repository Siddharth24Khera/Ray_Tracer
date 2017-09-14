#include "Poly.h"
#include<cmath>

using namespace std;

Poly::Poly()
{
}

Poly::Poly(list<Vect> lPoints,Color c,Material m)
{
	listOfPoints = lPoints;
	verticesNo = listOfPoints.size();
	col = c;
	mat = m;
	list<Vect>::iterator it;
	it =  listOfPoints.begin();
	containingPlane = Plane(*it++, *it++, *it++, col, mat);
}

Poly::Poly(const Poly & p)
{
	mat = p.mat;
	col = p.col;
	verticesNo = p.verticesNo;
	containingPlane = p.containingPlane;
	listOfPoints = p.listOfPoints;
}

Color Poly::getColor()
{
	return col;
}

Material Poly::getMaterial()
{
	return mat;
}

int Poly::getVerticeNo()
{
	return verticesNo;
}

list<Vect> Poly::getListOfPoints()
{
	return listOfPoints;
}

Vect Poly::getNormal(Vect v)
{
	return containingPlane.getNormal(v);
}

Vect Poly::getIntersect(Ray r)
{
	Vect v = containingPlane.getIntersect(r);
	bool isIn = containment(v);
	if (isIn == true) return v;
	else return Vect(-1, -1, -1);
}

double Poly::getT(Ray r)
{
	Vect v = containingPlane.getIntersect(r);
	bool isIn = containment(v);
	if (isIn == true) return containingPlane.getT(r);
	else return -1;
}

Vect Poly::getTransmitRayDirection(Ray incidentRay, Vect intersection)
{
	return incidentRay.getDir();
}

bool Poly::containment(Vect v)
{
	double m1, m2;
	double sum = 0;
	double theta=0;
	Vect v1 = Vect();
	Vect v2 = Vect();
	list<Vect>::iterator it;
	it = listOfPoints.begin();
	int c = listOfPoints.size();
	for(int i =1;i<c;i++) {
		v1 = (*it).minus(v);
		it++;
		v2 = (*it).minus(v);
		m1 = v1.mod();
		m2 = v2.mod();

		if (m1*m2 <= 0.0001)
			return true;
		
		theta = v1.dot(v2) / (m1*m2);
		sum += acos(theta);
	}
	v1 = listOfPoints.front().minus(v);
	m1 = v1.mod();
	if (m1*m2 <= 0.0001)
		return true;
	theta = v1.dot(v2) / (m1*m2);
	sum += acos(theta);

	if (fabs(sum - 2 * 3.1418) <= 0.01)
		return true;
	return false;
}

