#include "vec2.h"
#include <stdlib.h>
#include <math.h>

Vector2::Vector2(void)
{
}

Vector2::Vector2(vec_t X, vec_t Y)
{
	x = X; y = Y;
}

Vector2::Vector2(vec_t* clr)
{
	x = clr[0]; y = clr[1];
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

void Vector2::Init(vec_t ix, vec_t iy)
{
	x = ix; y = iy;
}

void Vector2::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
}

void Vector2Clear(Vector2& a)
{
	a.x = a.y = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

Vector2& Vector2::operator=(const Vector2& vOther)
{
	x = vOther.x; y = vOther.y;
	return *this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

vec_t& Vector2::operator[](int i)
{
	return ((vec_t*)this)[i];
}

vec_t Vector2::operator[](int i) const
{
	return ((vec_t*)this)[i];
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------

vec_t* Vector2::Base()
{
	return (vec_t*)this;
}

vec_t const* Vector2::Base() const
{
	return (vec_t const*)this;
}

//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------

bool Vector2::IsValid() const
{
	return true;
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

bool Vector2::operator==(const Vector2& src) const
{
	return (src.x == x) && (src.y == y);
}

bool Vector2::operator!=(const Vector2& src) const
{
	return (src.x != x) || (src.y != y);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

void Vector2Copy(const Vector2& src, Vector2& dst)
{
	dst.x = src.x;
	dst.y = src.y;
}

void Vector2::CopyToArray(float* rgfl) const
{
	rgfl[0] = x; rgfl[1] = y;
}

//-----------------------------------------------------------------------------
// standard Math operations
//-----------------------------------------------------------------------------

void Vector2::Negate()
{
	x = -x; y = -y;
}

void Vector2Add(const Vector2& a, const Vector2& b, Vector2& c)
{
	c.x = a.x + b.x;
	c.y = a.y + b.y;
}

void Vector2Subtract(const Vector2& a, const Vector2& b, Vector2& c)
{
	c.x = a.x - b.x;
	c.y = a.y - b.y;
}

void Vector2Multiply(const Vector2& a, vec_t b, Vector2& c)
{
	c.x = a.x * b;
	c.y = a.y * b;
}

void Vector2Multiply(const Vector2& a, const Vector2& b, Vector2& c)
{
	c.x = a.x * b.x;
	c.y = a.y * b.y;
}


void Vector2Divide(const Vector2& a, vec_t b, Vector2& c)
{
	vec_t oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
}

void Vector2Divide(const Vector2& a, const Vector2& b, Vector2& c)
{
	c.x = a.x / b.x;
	c.y = a.y / b.y;
}

void Vector2MA(const Vector2& start, float s, const Vector2& dir, Vector2& result)
{
	result.x = start.x + s * dir.x;
	result.y = start.y + s * dir.y;
}

// FIXME: Remove
// For backwards compatability
void Vector2::MulAdd(const Vector2& a, const Vector2& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
}

void Vector2Lerp(const Vector2& src1, const Vector2& src2, vec_t t, Vector2& dest)
{
	dest[0] = src1[0] + (src2[0] - src1[0]) * t;
	dest[1] = src1[1] + (src2[1] - src1[1]) * t;
}

//-----------------------------------------------------------------------------
// dot, cross
//-----------------------------------------------------------------------------
vec_t DotProduct2D(const Vector2& a, const Vector2& b)
{
	return(a.x * b.x + a.y * b.y);
}

// for backwards compatability
vec_t Vector2::Dot(const Vector2& vOther) const
{
	return DotProduct2D(*this, vOther);
}

vec_t Vector2Normalize(Vector2& v)
{
	vec_t l = v.Length();
	if (l != 0.0f) {
		v /= l;
	}
	else {
		v.x = v.y = 0.0f;
	}
	return l;
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
vec_t Vector2Length(const Vector2& v)
{
	return (vec_t)sqrt(v.x * v.x + v.y * v.y);
}

vec_t Vector2::NormalizeInPlace()
{
	return Vector2Normalize(*this);
}

bool Vector2::IsLengthGreaterThan(float val) const
{
	return LengthSqr() > val * val;
}

bool Vector2::IsLengthLessThan(float val) const
{
	return LengthSqr() < val * val;
}

vec_t Vector2::Length(void) const
{
	return Vector2Length(*this);
}

void Vector2::Clamp()
{
	if (x > 180.0f)
		x -= 360.0f;
	else if (x < -180.0f)
		x += 360.0f;

	if (y > 180.0f)
		y -= 360.0f;
	else if (y < -180.0f)
		y += 360.0f;

	if (x < -85.0f) { x = -85.0f; }

	if (x > 85.0f) { x = 85.0f; }

	while (y < -180.0f) { y += 360.0f; }

	while (y > 180.0f) { y -= 360.0f; }
}


void Vector2Min(const Vector2& a, const Vector2& b, Vector2& result)
{
	result.x = (a.x < b.x) ? a.x : b.x;
	result.y = (a.y < b.y) ? a.y : b.y;
}


void Vector2Max(const Vector2& a, const Vector2& b, Vector2& result)
{
	result.x = (a.x > b.x) ? a.x : b.x;
	result.y = (a.y > b.y) ? a.y : b.y;
}

//-----------------------------------------------------------------------------
// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
//-----------------------------------------------------------------------------
void ComputeClosestPoint2D(const Vector2& vecStart, float flMaxDist, const Vector2& vecTarget, Vector2* pResult)
{
	Vector2 vecDelta;
	Vector2Subtract(vecTarget, vecStart, vecDelta);
	float flDistSqr = vecDelta.LengthSqr();
	if (flDistSqr <= flMaxDist * flMaxDist) {
		*pResult = vecTarget;
	}
	else {
		vecDelta /= sqrt(flDistSqr);
		Vector2MA(vecStart, flMaxDist, vecDelta, *pResult);
	}
}

//-----------------------------------------------------------------------------
// Returns a Vector2 with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------

Vector2 Vector2::Min(const Vector2& vOther) const
{
	return Vector2(x < vOther.x ? x : vOther.x, y < vOther.y ? y : vOther.y);
}

Vector2 Vector2::Max(const Vector2& vOther) const
{
	return Vector2(x > vOther.x ? x : vOther.x, y > vOther.y ? y : vOther.y);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

Vector2 Vector2::operator-(void) const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const Vector2& v) const
{
	Vector2 res;
	Vector2Add(*this, v, res);
	return res;
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	Vector2 res;
	Vector2Subtract(*this, v, res);
	return res;
}

Vector2 Vector2::operator*(float fl) const
{
	Vector2 res;
	Vector2Multiply(*this, fl, res);
	return res;
}

Vector2 Vector2::operator*(const Vector2& v) const
{
	Vector2 res;
	Vector2Multiply(*this, v, res);
	return res;
}

Vector2 Vector2::operator/(float fl) const
{
	Vector2 res;
	Vector2Divide(*this, fl, res);
	return res;
}

Vector2 Vector2::operator/(const Vector2& v) const
{
	Vector2 res;
	Vector2Divide(*this, v, res);
	return res;
}

Vector2 operator*(float fl, const Vector2& v)
{
	return v * fl;
}