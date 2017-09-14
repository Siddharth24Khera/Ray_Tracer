#include"Vect.h"
#include<cmath>
#include<iostream>


using namespace std;

Vect::Vect(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}

Vect::Vect()
{
	x = 0; y = 0; z = 0;
}

Vect::Vect(const Vect &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}


double Vect::mod()
{
	return sqrt(x * x + y * y + z * z);
}

void Vect::setX(double a)
{
	x = a;
}

void Vect::setY(double a)
{
	y = a;
}

void Vect::setZ(double a)
{
	z = a;
}


Vect Vect::unitVector()
{
	Vect u;
	double mod = this->mod();
	u.setX(x / mod);
	u.setY(y / mod);
	u.setZ(z / mod);
	return u;
}

Vect Vect::scalarMult(double i)
{
	Vect u;
	u.x = x  * i;
	u.y = y * i;
	u.z = z * i;
	return u;
}

void Vect::print()
{
	cout << x << " " << y << " " << z << endl;
}

bool Vect::equals(Vect v)
{
	if (x == v.x && y == v.y && z == v.z)
		return true;
	else return false;
}

double Vect::getX()
{
	return x;
}

double Vect::getY()
{
	return y;
}

double Vect::getZ()
{
	return z;
}

Vect Vect::add(Vect v)
{
	Vect u;
	u.setX(v.getX() + x);
	u.setY(v.getY() + y);
	u.setZ(v.getZ() + z);
	return u;
}

Vect Vect::minus(Vect v)
{
	Vect u;
	u.x = x - v.x;
	u.y = y - v.y;
	u.z = z - v.z;
	return u;
}

double Vect::dot(Vect v)
{
	return (x * v.x + y *v.y + z * v.z) ;
}

Vect Vect::cross(Vect v)
{
	Vect u;
	u.x = (y * v.z) - (z * v.y);
	u.y = (z * v.x) - (x * v.z);
	u.z = (x * v.y) - (y * v.x);
	return u;
}

Vect Vect::opposite()
{
	return Vect(-x,-y,-z);
}
