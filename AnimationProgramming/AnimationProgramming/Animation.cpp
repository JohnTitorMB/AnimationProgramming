#include "stdafx.h"

#include "Animation.h"
#include "Bone.h"

Animation::Animation() : m_name{ "" }, m_keyCount{ 0 }
{}

Animation::Animation(const std::string& name, unsigned int keyCount) : m_name{ name }, m_keyCount{ keyCount }
{}

Animation::~Animation()
{
	for (KeyFrame* keyFrame : m_keyFrames)
	{
		delete keyFrame;
		keyFrame = nullptr;
	}
	m_keyFrames.clear();
}

const std::string& Animation::GetName() const
{
	return m_name;
}

unsigned int Animation::GetKeyCount() const
{
	return m_keyCount;
}

const std::vector<KeyFrame*>& Animation::GetKeyFrames() const
{
	return m_keyFrames;
}

void Animation::AddKeyFrame(const Vec3& localPosition,
	const Quaternion& localRotation,
	const Vec3& localPositionAnimate,
	const Quaternion& localRotationAnimate,
	int animationIndex,
	int keyFrameIndex,
	Bone* parent)
{
	if (parent)
		m_keyFrames.push_back(new KeyFrame(	localPosition, localRotation, localPositionAnimate, localRotationAnimate,
											parent->GetAnimations()[animationIndex]->GetKeyFrames()[keyFrameIndex]));
	else
		m_keyFrames.push_back(new KeyFrame(localPosition, localRotation, localPositionAnimate, localRotationAnimate, nullptr));
}
