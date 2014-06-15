#ifndef _ENCO3D_VECTOR2_H_
#define _ENCO3D_VECTOR2_H_

#include <math.h>
#include "DLLExport.h"

namespace Enco3D
{
	namespace Core
	{
		template <typename T> struct DLL_EXPORT Vector2
		{
			union
			{
				struct
				{
					T x, y;
				};

				T xy[2];
			};

			inline Vector2(T _x = 0, T _y = 0) : x(_x), y(_y) {  }
			inline Vector2(const Vector2<T> &v) : x(v.x), y(v.y) {  }

			inline Vector2<T> &clear() { x = y = 0; return *this; }
			inline Vector2<T> &set(T _x, T _y) { x = _x; y = _y; return *this; }
			inline Vector2<T> &set(const Vector2<T> &v) { x = v.x; y = v.y; return *this; }

			template <typename S> inline bool operator == (const Vector2<S> &v) const { return x == v.x && y == v.y; }
			template <typename S> inline bool operator != (const Vector2<S> &v) const { return x != v.x || y != v.y; }

			inline Vector2<T> operator - () const { return Vector2<T>(-x, -y); }

			template <typename S> inline Vector2<T> operator + (const Vector2<S> &v) const { return Vector2<T>(x + v.x, y + v.y); }
			template <typename S> inline Vector2<T> operator - (const Vector2<S> &v) const { return Vector2<T>(x - v.x, y - v.y); }
			template <typename S> inline Vector2<T> operator * (S val) const { return Vector2<T>(x * val, y * val); }
			template <typename S> inline Vector2<T> operator / (S val) const { T ival = (T)(1.0 / val); return Vector2<T>(x * ival, y * ival); }

			template <typename S> inline Vector2<T> &operator += (const Vector2<S> &v) { return set(x + v.x, y + v.y); }
			template <typename S> inline Vector2<T> &operator -= (const Vector2<S> &v) { return set(x - v.x, y - v.y); }
			template <typename S> inline Vector2<T> &operator *= (S val) { return set(x * val, y * val); }
			template <typename S> inline Vector2<T> &operator /= (S val) { T ival = (T)(1.0 / val); return set(x * ival, y * ival); }

			inline T getSquaredLength() const { return x * x + y * y; }
			inline T getLength() const { return (T)sqrt(x * x + y * y); }

			template <typename S> inline T getSquaredDistance(const Vector2<S> &v) { T xd = (T)(v.x - x); T yd = (T)(v.y - y); return xd * xd + yd * yd; }
			template <typename S> inline T getDistance(const Vector2<S> &v) { T xd = (T)(v.x - x); T yd = (T)(v.y - y); return (T)sqrt(xd * xd + yd * yd); }

			inline Vector2<T> &normalize() { return (*this * (T)(1.0 / getLength())); }

			template <typename S> inline T dot(const Vector2<S> &v) { return x * v.x + y * v.y; }
			template <typename S> inline T cross(const Vector2<S> &v) { return x * v.y - y * v.x; }
		};

		template <typename T, typename S> inline Vector2<T> operator * (S val, const Vector2<T> &v) { return Vector2<T>(v.x * val, v.y * val); }

		typedef Vector2<float> Vector2f;
		typedef Vector2<double> Vector2d;

		namespace Vector2Template
		{
			static Vector2f Zero(0, 0);
			static Vector2f One(1, 1);
		}
	}
}

#endif