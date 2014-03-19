#ifndef _ENCO3D_QUATERNION_H_
#define _ENCO3D_QUATERNION_H_

#include <math.h>

#include "Vector3.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

template <typename T>
struct Quaternion
{
	T x, y, z, w;

	inline Quaternion(T _x = 0, T _y = 0, T _z = 0, T _w = 0) : x(_x), y(_y), z(_z), w(_w) {  }
	inline Quaternion(const Quaternion<T> &q) : x(q.x), y(q.y), z(q.z), w(q.w) {  }

	inline Quaternion(const Vector3<T> &axis, T angle)
	{
		T s = (T)sin(angle * 0.5);
		T c = (T)cos(angle * 0.5);

		Set(axis.x * s, axis.y * s, axis.z * s, c);
	}

	inline Quaternion<T> &Clear() { x = y = z = w = 0; return *this; }
	inline Quaternion<T> &Set(T _x, T _y, T _z, T _w) { x = _x; y = _y; z = _z; w = _w; return *this; }
	inline Quaternion<T> &Set(const Quaternion<T> &q) { x = q.x; y = q.y; z = q.z; w = q.w; return *this; }

	inline bool operator == (const Quaternion<T> &q) const { return x == q.x && y == q.y && z == q.z && w == q.w; }
	inline bool operator != (const Quaternion<T> &q) const { return x != q.x || y != q.y || z != q.z || w != q.w; }

	inline Quaternion<T> operator - () const { return Quaternion<T>(-x, -y, -z, w); }

	inline Quaternion<T> operator * (const Quaternion<T> &q) const
	{
		const T _w = (w * q.w) - (x * q.x) - (y * q.y) - (z * q.z);
		const T _x = (x * q.w) + (w * q.x) + (y * q.z) - (z * q.y);
		const T _y = (y * q.w) + (w * q.y) + (z * q.x) - (x * q.z);
		const T _z = (z * q.w) + (w * q.z) + (x * q.y) - (y * q.x);

		return Quaternion<T>(_x, _y, _z, _w);
	}

	inline Quaternion<T> &operator *= (const Quaternion<T> &q)
	{
		const T _w = (w * q.w) - (x * q.x) - (y * q.y) - (z * q.z);
		const T _x = (x * q.w) + (w * q.x) + (y * q.z) - (z * q.y);
		const T _y = (y * q.w) + (w * q.y) + (z * q.x) - (x * q.z);
		const T _z = (z * q.w) + (w * q.z) + (x * q.y) - (y * q.x);

		return Set(_x, _y, _z, _w);
	}

	inline Quaternion<T> operator * (T val) const { return Quaternion<T>(x * val, y * val, z * val, w * val); }
	inline Quaternion<T> &operator *= (T val) { return Set(x * val, y * val, z * val, w * val); }

	inline T GetSquaredLength() const { return x * x + y * y + z * z + w * w; }
	inline T GetLength() const { return (T)sqrt(x * x + y * y + z * z + w * w); }

	inline Quaternion<T> &Normalize()
	{
		return (*this * ((T)(1.0 / GetLength())));
	}

	template <typename S> inline void RotateVector(Vector3<S> *v) const
	{
		Quaternion<S> conjugate = -(*this);
		Quaternion<S> w = ((*this) * (*v)) * conjugate;
		v->Set(w.x, w.y, w.z);
	}

	inline Matrix3x3<T> &ToRotationMatrix3x3() const
	{
		Vector3<T> forward(2 * (x * z - w * y), 2 * (y * z + w * x), 1 - 2 * (x * x + y * y));
		Vector3<T> up(2 * (x * y + w * z), 1 - 2 * (x * x + z * z), 2 * (y * z - w * x));
		Vector3<T> right(1 - 2 * (y * y + z * z), 2 * (x * y - w * z), 2 * (x * z + w * y));

		return Matrix3x3<T>().SetRotation(forward, up, right);
	}

	inline Matrix4x4<T> &ToRotationMatrix4x4() const
	{
		Vector3<T> forward(2 * (x * z - w * y), 2 * (y * z + w * x), 1 - 2 * (x * x + y * y));
		Vector3<T> up(2 * (x * y + w * z), 1 - 2 * (x * x + z * z), 2 * (y * z - w * x));
		Vector3<T> right(1 - 2 * (y * y + z * z), 2 * (x * y - w * z), 2 * (x * z + w * y));

		return Matrix4x4<T>().SetRotation(forward, up, right);
	}

	inline Vector3<T> GetForward() const { Vector3<T> dir(0, 0, 1); RotateVector(&dir); return dir; }
	inline Vector3<T> GetUp() const { Vector3<T> dir(0, 1, 0); RotateVector(&dir); return dir; }
	inline Vector3<T> GetRight() const { Vector3<T> dir(1, 0, 0); RotateVector(&dir); return dir; }
};

template <typename T, typename S> inline Quaternion<S> operator * (T val, const Quaternion<S> &q) { return Quaternion<S>(x * val, y * val, z * val, w * val); }

template <typename T, typename S>
inline Quaternion<T> operator * (const Quaternion<T> &q, const Vector3<S> &v)
{
	const T _w = -(q.x * v.x) - (q.y * v.y) - (q.z * v.z);
	const T _x = (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
	const T _y = (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
	const T _z = (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

	return Quaternion<T>(_x, _y, _z, _w);
}

template <typename T, typename S>
inline Quaternion<T> operator * (const Vector3<S> &v, const Quaternion<T> &q)
{
	const T _w = -(q.x * v.x) - (q.y * v.y) - (q.z * v.z);
	const T _x = (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
	const T _y = (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
	const T _z = (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

	return Quaternion<T>(_x, _y, _z, _w);
}

template <typename T, typename S>
inline Quaternion<T> &operator *= (Quaternion<T> &q, const Vector3<S> &v)
{
	const T _w = -(q.x * v.x) - (q.y * v.y) - (q.z * v.z);
	const T _x = (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
	const T _y = (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
	const T _z = (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

	return q.Set(_x, _y, _z, _w);
}

typedef Quaternion<float> Quaternionf;
typedef Quaternion<double> Quaterniond;

#endif