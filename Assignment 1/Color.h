#pragma once

class Color
{
public:
	Color();
	Color(double red, double green, double blue); // constructor
	Color(const Color &c);

	double getR();
	double getB();	//getter
	double getG();

	void setR(double i);
	void setG(double i);
	void setB(double i);

	Color colMuly(Color c);
	Color scalarmult(double i);
	bool equals(Color c);
	double getIntensityFromOriginalColor();

private:
	double r, g, b;
};

