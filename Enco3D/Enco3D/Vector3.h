#ifndef _ENCO3D_VECTOR3_H_
#define _ENCO3D_VECTOR3_H_

#include "Vector2.h"

namespace Enco3D
{
	namespace Core
	{
		template <typename T> struct Vector3
		{
			union
			{
				struct
				{
					T x, y, z;
				};

				T xyz[3];
			};

			inline Vector3(T _x = 0, T _y = 0, T _z = 0) : x(_x), y(_y), z(_z) {  }
			inline Vector3(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {  }

			inline Vector3<T> &clear() { x = y = z = 0; return *this; }
			inline Vector3<T> &set(T _x, T _y, T _z) { x = _x; y = _y; z = _z; return *this; }
			inline Vector3<T> &set(const Vector3<T> &v) { x = v.x; y = v.y; z = v.z; return *this; }

			template <typename S> inline bool operator == (const Vector3<S> &v) const { return x == v.x && y == v.y && z == v.z; }
			template <typename S> inline bool operator != (const Vector3<S> &v) const { return x != v.x || y != v.y || z != v.z; }

			inline Vector3<T> operator - () const { return Vector3<T>(-x, -y, -z); }

			template <typename S> inline Vector3<T> operator + (const Vector3<S> &v) const { return Vector3<T>(x + v.x, y + v.y, z + v.z); }
			template <typename S> inline Vector3<T> operator - (const Vector3<S> &v) const { return Vector3<T>(x - v.x, y - v.y, z - v.z); }
			template <typename S> inline Vector3<T> operator * (S val) const { return Vector3<T>(x * val, y * val, z * val); }
			template <typename S> inline Vector3<T> operator / (S val) const { T ival = (T)(1.0 / val); return Vector3<T>(x * ival, y * ival, z * ival); }

			template <typename S> inline Vector3<T> &operator += (const Vector3<S> &v) { return set(x + v.x, y + v.y, z + v.z); }
			template <typename S> inline Vector3<T> &operator -= (const Vector3<S> &v) { return set(x - v.x, y - v.y, z - v.z); }
			template <typename S> inline Vector3<T> &operator *= (S val) { return set(x * val, y * val, z * val); }
			template <typename S> inline Vector3<T> &operator /= (S val) { T ival = (T)(1.0 / val); return set(x * ival, y * ival, z * ival); }

			inline T getSquaredLength() const { return x * x + y * y + z * z; }
			inline T getLength() const { return (T)sqrt(x * x + y * y + z * z); }

			template <typename S> inline T getSquaredDistance(const Vector3<S> &v) { T xd = (T)(v.x - x); T yd = (T)(v.y - y); T zd = (T)(v.z - z); return xd * xd + yd * yd + zd * zd; }
			template <typename S> inline T getDistance(const Vector3<S> &v) { T xd = (T)(v.x - x); T yd = (T)(v.y - y); T zd = (T)(v.z - z); (T)sqrt(xd * xd + yd * yd + zd * zd); }

			inline Vector3<T> &normalize() { return (*this * (T)(1.0 / getLength())); }

			template <typename S> inline T dot(const Vector3<S> &v) { return x * v.x + y * v.y + z * v.z; }
			template <typename S> inline Vector3<T> &cross(const Vector3<S> &v) { return set(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }

			inline Vector3<T> &rotate(const Vector3<T> &axis, T angle)
			{
				T s = (T)(sin(angle));
				T c = (T)(cos(angle));
				return set(cross(axis * s) + (*this * c) + (axis * (dot(axis * (1 - c)))));
			}
		};

		template <typename T, typename S> inline Vector3<T> operator * (S val, const Vector3<T> &v) { return Vector3<T>(v.x * val, v.y * val, v.z * val); }

		typedef Vector3<float> Vector3f;
		typedef Vector3<double> Vector3d;

		namespace Vector3Template
		{
			static const Vector3f Zero(0, 0, 0);
			static const Vector3f One(1, 1, 1);
		}

		namespace Color3Template
		{
			static const Vector3f White(1, 1, 1);
			static const Vector3f Black(0, 0, 0);
		}
	}
}

#endif