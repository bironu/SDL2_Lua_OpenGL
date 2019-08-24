#pragma once
#if !defined(MATH_VECTOR3_H_)
#define MATH_VECTOR3_H_

#include "Math.h"
#include "Matrix4.h"

namespace Math
{
// 3D Vector
template<typename T>
class Vector3
{
public:
	using type = T;

	Vector3()
		:x_(0.0)
		,y_(0.0)
		,z_(0.0)
	{}

	explicit Vector3(T x, T y, T z)
		:x_(x)
		,y_(y)
		,z_(z)
	{}

    T getX() const { return x_; }
    T getY() const { return y_; }
    T getZ() const { return z_; }

    void setX(T x) { x_ = x; }
    void setY(T y) { y_ = y; }
    void setZ(T z) { z_ = z; }

	// Cast to a const T pointer
	const T* getAsArrayPtr() const
	{
		return reinterpret_cast<const T*>(&x_);
	}

	// Set all three components in one line
	void Set(T x, T y, T z)
	{
		setX(x);
		setY(y);
	    setZ(z);
	}

	// Scalar *=
	Vector3& operator*=(T scalar)
	{
		setX(getX() * scalar);
		setY(getY() * scalar);
		setZ(getZ() * scalar);
		return *this;
	}

	// Vector +=
	Vector3& operator+=(const Vector3& right)
	{
		setX(getX() + right.getX());
		setY(getY() + right.getY());
		setZ(getZ() + right.getZ());
		return *this;
	}

	// Vector -=
	Vector3& operator-=(const Vector3& right)
	{
		setX(getX() - right.getX());
		setY(getY() - right.getY());
		setZ(getZ() - right.getZ());
		return *this;
	}

	// Length squared of vector
	T LengthSq() const
	{
		return (getX()*getX() + getY()*getY() + getZ()*getZ());
	}

	// Length of vector
	T Length() const
	{
		return (Math::Sqrt(LengthSq()));
	}

	// Normalize this vector
	void Normalize()
	{
		const T length = Length();
		setX(getX() / length);
		setY(getY() / length);
		setZ(getZ() / length);
    }

	// Normalize the provided vector
	static Vector3 Normalize(const Vector3& vec)
	{
		Vector3 temp = vec;
		temp.Normalize();
		return temp;
	}

	// Dot product between two vectors (a dot b)
	static T Dot(const Vector3& a, const Vector3& b)
	{
		return (a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ());
	}

	// Cross product between two vectors (a cross b)
	static Vector3 Cross(const Vector3& a, const Vector3& b)
	{
		return {
            (a.getY() * b.getZ() - a.getZ() * b.getY()),
            (a.getZ() * b.getX() - a.getX() * b.getZ()),
            (a.getX() * b.getY() - a.getY() * b.getX())
        };
	}

	// Lerp from A to B by f
	static Vector3 Lerp(const Vector3& a, const Vector3& b, const T f)
	{
		return Vector3(a + f * (b - a));
	}
	
	// Reflect V about (normalized) N
	static Vector3 Reflect(const Vector3& v, const Vector3& n)
	{
		return v - static_cast<T>(2.0) * Vector3::Dot(v, n) * n;
	}

	static Vector3 Transform(const Vector3& vec, const class Matrix4& mat, const T w = static_cast<T>(1.0))
    {
        return {
            vec.getX() * mat.mat[0][0] + vec.getY() * mat.mat[1][0] + vec.getZ() * mat.mat[2][0] + w * mat.mat[3][0],
            vec.getX() * mat.mat[0][1] + vec.getY() * mat.mat[1][1] + vec.getZ() * mat.mat[2][1] + w * mat.mat[3][1],
            vec.getX() * mat.mat[0][2] + vec.getY() * mat.mat[1][2] + vec.getZ() * mat.mat[2][2] + w * mat.mat[3][2]
        };
    }

	// This will transform the vector and renormalize the w component
	static Vector3 TransformWithPerspDiv(const Vector3& vec, const class Matrix4& mat, const T w = static_cast<T>(1.0))
    {
        Vector3 retVal = Transform(vec, mat, w);
        const T transformedW = vec.getX() * mat.mat[0][3] + vec.getY() * mat.mat[1][3] + vec.getZ() * mat.mat[2][3] + w * mat.mat[3][3];
        if (!Math::NearZero(Math::Abs(transformedW)))
        {
            transformedW = static_cast<T>(1.0) / transformedW;
            retVal *= transformedW;
        }
        return retVal;
    }

	// Transform a Vector3 by a quaternion
	static Vector3 Transform(const Vector3& v, const class Quaternion& q)
    {
        // v + 2.0*cross(q.xyz, cross(q.xyz,v) + q.w*v);
        Vector3 qv(q.x, q.y, q.z);
        Vector3 retVal = v;
        retVal += static_cast<T>(2.0) * Vector3::Cross(qv, Vector3::Cross(qv, v) + q.w * v);
        return retVal;
    }

	static const Vector3 Zero;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 NegUnitX;
	static const Vector3 NegUnitY;
	static const Vector3 NegUnitZ;
	static const Vector3 Infinity;
	static const Vector3 NegInfinity;

private:
	T x_;
	T y_;
	T z_;
};

// Vector addition (lh + rh)
template<typename T>
inline Vector3<T> operator+(const Vector3<T>& lh, const Vector3<T>& rh)
{
    return {
        lh.getX() + rh.getX(),
        lh.getY() + rh.getY(),
        lh.getZ() + rh.getZ()
    };
}

// Vector subtraction (lh - rh)
template<typename T>
inline Vector3<T> operator-(const Vector3<T>& lh, const Vector3<T>& rh)
{
    return {
        lh.getX() - rh.getX(),
        lh.getY() - rh.getY(),
        lh.getZ() - rh.getZ()
    };

// Component-wise multiplication
template<typename T>
inline Vector3<T> operator*(const Vector3<T>& left, const Vector3<T>& right)
{
    return {
        left.getX() * right.getX(),
        left.getY() * right.getY(),
        left.getZ() * right.getZ()
    };
}

// Scalar multiplication
template<typename T>
inline Vector3 operator*(const Vector3<T>& vec, const T scalar)
{
    return {
        vec.getX() * scalar,
        vec.getY() * scalar,
        vec.getZ() * scalar
    };
}

// Scalar multiplication
static Vector3 operator*(const T scalar, const Vector3& vec)
{
    return vec * scalar;
}

using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;

}

#endif // MATH_VECTOR3_H_