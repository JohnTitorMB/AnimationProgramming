#include "stdafx.h"

#include "Engine.h"
#include "Skeleton.h"


Skeleton::Skeleton() :
	m_rootBone{nullptr},
	m_numb{ 0 },
	m_currentKeyFrame{ 0 },
	m_currentAnimationIndex{ 0 },
	m_keyFrameTime{ 0 }
{}

Skeleton::Skeleton(Bone* rootBone, const std::vector<std::string>& animationsName) :
	m_rootBone{ rootBone },
	m_animationsName{ animationsName },
	m_numb{ 0 },
	m_currentAnimationIndex{ 1 }, //switch between 0 and 1 (0 == walkAnimation, 1 == runAnimation)
	m_currentKeyFrame{ 0 }, //0 == animation beginning
	m_keyFrameTime{ 0 }
{
	if (m_currentAnimationIndex > animationsName.size()) //prevents out of range errors
		m_currentAnimationIndex = 0;

	if (m_currentKeyFrame > m_rootBone->GetAnimations()[m_currentAnimationIndex]->GetKeyCount()) //prevents out of range errors
		m_currentKeyFrame = 0; 
}

Skeleton::~Skeleton()
{
	if (m_rootBone)
	{
		delete m_rootBone;
		m_rootBone = nullptr;
	}
}

Skeleton::Skeleton(const Skeleton& skeleton) :
	m_rootBone{ skeleton.m_rootBone },
	m_animationsName{ skeleton.m_animationsName },
	m_numb{ skeleton.m_numb },
	m_currentAnimationIndex{ skeleton.m_currentAnimationIndex },
	m_currentKeyFrame{ skeleton.m_currentKeyFrame },
	m_keyFrameTime{ skeleton.m_keyFrameTime }
{}

Skeleton& Skeleton::operator=(const Skeleton& skeleton)
{
	m_rootBone = skeleton.m_rootBone;
	m_animationsName = skeleton.m_animationsName;
	m_numb = skeleton.m_numb;
	m_currentAnimationIndex = skeleton.m_currentAnimationIndex;
	m_currentKeyFrame = skeleton.m_currentKeyFrame;
	m_keyFrameTime = skeleton.m_keyFrameTime;
	
	return *this;
}

Bone* Skeleton::GetRootBone() const
{
	if (m_rootBone)
		return m_rootBone;

	return nullptr;
}

float Skeleton::GetKeyFrameTime() const
{
	return m_keyFrameTime;
}

const float* Skeleton::GetTransform() const
{
	return m_transform;
}

void Skeleton::Draw(const std::vector<Bone*>& bones)
{
	for (unsigned int i{ 0 }; i < bones.size(); ++i)
	{
		Vec3 globalPosParent{ bones[i]->GetAnimations()[m_currentAnimationIndex]->GetKeyFrames()[m_currentKeyFrame]->GetGlobalPositionAnimate() };
		for (unsigned int j{ 0 }; j < bones[i]->GetChildrenBones().size(); ++j)
		{
			Vec3 globalPos{ bones[i]->GetChildrenBones()[j]->GetAnimations()[m_currentAnimationIndex]->GetKeyFrames()[m_currentKeyFrame]->GetGlobalPositionAnimate() };
			DrawLine(globalPosParent.m_x, globalPosParent.m_y - 100, globalPosParent.m_z, globalPos.m_x, globalPos.m_y - 100, globalPos.m_z, 0, 0, 1);
		}
		Draw(bones[i]->GetChildrenBones());
	}
}

void Skeleton::AddChildrenBones(const std::vector<Bone*>& bones)
{
	Vec3 localScale{ Vec3::One() };
	
	for (unsigned int i{ 0 }; i < bones.size(); ++i)
	{
		for (unsigned int j{ 1 }; j < GetSkeletonBoneCount() - 4; ++j)
		{
			int index{ GetSkeletonBoneParentIndex(j) };
			if (index == bones[i]->GetIndex() && index != -1)
			{
				Bone* bone{ new Bone(j,GetSkeletonBoneName(j)) };
				for (unsigned int k{ 0 }; k < m_animationsName.size(); ++k)
				{
					size_t keyCount{ GetAnimKeyCount(m_animationsName[k].c_str())};
					Animation* animation{ new Animation(m_animationsName[k], keyCount) };
					for (unsigned int key{ 0 }; key < keyCount; ++key)
					{
						Vec3 localPos, localPosAnimate;
						Quaternion localQ, localQAnimate;
						GetSkeletonBoneLocalBindTransform(	j, 
															localPos.m_x, localPos.m_y, localPos.m_z, 
															localQ.m_w, localQ.m_vec.m_x, localQ.m_vec.m_y, localQ.m_vec.m_z);

						GetAnimLocalBoneTransform(	m_animationsName[k].c_str(), j, key, 
													localPosAnimate.m_x, localPosAnimate.m_y, localPosAnimate.m_z, 
													localQAnimate.m_w, localQAnimate.m_vec.m_x, localQAnimate.m_vec.m_y, localQAnimate.m_vec.m_z);

						animation->AddKeyFrame(localPos, localQ, localPosAnimate, localQAnimate, k, key, bones[i]);
					}
					bone->AddAnimation(animation);
				}
				bones[i]->AddChildBone(bone);
			}
		}
		AddChildrenBones(bones[i]->GetChildrenBones());
	}
}

void Skeleton::SetTransform(int keyFrameIndex)
{
	m_numb = 0;
    Transform rootBoneTransform{ m_rootBone->GetTransform(m_currentAnimationIndex, keyFrameIndex) };

	for (int i{ 0 }; i < 16; ++i)
		m_transform[i+m_numb] = rootBoneTransform.GetTransform()[i];

	m_numb += 16;

	AddTransform(keyFrameIndex, m_rootBone->GetChildrenBones());
}

void Skeleton::AddTransform(int keyFrameIndex, const std::vector<Bone*>& bones)
{
	for (unsigned int i{ 0 }; i < bones.size(); ++i)
	{
		Transform boneTransform{ bones[i]->GetTransform(m_currentAnimationIndex, keyFrameIndex) };

		for (int j{ 0 }; j < 16; ++j)
			m_transform[j+m_numb] = boneTransform.GetTransform()[j];

		m_numb += 16;

		AddTransform(keyFrameIndex,bones[i]->GetChildrenBones());
	}

}

void Skeleton::InterpolateRootBone(int currentFrameIndex, int nextFrameIndex, float percent)
{
	
	KeyFrame* rootBoneCurrentKeyFrame{ m_rootBone->GetAnimations()[m_currentAnimationIndex]->GetKeyFrames()[currentFrameIndex] };
	KeyFrame* rootBoneNextKeyFrame{ m_rootBone->GetAnimations()[m_currentAnimationIndex]->GetKeyFrames()[nextFrameIndex] };

	Quaternion startQ{ rootBoneCurrentKeyFrame->GetLocalRotationAnimate() };
	Quaternion endQ{ rootBoneNextKeyFrame->GetLocalRotationAnimate() };

	Vec3 startVec{ rootBoneCurrentKeyFrame->GetLocalPositionAnimate() };
	Vec3 endVec{ rootBoneNextKeyFrame->GetLocalPositionAnimate() };

	rootBoneCurrentKeyFrame->Interpolate(startQ, endQ, startVec, endVec, percent);
	InterpolateChildrenBones(currentFrameIndex, nextFrameIndex, percent, m_rootBone->GetChildrenBones());
}

void Skeleton::InterpolateChildrenBones(int currentFrame, int nextFrame, float percent, const std::vector<Bone*>& bones)
{
	for (unsigned int i{ 0 }; i < bones.size(); ++i)
	{
		KeyFrame* boneCurrentKeyFrame{ bones[i]->GetAnimations()[m_currentAnimationIndex]->GetKeyFrames()[currentFrame] };
		KeyFrame* boneNextKeyFrame{ bones[i]->GetAnimations()[m_currentAnimationIndex]->GetKeyFrames()[nextFrame] };

		Quaternion startQ{ boneCurrentKeyFrame->GetLocalRotationAnimate() };
		Quaternion endQ{ boneNextKeyFrame->GetLocalRotationAnimate() };

		Vec3 startVec{ boneCurrentKeyFrame->GetLocalPositionAnimate() };
		Vec3 endVec{ boneNextKeyFrame->GetLocalPositionAnimate() };

		boneCurrentKeyFrame->Interpolate(startQ, endQ, startVec, endVec, percent);

		InterpolateChildrenBones(currentFrame, nextFrame, percent, bones[i]->GetChildrenBones());
	}
}

void Skeleton::Update(float frameTime)
{
	std::vector<Bone*> bones;
	bones.push_back(m_rootBone);
	Draw(bones);
	bones.clear();

	m_keyFrameTime += 30.0f * frameTime;

	unsigned int nextKeyFrame{ m_currentKeyFrame + 1 };
	float percent{ m_keyFrameTime - m_currentKeyFrame };
	InterpolateRootBone(m_currentKeyFrame, nextKeyFrame, percent);

	if (m_keyFrameTime > nextKeyFrame)
	{
		if (m_keyFrameTime > m_rootBone->GetAnimations()[m_currentAnimationIndex]->GetKeyCount() - 1)
		{
			m_keyFrameTime = 0;
			m_currentKeyFrame = 0;
		}
		else
			m_currentKeyFrame = nextKeyFrame;
	}
}