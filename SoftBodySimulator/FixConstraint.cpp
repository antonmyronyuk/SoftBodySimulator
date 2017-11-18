#include "FixConstraint.h"

FixConstraint::FixConstraint(const FixConstraint& fixConstraint): 
	particle_(fixConstraint.particle_),
	position_(fixConstraint.position_), 
	type_(eFix) {
}

FixConstraint::FixConstraint(Particle& particle, const Point3d& position): 
	particle_(particle), 
	position_(position), 
	type_(eFix) {
}

FixConstraint::~FixConstraint(){
}

void FixConstraint::apply(float step) {
	particle_.position.set(position_);
}

Particle& FixConstraint::getParticle() const {
	return particle_;
}

Point3d FixConstraint::getPosition() const {
	return position_;
}

CONSTRAINT_TYPE FixConstraint::getType() const {
	return type_;
}