#pragma once

#include "Constraint.h"
#include "Point3d.h"

class FixConstraint : public Constraint {

	Particle& particle_;
	Point3d position_;
	CONSTRAINT_TYPE type_;

public:
	FixConstraint(const FixConstraint& fixConstraint);
	FixConstraint(Particle& particle, const Point3d& position);
	virtual ~FixConstraint();

	virtual void apply(float step);

	Particle& getParticle() const;
	Point3d getPosition() const;

	virtual CONSTRAINT_TYPE getType() const;

};