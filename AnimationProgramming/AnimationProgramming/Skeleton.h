#ifndef __SKELETON_H__
#define __SKELETON_H__

#include "Bone.h"

class Skeleton
{
private:
	Bone* m_rootBone;
	std::vector<std::string> m_animationsName;

	unsigned int m_numb;
	unsigned int m_currentAnimationIndex; //switch between 0 and 1 (0 == walkAnimation, 1 == runAnimation)
	unsigned int m_currentKeyFrame;
	float m_keyFrameTime;

	Vec3 m_globalPosition;
	Quaternion m_globalRotation;
	Vec3 m_globalScale;

	float m_transform[1024];

public:
	Skeleton();
	Skeleton(Bone* rootBone, const std::vector<std::string>& animationsName);
	~Skeleton();
	Skeleton(const Skeleton& skeleton);
	Skeleton& operator=(const Skeleton& skeleton);
	Skeleton(Skeleton&& skeleton) = default;

	Bone* GetRootBone() const;
	float GetKeyFrameTime() const;
	const float* GetTransform() const;

	void Draw(const std::vector<Bone*>& bones);
	void AddChildrenBones(const std::vector<Bone*>& bones);

	void SetTransform(int keyFrameIndex);

	void AddTransform(int keyFrameIndex, const std::vector<Bone*>& bones);
	
	void InterpolateRootBone(int currentFrameIndex, int nextFrameIndex, float percent);
	void InterpolateChildrenBones(int currentFrameIndex, int nextFrameIndex, float percent, const std::vector<Bone*>& bones);

	void Update(float frameTime);
};

#endif