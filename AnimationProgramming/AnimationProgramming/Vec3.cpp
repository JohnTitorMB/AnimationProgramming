#include "stdafx.h"

#include "Vec3.h"

#include <math.h>
#include <algorithm>
#include <string>
#include <iomanip>

#pragma region Shorthands
Vec3 Vec3::Zero()
{
	return Vec3(0.f, 0.f, 0.f);
}

Vec3 Vec3::Left()
{
	return Vec3(-1.f, 0.f, 0.f);
}

Vec3 Vec3::Right()
{
	return Vec3(1.f, 0.f, 0.f);
}

Vec3 Vec3::Down()
{
	return Vec3(0.f, -1.f, 0.f);
}

Vec3 Vec3::Up()
{
	return Vec3(0.f, 1.f, 0.f);
}

Vec3 Vec3::Back()
{
	return Vec3(0.f, 0.f, -1.f);
}

Vec3 Vec3::Forward()
{
	return Vec3(0.f, 0.f, 1.f);
}

Vec3 Vec3::One()
{
	return Vec3(1.f, 1.f, 1.f);
}
#pragma endregion

#pragma region Constructors/destructor
Vec3::Vec3() : m_x{ 0.f }, m_y{ 0.f }, m_z{ 0.f }
{}

Vec3::Vec3(float x, float y, float z) : m_x{ x }, m_y{ y }, m_z{ z }
{}

Vec3::Vec3(const Vec3& vec) : m_x{ vec.m_x }, m_y{ vec.m_y }, m_z{ vec.m_z }
{}

Vec3::~Vec3()
{}
#pragma endregion

#pragma region Tools
Vec3 Vec3::Lerp(const Vec3& firstVec, const Vec3& secondVec, float ratio)
{
	ratio = fmax(0.f, (fmin(ratio, 1.f)));
	Vec3 lerpedVec((firstVec * (1.f - ratio)) + (secondVec * ratio));
	return lerpedVec;
}

float Vec3::GetAngle(const Vec3& firstVec, const Vec3& secondVec)
{
	float angle{ acos((firstVec.DotProduct(secondVec)) / sqrt(firstVec.GetMagnitudeSQ() * secondVec.GetMagnitudeSQ())) };
	return angle;
}

float Vec3::GetAngleInDegrees(const Vec3& firstVec, const Vec3& secondVec)
{
	float angle{ Vec3::GetAngle(firstVec, secondVec) };
	angle *= 180.f / (float)M_PI;
	return angle;
}

Vec3& Vec3::Shortest(Vec3& firstVec, Vec3& secondVec)
{
	return (firstVec.GetMagnitudeSQ() < secondVec.GetMagnitudeSQ()) ? firstVec : secondVec;
}

Vec3& Vec3::Longest(Vec3& firstVec, Vec3& secondVec)
{
	return (firstVec.GetMagnitudeSQ() > secondVec.GetMagnitudeSQ()) ? firstVec : secondVec;
}

Vec3 Vec3::Min(const Vec3& firstVec, const Vec3& secondVec)
{
	Vec3 min(Vec3::Zero());
	min.m_x = firstVec.m_x < secondVec.m_x ? firstVec.m_x : secondVec.m_x;
	min.m_y = firstVec.m_y < secondVec.m_y ? firstVec.m_y : secondVec.m_y;
	min.m_z = firstVec.m_z < secondVec.m_z ? firstVec.m_z : secondVec.m_z;
	return min;
}

Vec3 Vec3::Max(const Vec3& firstVec, const Vec3& secondVec)
{
	Vec3 max(Vec3::Zero());
	max.m_x = firstVec.m_x > secondVec.m_x ? firstVec.m_x : secondVec.m_x;
	max.m_y = firstVec.m_y > secondVec.m_y ? firstVec.m_y : secondVec.m_y;
	max.m_z = firstVec.m_z > secondVec.m_z ? firstVec.m_z : secondVec.m_z;
	return max;
}

float Vec3::Distance(const Vec3& firstVertex, const Vec3& secondVertex)
{
	float distance{ sqrt(DistanceSQ(firstVertex, secondVertex)) };

	return distance;
}

float Vec3::DistanceSQ(const Vec3& firstVertex, const Vec3& secondVertex)
{
	Vec3 tempVec(secondVertex - firstVertex);
	float distanceSQ{ tempVec.GetMagnitudeSQ() };

	return distanceSQ;
}

#pragma endregion

#pragma region Operators
Vec3 Vec3::operator+(const Vec3& vec) const
{
	Vec3 vecResult(
		m_x + vec.m_x,
		m_y + vec.m_y,
		m_z + vec.m_z
	);

	return vecResult;
}

Vec3& Vec3::operator+=(const Vec3& vec)
{
	*this = *this + vec;

	return *this;
}

Vec3 Vec3::operator-() const
{
	Vec3 vecResult(
		-m_x,
		-m_y,
		-m_z
	);

	return vecResult;
}

Vec3 Vec3::operator-(const Vec3& vec) const
{
	Vec3 vecResult(
		m_x - vec.m_x,
		m_y - vec.m_y,
		m_z - vec.m_z
	);

	return vecResult;
}

Vec3& Vec3::operator-=(const Vec3& vec)
{
	*this = *this - vec;

	return *this;
}

Vec3 Vec3::operator*(float factor) const
{
	Vec3 vecResult(
		m_x * factor,
		m_y * factor,
		m_z * factor
	);

	return vecResult;
}

Vec3& Vec3::operator*=(float factor)
{
	*this = *this * factor;

	return *this;
}

Vec3 Vec3::operator/(float divisor) const
{
	if (divisor == 0.f)
		return Vec3::Zero();

	Vec3 vecResult(
		m_x / divisor,
		m_y / divisor,
		m_z / divisor
	);

	return vecResult;
}

Vec3& Vec3::operator/=(float divisor)
{
	*this = *this / divisor;

	return *this;
}

Vec3& Vec3::operator=(const Vec3& vec)
{
	m_x = vec.m_x;
	m_y = vec.m_y;
	m_z = vec.m_z;

	return *this;
}

bool Vec3::operator==(const Vec3& vec) const
{
	bool sameXValue{ m_x == vec.m_x };
	bool sameYValue{ m_y == vec.m_y };
	bool sameZValue{ m_z == vec.m_z };
	bool sameVectors{ (sameXValue && sameYValue && sameZValue) };

	return sameVectors;
}

bool Vec3::operator!=(const Vec3& vec) const
{
	return !(*this == vec);
}

float& Vec3::operator[](int index)
{
	index = std::max(0, std::min(index, 2));

	switch (index)
	{
	case 0:
		return m_x;
		break;
	case 1:
		return m_y;
		break;
	default:
		return m_z;
		break;
	}
}
#pragma endregion

#pragma region Operations
void Vec3::Normalize()
{
	float magnitude = GetMagnitude();

	*this /= magnitude;
}

Vec3 Vec3::GetNormalized() const
{
	Vec3 normalizedVec(*this);
	normalizedVec.Normalize();

	return normalizedVec;
}

float Vec3::GetMagnitude() const
{
	return sqrt(GetMagnitudeSQ());
}

float Vec3::GetMagnitudeSQ() const
{
	return (m_x * m_x) + (m_y * m_y) + (m_z * m_z);
}

void Vec3::SetMagnitude(float magnitude)
{
	Normalize();
	*this *= magnitude;
}

float Vec3::DotProduct(const Vec3& vec) const
{
	return (m_x * vec.m_x) + (m_y * vec.m_y) + (m_z * vec.m_z);
}

Vec3 Vec3::CrossProduct(const Vec3& vec) const
{
	Vec3 normalVec(
		(m_y * vec.m_z) - (m_z * vec.m_y),
		(m_z * vec.m_x) - (m_x * vec.m_z),
		(m_x * vec.m_y) - (m_y * vec.m_x)
	);

	return normalVec;
}
#pragma endregion

#pragma region Console output
Vec3::operator std::string() const
{
	std::string str = "Vec3 : ( ";
	str += std::to_string(m_x) + " ; ";
	str += std::to_string(m_y) + " ; ";
	str += std::to_string(m_z) + " )";

	return str;
}

std::ostream& operator<<(std::ostream& stream, const Vec3& vec)
{
	stream << "Vec3 : ( " << std::fixed << std::setprecision(2) << vec.m_x << " ; " << vec.m_y << " ; " << vec.m_z << " )";

	return stream;
}
#pragma endregion