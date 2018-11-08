#include "stdafx.h"

#include "Simulation.h"
#include <math.h>

CSimulation::CSimulation()
{}

CSimulation::~CSimulation()
{
	if (m_skeleton)
	{
		delete m_skeleton;
		m_skeleton = nullptr;
	}
}

void CSimulation::Init()
{
	std::vector<std::string> animationsName;
	animationsName.push_back("ThirdPersonWalk.anim");
	animationsName.push_back("ThirdPersonRun.anim");

	Vec3 localScale{ Vec3::One() };
	Bone* rootBone{ new Bone(0,GetSkeletonBoneName(0)) };

	for (unsigned int i{ 0 }; i < animationsName.size(); ++i)
	{
		size_t animKeyCount{ GetAnimKeyCount(animationsName[i].c_str()) };
		Animation* animation{ new Animation(animationsName[i], animKeyCount) };

		for (unsigned int key{ 0 }; key < animKeyCount; ++key)
		{
			Vec3 localPosRoot, localPosRootAnimate;
			Quaternion localQRoot, localQRootAnimate;
			GetSkeletonBoneLocalBindTransform(	0, 
												localPosRoot.m_x, localPosRoot.m_y, localPosRoot.m_z, 
												localQRoot.m_w, localQRoot.m_vec.m_x, localQRoot.m_vec.m_z, localQRoot.m_vec.m_z);

			GetAnimLocalBoneTransform(	animationsName[i].c_str(), 0, key, 
										localPosRootAnimate.m_x, localPosRootAnimate.m_y, localPosRootAnimate.m_z, 
										localQRootAnimate.m_w, localQRootAnimate.m_vec.m_x, localQRootAnimate.m_vec.m_y, localQRootAnimate.m_vec.m_z);

			animation->AddKeyFrame(localPosRoot, localQRoot, localPosRootAnimate, localQRootAnimate, i, key);
		}
		rootBone->AddAnimation(animation);
	}

	m_skeleton = new Skeleton(rootBone, animationsName);

	std::vector<Bone*> bones;
	bones.push_back(rootBone);
	m_skeleton->AddChildrenBones(bones);

	bones.clear();
}

void CSimulation::Update(float frameTime)
{
	DrawBase();

	m_skeleton->SetTransform((int)m_skeleton->GetKeyFrameTime());
	SetSkinningPose(m_skeleton->GetTransform(), GetSkeletonBoneCount() - 4);

	m_skeleton->Update(frameTime);
}

void CSimulation::DrawBase()
{
	// X axis
	DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

	// Y axis
	DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

	// Z axis
	DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);
}