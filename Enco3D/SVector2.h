#ifndef __ENCO3D_SVECTOR2_H_INCLUDED__
#define __ENCO3D_SVECTOR2_H_INCLUDED__

#include "Enco3DDatatypes.h"
#include "Enco3DMath.h"

namespace enco
{
	namespace core
	{
		namespace math
		{
			template <typename T> struct Vector2
			{
				T x, y;

				inline Vector2() : x(0), y(0) {  }
				inline Vector2(T _x, T _y) : x(_x), y(_y) {  }
				inline Vector2(const Vector2<T> &v) : x(v.x), y(v.y) {  }

				inline Vector2<T> &clear() { x = y = 0; return *this; }
				inline Vector2<T> &set(T _x, T _y) { x = _x; y = _y; return *this; }
				inline Vector2<T> &set(const Vector2<T> &v) { x = v.x; y = v.y; return *this; }

				inline T getSquaredLength() const { return x*x + y*y; }
				inline T getLength() const { return (T)math::sqrt(x*x + y*y); }

				inline Vector2<T> getNormalized() const { return *this*(1.0 / getLength()); }

				inline Vector2<T> &setDirectionFromAngle(T angle) {
					float64 sin_cos[2];
					math::sin_cos((float64)angle, sin_cos);
					return set((T)sin_cos[__SIN_INDEX], (T)sin_cos[__COS_INDEX]);
				}
			};

			template <typename T>
			inline Vector2<T> operator - (const Vector2<T> &v) {
				return Vector2<T>(-v.x, -v.y);
			}

			template <typename T, typename S>
			inline Vector2<T> operator + (const Vector2<T> &v0, const Vector2<S> &v1) {
				return Vector2<T>(v0.x + v1.x, v0.y + v1.y);
			}

			template <typename T, typename S>
			inline Vector2<T> operator - (const Vector2<T> &v0, const Vector2<S> &v1) {
				return Vector2<T>(v0.x - v1.x, v0.y - v1.y);
			}

			template <typename T, typename S>
			inline Vector2<T> operator * (const Vector2<T> &v, S val) {
				return Vector2<T>(v.x * val, v.y * val);
			}

			template <typename T, typename S>
			inline Vector2<T> operator / (const Vector2<T> &v, S val) {
				T ival = (T)(1.0 / val); return Vector2<T>(v.x * ival, v.y * ival);
			}

			template <typename T, typename S>
			inline Vector2<T> &operator += (Vector2<T> &v0, const Vector2<S> &v1) {
				return v0.set(v0.x + v1.x, v0.y + v1.y);
			}

			template <typename T, typename S>
			inline Vector2<T> &operator -= (Vector2<T> &v0, const Vector2<S> &v1) {
				return v0.set(v0.x - v1.x, v0.y - v1.y);
			}

			template <typename T, typename S>
			inline Vector2<T> &operator *= (Vector2<T> &v, S val) {
				return v.set(v.x * val, v.y * val);
			}

			template <typename T, typename S>
			inline Vector2<T> &operator /= (Vector2<T> &v, S val) {
				T ival = (T)(1.0 / val); return v.set(v.x * ival, v.y * ival);
			}

			typedef Vector2<sint8>   Vector2s8;
			typedef Vector2<sint16>  Vector2s16;
			typedef Vector2<sint32>  Vector2s32;
			typedef Vector2<sint64>  Vector2s64;

			typedef Vector2<uint8>   Vector2u8;
			typedef Vector2<uint16>  Vector2u16;
			typedef Vector2<uint32>  Vector2u32;
			typedef Vector2<uint64>  Vector2u64;

			typedef Vector2<float32> Vector2f32;
			typedef Vector2<float64> Vector2f64;
		}
	}
}

#endif