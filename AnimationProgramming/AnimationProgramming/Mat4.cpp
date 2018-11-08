#include "stdafx.h"

#include "Mat4.h"
#include <iomanip>

#pragma region Shorthands
Mat4 Mat4::Zero()
{
	Mat4 tempMat;
	tempMat.Clear();

	return tempMat;
}

Mat4 Mat4::Unitary()
{
	Mat4 tempMat;
	tempMat.Init();

	return tempMat;
}
#pragma endregion

#pragma region Constructors/destructor
Mat4::Mat4()
{
	this->Init();
}

Mat4::Mat4(float aa, float ab, float ac, float ad,
	float ba, float bb, float bc, float bd,
	float ca, float cb, float cc, float cd,
	float da, float db, float dc, float dd)
{
	m_matrix[0][0] = aa; m_matrix[0][1] = ab; m_matrix[0][2] = ac; m_matrix[0][3] = ad;
	m_matrix[1][0] = ba; m_matrix[1][1] = bb; m_matrix[1][2] = bc; m_matrix[1][3] = bd;
	m_matrix[2][0] = ca; m_matrix[2][1] = cb; m_matrix[2][2] = cc; m_matrix[2][3] = cd;
	m_matrix[3][0] = da; m_matrix[3][1] = db; m_matrix[3][2] = dc; m_matrix[3][3] = dd;
}

Mat4::Mat4(float matrix[4][4])
{
	for (int row{ 0 }; row < 4; ++row)
		for (int column{ 0 }; column < 4; ++column)
			m_matrix[row][column] = matrix[row][column];
}

Mat4::Mat4(const Mat4& mat)
{
	*this = mat;
}

Mat4::~Mat4()
{}

Mat4& Mat4::operator=(const Mat4& mat)
{
	for (int row{ 0 }; row < 4; ++row)
		for (int column{ 0 }; column < 4; ++column)
			m_matrix[row][column] = mat.m_matrix[row][column];

	return *this;
}
#pragma endregion

#pragma region Tools
void Mat4::Clear()
{
	for (int row{ 0 }; row < 4; ++row)
		for (int column{ 0 }; column < 4; ++column)
			m_matrix[row][column] = 0.f;
}

void Mat4::Init()
{
	for (int row{ 0 }; row < 4; ++row)
		for (int column{ 0 }; column < 4; ++column)
		{
			if (row == column)
				m_matrix[row][column] = 1;
			else
				m_matrix[row][column] = 0;
		}
}

Mat4 Mat4::Inverse()
{
	Mat4 mat4 = *this;

	Mat4 temp;

	for (int i = 0; i<4; i++)
	{

		for (int j = 0; j<4; j++)
		{
			temp.m_matrix[i][i] = 1 / mat4.m_matrix[i][i];
			if (j != i)
			{
				temp.m_matrix[i][j] = -mat4.m_matrix[i][j] / mat4.m_matrix[i][i];
			}
			for (int k = 0; k<4; k++)
			{

				if (k != i)
				{
					temp.m_matrix[k][i] = mat4.m_matrix[k][i] / mat4.m_matrix[i][i];
				}
				if (j != i &&k != i)
				{
					temp.m_matrix[k][j] = mat4.m_matrix[k][j] - mat4.m_matrix[i][j] * mat4.m_matrix[k][i] / mat4.m_matrix[i][i];
				}
			}

		}
		for (int i = 0; i<4; i++)
		{
			for (int j = 0; j<4; j++)
			{
				mat4.m_matrix[i][j] = temp.m_matrix[i][j];
			}

		}
	}

	return mat4;
}
#pragma endregion

#pragma region Operators
Mat4 Mat4::operator+(const Mat4& mat) const
{
	Mat4 tempMat{ *this };

	for (int row{ 0 }; row < 4; ++row)
		for (int column{ 0 }; column < 4; ++column)
			tempMat.m_matrix[row][column] += mat.m_matrix[row][column];

	return tempMat;
}

Mat4& Mat4::operator+=(const Mat4& mat)
{
	*this = *this + mat;

	return *this;
}

Mat4 Mat4::operator*(const Mat4& mat) const
{
	Mat4 tempMat{ Mat4::Zero() };

	for (int i{ 0 }; i < 4; ++i)
		for (int j{ 0 }; j < 4; ++j)
			for (int k{ 0 }; k < 4; ++k)
				tempMat.m_matrix[i][j] += m_matrix[i][k] * mat.m_matrix[k][j];

	return tempMat;
}

Mat4& Mat4::operator*=(const Mat4& mat)
{
	*this = *this * mat;

	return *this;
}

bool Mat4::operator==(const Mat4& mat) const
{
	for (int row{ 0 }; row < 4; ++row)
		for (int column{ 0 }; column < 4; ++column)
			if (!(m_matrix[row][column] == mat.m_matrix[row][column]))
				return false;

	return true;
}
#pragma endregion

#pragma region Console output
std::ostream& operator<<(std::ostream& stream, const Mat4& mat)
{
	stream << "Mat4 :\n(" << std::fixed << std::setprecision(2);
	for (int row{ 0 }; row < 4; ++row)
	{
		for (int column{ 0 }; column < 4; ++column)
			stream << "	" << mat.m_matrix[row][column];

		if (row == 3)
			stream << "	)";

		stream << std::endl;
	}

	return stream;
}
#pragma endregion

