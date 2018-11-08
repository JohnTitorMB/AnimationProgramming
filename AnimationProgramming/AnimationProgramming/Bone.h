#ifndef __BONE_H__
#define __BONE_H__

#include "Animation.h"

class Bone
{
private:
	int m_index;
	std::string m_name;

	std::vector<Bone*> m_childrenBones;
	std::vector<Animation*> m_animations;

public:
	Bone();
	Bone(int index, const std::string& name);
	Bone(const Bone& bone) = delete;
	~Bone();
	Bone& operator=(const Bone& bone) = delete;
	Bone(Bone&& bone) = delete;

	int GetIndex() const;
	const std::string& GetName() const;
	
	const std::vector<Bone*>& GetChildrenBones() const;
	const std::vector<Animation*>& GetAnimations() const;

	const Transform& GetTransform(int currentAnimationIndex, int currentKeyFrameIndex) const;

	void AddChildBone(Bone* bone);
	void AddAnimation(Animation* animation);
};

#endif
