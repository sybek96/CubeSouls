#pragma once
#include "Vector3.h"
#include <math.h>

class Matrix3
{
	friend Vector3 operator*(const Matrix3&, const Vector3&);
	friend Matrix3 operator+(const Matrix3&, const Matrix3&);
	friend Matrix3 operator-(const Matrix3&, const Matrix3&);
	friend Matrix3 operator*(const Matrix3&, const double&);
	friend Matrix3 operator*(const Matrix3&, const Matrix3&);

public:
	enum class Axis{X,Y,Z};
	Matrix3();
	Matrix3(Vector3, Vector3, Vector3);
	Matrix3(double, double, double, double, double, double, double, double, double);
	Vector3 Row(int) const;
	Vector3 Column(int) const;
	static Matrix3 transpose(const Matrix3&);
	double determinant() const;
	static Matrix3 inverse(const Matrix3&);
	static Matrix3 rotation(const Axis&, const int&);
	static Vector3 translate(Vector3&,float&,Axis&);
	static Matrix3 scale(const double&, const double&, const double& dz = 1);
private:
	double m_a11;
	double m_a12;
	double m_a13;
	double m_a21;
	double m_a22;
	double m_a23;
	double m_a31;
	double m_a32;
	double m_a33;
};

