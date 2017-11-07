#pragma once

#include "Particle.h"

enum CONSTRAINT_TYPE {
	eDistance = 0,
	eFix,
	eBand
};

class Constraint {
public:
	Constraint() {};
	Constraint(const Constraint& constraint) {};
	virtual ~Constraint() {};

	virtual void apply(float step) = 0;

	virtual CONSTRAINT_TYPE getType() const = 0;

};