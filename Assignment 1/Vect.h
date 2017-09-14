#pragma once

class Vect {
public:
	Vect(double a, double b, double c);
	Vect();
	Vect(const Vect &v);
	
	double mod();
	Vect unitVector();
	Vect scalarMult(double i);	// methods
	Vect add(Vect v);
	Vect minus(Vect v);
	double dot(Vect v);
	Vect cross(Vect v);
	Vect opposite();
	void print();
	bool equals(Vect v);
	
	double getX();
	double getY();	// getter
	double getZ();
	
	void setX(double a);
	void setY(double a);	// setters
	void setZ(double a);

private:
	double x;
	double y;
	double z;
};
