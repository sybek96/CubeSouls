#pragma once
#include <math.h>
#include <string>

class Vector3
{
	friend Vector3 operator+(const Vector3&, const Vector3&);
	friend Vector3 operator-(const Vector3&, const Vector3&);
	friend double operator*(const Vector3&, const Vector3&);
	friend Vector3 operator*(const Vector3&, const double&);
	friend Vector3 operator*(const Vector3&, const float&);
	friend Vector3 operator*(const Vector3&, const int&);
	friend Vector3 operator^(const Vector3&, const Vector3&);
public:
	Vector3();
	Vector3(double, double, double);
	double length();
	double lengthSquared();
	void normalise();
	Vector3 operator- () const;
	std::string toString();
	double getX() const;
	double getY() const;
	double getZ() const;
private:
	double m_x;
	double m_y;
	double m_z;
};

