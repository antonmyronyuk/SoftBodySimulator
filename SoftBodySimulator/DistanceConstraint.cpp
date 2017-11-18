#include "DistanceConstraint.h"

DistanceConstraint::DistanceConstraint(Particle& particleA, Particle& particleB, float stiffness, float distance): 
	particleA_(particleA),
	particleB_(particleB), 
	stiffness_(stiffness), 
	type_(eDistance) {

	distance_ = (distance <= 0) ? particleA.position.distance(particleB.position) : distance;
}

DistanceConstraint::DistanceConstraint(const DistanceConstraint& distConstraint): 
	particleA_(distConstraint.particleA_), 
	particleB_(distConstraint.particleB_), 
	stiffness_(distConstraint.stiffness_), 
	distance_(distConstraint.distance_), 
	type_(eDistance) {
}

DistanceConstraint::~DistanceConstraint() {
}

void DistanceConstraint::apply(float step) {

	Point3d vec = particleA_.position - particleB_.position;
	float len = vec.length();
	vec *= (distance_ - len) / len * stiffness_ * step;
	particleA_.position += vec * particleA_.w / (particleA_.w + particleB_.w);
	particleB_.position -= vec * particleB_.w / (particleA_.w + particleB_.w);
}

Particle& DistanceConstraint::getParticleA() const {
	return particleA_;
}

Particle& DistanceConstraint::getParticleB() const {
	return particleB_;
}

float DistanceConstraint::getStiffness() const {
	return stiffness_;
}

float DistanceConstraint::getDistance() const {
	return distance_;
}

CONSTRAINT_TYPE DistanceConstraint::getType() const {
	return type_;
}