#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "KeyFrame.h"

#include <string>
#include <vector>

class Animation
{
private:
	std::string m_name;
	unsigned int m_keyCount;

	std::vector<KeyFrame*> m_keyFrames;

public:
	Animation();
	Animation(const std::string& name, unsigned int keyCount);
	Animation(const Animation& animation) = delete;
	~Animation();
	Animation& operator=(const Animation& animation) = delete;
	Animation(Animation&& animation) = delete;

	const std::string& GetName() const;
	unsigned int GetKeyCount() const;
	const std::vector<KeyFrame*>& GetKeyFrames() const;

	void AddKeyFrame(	const Vec3& localPosition,
						const Quaternion& localRotation,
						const Vec3& localPositionAnimate,
						const Quaternion& localRotationAnimate,
						int animationIndex,
						int keyFrameIndex,
						class Bone* parent = nullptr);
};

#endif