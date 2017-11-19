#include <iostream>
#include <math.h>
#include "Point3d.h"

Point3d::Point3d() :
	m_x(0.f), 
	m_y(0.f),
	m_z(0.f) 
{}

Point3d::Point3d(float x, float y, float z) : 
	m_x(x), 
	m_y(y),
	m_z(z)
{}

Point3d::Point3d(const Point3d& point) : 
	m_x(point.m_x),
	m_y(point.m_y),
	m_z(point.m_z)
{}

Point3d::~Point3d()
{}

void Point3d::set(const Point3d& point) {
	m_x = point.m_x;
	m_y = point.m_y;
	m_z = point.m_z;
}

void Point3d::set(float x, float y, float z) {
	m_x = x;
	m_y = y;
	m_z = z;
}

void Point3d::setX(float x) {
	m_x = x;
}

void Point3d::setY(float y) {
	m_y = y;
}

void Point3d::setZ(float z) {
	m_z = z;
}

float Point3d::X() const {
	return m_x;
}

float Point3d::Y() const {
	return m_y;
}

float Point3d::Z() const {
	return m_z;
}

Point3d& Point3d::operator=(const Point3d& point) {
	m_x = point.m_x;
	m_y = point.m_y;
	m_z = point.m_z;
	return *this;
}

Point3d& Point3d::operator+=(const Point3d& point) {
	m_x += point.m_x;
	m_y += point.m_y;
	m_z += point.m_z;
	return *this;
}

Point3d Point3d::operator+(const Point3d& point) const {
	return Point3d(
		m_x + point.m_x, 
		m_y + point.m_y, 
		m_z + point.m_z
	);
}

Point3d& Point3d::operator-=(const Point3d& point) {
	m_x -= point.m_x;
	m_y -= point.m_y;
	m_z -= point.m_z;
	return *this;
}

Point3d Point3d::operator-(const Point3d& point) const
{
	return Point3d(
		m_x - point.m_x, 
		m_y - point.m_y, 
		m_z - point.m_z
	);
}

Point3d& Point3d::operator*=(const Point3d& point) {
	m_x *= point.m_x;
	m_y *= point.m_y;
	m_z *= point.m_z;
	return *this;
}

Point3d Point3d::operator*(const Point3d& point) const {
	return Point3d(
		m_x * point.m_x, 
		m_y * point.m_y, 
		m_z * point.m_z
	);
}

Point3d& Point3d::operator+=(float value) {
	m_x += value;
	m_y += value;
	m_z += value;
	return *this;
}

Point3d Point3d::operator+(float value) const {
	return Point3d(
		m_x + value, 
		m_y + value, 
		m_z + value
	);
}

Point3d& Point3d::operator*=(float value) {
	m_x *= value;
	m_y *= value;
	m_z *= value;
	return *this;
}

Point3d Point3d::operator*(float value) const {
	return Point3d(
		m_x * value, 
		m_y * value, 
		m_z * value
	);
}

Point3d& Point3d::operator/=(float value) {
	if (fabs(value) < 0.00000001f) {
		value = 0.00000001f;
	}
	m_x /= value;
	m_y /= value;
	m_z /= value;
	return *this;
}

Point3d Point3d::operator/(float value) const {
	if (fabs(value) < 0.00000001f) {
		value = 0.00000001f;
	}
	return Point3d(
		m_x / value, 
		m_y / value, 
		m_z / value
	);
}

float Point3d::distance(const Point3d& point) const {
	return sqrtf((m_x - point.m_x)*(m_x - point.m_x) 
		+ (m_y - point.m_y)*(m_y - point.m_y) 
		+ (m_z - point.m_z)*(m_z - point.m_z));
}


float Point3d::distance2(const Point3d& point) const {
	return ((m_x - point.m_x)*(m_x - point.m_x) 
		+ (m_y - point.m_y)*(m_y - point.m_y) 
		+ (m_z - point.m_z)*(m_z - point.m_z));
}

float Point3d::length() const {
	return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
}

float Point3d::length2() const {
	return (m_x * m_x + m_y * m_y + m_z * m_z);
}

void Point3d::show() {
	std::cout
		<< m_x << ' '
		<< m_y << ' '
		<< m_z << '\n';
}

Point3d Point3d::cross(const Point3d& point) const {
	return Point3d(
		m_y * point.m_z - m_z * point.m_y,
		m_z * point.m_x - m_x * point.m_z,
		m_x * point.m_y - m_y * point.m_x
	);
}