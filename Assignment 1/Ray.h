#pragma once
#include"Vect.h"
class Ray {
public:
	
	Ray(Vect v1, Vect v2, double i);	//contructor
	Ray();
	
	Vect getStart();
	Vect getDir();		// getter
	double getIntense();
	
	void setStart(Vect v);
	void setDir(Vect v);			//setter
	void setIntense(double i);

private:
	Vect start;
	Vect dir;
	double intense;
};