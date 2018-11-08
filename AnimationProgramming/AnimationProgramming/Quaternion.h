#ifndef  __QUATERNION_H__
#define  __QUATERNION_H__

#include "Vec3.h"

struct Quaternion
{
	float m_w;
	Vec3 m_vec;
	
	Quaternion();
	Quaternion(float w, float x, float y, float z);
	Quaternion(float w, const Vec3& vec);
	Quaternion(const Quaternion& q);
	~Quaternion();
	Quaternion& operator=(const Quaternion& q);
	Quaternion(Quaternion&& q) = default;

	static Quaternion Identity();
	static Quaternion Lerp(const Quaternion& startQ, const Quaternion& endQ, float percent);
	static Quaternion SLerp(const Quaternion& q1, const Quaternion& q2, float t);

	bool operator==(const Quaternion& q) const;
	bool operator!=(const Quaternion& q) const;

	Quaternion operator+(const Quaternion& q) const;
	Quaternion operator-(const Quaternion& q) const;
	Quaternion operator-() const;
	Quaternion operator*(const Quaternion& q) const;
	Quaternion operator/(const Quaternion& q) const;
	

	Quaternion operator*(float f) const;
	Quaternion operator/(float f) const;
	Quaternion& operator*=(float f);
	Quaternion& operator/=(float f);
	
	float Length() const;
	float SquaredLength() const;
	float DotProduct(const Quaternion& q) const;

	Quaternion Conjugate() const;
	Quaternion Inverse() const;
	void Normalize();

	Vec3 Rotate(const Vec3& vec);
};
std::ostream& operator<<(std::ostream&, const Quaternion&);

#endif
