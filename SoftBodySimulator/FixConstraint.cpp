#include "FixConstraint.h"

FixConstraint::FixConstraint(const FixConstraint& fixConstraint): 
	particle(fixConstraint.particle),
	position(fixConstraint.position), 
	type(eFix) {
}

FixConstraint::FixConstraint(Particle& particle, const Point3d& position): 
	particle(particle), 
	position(position), 
	type(eFix) {
}

FixConstraint::~FixConstraint(){
}

void FixConstraint::apply(float step) {
	particle.setPosition(position);
}

Particle& FixConstraint::getParticle() const {
	return particle;
}

Point3d FixConstraint::getPosition() const {
	return position;
}

CONSTRAINT_TYPE FixConstraint::getType() const {
	return type;
}