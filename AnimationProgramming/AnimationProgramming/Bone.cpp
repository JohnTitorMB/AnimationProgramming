#include "stdafx.h"

#include "Bone.h"

Bone::Bone() : 
	m_index{ 0 },
	m_name{ "" }
{}

Bone::Bone(int index, const std::string& name) :
	m_index{ index },
	m_name{ name }
{}

Bone::~Bone()
{
	for (Bone* bone : m_childrenBones)
	{
		delete bone;
		bone = nullptr;
	}
	m_childrenBones.clear();

	for (Animation* animation : m_animations)
	{
		delete animation;
		animation = nullptr;
	}
	m_animations.clear();
}

int Bone::GetIndex() const
{
	return m_index;
}

const std::string& Bone::GetName() const
{
	return m_name;
}

const std::vector<Bone*>& Bone::GetChildrenBones() const
{
	return m_childrenBones;
}

const std::vector<Animation*>& Bone::GetAnimations() const
{
	return m_animations;
}

const Transform& Bone::GetTransform(int currentAnimationIndex, int currentKeyFrameIndex) const
{
	return m_animations[currentAnimationIndex]->GetKeyFrames()[currentKeyFrameIndex]->GetTransform();
}

void Bone::AddChildBone(Bone* bone)
{
	if (bone)
		m_childrenBones.push_back(bone);
}

void Bone::AddAnimation(Animation* animation)
{
	if (animation)
		m_animations.push_back(animation);
}

