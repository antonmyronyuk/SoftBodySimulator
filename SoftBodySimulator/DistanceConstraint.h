#pragma once

#include "Constraint.h"

class DistanceConstraint : public Constraint {
	Particle& particleA_;
	Particle& particleB_;
	float distance_;
	float stiffness_;
	CONSTRAINT_TYPE type_;
public:
	DistanceConstraint(Particle& particleA, Particle& particleB, float stiffness, float distance = 0.f);
	DistanceConstraint(const DistanceConstraint& distConstraint);
	virtual ~DistanceConstraint();

	virtual void apply(float step);

	Particle& getParticleA() const;
	Particle& getParticleB() const;
	float getStiffness() const;
	float getDistance() const;

	virtual CONSTRAINT_TYPE getType() const;

	
};
