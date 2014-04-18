#ifndef __ENCO3D_SVECTOR3_H_INCLUDED__
#define __ENCO3D_SVECTOR3_H_INCLUDED__

#include "Enco3DDatatypes.h"
#include "Enco3DMath.h"
#include "SVector2.h"

namespace enco
{
	namespace core
	{
		namespace math
		{
			template <typename T> struct Vector3
			{
				T x, y, z;

				inline Vector3() : x(0), y(0), z(0) {  }
				inline Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {  }
				inline Vector3(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {  }
				inline Vector3(const Vector2<T> &v, T _z) : x(v.x), y(v.y), z(_z) {  }

				inline Vector3<T> &clear() { x = y = z = 0; return *this; }
				inline Vector3<T> &set(T _x, T _y, T _z) { x = _x; y = _y; z = _z; return *this; }
				inline Vector3<T> &set(const Vector3<T> &v) { x = v.x; y = v.y; z = v.z; return *this; }

				inline Vector3<T> &setDirectionFromYawPitch(T yaw, T pitch) {
					float64 sin_cos_yaw[2], sin_cos_pitch[2];
					math::sin_cos((float64)yaw+math::pi_div_2_f64, sin_cos_yaw);
					math::sin_cos((float64)pitch, sin_cos_pitch);
					return set((T)(-sin_cos_yaw[__COS_INDEX] * sin_cos_pitch[__COS_INDEX]),
						(T)(sin_cos_pitch[__SIN_INDEX]),
						(T)(sin_cos_yaw[__SIN_INDEX] * sin_cos_pitch[__COS_INDEX]));
				}

				inline T getSquaredLength() const { return x*x + y*y + z*z; }
				inline T getLength() const { return (T)math::sqrt((float64)x*x + y*y + z*z); }

				inline Vector3<T> getNormalized() const { return *this*((T)1.0 / getLength()); }

				inline T dot(const Vector3<T> &o) const { return x*o.x+y*o.y+z*o.z; } 

#ifdef __ENCO3D_DEBUG
				inline void print()
				{
					std::cout << x << ", " << y << ", " << z << std::endl;
				}
#endif
			};

			template <typename T, typename S>
			inline bool operator == (const Vector3<T> &v0, const Vector3<S> &v1) {
				return v0.x == v1.x && v0.y == v1.y && v0.z == v1.z;
			}

			template <typename T, typename S>
			inline bool operator != (const Vector3<T> &v0, const Vector3<S> &v1) {
				return v0.x != v1.x || v0.y != v1.y || v0.z != v1.z;
			}

			template <typename T>
			inline Vector3<T> operator - (const Vector3<T> &v) {
				return Vector3<T>(-v.x, -v.y, -v.z);
			}

			template <typename T, typename S>
			inline Vector3<T> operator + (const Vector3<T> &v0, const Vector3<S> &v1) {
				return Vector3<T>(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
			}

			template <typename T, typename S>
			inline Vector3<T> operator - (const Vector3<T> &v0, const Vector3<S> &v1) {
				return Vector3<T>(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
			}

			template <typename T, typename S>
			inline Vector3<T> operator * (const Vector3<T> &v, S val) {
				return Vector3<T>(v.x * val, v.y * val, v.z * val);
			}

			template <typename T, typename S>
			inline Vector3<T> operator / (const Vector3<T> &v, S val) {
				T ival = (T)(1.0 / val); return Vector3<T>(v.x * ival, v.y * ival, v.z * ival);
			}

			template <typename T, typename S>
			inline Vector3<T> &operator += (Vector3<T> &v0, const Vector3<S> &v1) {
				return v0.set(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
			}

			template <typename T, typename S>
			inline Vector3<T> &operator -= (Vector3<T> &v0, const Vector3<S> &v1) {
				return v0.set(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
			}

			template <typename T, typename S>
			inline Vector3<T> &operator *= (Vector3<T> &v, S val) {
				return v.set(v.x * val, v.y * val, v.z * val);
			}

			template <typename T, typename S>
			inline Vector3<T> &operator /= (Vector3<T> &v, S val) {
				T ival = (T)(1.0 / val); return v.set(v.x * ival, v.y * ival, v.z * ival);
			}


			typedef Vector3<sint8>   Vector3s8;
			typedef Vector3<sint16>  Vector3s16;
			typedef Vector3<sint32>  Vector3s32;
			typedef Vector3<sint64>  Vector3s64;

			typedef Vector3<uint8>   Vector3u8;
			typedef Vector3<uint16>  Vector3u16;
			typedef Vector3<uint32>  Vector3u32;
			typedef Vector3<uint64>  Vector3u64;

			typedef Vector3<float32> Vector3f32;
			typedef Vector3<float64> Vector3f64;
		}
	}
}

#endif