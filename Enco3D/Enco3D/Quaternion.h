#ifndef _ENCO3D_QUATERNION_H_
#define _ENCO3D_QUATERNION_H_

#include <math.h>
#include "DLLExport.h"

#include "Vector3.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

namespace Enco3D
{
	namespace Core
	{
		template <typename T> struct DLL_EXPORT Quaternion
		{
			T x, y, z, w;

			inline Quaternion() : x(0), y(0), z(0), w(0) {  }
			inline Quaternion(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {  }
			inline Quaternion(const Quaternion<T> &q) : x(q.x), y(q.y), z(q.z), w(q.w) {  }

			inline Quaternion(const Vector3<T> &axis, T angle)
			{
				T s = (T)sin(angle * 0.5);
				T c = (T)cos(angle * 0.5);

				set(axis.x * s, axis.y * s, axis.z * s, c);
			}

			inline Quaternion(T rotX, T rotY, T rotZ)
			{
				T srx = (T)sin(rotX * 0.5);
				T crx = (T)cos(rotX * 0.5);

				T sry = (T)sin(rotY * 0.5);
				T cry = (T)cos(rotY * 0.5);

				T srz = (T)sin(rotZ * 0.5);
				T crz = (T)cos(rotZ * 0.5);

				w = crx * cry * crz + srx * sry * srz;
				x = srx * cry * crz - crx * sry * srz;
				y = crx * sry * crz + srx * cry * srz;
				z = crx * cry * srz - srx * sry * crz;
			}

			inline Quaternion<T> &clear() { x = y = z = w = 0; return *this; }
			inline Quaternion<T> &set(T _x, T _y, T _z, T _w) { x = _x; y = _y; z = _z; w = _w; return *this; }
			inline Quaternion<T> &set(const Quaternion<T> &q) { x = q.x; y = q.y; z = q.z; w = q.w; return *this; }

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

			inline T getSquaredLength() const { return x * x + y * y + z * z + w * w; }
			inline T getLength() const { return (T)sqrt(x * x + y * y + z * z + w * w); }

			inline Quaternion<T> &normalize()
			{
				return (*this * ((T)(1.0 / getLength())));
			}

			template <typename S> inline void rotateVector(Vector3<S> *v) const
			{
				Quaternion<S> conjugate = -(*this);
				Quaternion<S> w = ((*this) * (*v)) * conjugate;
				v->set(w.x, w.y, w.z);
			}

			inline Matrix3x3<T> &toRotationMatrix3x3() const
			{
				Vector3<T> forward(2 * (x * z - w * y), 2 * (y * z + w * x), 1 - 2 * (x * x + y * y));
				Vector3<T> up(2 * (x * y + w * z), 1 - 2 * (x * x + z * z), 2 * (y * z - w * x));
				Vector3<T> right(1 - 2 * (y * y + z * z), 2 * (x * y - w * z), 2 * (x * z + w * y));

				return Matrix3x3<T>().setRotation(forward, up, right);
			}

			inline Matrix4x4<T> &toRotationMatrix4x4() const
			{
				Vector3<T> forward(2 * (x * z - w * y), 2 * (y * z + w * x), 1 - 2 * (x * x + y * y));
				Vector3<T> up(2 * (x * y + w * z), 1 - 2 * (x * x + z * z), 2 * (y * z - w * x));
				Vector3<T> right(1 - 2 * (y * y + z * z), 2 * (x * y - w * z), 2 * (x * z + w * y));

				return Matrix4x4<T>().setRotation(forward, up, right);
			}

			inline Vector3<T> getForward() const { Vector3<T> dir(0, 0, 1); rotateVector(&dir); return dir; }
			inline Vector3<T> getUp() const { Vector3<T> dir(0, 1, 0); rotateVector(&dir); return dir; }
			inline Vector3<T> getRight() const { Vector3<T> dir(1, 0, 0); rotateVector(&dir); return dir; }
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
	}
}

#endif