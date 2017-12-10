#pragma once

#include "Constraint.h"

class BendConstraint : public Constraint {
	Particle& particle1_;
	Particle& particle2_;
	Particle& particle3_;
	Particle& particle4_;
	float f0_;
	CONSTRAINT_TYPE type_;
public:
	BendConstraint(const BendConstraint& BendConstraint);
	BendConstraint(Particle& particle1, Particle& particle2, Particle& particle3, Particle& particle4, float f0);
	virtual ~BendConstraint();

	virtual void apply(float step);

	Particle& getParticle1() const;
	Particle& getParticle2() const;
	Particle& getParticle3() const;
	Particle& getParticle4() const;
	float getF0() const;

	virtual CONSTRAINT_TYPE getType() const;

};

