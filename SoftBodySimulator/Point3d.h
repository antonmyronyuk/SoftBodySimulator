#pragma once

class Point3d {

	// position
	float m_x;
	float m_y;
	float m_z;

public:
	Point3d();
	Point3d(float x, float y, float z);
	Point3d(const Point3d& point);
	~Point3d();

	void set(const Point3d& point);
	void set(float x, float y, float z);
	void setX(float x);
	void setY(float y);
	void setZ(float z);

	float X() const;
	float Y() const;
	float Z() const;

	Point3d& operator=(const Point3d& point);

	Point3d& operator+=(const Point3d& point);
	Point3d operator+(const Point3d& point) const;
	Point3d& operator-=(const Point3d& point);
	Point3d operator-(const Point3d& point) const;
	Point3d& operator*=(const Point3d& point);
	Point3d operator*(const Point3d& point) const;

	Point3d& operator+=(float value);
	Point3d operator+(float value) const;
	Point3d& operator*=(float value);
	Point3d operator*(float value) const;
	Point3d& operator/=(float value);
	Point3d operator/(float value) const;

	float distance(const Point3d& point) const;
	float distance2(const Point3d& point) const;

	float length() const;
	float length2() const;

	void show();

};