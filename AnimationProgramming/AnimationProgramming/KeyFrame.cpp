#include "stdafx.h"

#include "KeyFrame.h"

KeyFrame::KeyFrame() :
	m_localPosition{ Vec3::Zero() },
	m_localRotation{ Quaternion::Identity() },
	m_globalPosition{ Vec3::Zero() },
	m_globalRotation{ Quaternion::Identity() },
	m_localPositionAnimate{ Vec3::Zero() },
	m_localRotationAnimate{ Quaternion::Identity() },
	m_globalRotationAnimate{ Quaternion::Identity() },
	m_globalPositionAnimate{ Vec3::Zero() },
	m_parent {nullptr}
{}

KeyFrame::KeyFrame(	const Vec3& localPosition, 
					const Quaternion& localRotation, 
					const Vec3& localPositionAnimate, 
					const Quaternion& localRotationAnimate, 
					const KeyFrame* parent) :

	m_localPosition{ localPosition },
	m_localRotation{ localRotation },
	m_localPositionAnimate{ localPositionAnimate },
	m_localRotationAnimate{ localRotationAnimate },
	m_parent{ parent }
{
	if (parent)
	{
		Quaternion parentGlobalRotation{ parent->GetGlobalRotation() };
		m_globalRotation = parentGlobalRotation * localRotation;
		m_globalPosition = parentGlobalRotation.Rotate(localPosition) + parent->GetGlobalPosition();

		Quaternion parentGlobalRotationAnimate{ parent->GetGlobalRotationAnimate() };
		m_globalRotationAnimate = parentGlobalRotationAnimate * localRotation * localRotationAnimate;
		m_globalPositionAnimate = parentGlobalRotationAnimate.Rotate(localPosition + localPositionAnimate) + parent->GetGlobalPositionAnimate();
	}
	else
	{
		m_globalRotation = Quaternion::Identity();
		m_globalPosition = Vec3::Zero();

		m_globalRotationAnimate = Quaternion::Identity();
		m_globalPositionAnimate = Vec3::Zero();
	}
	
	Transform transform(m_globalPosition, m_globalRotation, m_globalPositionAnimate, m_globalRotationAnimate);
	m_transform = transform;
}


KeyFrame::~KeyFrame()
{}

const Vec3& KeyFrame::GetLocalPosition() const
{
	return m_localPosition;
}

const Quaternion& KeyFrame::GetLocalRotation() const
{
	return m_localRotation;
}

const Vec3& KeyFrame::GetGlobalPosition() const
{
	return m_globalPosition;
}

const Quaternion& KeyFrame::GetGlobalRotation() const
{
	return m_globalRotation;
}

const Vec3& KeyFrame::GetLocalPositionAnimate() const
{
	return m_localPositionAnimate;
}

const Quaternion& KeyFrame::GetLocalRotationAnimate() const
{
	return m_localRotationAnimate;
}

const Vec3& KeyFrame::GetGlobalPositionAnimate() const
{
	return m_globalPositionAnimate;
}

const Quaternion& KeyFrame::GetGlobalRotationAnimate() const
{
	return m_globalRotationAnimate;
}

const Transform& KeyFrame::GetTransform() const
{
	return m_transform;
}

void KeyFrame::Interpolate(const Quaternion& startQ, const Quaternion& endQ, const Vec3& startQ2, const Vec3& endQ2, float percent)
{
	if (percent >= 1.0f)
		percent -= 1.0f;

		Quaternion q{ Quaternion::SLerp(startQ, endQ, percent) };

		Vec3 pos{ Vec3::Lerp(startQ2, endQ2, percent) };

		if (m_parent)
		{
			Quaternion parentGlobalRotationAnimate{ m_parent->GetGlobalRotationAnimate() };

			m_globalRotationAnimate = parentGlobalRotationAnimate * m_localRotation * q;
			m_globalPositionAnimate = parentGlobalRotationAnimate.Rotate(m_localPosition + pos) + m_parent->GetGlobalPositionAnimate();
		}

		Transform transform(m_globalPosition, m_globalRotation, m_globalPositionAnimate, m_globalRotationAnimate);
		m_transform = transform;

}
