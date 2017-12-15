#pragma once

#include "Point3d.h"
#include "Particle.h"
#include "ParticlesSym.h"
#include <vector>

class SoftBody {

	std::vector<size_t> m_particleInds;
	std::vector<size_t> m_inds;
	std::vector<Point3d> m_normals;
	std::vector<int> m_normsCount;
	float m_colorR;
	float m_colorG;
	float m_colorB;
	bool m_solidDraw;
	float m_stiffness;
	bool m_smoothed;
	ParticlesSym* m_sym;

public:
	SoftBody(ParticlesSym* sym);
	~SoftBody();

	void setMesh(const std::vector<Point3d>& points, const std::vector<size_t>& inds, bool smoothed, const std::vector<std::pair<size_t, size_t>>& links);
	void addFix(int pointInd, float x, float y, float z);
	void disableFix();
	void setPointPos(int pointInd, float x, float y, float z);
	void setStiffness(float stiffness);
	void setColor(float r, float g, float b);
	void setRenderMode(bool solid);
	void renderSmoothed();
	void renderNotSmoothed();
	void render();
	void renderLines();
	void renderCube();

};