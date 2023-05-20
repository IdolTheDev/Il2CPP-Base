#pragma once
#include <math.h>

struct Vector3
{
	float x;
	float y;
	float z;

public:
	Vector3(void)
	{
		x = 0;
		y = 0;
		z = 0;
		Invalidate();
	}
	Vector3(float val)
	{
		x = val;
		y = val;
		z = val;
	}
	Vector3(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}
	Vector3(const float* clr)
	{
		x = clr[0];
		y = clr[1];
		z = clr[2];
	}

	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)
	{
		x = ix; y = iy; z = iz;
	}
	bool IsValid() const
	{
		return true;
	}
	void Invalidate()
	{
		return;
	}

	float& operator[](int i)
	{
		return ((float*)this)[i];
	}
	float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	Vector3 Zero()
	{
		Vector3 ret;
		ret.x = 0;
		ret.y = 0;
		ret.z = 0;
		return ret;
	}

	bool IsZero()
	{
		if (x == 0 && y == 0 && z == 0)
			return true;
		else
			return false;
	}

	bool operator==(const Vector3& src) const
	{
		return (src.x == x) && (src.y == y) && (src.z == z);
	}
	bool operator!=(const Vector3& src) const
	{
		return (src.x != x) || (src.y != y) || (src.z != z);
	}
	inline float Distance(const Vector3& Vector3)
	{
		return sqrt(
			(x - Vector3.x) * (x - Vector3.x) +
			(y - Vector3.y) * (y - Vector3.y) +
			(z - Vector3.z) * (z - Vector3.z));
	}
	Vector3& operator+=(const Vector3& v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}
	Vector3& operator-=(const Vector3& v)
	{
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}
	Vector3& operator*=(float fl)
	{
		x *= fl;
		y *= fl;
		z *= fl;
		return *this;
	}
	Vector3& operator*=(const Vector3& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}
	Vector3& operator/=(const Vector3& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}
	Vector3& operator+=(float fl)
	{
		x += fl;
		y += fl;
		z += fl;
		return *this;
	}
	Vector3& operator/=(float fl)
	{
		x /= fl;
		y /= fl;
		z /= fl;
		return *this;
	}
	Vector3& operator-=(float fl)
	{
		x -= fl;
		y -= fl;
		z -= fl;
		return *this;
	}

	void Clamp()
	{
		if (this->x > 180.f)
			this->x -= 360.f;

		else if (this->x < -180.f)
			this->x += 360.f;

		if (this->z > 180.f)
			this->z -= 360.f;

		else if (this->z < -180.f)
			this->z += 360.f;

		if (this->x < -89.f)
			this->x = -89.f;

		if (this->x > 89.f)
			this->x = 89.f;

		while (this->z < -180.0f)
			this->z += 360.0f;

		while (this->z > 180.0f)
			this->z -= 360.0f;
	}

	void NormalizeInPlace()
	{
		*this = Normalized();
	}
	Vector3 Normalized() const
	{
		Vector3 res = *this;
		float l = res.Length();
		if (l != 0.0f) {
			res /= l;
		}
		else {
			res.x = res.y = res.z = 0.0f;
		}
		return res;
	}

	float DistTo(const Vector3& vOther) const
	{
		Vector3 delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.Length();
	}
	float DistToSqr(const Vector3& vOther) const
	{
		Vector3 delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.LengthSqr();
	}
	float Dot(const Vector3& vOther) const
	{
		return (x * vOther.x + y * vOther.y + z * vOther.z);
	}
	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}
	float LengthSqr(void) const
	{
		return (x * x + y * y + z * z);
	}
	float Length2D() const
	{
		return sqrt(x * x + y * y);
	}
	float deltaDistance(Vector3 target_position) const
	{
		return sqrt(
			pow(x - target_position.x, 2) +
			pow(y - target_position.y, 2) +
			pow(z - target_position.z, 2));
	}

	Vector3& operator=(const Vector3& vOther)
	{
		x = vOther.x; y = vOther.y; z = vOther.z;
		return *this;
	}

	Vector3 operator-(void) const
	{
		return Vector3(-x, -y, -z);
	}
	Vector3 operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	Vector3 operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	Vector3 operator*(float fl) const
	{
		return Vector3(x * fl, y * fl, z * fl);
	}
	Vector3 operator*(const Vector3& v) const
	{
		return Vector3(x * v.x, y * v.y, z * v.z);
	}
	Vector3 operator/(float fl) const
	{
		return Vector3(x / fl, y / fl, z / fl);
	}
	Vector3 operator/(const Vector3& v) const
	{
		return Vector3(x / v.x, y / v.y, z / v.z);
	}
	inline Vector3 Normalize()
	{
		Vector3 Vector3;
		float length = this->Length();

		if (length != 0) {
			Vector3.x = x / length;
			Vector3.y = y / length;
			Vector3.z = z / length;
		}
		else
			Vector3.x = Vector3.y = 0.0f; Vector3.z = 1.0f;

		return Vector3;
	}
	inline float Normalizes()
	{
		Vector3 res = *this;
		float l = res.Length();
		if (l != 0.0f)
		{
			res /= l;
		}
		else
		{
			res.x = res.y = res.z = 0.0f;
		}
		return l;
	}
};

inline Vector3 operator*(float lhs, const Vector3& rhs)
{
	return rhs * lhs;
}
inline Vector3 operator/(float lhs, const Vector3& rhs)
{
	return rhs / lhs;
}

class __declspec(align(16)) Vector3Aligned : public Vector3
{
public:
	inline Vector3Aligned(void) {};
	inline Vector3Aligned(float X, float Y, float Z)
	{
		Init(X, Y, Z);
	}

public:
	explicit Vector3Aligned(const Vector3& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
	}

	Vector3Aligned& operator=(const Vector3& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	Vector3Aligned& operator=(const Vector3Aligned& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	float w;
};

struct Vector4
{
public:
	float x;
	float y;
	float z;
	float w;
	Vector4 Zero();
};

struct Matrix3x4
{
	float m[3][4];
};

struct Matrix4x3
{
	float m[4][3];
};

struct Matrix4x4
{
	union { Vector4 v[4]; float m[4][4]; struct { Vector4 right; Vector4 up; Vector4 forward; Vector4 trans; }; };
};