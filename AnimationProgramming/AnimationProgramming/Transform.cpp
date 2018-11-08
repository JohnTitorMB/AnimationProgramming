#include "stdafx.h"

#include "Transform.h"
#include "Mat4.h"

Transform::Transform()
{}

Transform::Transform(	const Vec3& globalPosition, 
						const Quaternion& globalRotation, 
						const Vec3& globalPositionAnimate, 
						const Quaternion& globalRotationAnimate)
{

	float w{ globalRotation.m_w };
	float x{ globalRotation.m_vec.m_x };
	float y{ globalRotation.m_vec.m_y };
	float z{ globalRotation.m_vec.m_z };

	Mat4 transform(	w*w + x*x - y*y - z*z, 2*x*y - 2*w*z, 2*x*z + 2*w*y, globalPosition.m_x,
					2*x*y + 2*w*z, w*w - x*x + y*y - z*z, 2*y*z - 2*w*x, globalPosition.m_y,
					2*x*z - 2*w*y, 2*y*z + 2*w*x, w*w - x*x - y*y + z*z, globalPosition.m_z,
					0, 0, 0, 1);

	w = globalRotationAnimate.m_w;
	x = globalRotationAnimate.m_vec.m_x;
	y = globalRotationAnimate.m_vec.m_y;
	z = globalRotationAnimate.m_vec.m_z;

	Mat4 tranformAnimate (	w*w + x*x - y*y - z*z, 2*x*y - 2*w*z, 2*x*z + 2*w*y, globalPositionAnimate.m_x,
							2*x*y + 2*w*z, w*w - x*x + y*y - z*z, 2*y*z - 2*w*x, globalPositionAnimate.m_y,
							2*x*z - 2*w*y, 2*y*z + 2*w*x, w*w - x*x - y*y + z*z, globalPositionAnimate.m_z,
							0, 0, 0, 1);

	Mat4 finalMat{ tranformAnimate * transform.Inverse() };

	m_transform[0] = finalMat.m_matrix[0][0];	m_transform[1] = finalMat.m_matrix[1][0];	m_transform[2] = finalMat.m_matrix[2][0];	m_transform[3] = finalMat.m_matrix[3][0];
	m_transform[4] = finalMat.m_matrix[0][1];	m_transform[5] = finalMat.m_matrix[1][1];	m_transform[6] = finalMat.m_matrix[2][1];	m_transform[7] = finalMat.m_matrix[3][1];
	m_transform[8] = finalMat.m_matrix[0][2];	m_transform[9] = finalMat.m_matrix[1][2];	m_transform[10] = finalMat.m_matrix[2][2];	m_transform[11] = finalMat.m_matrix[3][2];
	m_transform[12] = finalMat.m_matrix[0][3];	m_transform[13] = finalMat.m_matrix[1][3];	m_transform[14] = finalMat.m_matrix[2][3];	m_transform[15] = finalMat.m_matrix[3][3];

	
}


Transform::~Transform()
{}

const float* Transform::GetTransform() const
{
	return m_transform;
}