#ifndef __KEYFRAME_H__
#define __KEYFRAME_H__

#include "Transform.h"

class KeyFrame
{
	Vec3 m_localPosition;
	Quaternion m_localRotation;
	Vec3 m_globalPosition;
	Quaternion m_globalRotation;

	Vec3 m_localPositionAnimate;
	Quaternion m_localRotationAnimate;
	Vec3 m_globalPositionAnimate;
	Quaternion m_globalRotationAnimate;
	
	Transform m_transform;

	const KeyFrame* m_parent;

public:
	KeyFrame();
	KeyFrame(	const Vec3& localPosition, 
				const Quaternion& localRotation, 
				const Vec3& localPositionAnimate, 
				const Quaternion& localRotationAnimate, 
				const KeyFrame* parent);
	KeyFrame(const KeyFrame& keyFrame) = delete;
	~KeyFrame();
	KeyFrame& operator=(const KeyFrame& keyFrame) = delete;
	KeyFrame(KeyFrame&& keyFrame) = delete;

	const Vec3& GetLocalPosition() const;
	const Quaternion& GetLocalRotation() const;

	const Vec3& GetGlobalPosition() const;
	const Quaternion& GetGlobalRotation() const;

	const Vec3& GetLocalPositionAnimate() const;
	const Quaternion& GetLocalRotationAnimate() const;

	const Vec3& GetGlobalPositionAnimate() const;
	const Quaternion& GetGlobalRotationAnimate() const;

	const Transform& GetTransform() const;

	void Interpolate(const Quaternion& startQ, const Quaternion& endQ, const Vec3& startVec, const Vec3& endVec, float percent);

};

#endif
