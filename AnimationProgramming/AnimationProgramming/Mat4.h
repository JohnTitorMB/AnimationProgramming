#ifndef  __MAT4_H__
#define  __MAT4_H__

#include <iostream>

struct Mat4
{
	float m_matrix[4][4];

	#pragma region Shorthands
	// Generates a matrix full of 0
	static Mat4 Zero();
	// Generates a unitary matrix
	static Mat4 Unitary();
	#pragma endregion

	#pragma region Constructors/destructor
	Mat4();
	Mat4(	float aa, float ab, float ac, float ad,
			float ba, float bb, float bc, float bd,
			float ca, float cb, float cc, float cd,
			float da, float db, float dc, float dd);
	Mat4(float matrix[4][4]);
	Mat4(const Mat4& squareMatrix4);
	~Mat4();
	Mat4& operator=(const Mat4&);
	Mat4(Mat4&& mat) = default;
	#pragma endregion

	#pragma region Tools
	// Sets all values to 0
	void Clear();
	// Changes the matrix into a unitary matrix
	void Init();
	// Inverse a matrix
	Mat4 Inverse();
	#pragma endregion

	#pragma region Operators
	Mat4 operator+(const Mat4&) const;
	Mat4& operator+=(const Mat4&);
	Mat4 operator*(const Mat4&) const;
	Mat4& operator*=(const Mat4&);
	bool operator==(const Mat4&) const;
	#pragma endregion
};
std::ostream& operator<<(std::ostream&, const Mat4&);

#endif

