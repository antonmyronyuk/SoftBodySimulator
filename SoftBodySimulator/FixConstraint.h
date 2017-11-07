#pragma once

#include "Constraint.h"
#include "Point3d.h"

class FixConstraint : public Constraint {

	Particle& particle;
	Point3d position;
	CONSTRAINT_TYPE type;

public:
	FixConstraint(const FixConstraint& fixConstraint);
	FixConstraint(Particle& particle, const Point3d& position);
	virtual ~FixConstraint();

	virtual void apply(float step);

	Particle& getParticle() const;
	Point3d getPosition() const;

	virtual CONSTRAINT_TYPE getType() const;

};