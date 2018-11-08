#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "Quaternion.h"

class Transform
{
private:
	float m_transform[16];

public:
	Transform();
	Transform(	const Vec3& globalPosition, 
				const Quaternion& globalRotation, 
				const Vec3& globalPositionAnimate, 
				const Quaternion& globalRotationAnimate);
	Transform(const Transform& transform) = default;
	~Transform();
	Transform& operator=(const Transform& transform) = default;
	Transform(Transform&& transform) = default;

	const float* GetTransform() const;
};

#endif

