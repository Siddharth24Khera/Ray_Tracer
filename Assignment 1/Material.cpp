#include "Material.h"
#include "json/json.h"
#include "json/json-forwards.h"

Material::Material()
{
	ka = 0; kd = 0; ks = 0; specPow = 1; kr = 0; kt = 0; refractiveIndex = 1;
}

Material::Material(double a1, double b1, double c1, double d1)
{
	ka = a1;
	kd = b1;
	ks = c1;
	specPow = d1;
	kr = 0; kt = 0; refractiveIndex = 1;
}

Material::Material(double a1, double b1, double c1, double d1, double e1, double f1)
{
	ka = a1;
	kd = b1;
	ks = c1;
	specPow = d1;
	kr = e1;
	kt = f1;
	refractiveIndex = 1;
}

Material::Material(double a1, double b1, double c1, double d1, double e1, double f1, double g1)
{
	ka = a1;
	kd = b1;
	ks = c1;
	specPow = d1;
	kr = e1;
	kt = f1;
	refractiveIndex = g1;
}

Material::Material(Json::Value matProp)
{

}

Material::Material(const Material & m)
{
	ka = m.ka;
	kd = m.kd;
	ks = m.ks;
	specPow = m.specPow;
	kr = m.kr;
	kt = m.kt;
}

double Material::getAmbCoff()
{
	return ka;
}

double Material::getDifCoff()
{
	return kd;
}

double Material::getSpecCoff()
{
	return ks;
}

double Material::getSpecPow()
{
	return specPow;
}

double Material::getCoeffForReflect()
{
	return kr;
}

double Material::getCoeffForTransmit()
{
	return kt;
}

double Material::getRefractiveIndex()
{
	return refractiveIndex;
}
