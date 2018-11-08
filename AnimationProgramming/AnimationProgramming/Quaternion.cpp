#include "stdafx.h"

#include "Quaternion.h"
#include "math.h"

#include <string>
#include <iomanip>

Quaternion::Quaternion() : m_w{ 0.0f }, m_vec{ Vec3::Zero() }
{}

Quaternion::Quaternion(float w, float x, float y, float z) : m_w{ w }, m_vec(x, y, z)
{}

Quaternion::Quaternion(float w, const Vec3& vec) : m_w{ w }, m_vec{ vec }
{}

Quaternion::Quaternion(const Quaternion& q) : m_w{ q.m_w }, m_vec{ q.m_vec }
{}

Quaternion::~Quaternion()
{}

Quaternion& Quaternion::operator=(const Quaternion& q)
{
	m_w = q.m_w;
	m_vec = q.m_vec;

	return *this;
}

Quaternion Quaternion::Identity()
{
	return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
}

Quaternion Quaternion::Lerp(const Quaternion& startQ, const Quaternion& endQ, float percent)
{
	Quaternion q(startQ*(1 - percent) + endQ*percent);
	q.Normalize();
	return q;
}

Quaternion Quaternion::SLerp(const Quaternion& q1, const Quaternion& q2, float t)
{
	Quaternion q3;
	float dot{ q1.DotProduct(q2) };

	/*	dot = cos(theta)
	if (dot < 0), q1 and q2 are more than 90 degrees apart,
	so we can invert one to reduce spinning	*/
	if (dot < 0)
	{
		dot = -dot;
		q3 = -q2;
	}
	else q3 = q2;

	if (dot < 0.95f)
	{
		float angle{ acosf(dot) };
		return (q1*sinf(angle*(1 - t)) + q3*sinf(angle*t)) / sinf(angle);
	}
	else // if the angle is small, use linear interpolation								
		return Lerp(q1, q3, t);
}

bool Quaternion::operator==(const Quaternion& q) const
{
	return(m_w == q.m_w && m_vec == q.m_vec);
}

bool Quaternion::operator!=(const Quaternion& q) const
{
	return !(*this == q);
}

Quaternion Quaternion::operator+(const Quaternion& q) const
{
	return Quaternion(m_w + q.m_w, m_vec + q.m_vec);
}

Quaternion Quaternion::operator-(const Quaternion& q) const
{
	return Quaternion(m_w - q.m_w, m_vec - q.m_vec);
}

Quaternion Quaternion::operator-() const
{
	return Quaternion(-m_w, -m_vec);
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
	//WARNING : (*this * q) != (q * (*this))
	
	Quaternion resQ;
	
	resQ.m_w = (m_w*q.m_w - m_vec.DotProduct(q.m_vec));
	
	resQ.m_vec.m_x = (m_w*q.m_vec.m_x + m_vec.m_x*q.m_w + m_vec.m_y*q.m_vec.m_z - m_vec.m_z*q.m_vec.m_y);
	resQ.m_vec.m_y = (m_w*q.m_vec.m_y - m_vec.m_x*q.m_vec.m_z + m_vec.m_y*q.m_w + m_vec.m_z*q.m_vec.m_x);
	resQ.m_vec.m_z = (m_w*q.m_vec.m_z + m_vec.m_x*q.m_vec.m_y - m_vec.m_y*q.m_vec.m_x + m_vec.m_z*q.m_w);

	return resQ;
}

Quaternion Quaternion::operator/(const Quaternion& q) const
{
	Quaternion resQ(q);
	resQ.Inverse();
	return (*this) * resQ;
}

Quaternion Quaternion::operator*(float f) const
{
	return Quaternion(m_w*f, m_vec*f);
}

Quaternion Quaternion::operator/(float f) const
{
	return Quaternion(m_w/f, m_vec/f);
}

Quaternion& Quaternion::operator*=(float f)
{
	m_vec *= f;
	m_w *= f;

	return *this;
}

Quaternion& Quaternion::operator/=(float f)
{
	m_vec /= f;
	m_w /= f;

	return *this;
}

float  Quaternion::Length() const
{
	return sqrtf(m_w * m_w + m_vec.DotProduct(m_vec));	
}

float Quaternion::SquaredLength() const
{
	return m_w*m_w + m_vec.DotProduct(m_vec);
}

float Quaternion::DotProduct(const Quaternion& q) const
{
	Quaternion q1{ *this };
	return q1.m_w * q.m_w + q1.m_vec.m_x * q.m_vec.m_x + q1.m_vec.m_y * q.m_vec.m_y + q1.m_vec.m_z * q.m_vec.m_z;
}

Quaternion Quaternion::Conjugate() const
{
	return(Quaternion(m_w, -m_vec));
}

Quaternion Quaternion::Inverse() const
{
	Quaternion cQ{ Conjugate() };
	float l{ SquaredLength() };
	Quaternion invQ{ cQ / l };

	return invQ;
}

void Quaternion::Normalize()
{
	*this /= Length();
}

Vec3 Quaternion::Rotate(const Vec3& vec)
{	
	Quaternion p(0, vec);
	Quaternion q{ *this };

	return (q*p*q.Inverse()).m_vec;
}

std::ostream& operator<<(std::ostream& stream, const Quaternion& quat)
{
	stream << "Quaternion : ( " << std::fixed << std::setprecision(2) << quat.m_w << " ; " << quat.m_vec.m_x << " ; " << quat.m_vec.m_y << " ; " << quat.m_vec.m_z << " )";

	return stream;
}
