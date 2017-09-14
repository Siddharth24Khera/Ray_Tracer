#pragma once
#include"Vect.h"
#include"Color.h"
#include"Material.h"
#include "Ray.h"

class WorldObject
{
public:
	WorldObject();
	Vect getIntersect(Ray r);
	Vect getNormal(Vect intersect);
	Color getColor();
	Material getMaterial();
};

