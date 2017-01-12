#include "Vector3.h"


/// <summary>
/// Default constructor for a vector3
/// </summary>
Vector3::Vector3() :
	m_x(0.0),
	m_y(0.0),
	m_z(0.0)
{
}
/// <summary>
/// constructor for vector3 that takes in 3 doubles as paramaters
/// </summary>
/// <param name="x1">x component of the passed vector</param>
/// <param name="y1">y component of the passed vector</param>
/// <param name="z1">z component of the passed vector</param>
Vector3::Vector3(double x1, double y1, double z1) :
	m_x(x1),
	m_y(y1),
	m_z(z1)
{
}

/// <summary>
/// calculate the length of a vector by multiplying components by itself and adding them
/// x*x + y*y + z*z
/// </summary>
/// <returns>the length of the vector</returns>
double Vector3::length()
{
	return sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z));
}
/// <summary>
/// calcualtes the length squared of the vector
/// x*x + y*y + z*z
/// </summary>
/// <returns>return the length squared</returns>
double Vector3::lengthSquared()
{
	return (m_x * m_x) + (m_y * m_y) + (m_z * m_z);
}
/// <summary>
/// make the length of the vector equal to 1 keeping its direction
/// </summary>
void Vector3::normalise()
{
	if (length() > 0.0)
	{
		double magnitude = length();
		m_x /= magnitude;
		m_y /= magnitude;
		m_z /= magnitude;
	}
}
/// <summary>
/// Overloaded operator that allows to negate a vector
/// </summary>
/// <returns>negated vector</returns>
Vector3 Vector3::operator-() const
{
	return Vector3(-m_x, -m_y, -m_z);
}
/// <summary>
/// A method that returns a string of the vector
/// </summary>
/// <returns>vector as string</returns>
std::string Vector3::toString()
{
	return std::string("( " + std::to_string(m_x) + ", " + std::to_string(m_y) + ", " + std::to_string(m_z) + " )");
}
/// <summary>
/// Returns x component of a vector
/// </summary>
/// <returns>double m_x</returns>
double Vector3::getX() const
{
	return m_x;
}
/// <summary>
/// Returns y component of vector
/// </summary>
/// <returns>double m_y</returns>
double Vector3::getY() const
{
	return m_y;
}
/// <summary>
/// Returns z component of a vector
/// </summary>
/// <returns>double m_z</returns>
double Vector3::getZ() const
{
	return m_z;
}
/// <summary>
/// An overloaded operator that will add 2 vectors together
/// </summary>
/// <param name="V1">lhs</param>
/// <param name="V2">rhs</param>
/// <returns>sum of 2 vectors</returns>
Vector3 operator+(const Vector3& V1, const Vector3& V2)
{
	return Vector3 (V1.getX() + V2.getX(),
					V1.getY() + V2.getY(),
					V1.getZ() + V2.getZ());
}
/// <summary>
/// Overloaded operator that takes away one vector from another
/// </summary>
/// <param name="V1">lhs</param>
/// <param name="V2">rhs</param>
/// <returns>subtraction of 2 vectors</returns>
Vector3 operator-(const Vector3& V1, const Vector3& V2)
{
	return Vector3 (V1.getX() - V2.getX(),
					V1.getY() - V2.getY(),
					V1.getZ() - V2.getZ());
}
/// <summary>
/// overloaded operator to multiply 2 vectors
/// </summary>
/// <param name="V1">lhs</param>
/// <param name="V2">rhs</param>
/// <returns>product of 2 vectors</returns>
double operator*(const Vector3 &V1, const Vector3 &V2)
{
	return (V1.getX() * V2.getX() + V1.getY() * V2.getY() + V1.getZ() * V2.getZ());
}
/// <summary>
/// overloaded operator to allow multiplication of a vector by a double
/// </summary>
/// <param name="V">vector</param>
/// <param name="k">double</param>
/// <returns>product of vector by double</returns>
Vector3 operator*(const Vector3 &V, const double &k)
{
	return Vector3(V.getX() * k, V.getY() * k, V.getZ() * k);
}
/// <summary>
/// overloaded operator to allow multiplication of a vector by a float
/// </summary>
/// <param name="V">vector</param>
/// <param name="k">float</param>
/// <returns>product of vector by float</returns>
Vector3 operator*(const Vector3 &V, const float &k)
{
	return Vector3(V.getX() * k, V.getY() * k, V.getZ() * k);
}
/// <summary>
/// overloaded operator to allow multiplication of a vector by an int
/// </summary>
/// <param name="V">vector</param>
/// <param name="k">int</param>
/// <returns>product of vector by int</returns>
Vector3 operator*(const Vector3 &V, const int &k)
{
	return Vector3(V.getX() * k, V.getY() * k, V.getZ() * k);
}
/// <summary>
/// The cross product of two vectors
/// </summary>
/// <param name="V1">lhs</param>
/// <param name="V2">rhs</param>
/// <returns>cross product</returns>
Vector3 operator^(const Vector3 &V1, const Vector3 &V2)
{
	return Vector3((V1.getY() * V2.getZ()) - (V1.getZ() * V2.getY()), (V1.getZ() * V2.getX()) - (V1.getX() * V2.getZ()), (V1.getX() * V2.getY()) - (V1.getY() * V2.getX()));
}


