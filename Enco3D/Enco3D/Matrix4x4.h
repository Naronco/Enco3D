#ifndef _ENCO3D_MATRIX4X4_H_
#define _ENCO3D_MATRIX4X4_H_

#include "Matrix3x3.h"
#include "Vector4.h"

namespace Enco3D
{
	namespace Core
	{
		/// <summary>A 4x4 matrix structure</summary>
		template <typename T>
		struct Matrix4x4
		{
			union
			{
				struct
				{
					T m00, m01, m02, m03;
					T m10, m11, m12, m13;
					T m20, m21, m22, m23;
					T m30, m31, m32, m33;
				};

				T m[4][4];
			};

			inline Matrix4x4()
			{
				SetIdentity();
			}

			inline Matrix4x4(T _m00, T _m01, T _m02, T _m03, T _m10, T _m11, T _m12, T _m13, T _m20, T _m21, T _m22, T _m23, T _m30, T _m31, T _m32, T _m33)
			{
				Set(_m00, _m01, _m02, _m03, _m10, _m11, _m12, _m13, _m20, _m21, _m22, _m23, _m30, _m31, _m32, _m33);
			}

			inline Matrix4x4(const Matrix4x4<T> &m)
			{
				Set(m);
			}

			inline Matrix4x4<T> &Set(T _m00, T _m01, T _m02, T _m03, T _m10, T _m11, T _m12, T _m13, T _m20, T _m21, T _m22, T _m23, T _m30, T _m31, T _m32, T _m33)
			{
				m00 = _m00;
				m01 = _m01;
				m02 = _m02;
				m03 = _m03;
				m10 = _m10;
				m11 = _m11;
				m12 = _m12;
				m13 = _m13;
				m20 = _m20;
				m21 = _m21;
				m22 = _m22;
				m23 = _m23;
				m30 = _m30;
				m31 = _m31;
				m32 = _m32;
				m33 = _m33;
				return *this;
			}

			inline Matrix4x4<T> &Set(const Matrix4x4<T> &mat)
			{
				return Set(mat.m00, mat.m01, mat.m02, mat.m03, mat.m10, mat.m11, mat.m12, mat.m13, mat.m20, mat.m21, mat.m22, mat.m23, mat.m30, mat.m31, mat.m32, mat.m33);
			}

			inline Matrix4x4<T> &SetIdentity()
			{
				return Set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
			}

			inline Matrix4x4<T> operator * (const Matrix4x4<T> &mat) const
			{
				Matrix4x4<T> r;

				for (int y = 0; y < 4; y++)
				for (int x = 0; x < 4; x++)
				{
					r.m[x][y] = (m[x][0] * mat.m[0][y]) + (m[x][1] * mat.m[1][y]) + (m[x][2] * mat.m[2][y]) + (m[x][3] * mat.m[3][y]);
				}

				return r;
			}

			inline Matrix4x4<T> &operator *= (const Matrix4x4<T> &mat)
			{
				Matrix4x4<T> r;

				for (int y = 0; y < 4; y++)
				for (int x = 0; x < 4; x++)
				{
					r.m[x][y] = (m[x][0] * mat.m[0][y]) + (m[x][1] * mat.m[1][y]) + (m[x][2] * mat.m[2][y]) + (m[x][3] * mat.m[3][y]);
				}

				return Set(r);
			}

			inline Matrix4x4<T> &Translate(T x, T y, T z)
			{
				return (*this *= Matrix4x4<T>(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1));
			}

			inline Matrix4x4<T> &RotateX(T angle)
			{
				T s = (T)sin(angle);
				T c = (T)cos(angle);
				return (*this *= Matrix4x4<T>(1, 0, 0, 0, 0, c, -s, 0, 0, s, c, 0, 0, 0, 0, 1));
			}

			inline Matrix4x4<T> &RotateY(T angle)
			{
				T s = (T)sin(angle);
				T c = (T)cos(angle);
				return (*this *= Matrix4x4<T>(c, 0, s, 0, 0, 1, 0, 0, -s, 0, c, 0, 0, 0, 0, 1));
			}

			inline Matrix4x4<T> &RotateZ(T angle)
			{
				T s = (T)sin(angle);
				T c = (T)cos(angle);
				return (*this *= Matrix4x4<T>(c, -s, 0, 0, s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
			}

			inline Matrix4x4<T> &Scale(T x, T y, T z)
			{
				return (*this *= Matrix4x4<T>(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1));
			}

			inline Matrix4x4<T> &SetRotation(const Matrix3x3<T> &m)
			{
				m00 = m.m00;
				m01 = m.m01;
				m02 = m.m02;
				m10 = m.m10;
				m11 = m.m11;
				m12 = m.m12;
				m20 = m.m20;
				m21 = m.m21;
				m22 = m.m22;
				return *this;
			}

			inline Matrix4x4<T> &SetRotation(const Vector3<T> &forward, const Vector3<T> &up, const Vector3<T> &right)
			{
				return Set(right.x, right.y, right.z, 0, up.x, up.y, up.z, 0, forward.x, forward.y, forward.z, 0, 0, 0, 0, 1);
			}

			inline Matrix4x4<T> &SetRotation(const Vector3<T> &forward, const Vector3<T> &up)
			{
				Vector3<T> right(up);
				right.Cross(forward).Normalize();

				return SetRotation(forward, up, right);
			}

			inline Matrix4x4<T> &SetOrthographicProjection(T left, T right, T bottom, T top, T zNear, T zFar)
			{
				T width = right - left;
				T height = top - bottom;
				T depth = zFar - zNear;

				return Set(2 / width, 0, 0, -(right + left) / width, 0, 2 / height, 0, -(top + bottom) / height, 0, 0, -2 / depth, -(zFar + zNear) / depth, 0, 0, 0, 1);
			}

			inline Matrix4x4<T> &SetPerspectiveProjection(T fov, T aspectRatio, T zNear, T zFar)
			{
				T tanHalfFov = (T)tan(fov * 0.5);
				T zRange = zNear - zFar;

				return Set((T)(1.0 / (tanHalfFov * aspectRatio)), 0, 0, 0, 0, (T)(1.0 / tanHalfFov), 0, 0, 0, 0, (-zNear - zFar) / zRange, 2 * zFar * zNear / zRange, 0, 0, 1, 0);
			}

			inline Matrix4x4<T> &Transpose()
			{
				return Set(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			}
		};

		template <typename T1, typename T2>
		inline Vector4<T1> &operator *= (const Vector4<T1> &v, const Matrix4x4<T2> &m)
		{
			return v.Set(m.m00 * v.x + m.m01 * v.y + m.m02 * v.z + m.m03 * v.w,
				m.m10 * v.x + m.m11 * v.y + m.m12 * v.z + m.m13 * v.w,
				m.m20 * v.x + m.m21 * v.y + m.m22 * v.z + m.m23 * v.w,
				m.m33 * v.w);
		}

		template <typename T1, typename T2>
		inline Vector4<T1> operator * (const Vector4<T1> &v, const Matrix4x4<T2> &m)
		{
			return Vector4<T1>(m.m00 * v.x + m.m01 * v.y + m.m02 * v.z + m.m03 * v.w,
				m.m10 * v.x + m.m11 * v.y + m.m12 * v.z + m.m13 * v.w,
				m.m20 * v.x + m.m21 * v.y + m.m22 * v.z + m.m23 * v.w,
				m.m33 * v.w);
		}

		template <typename T1, typename T2>
		inline Vector4<T1> operator * (const Matrix4x4<T2> &m, const Vector4<T1> &v)
		{
			return Vector4<T1>(m.m00 * v.x + m.m01 * v.y + m.m02 * v.z + m.m03 * v.w,
				m.m10 * v.x + m.m11 * v.y + m.m12 * v.z + m.m13 * v.w,
				m.m20 * v.x + m.m21 * v.y + m.m22 * v.z + m.m23 * v.w,
				m.m33 * v.w);
		}

		template <typename T1, typename T2>
		inline Vector3<T1> operator * (const Vector3<T1> &v, const Matrix4x4<T2> &m)
		{
			return Vector3<T1>(m.m00 * v.x + m.m01 * v.y + m.m02 * v.z + m.m03,
				m.m10 * v.x + m.m11 * v.y + m.m12 * v.z + m.m13,
				m.m20 * v.x + m.m21 * v.y + m.m22 * v.z + m.m23);
		}

		template <typename T1, typename T2>
		inline Vector3<T1> operator * (const Matrix4x4<T2> &m, const Vector3<T1> &v)
		{
			return Vector3<T1>(m.m00 * v.x + m.m01 * v.y + m.m02 * v.z + m.m03,
				m.m10 * v.x + m.m11 * v.y + m.m12 * v.z + m.m13,
				m.m20 * v.x + m.m21 * v.y + m.m22 * v.z + m.m23);
		}

		typedef Matrix4x4<float> Matrix4x4f;
		typedef Matrix4x4<double> Matrix4x4d;
	}
}

#endif