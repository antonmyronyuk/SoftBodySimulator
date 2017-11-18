#include "Particle.h"



Particle::Particle(): 
	position(Point3d()), //(0, 0, 0) point
	lastPosition(Point3d()), //(0, 0, 0) point
	mass(1.f),
	objectId(0) {
	w = 1.f / mass; 
}

Particle::Particle(const Point3d& position, float mass): 
	position(position), 
	lastPosition(position), 
	mass(mass), 
	objectId(0) {
	w = 1.f / mass;
}

Particle::Particle(const Point3d& position, int objectId, float mass): 
	position(position), 
	lastPosition(position), 
	objectId(objectId), 
	mass(mass) {
	w = 1.f / mass;
}
