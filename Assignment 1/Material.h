#pragma once
#include "json/json.h"
#include "json/json-forwards.h"

class Material
{
public:
	Material();
	Material(double a, double b, double c, double d);
	Material(double a, double b, double c, double d,double e,double f);
	Material(double a, double b, double c, double d, double e, double f, double g);
	Material(Json::Value matProp);
	Material(const Material &m);
	double getAmbCoff();
	double getDifCoff();
	double getSpecCoff();
	double getSpecPow();
	double getCoeffForReflect();
	double getCoeffForTransmit();
	double getRefractiveIndex();
private:
	double ka;
	double kd;
	double ks;
	double specPow;
	double kr;
	double kt;
	double refractiveIndex;
};

