#ifndef _ENCO3D_VECTOR4_H_
#define _ENCO3D_VECTOR4_H_

#include "Vector3.h"

namespace Enco3D
{
	namespace Core
	{
		template <typename T>
		struct Vector4
		{
			union
			{
				struct
				{
					T x, y, z, w;
				};

				T xyzw[4];
			};

			inline Vector4(T _x = 0, T _y = 0, T _z = 0, T _w = 0) : x(_x), y(_y), z(_z), w(_w) {  }
			inline Vector4(const Vector4<T> &v) : x(v.x), y(v.y), z(v.z), w(v.w) {  }

			inline Vector4<T> &Clear() { x = y = z = w = 0; return *this; }
			inline Vector4<T> &Set(T _x, T _y, T _z, T _w) { x = _x; y = _y; z = _z; w = _w; return *this; }
			inline Vector4<T> &Set(const Vector4<T> &v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }

			template <typename S> inline bool operator == (const Vector4<S> &v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }
			template <typename S> inline bool operator != (const Vector4<S> &v) const { return x != v.x || y != v.y || z != v.z || w != v.w; }

			inline Vector4<T> operator - () const { return Vector4<T>(-x, -y, -z, w); }

			template <typename S> inline Vector4<T> operator + (const Vector4<S> &v) const { return Vector4<T>(x + v.x, y + v.y, z + v.z, w); }
			template <typename S> inline Vector4<T> operator - (const Vector4<S> &v) const { return Vector4<T>(x - v.x, y - v.y, z - v.z, w); }
			template <typename S> inline Vector4<T> operator * (S val) const { return Vector4<T>(x * val, y * val, z * val, w); }
			template <typename S> inline Vector4<T> operator / (S val) const { T ival = (T)(1.0 / val); return Vector4<T>(x * ival, y * ival, z * ival, w); }

			template <typename S> inline Vector4<T> &operator += (const Vector4<S> &v) { return Set(x + v.x, y + v.y, z + v.z, w); }
			template <typename S> inline Vector4<T> &operator -= (const Vector4<S> &v) { return Set(x - v.x, y - v.y, z - v.z, w); }
			template <typename S> inline Vector4<T> &operator *= (S val) { return Set(x * val, y * val, z * val, w); }
			template <typename S> inline Vector4<T> &operator /= (S val) { T ival = (T)(1.0 / val); return Set(x * ival, y * ival, z * ival, w); }

			inline T GetSquaredLength() const { return x * x + y * y + z * z + w * w; }
			inline T GetLength() const { return (T)sqrt(x * x + y * y + z * z + w * w); }

			template <typename S> inline T GetSquaredDistance(const Vector4<S> &v) { T xd = (T)(v.x - x); T yd = (T)(v.y - y); T zd = (T)(v.z - z); return xd * xd + yd * yd + zd * zd; }
			template <typename S> inline T GetDistance(const Vector4<S> &v) { T xd = (T)(v.x - x); T yd = (T)(v.y - y); T zd = (T)(v.z - z); (T)sqrt(xd * xd + yd * yd + zd * zd); }

			inline Vector4<T> &Normalize() { return (*this * (T)(1.0 / GetLength())); }

			template <typename S> inline T Dot(const Vector4<S> &v) { return x * v.x + y * v.y + z * v.z + w * v.w; }
			template <typename S> inline Vector4<T> &Cross(const Vector4<S> &v) { return Set(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x, w); }
		};

		template <typename T, typename S> inline Vector4<T> operator * (S val, const Vector4<T> &v) { return Vector4<T>(v.x * val, v.y * val, v.z * val, v.w); }

		typedef Vector4<float> Vector4f;
		typedef Vector4<double> Vector4d;
	}
}

#endif