#pragma once

#include "Point3d.h"
#include "Particle.h"
#include "Constraint.h"
#include <vector>

class ParticlesSym {

	float widht_;
	float height_;
	float depth_;
	Point3d gravity_;
	float friction_;
	float groundFriction_;
	std::vector<Particle> particles_;
	std::vector<Constraint*> constraints_;
	float m_forcePower;
	Point3d m_forceCenter;

public:
	ParticlesSym();
	~ParticlesSym();

	void setGravity(const Point3d& gravity);
	void setFriction(float friction);
	void setGroundFriction(float friction);
	void setWorldSize(float width, float height, float depth);

	size_t addParticle(float x, float y, float z, float mass = 1.f);
	void setParticle(size_t ind, Point3d p);
	void addDistanceConstraint(unsigned int particleInd1, unsigned int particleInd2, float stiffness, float distance = 0.f);
	void addFixConstraint(unsigned int particleInd, const Point3d& position);
	void disableFixConstraints();
	void addBandConstraint(unsigned int particleInd1, unsigned int particleInd2, unsigned int particleInd3, unsigned int particleInd4, float f0 = 100000.f);

	void step(int steps);

	unsigned int getParticesCount() const;
	Point3d getParticlePos(unsigned int ind) const;

	void turnForceOn(const Point3d& p);
	void turnForceOff();

};