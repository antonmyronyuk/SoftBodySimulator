#include "ParticlesSym.h"
#include "FixConstraint.h"
#include "DistanceConstraint.h"
#include "BendConstraint.h"
#include <math.h>

ParticlesSym::ParticlesSym(): 
	gravity_(Point3d(0.f, 0.98f, 0.f)), 
	friction_(0.99f), 
	groundFriction_(0.7f), 
	widht_(200.f), 
	height_(200.f), 
	depth_(200.f) {
}

ParticlesSym::~ParticlesSym() {
}

void ParticlesSym::setGravity(const Point3d& gravity) {
	gravity_.set(gravity);
}

void ParticlesSym::setFriction(float friction) {
	friction_ = friction;
}

void ParticlesSym::setGroundFriction(float friction) {
	groundFriction_ = friction;
}

size_t ParticlesSym::addParticle(float x, float y, float z, float mass) {
	particles_.push_back(Particle(Point3d(x, y, z), mass));
	return particles_.size() - 1;
}

void ParticlesSym::setParticle(size_t ind, Point3d p) {
	if (ind >= particles_.size() || ind < 0) {
		return;
	}
	particles_[ind] = Particle(p, particles_[ind].mass);
}

void ParticlesSym::addDistanceConstraint(unsigned int particleInd1, unsigned int particleInd2, float stiffness, float distance) {
	constraints_.push_back(new DistanceConstraint(particles_[particleInd1], particles_[particleInd2], stiffness, distance));
}

void ParticlesSym::addFixConstraint(unsigned int particleInd, const Point3d& position) {
	constraints_.push_back(new FixConstraint(particles_[particleInd], position));
}

void ParticlesSym::disableFixConstraints() {
	size_t i = constraints_.size() - 1;
	while (i >= 0 && constraints_[i]->getType() == eFix) {
		auto temp = constraints_[i];
		delete temp;
		constraints_.pop_back();
		--i;
	}
}

void ParticlesSym::addBandConstraint(unsigned int particleInd1, unsigned int particleInd2, unsigned int particleInd3, unsigned int particleInd4, float f0) {
	constraints_.push_back(new BendConstraint(particles_[particleInd1], particles_[particleInd2], particles_[particleInd3], particles_[particleInd4], f0));
}

void ParticlesSym::setWorldSize(float width, float height, float depth) {
	widht_ = width;
	height_ = height;
	depth_ = depth;
}

void ParticlesSym::step(int steps) {

	if (particles_.empty()) {
		return;
	}

	float step = 1.f / (float)steps;
	float friction = powf(friction_, step);
	float groundFriction = powf(groundFriction_, step);

	for (int st = 0; st < steps; ++st) {

		for (unsigned int i = 0; i < particles_.size(); ++i) {
			Point3d velocity = (particles_[i].position - particles_[i].lastPosition) * friction;
			if (fabsf(particles_[i].position.Y() + height_ / 2.f) < 0.001f) {
				velocity *= groundFriction;
			}

			if (velocity.length() < 0.00000001f) {
				velocity.set(0.f, 0.f, 0.f);
			}

			// save position
			particles_[i].lastPosition.set(particles_[i].position);

			// add gravity
			particles_[i].position += gravity_ * step * step;

			// inertia
			particles_[i].position += velocity;

			// forces
			float len = m_forceCenter.distance(particles_[i].position);
			if (len < 1.f) {
				len = 1.f;
			}
			particles_[i].position += (particles_[i].position - m_forceCenter) * powf(1 / len, 3.f) * m_forcePower * step * step;
		}


		for (unsigned int i = 0; i < constraints_.size(); ++i) {
			constraints_[i]->apply(step);
		}

		// check if particles not out the screen
		for (unsigned int i = 0; i < particles_.size(); ++i) {
			if (particles_[i].position.X() < -widht_ / 2.f)    particles_[i].position.setX(-widht_ / 2.f);
			if (particles_[i].position.X() > widht_ / 2.f) particles_[i].position.setX(widht_ / 2.f);
			if (particles_[i].position.Y() < -height_ / 2.f)     particles_[i].position.setY(-height_ / 2.f);
			if (particles_[i].position.Y() > height_ / 2.f) particles_[i].position.setY(height_ / 2.f);
			if (particles_[i].position.Z() < -depth_ / 2.f)     particles_[i].position.setZ(-depth_ / 2.f);
			if (particles_[i].position.Z() > depth_ / 2.f) particles_[i].position.setZ(depth_ / 2.f);
		}
	}
}

unsigned int ParticlesSym::getParticesCount() const {
	return particles_.size();
}

Point3d ParticlesSym::getParticlePos(unsigned int ind) const {
	if (ind >= particles_.size())
		return Point3d();

	return particles_[ind].position;
}

void ParticlesSym::turnForceOn(const Point3d& p) {
	m_forceCenter = p;
	m_forcePower = 5360.f;
}

void ParticlesSym::turnForceOff() {
	m_forcePower = 0.f;
}