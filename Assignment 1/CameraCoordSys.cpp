#include "CameraCoordSys.h"
#include"Vect.h"


CameraCoordSys::CameraCoordSys()
{
	VRP = Vect();
	normal = Vect(1, 0, 0);
	up = Vect(0, 1, 0);
	u = normal.cross(up).unitVector();
}

CameraCoordSys::CameraCoordSys(Vect vr, Vect globalUp, Vect n)
{
	VRP = vr;
	normal = n.unitVector();
	up = globalUp.minus(normal.scalarMult(globalUp.dot(normal)));
	up = up.unitVector();
	u = normal.cross(up).unitVector();
}

Vect CameraCoordSys::VCS2WCS(Vect v)
{
	double x, y, z;
	x = v.getX()*u.getX() + v.getY()*up.getX() + v.getZ()*normal.getX();
	y = v.getX()*u.getY() + v.getY()*up.getY() + v.getZ()*normal.getY();
	z = v.getX()*u.getZ() + v.getY()*up.getZ() + v.getZ()*normal.getZ();
	return Vect(x,y,z).add(VRP);
}

Vect CameraCoordSys::WCS2VCS(Vect v)
{
	Vect a = v.minus(VRP);
	double x, y, z;
	x = a.dot(u);
	y = a.dot(up);
	z = a.dot(normal);
	return Vect(x, y, z);
}




