#include"WorldObject.h"
#include"Vect.h"
#include"Color.h"
#include"Material.h"
#include "Ray.h"

WorldObject::WorldObject()
{
}

Vect WorldObject::getIntersect(Ray r)
{
	return Vect();
}

Vect WorldObject::getNormal(Vect intersect)
{
	return Vect();
}

Color WorldObject::getColor()
{
	return Color();
}

Material WorldObject::getMaterial()
{
	return Material();
}
