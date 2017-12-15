#include "SoftBody.h"
#include <iostream>
#include <glut.h>

SoftBody::SoftBody(ParticlesSym* sym): 
	m_sym(sym), 
	m_colorR(1.0f), 
	m_colorG(1.0f), 
	m_colorB(1.0f), 
	m_stiffness(0.9f), 
	m_solidDraw(true), 
	m_smoothed(false) {
}

SoftBody::~SoftBody() {
}

void SoftBody::setPointPos(int pointInd, float x, float y, float z) {
	m_sym->setParticle(pointInd, Point3d(x, y, z));
}

void SoftBody::setMesh(const std::vector<Point3d>& points, const std::vector<size_t>& inds, bool smoothed, const std::vector<std::pair<size_t, size_t>>& links)
{
	m_smoothed = smoothed;
	m_inds = inds;
	m_particleInds.clear();
	for (size_t i = 0; i < points.size(); ++i) {
		m_particleInds.push_back(m_sym->addParticle(points[i].X(), points[i].Y(), points[i].Z(), (rand() % 1000 + 500) / 500.f));
	}

	for (size_t i = 0; i < links.size(); ++i) {
		m_sym->addDistanceConstraint(m_particleInds[links[i].first], m_particleInds[links[i].second], m_stiffness);
	}

	if (m_smoothed) {
		m_normals.resize(points.size());
		m_normsCount.resize(points.size());
	}
}

void SoftBody::addFix(int pointInd, float x, float y, float z) {
	m_sym->addFixConstraint(m_particleInds[pointInd], Point3d(x, y, z));
}

void SoftBody::disableFix() {
	m_sym->disableFixConstraints();
}

void SoftBody::setStiffness(float stiffness) {
	m_stiffness = stiffness;
}

void SoftBody::setColor(float r, float g, float b) {
	m_colorR = r;
	m_colorG = g;
	m_colorB = b;
}

void SoftBody::setRenderMode(bool solid) {
	m_solidDraw = solid;
}

Point3d calcNormal(const Point3d& p1, const Point3d& p2, const Point3d& p3) {

	Point3d u(p2.X() - p1.X(), p2.Y() - p1.Y(), p2.Z() - p1.Z());
	Point3d v(p3.X() - p1.X(), p3.Y() - p1.Y(), p3.Z() - p1.Z());

	Point3d n(
		u.Y() * v.Z() - u.Z() * v.Y(),
		-(u.X() * v.Z() - u.Z() * v.X()),
		u.X() * v.Y() - u.Y() * v.X()
	);

	n /= -n.length();
	return n;
}

void SoftBody::render() {
	if (m_smoothed) {
		renderSmoothed();
	}
	else {
		renderNotSmoothed();
	}
}

void SoftBody::renderSmoothed() {

	size_t count = m_inds.size() / 3;
	for (size_t i = 0; i < count; ++i) {
		Point3d p1 = m_sym->getParticlePos(m_particleInds[m_inds[i * 3]]);
		Point3d p2 = m_sym->getParticlePos(m_particleInds[m_inds[i * 3 + 1]]);
		Point3d p3 = m_sym->getParticlePos(m_particleInds[m_inds[i * 3 + 2]]);
		Point3d n = calcNormal(p1, p2, p3);
		m_normals[m_inds[i * 3]] += n;
		m_normals[m_inds[i * 3 + 1]] += n;
		m_normals[m_inds[i * 3 + 2]] += n;
	}

	for (size_t i = 0; i < m_normals.size(); ++i) {
		m_normals[i] /= m_normals[i].length();
	}

	glColor3f(m_colorR, m_colorG, m_colorB);
	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < count; ++i) {
		Point3d p1 = m_sym->getParticlePos(m_particleInds[m_inds[i * 3]]);
		Point3d p2 = m_sym->getParticlePos(m_particleInds[m_inds[i * 3 + 1]]);
		Point3d p3 = m_sym->getParticlePos(m_particleInds[m_inds[i * 3 + 2]]);

		//Point3d n = calcNormal(p1, p2, p3);
		Point3d n = m_normals[m_inds[i * 3]];
		glNormal3f(n.X(), n.Y(), n.Z());
		glVertex3f(p1.X(), p1.Y(), p1.Z());

		n = m_normals[m_inds[i * 3 + 1]];
		glNormal3f(n.X(), n.Y(), n.Z());
		glVertex3f(p2.X(), p2.Y(), p2.Z());

		n = m_normals[m_inds[i * 3 + 2]];
		glNormal3f(n.X(), n.Y(), n.Z());
		glVertex3f(p3.X(), p3.Y(), p3.Z());
	}
	glEnd();

	for (size_t i = 0; i < m_normals.size(); ++i) {
		m_normals[i] = Point3d(0.f, 0.f, 0.f);
	}
}

void SoftBody::renderNotSmoothed() {
	size_t count = m_inds.size() / 3;
	glColor3f(m_colorR, m_colorG, m_colorB);
	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < count; ++i) {
		Point3d p1 = m_sym->getParticlePos(m_particleInds[m_inds[i * 3]]);
		Point3d p2 = m_sym->getParticlePos(m_particleInds[m_inds[i * 3 + 1]]);
		Point3d p3 = m_sym->getParticlePos(m_particleInds[m_inds[i * 3 + 2]]);

		Point3d n = calcNormal(p1, p2, p3);
		glNormal3f(n.X(), n.Y(), n.Z());
		glVertex3f(p1.X(), p1.Y(), p1.Z());

		glNormal3f(n.X(), n.Y(), n.Z());
		glVertex3f(p2.X(), p2.Y(), p2.Z());

		glNormal3f(n.X(), n.Y(), n.Z());
		glVertex3f(p3.X(), p3.Y(), p3.Z());
	}
	glEnd();
}

void SoftBody::renderLines() {
	glBegin(GL_LINES);
	Point3d p;
	p = m_sym->getParticlePos(0);
	glVertex3f(p.X(), p.Y(), p.Z());
	p = m_sym->getParticlePos(1);
	glVertex3f(p.X(), p.Y(), p.Z());

	p = m_sym->getParticlePos(1);
	glVertex3f(p.X(), p.Y(), p.Z());
	p = m_sym->getParticlePos(2);
	glVertex3f(p.X(), p.Y(), p.Z());

	p = m_sym->getParticlePos(2);
	glVertex3f(p.X(), p.Y(), p.Z());
	p = m_sym->getParticlePos(3);
	glVertex3f(p.X(), p.Y(), p.Z());

	p = m_sym->getParticlePos(3);
	glVertex3f(p.X(), p.Y(), p.Z());
	p = m_sym->getParticlePos(0);
	glVertex3f(p.X(), p.Y(), p.Z());

	p = m_sym->getParticlePos(4);
	glVertex3f(p.X(), p.Y(), p.Z());
	p = m_sym->getParticlePos(5);
	glVertex3f(p.X(), p.Y(), p.Z());

	p = m_sym->getParticlePos(5);
	glVertex3f(p.X(), p.Y(), p.Z());
	p = m_sym->getParticlePos(6);
	glVertex3f(p.X(), p.Y(), p.Z());

	p = m_sym->getParticlePos(6);
	glVertex3f(p.X(), p.Y(), p.Z());
	p = m_sym->getParticlePos(7);
	glVertex3f(p.X(), p.Y(), p.Z());

	p = m_sym->getParticlePos(7);
	glVertex3f(p.X(), p.Y(), p.Z());
	p = m_sym->getParticlePos(4);
	glVertex3f(p.X(), p.Y(), p.Z());

	p = m_sym->getParticlePos(0);
	glVertex3f(p.X(), p.Y(), p.Z());
	p = m_sym->getParticlePos(4);
	glVertex3f(p.X(), p.Y(), p.Z());

	p = m_sym->getParticlePos(1);
	glVertex3f(p.X(), p.Y(), p.Z());
	p = m_sym->getParticlePos(5);
	glVertex3f(p.X(), p.Y(), p.Z());

	p = m_sym->getParticlePos(2);
	glVertex3f(p.X(), p.Y(), p.Z());
	p = m_sym->getParticlePos(6);
	glVertex3f(p.X(), p.Y(), p.Z());

	p = m_sym->getParticlePos(3);
	glVertex3f(p.X(), p.Y(), p.Z());
	p = m_sym->getParticlePos(7);
	glVertex3f(p.X(), p.Y(), p.Z());

	glEnd();

}

void SoftBody::renderCube() {
	size_t count = m_inds.size() / 3;
	//std::cout << count << std::endl;
	glColor3f(m_colorR, m_colorG, m_colorB);
	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < count; i+= 2) {
		std::vector<Point3d> pts;
		for (size_t j = 0; j < 6; ++j) {
			pts.push_back(m_sym->getParticlePos(m_particleInds[m_inds[i * 3 + j]]));
		}

		//normal for cube face
		Point3d n = (calcNormal(pts[0], pts[1], pts[2]) + calcNormal(pts[3], pts[4], pts[5])) / 2;
		for (size_t j = 0; j < 6; ++j) {
			//render 2 triangles with mutal normal
			glNormal3f(n.X(), n.Y(), n.Z());
			glVertex3f(pts[j].X(), pts[j].Y(), pts[j].Z());
		}
	}
	glEnd();
}
