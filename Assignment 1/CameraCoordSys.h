#pragma once
#include "Vect.h"


class CameraCoordSys
{
public:
	CameraCoordSys();
	CameraCoordSys(Vect vr,Vect globalUp,Vect n);
	Vect VCS2WCS(Vect v);
	Vect WCS2VCS(Vect v);
	
private:
	Vect VRP;
	Vect normal;
	Vect up;		// left handed coordinate system
	Vect u;

};

