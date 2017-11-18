#pragma once
#include "Point3d.h"

class Particle {

public:
	Point3d position;
	Point3d lastPosition;
	//mass of the body particle 
	//may be not equal to 1.f
	//so we can simulate uneven body
	float mass;
	int objectId;

	//w = 1 / mass
	float w; 

	Particle();
	Particle(const Point3d& position, float mass = 1.f);
	Particle(const Point3d& position, int objectId, float mass = 1.f);
	
};