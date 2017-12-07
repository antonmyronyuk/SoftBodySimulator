#include "Point3d.h"
#include <math.h>
#include "BendConstraint.h"

BandConstraint::BandConstraint(const BandConstraint& bandConstraint): 
	particle1_(bandConstraint.particle1_),
	particle2_(bandConstraint.particle3_), 
	particle3_(bandConstraint.particle3_), 
	particle4_(bandConstraint.particle4_), 
	f0_(bandConstraint.getF0()), 
	type_(eBend) {

	if (bandConstraint.f0_ > 1000.f) {
		Point3d p2 = particle2_.position - particle1_.position;
		Point3d p3 = particle3_.position - particle1_.position;
		Point3d p4 = particle4_.position - particle1_.position;

		Point3d n1 = p2.cross(p3);
		n1 /= n1.length();
		Point3d n2 = p4.cross(p2);
		n2 /= n2.length();

		f0_ = acosf(n1.X() * n2.X() + n1.Y() * n2.Y() + n1.Z() * n2.Z());
	}
}

BandConstraint::BandConstraint(Particle& particle1, Particle& particle2, Particle& particle3, Particle& particle4, float f0): 
	particle1_(particle1), 
	particle2_(particle2), 
	particle3_(particle3), 
	particle4_(particle4), 
	f0_(f0), 
	type_(eBend) {

	if (f0 > 1000.f) {
		Point3d p2 = particle2_.position - particle1_.position;
		Point3d p3 = particle3_.position - particle1_.position;
		Point3d p4 = particle4_.position - particle1_.position;

		Point3d n1 = p2.cross(p3);
		n1 /= n1.length();
		Point3d n2 = p4.cross(p2);
		n2 /= n2.length();

		f0_ = acosf(n1.X() * n2.X() + n1.Y() * n2.Y() + n1.Z() * n2.Z());
	}
}

BandConstraint::~BandConstraint() {
}

void BandConstraint::apply(float step) {
	Point3d p2 = particle2_.position - particle1_.position;
	Point3d p3 = particle3_.position - particle1_.position;
	Point3d p4 = particle4_.position - particle1_.position;

	Point3d n1 = p2.cross(p3);
	n1 /= n1.length();
	Point3d n2 = p4.cross(p2);
	n2 /= n2.length();

	float d = n1.X() * n2.X() + n1.Y() * n2.Y() + n1.Z() * n2.Z();

	Point3d p2p3 = p2.cross(p3);
	float p2p3Len = p2p3.length();

	Point3d p2p4 = p2.cross(p4);
	float p2p4Len = p2p4.length();

	Point3d q3 = (p2.cross(n2) + n1.cross(p2) * d) / p2p3Len;
	Point3d q4 = (p2.cross(n1) + n2.cross(p2) * d) / p2p4Len;
	Point3d q2 = Point3d(0.f, 0.f, 0.f) - ((p3.cross(n2) + n1.cross(p3) * d) / p2p3Len + (p4.cross(n1) + n2.cross(p4) * d) / p2p4Len);
	Point3d q1 = Point3d(0.f, 0.f, 0.f) - q2 - q3 - q4;

	float sd = sqrtf(1.f - d * d) * (acosf(d) - f0_) /
		(particle1_.w * q1.length2() + particle2_.w * q2.length2() + particle3_.w * q3.length2() + particle4_.w * q4.length2());

	particle1_.position -= q1 * particle1_.w * sd;
	particle2_.position -= q2 * particle2_.w * sd;
	particle3_.position -= q3 * particle3_.w * sd;
	particle4_.position -= q4 * particle4_.w * sd;
}

Particle& BandConstraint::getParticle1() const {
	return particle1_;
}

Particle& BandConstraint::getParticle2() const {
	return particle2_;
}

Particle& BandConstraint::getParticle3() const {
	return particle3_;
}

Particle& BandConstraint::getParticle4() const {
	return particle4_;
}

float BandConstraint::getF0() const {
	return f0_;
}

CONSTRAINT_TYPE BandConstraint::getType() const {
	return type_;
}