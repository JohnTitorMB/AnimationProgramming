#ifndef  __VEC3_H__
#define  __VEC3_H__

#include <iostream>

#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288
#endif

struct Vec3
{
	float m_x;
	float m_y;
	float m_z;


	#pragma region Shorthands
	// Generates a Vec3 : ( 0 ; 0 ; 0 ).
	static Vec3 Zero();
	// Generates a Vec3 : ( -1 ; 0 ; 0 ).
	static Vec3 Left();
	// Generates a Vec3 : ( 1 ; 0 ; 0 ).
	static Vec3 Right();
	// Generates a Vec3 : ( 0 ; -1 ; 0 ).
	static Vec3 Down();
	// Generates a Vec3 : ( 0 ; 1 ; 0 ).
	static Vec3 Up();
	// Generates a Vec3 : ( 0 ; 0 ; -1 ).
	static Vec3 Back();
	// Generates a Vec3 : ( 0 ; 0 ; 1 ).
	static Vec3 Forward();
	// Generates a Vec3 : ( 1 ; 1 ; 1 ).
	static Vec3 One();
	#pragma endregion
	
	#pragma region Constructors/destructor
	Vec3();
	Vec3(float x, float y, float z);
	Vec3(const Vec3& vector3);
	~Vec3();
	Vec3(Vec3&& vector3) = default;
	#pragma endregion

	#pragma region Tools
	// Returns a Vec3 between the left vector and the right vector.
	// The ratio is clamped to the range[0, 1].
	// If the ratio is 0, the vector returned is equal to the left vector.
	// If the ratio is 1, the vector returned is equal to the right vector.
	static Vec3 Lerp(const Vec3& leftVector, const Vec3& rightVector, float ratio);
	// Returns the angle in radians between the two vectors.
	static float GetAngle(const Vec3& firstVector, const Vec3& secondVector);
	// Returns the angle in degrees between the two vectors.
	static float GetAngleInDegrees(const Vec3& firstVector, const Vec3& secondVector);
	// Returns the vector with the smallest magnitude.
	static Vec3& Shortest(Vec3& firstVector, Vec3& secondVector);
	// Returns the vector with the biggest magnitude.
	static Vec3& Longest(Vec3& firstVector, Vec3& secondVector);
	// Returns a vector with the smallest components.
	static Vec3 Min(const Vec3& firstVector, const Vec3& secondVector);
	// Returns a vector with the biggest components.
	static Vec3 Max(const Vec3& firstVector, const Vec3& secondVector);
	// Returns the distance between two vertices.
	static float Distance(const Vec3& firstVertex, const Vec3& secondVertex);
	// Returns the distance squared between two vertices.
	static float DistanceSQ(const Vec3& firstVertex, const Vec3& secondVertex);

	// Returns a vector2 made form this vector3.
	// z component is lost.
	#pragma endregion

#	pragma region Operators
	Vec3 operator+(const Vec3&) const;
	Vec3& operator+=(const Vec3&);
	Vec3 operator-() const;
	Vec3 operator-(const Vec3&) const;
	Vec3& operator-=(const Vec3&);
	Vec3 operator*(float) const;
	Vec3& operator*=(float);
	Vec3 operator/(float) const;
	Vec3& operator/=(float);
	Vec3& operator=(const Vec3&);
	bool operator==(const Vec3&) const;
	bool operator!=(const Vec3&) const;
	// Returns the associated component.
	float& operator[](int index);
	#pragma endregion

	#pragma region Operations
	void Normalize();
	Vec3 GetNormalized() const;
	float GetMagnitude() const;
	float GetMagnitudeSQ() const;
	// Changes the magnitude of the vector.
	void SetMagnitude(float magnitude);
	float DotProduct(const Vec3& vector3) const;
	Vec3 CrossProduct(const Vec3& vector3) const;
	#pragma endregion

	operator std::string() const;
};
std::ostream& operator<<(std::ostream&, const Vec3&);


#endif
