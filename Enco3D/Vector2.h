#ifndef _ENCO3D_VECTOR2_H_
#define _ENCO3D_VECTOR2_H_

#include <math.h>

namespace Enco3D
{
	namespace Core
	{
		template <typename T>
		struct Vector2
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

			inline Vector2<T> &Clear() { x = y = 0; return *this; }
			inline Vector2<T> &Set(T _x, T _y) { x = _x; y = _y; return *this; }
			inline Vector2<T> &Set(const Vector2<T> &v) { x = v.x; y = v.y; return *this; }

			template <typename S> inline bool operator == (const Vector2<S> &v) const { return x == v.x && y == v.y; }
			template <typename S> inline bool operator != (const Vector2<S> &v) const { return x != v.x || y != v.y; }

			inline Vector2<T> operator - () const { return Vector2<T>(-x, -y); }

			template <typename S> inline Vector2<T> operator + (const Vector2<S> &v) const { return Vector2<T>(x + v.x, y + v.y); }
			template <typename S> inline Vector2<T> operator - (const Vector2<S> &v) const { return Vector2<T>(x - v.x, y - v.y); }
			template <typename S> inline Vector2<T> operator * (S val) const { return Vector2<T>(x * val, y * val); }
			template <typename S> inline Vector2<T> operator / (S val) const { T ival = (T)(1.0 / val); return Vector2<T>(x * ival, y * ival); }

			template <typename S> inline Vector2<T> &operator += (const Vector2<S> &v) { return Set(x + v.x, y + v.y); }
			template <typename S> inline Vector2<T> &operator -= (const Vector2<S> &v) { return Set(x - v.x, y - v.y); }
			template <typename S> inline Vector2<T> &operator *= (S val) { return Set(x * val, y * val); }
			template <typename S> inline Vector2<T> &operator /= (S val) { T ival = (T)(1.0 / val); return Set(x * ival, y * ival); }

			inline T GetSquaredLength() const { return x * x + y * y; }
			inline T GetLength() const { return (T)sqrt(x * x + y * y); }

			template <typename S> inline T GetSquaredDistance(const Vector2<S> &v) { T xd = (T)(v.x - x); T yd = (T)(v.y - y); return xd * xd + yd * yd; }
			template <typename S> inline T GetDistance(const Vector2<S> &v) { T xd = (T)(v.x - x); T yd = (T)(v.y - y); return (T)sqrt(xd * xd + yd * yd); }

			inline Vector2<T> &Normalize() { return (*this * (T)(1.0 / GetLength())); }

			template <typename S> inline T Dot(const Vector2<S> &v) { return x * v.x + y * v.y; }
			template <typename S> inline T Cross(const Vector2<S> &v) { return x * v.y - y * v.x; }
		};

		template <typename T, typename S> inline Vector2<T> operator * (S val, const Vector2<T> &v) { return Vector2<T>(v.x * val, v.y * val); }

		typedef Vector2<float> Vector2f;
		typedef Vector2<double> Vector2d;
	}
}

#endif