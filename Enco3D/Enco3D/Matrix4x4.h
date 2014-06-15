#ifndef _ENCO3D_MATRIX4X4_H_
#define _ENCO3D_MATRIX4X4_H_

#include "Matrix3x3.h"
#include "Vector4.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Core
	{
		/// <summary>A 4x4 matrix structure</summary>
		template <typename T> struct DLL_EXPORT Matrix4x4
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
				setIdentity();
			}

			inline Matrix4x4(T _m00, T _m01, T _m02, T _m03, T _m10, T _m11, T _m12, T _m13, T _m20, T _m21, T _m22, T _m23, T _m30, T _m31, T _m32, T _m33)
			{
				set(_m00, _m01, _m02, _m03, _m10, _m11, _m12, _m13, _m20, _m21, _m22, _m23, _m30, _m31, _m32, _m33);
			}

			inline Matrix4x4(const Matrix4x4<T> &m)
			{
				set(m);
			}

			inline Matrix4x4<T> &set(T _m00, T _m01, T _m02, T _m03, T _m10, T _m11, T _m12, T _m13, T _m20, T _m21, T _m22, T _m23, T _m30, T _m31, T _m32, T _m33)
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

			inline Matrix4x4<T> &set(const Matrix4x4<T> &mat)
			{
				return set(mat.m00, mat.m01, mat.m02, mat.m03, mat.m10, mat.m11, mat.m12, mat.m13, mat.m20, mat.m21, mat.m22, mat.m23, mat.m30, mat.m31, mat.m32, mat.m33);
			}

			inline Matrix4x4<T> &setIdentity()
			{
				return set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
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

			inline bool operator == (const Matrix4x4<T> &other) const
			{
				return other.m00 == m00 &&
					other.m01 == m01 &&
					other.m02 == m02 &&
					other.m03 == m03 &&
					other.m10 == m10 &&
					other.m11 == m11 &&
					other.m12 == m12 &&
					other.m13 == m13 &&
					other.m20 == m20 &&
					other.m21 == m21 &&
					other.m22 == m22 &&
					other.m23 == m23 &&
					other.m30 == m30 &&
					other.m31 == m31 &&
					other.m32 == m32 &&
					other.m33 == m33;
			}

			inline Matrix4x4<T> &operator *= (const Matrix4x4<T> &mat)
			{
				Matrix4x4<T> r;

				for (int y = 0; y < 4; y++)
					for (int x = 0; x < 4; x++)
					{
					r.m[x][y] = (m[x][0] * mat.m[0][y]) + (m[x][1] * mat.m[1][y]) + (m[x][2] * mat.m[2][y]) + (m[x][3] * mat.m[3][y]);
					}

				return set(r);
			}

			inline Matrix4x4<T> &setTranslation(T x, T y, T z)
			{
				return set(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1);
			}

			inline Matrix4x4<T> &translate(T x, T y, T z)
			{
				return (*this *= Matrix4x4<T>(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1));
			}

			inline Matrix4x4<T> &setRotationX(T angle)
			{
				T s = (T)sin(angle);
				T c = (T)cos(angle);
				return set(1, 0, 0, 0, 0, c, -s, 0, 0, s, c, 0, 0, 0, 0, 1);
			}

			inline Matrix4x4<T> &rotateX(T angle)
			{
				T s = (T)sin(angle);
				T c = (T)cos(angle);
				return (*this *= Matrix4x4<T>(1, 0, 0, 0, 0, c, -s, 0, 0, s, c, 0, 0, 0, 0, 1));
			}

			inline Matrix4x4<T> &setRotationY(T angle)
			{
				T s = (T)sin(angle);
				T c = (T)cos(angle);
				return set(c, 0, s, 0, 0, 1, 0, 0, -s, 0, c, 0, 0, 0, 0, 1);
			}

			inline Matrix4x4<T> &rotateY(T angle)
			{
				T s = (T)sin(angle);
				T c = (T)cos(angle);
				return (*this *= Matrix4x4<T>(c, 0, s, 0, 0, 1, 0, 0, -s, 0, c, 0, 0, 0, 0, 1));
			}

			inline Matrix4x4<T> &setRotationZ(T angle)
			{
				T s = (T)sin(angle);
				T c = (T)cos(angle);
				return set(c, -s, 0, 0, s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
			}

			inline Matrix4x4<T> &rotateZ(T angle)
			{
				T s = (T)sin(angle);
				T c = (T)cos(angle);
				return (*this *= Matrix4x4<T>(c, -s, 0, 0, s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
			}

			inline Matrix4x4<T> &setScaling(T x, T y, T z)
			{
				return set(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1);
			}

			inline Matrix4x4<T> &setScaling(T s)
			{
				return set(s, 0, 0, 0, 0, s, 0, 0, 0, 0, s, 0, 0, 0, 0, 1);
			}

			inline Matrix4x4<T> &scale(T x, T y, T z)
			{
				return (*this *= Matrix4x4<T>(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1));
			}

			inline Matrix4x4<T> &scale(T s)
			{
				return (*this *= Matrix4x4<T>(s, 0, 0, 0, 0, s, 0, 0, 0, 0, s, 0, 0, 0, 0, 1));
			}

			inline Matrix4x4<T> &setRotation(const Matrix3x3<T> &m)
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

			inline Matrix4x4<T> &setRotation(const Vector3<T> &forward, const Vector3<T> &up, const Vector3<T> &right)
			{
				return set(right.x, right.y, right.z, 0, up.x, up.y, up.z, 0, forward.x, forward.y, forward.z, 0, 0, 0, 0, 1);
			}

			inline Matrix4x4<T> &setRotation(const Vector3<T> &forward, const Vector3<T> &up)
			{
				Vector3<T> right(up);
				right.cross(forward).normalize();

				return setRotation(forward, up, right);
			}

			inline Matrix4x4<T> &setOrthographicProjection(T left, T right, T bottom, T top, T zNear, T zFar)
			{
				T width = right - left;
				T height = top - bottom;
				T depth = zFar - zNear;

				return set(2 / width, 0, 0, -(right + left) / width, 0, 2 / height, 0, -(top + bottom) / height, 0, 0, -2 / depth, -(zFar + zNear) / depth, 0, 0, 0, 1);
			}

			inline Matrix4x4<T> &setPerspectiveProjection(T fov, T aspectRatio, T zNear, T zFar)
			{
				T tanHalfFov = (T)tan(fov * 0.5);
				T zRange = zNear - zFar;

				return set((T)(1.0 / (tanHalfFov * aspectRatio)), 0, 0, 0, 0, (T)(1.0 / tanHalfFov), 0, 0, 0, 0, (-zNear - zFar) / zRange, 2 * zFar * zNear / zRange, 0, 0, 1, 0);
			}

			inline Matrix4x4<T> &transpose()
			{
				return set(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			}

			inline Matrix4x4<T> createBillboard(const Vector3<T>& objectPosition, const Vector3<T>& cameraPosition, const Vector3<T>& cameraUpVector)
			{
				Vector3<T> vector;
				Vector3<T> vector2;
				Vector3<T> vector3;
				vector = objectPosition - cameraPosition;
				float num = vector.getSquaredLength();
				if (num < 0.0001f)
				{
					vector = Vector3Template::Forward;
				}
				else
				{
					vector = (float)(1.0f / ((float)sqrt((double)num))) * vector;
				}
				vector3 = cameraUpVector.cross(vector);
				vector3.normalize();
				vector2 = vector.cross(vector3);

				Vector3<T> result;

				result.m00 = vector3.x;
				result.m01 = vector3.y;
				result.m02 = vector3.z;
				result.m03 = 0;
				result.m10 = vector2.x;
				result.m11 = vector2.y;
				result.m12 = vector2.z;
				result.m13 = 0;
				result.m20 = vector.x;
				result.m21 = vector.y;
				result.m22 = vector.z;
				result.m23 = 0;
				result.m30 = objectPosition.x;
				result.m31 = objectPosition.y;
				result.m32 = objectPosition.z;
				result.m33 = 1;

				return result;
			}

			inline Matrix4x4<T> getTranspose()
			{
				return Matrix4x4<T>(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
			}

			inline float getAtIndex(int index)
			{
				return m[index % 4][index >> 2];
			}

			inline Matrix4x4<T> inverse()
			{
				float inv[16];

				inv[0] = getAtIndex(5) * getAtIndex(10) * getAtIndex(15) -
					getAtIndex(5) * getAtIndex(11) * getAtIndex(14) -
					getAtIndex(9) * getAtIndex(6) * getAtIndex(15) +
					getAtIndex(9) * getAtIndex(7) * getAtIndex(14) +
					getAtIndex(13) * getAtIndex(6) * getAtIndex(11) -
					getAtIndex(13) * getAtIndex(7) * getAtIndex(10);

				inv[4] = -getAtIndex(4) * getAtIndex(10) * getAtIndex(15) +
					getAtIndex(4) * getAtIndex(11) * getAtIndex(14) +
					getAtIndex(8) * getAtIndex(6) * getAtIndex(15) -
					getAtIndex(8) * getAtIndex(7) * getAtIndex(14) -
					getAtIndex(12) * getAtIndex(6) * getAtIndex(11) +
					getAtIndex(12) * getAtIndex(7) * getAtIndex(10);

				inv[8] = getAtIndex(4) * getAtIndex(9) * getAtIndex(15) -
					getAtIndex(4) * getAtIndex(11) * getAtIndex(13) -
					getAtIndex(8) * getAtIndex(5) * getAtIndex(15) +
					getAtIndex(8) * getAtIndex(7) * getAtIndex(13) +
					getAtIndex(12) * getAtIndex(5) * getAtIndex(11) -
					getAtIndex(12) * getAtIndex(7) * getAtIndex(9);

				inv[12] = -getAtIndex(4) * getAtIndex(9) * getAtIndex(14) +
					getAtIndex(4) * getAtIndex(10) * getAtIndex(13) +
					getAtIndex(8) * getAtIndex(5) * getAtIndex(14) -
					getAtIndex(8) * getAtIndex(6) * getAtIndex(13) -
					getAtIndex(12) * getAtIndex(5) * getAtIndex(10) +
					getAtIndex(12) * getAtIndex(6) * getAtIndex(9);

				inv[1] = -getAtIndex(1) * getAtIndex(10) * getAtIndex(15) +
					getAtIndex(1) * getAtIndex(11) * getAtIndex(14) +
					getAtIndex(9) * getAtIndex(2) * getAtIndex(15) -
					getAtIndex(9) * getAtIndex(3) * getAtIndex(14) -
					getAtIndex(13) * getAtIndex(2) * getAtIndex(11) +
					getAtIndex(13) * getAtIndex(3) * getAtIndex(10);

				inv[5] = getAtIndex(0) * getAtIndex(10) * getAtIndex(15) -
					getAtIndex(0) * getAtIndex(11) * getAtIndex(14) -
					getAtIndex(8) * getAtIndex(2) * getAtIndex(15) +
					getAtIndex(8) * getAtIndex(3) * getAtIndex(14) +
					getAtIndex(12) * getAtIndex(2) * getAtIndex(11) -
					getAtIndex(12) * getAtIndex(3) * getAtIndex(10);

				inv[9] = -getAtIndex(0) * getAtIndex(9) * getAtIndex(15) +
					getAtIndex(0) * getAtIndex(11) * getAtIndex(13) +
					getAtIndex(8) * getAtIndex(1) * getAtIndex(15) -
					getAtIndex(8) * getAtIndex(3) * getAtIndex(13) -
					getAtIndex(12) * getAtIndex(1) * getAtIndex(11) +
					getAtIndex(12) * getAtIndex(3) * getAtIndex(9);

				inv[13] = getAtIndex(0) * getAtIndex(9) * getAtIndex(14) -
					getAtIndex(0) * getAtIndex(10) * getAtIndex(13) -
					getAtIndex(8) * getAtIndex(1) * getAtIndex(14) +
					getAtIndex(8) * getAtIndex(2) * getAtIndex(13) +
					getAtIndex(12) * getAtIndex(1) * getAtIndex(10) -
					getAtIndex(12) * getAtIndex(2) * getAtIndex(9);

				inv[2] = getAtIndex(1) * getAtIndex(6) * getAtIndex(15) -
					getAtIndex(1) * getAtIndex(7) * getAtIndex(14) -
					getAtIndex(5) * getAtIndex(2) * getAtIndex(15) +
					getAtIndex(5) * getAtIndex(3) * getAtIndex(14) +
					getAtIndex(13) * getAtIndex(2) * getAtIndex(7) -
					getAtIndex(13) * getAtIndex(3) * getAtIndex(6);

				inv[6] = -getAtIndex(0) * getAtIndex(6) * getAtIndex(15) +
					getAtIndex(0) * getAtIndex(7) * getAtIndex(14) +
					getAtIndex(4) * getAtIndex(2) * getAtIndex(15) -
					getAtIndex(4) * getAtIndex(3) * getAtIndex(14) -
					getAtIndex(12) * getAtIndex(2) * getAtIndex(7) +
					getAtIndex(12) * getAtIndex(3) * getAtIndex(6);

				inv[10] = getAtIndex(0) * getAtIndex(5) * getAtIndex(15) -
					getAtIndex(0) * getAtIndex(7) * getAtIndex(13) -
					getAtIndex(4) * getAtIndex(1) * getAtIndex(15) +
					getAtIndex(4) * getAtIndex(3) * getAtIndex(13) +
					getAtIndex(12) * getAtIndex(1) * getAtIndex(7) -
					getAtIndex(12) * getAtIndex(3) * getAtIndex(5);

				inv[14] = -getAtIndex(0) * getAtIndex(5) * getAtIndex(14) +
					getAtIndex(0) * getAtIndex(6) * getAtIndex(13) +
					getAtIndex(4) * getAtIndex(1) * getAtIndex(14) -
					getAtIndex(4) * getAtIndex(2) * getAtIndex(13) -
					getAtIndex(12) * getAtIndex(1) * getAtIndex(6) +
					getAtIndex(12) * getAtIndex(2) * getAtIndex(5);

				inv[3] = -getAtIndex(1) * getAtIndex(6) * getAtIndex(11) +
					getAtIndex(1) * getAtIndex(7) * getAtIndex(10) +
					getAtIndex(5) * getAtIndex(2) * getAtIndex(11) -
					getAtIndex(5) * getAtIndex(3) * getAtIndex(10) -
					getAtIndex(9) * getAtIndex(2) * getAtIndex(7) +
					getAtIndex(9) * getAtIndex(3) * getAtIndex(6);

				inv[7] = getAtIndex(0) * getAtIndex(6) * getAtIndex(11) -
					getAtIndex(0) * getAtIndex(7) * getAtIndex(10) -
					getAtIndex(4) * getAtIndex(2) * getAtIndex(11) +
					getAtIndex(4) * getAtIndex(3) * getAtIndex(10) +
					getAtIndex(8) * getAtIndex(2) * getAtIndex(7) -
					getAtIndex(8) * getAtIndex(3) * getAtIndex(6);

				inv[11] = -getAtIndex(0) * getAtIndex(5) * getAtIndex(11) +
					getAtIndex(0) * getAtIndex(7) * getAtIndex(9) +
					getAtIndex(4) * getAtIndex(1) * getAtIndex(11) -
					getAtIndex(4) * getAtIndex(3) * getAtIndex(9) -
					getAtIndex(8) * getAtIndex(1) * getAtIndex(7) +
					getAtIndex(8) * getAtIndex(3) * getAtIndex(5);

				inv[15] = getAtIndex(0) * getAtIndex(5) * getAtIndex(10) -
					getAtIndex(0) * getAtIndex(6) * getAtIndex(9) -
					getAtIndex(4) * getAtIndex(1) * getAtIndex(10) +
					getAtIndex(4) * getAtIndex(2) * getAtIndex(9) +
					getAtIndex(8) * getAtIndex(1) * getAtIndex(6) -
					getAtIndex(8) * getAtIndex(2) * getAtIndex(5);

				float det = getAtIndex(0) * inv[0] + getAtIndex(1) * inv[4] + getAtIndex(2) * inv[8] + getAtIndex(3) * inv[12];

				if (det == 0.0f)
					return *this;

				det = 1.0f / det;

				for (int i = 0; i < 16; i++)
					m[i % 4][i >> 2] = inv[i] * det;

				return *this;
			}

			inline Matrix4x4<T> getInverse()
			{
				float inv[16];

				inv[0] = getAtIndex(5) * getAtIndex(10) * getAtIndex(15) -
					getAtIndex(5) * getAtIndex(11) * getAtIndex(14) -
					getAtIndex(9) * getAtIndex(6) * getAtIndex(15) +
					getAtIndex(9) * getAtIndex(7) * getAtIndex(14) +
					getAtIndex(13) * getAtIndex(6) * getAtIndex(11) -
					getAtIndex(13) * getAtIndex(7) * getAtIndex(10);

				inv[4] = -getAtIndex(4) * getAtIndex(10) * getAtIndex(15) +
					getAtIndex(4) * getAtIndex(11) * getAtIndex(14) +
					getAtIndex(8) * getAtIndex(6) * getAtIndex(15) -
					getAtIndex(8) * getAtIndex(7) * getAtIndex(14) -
					getAtIndex(12) * getAtIndex(6) * getAtIndex(11) +
					getAtIndex(12) * getAtIndex(7) * getAtIndex(10);

				inv[8] = getAtIndex(4) * getAtIndex(9) * getAtIndex(15) -
					getAtIndex(4) * getAtIndex(11) * getAtIndex(13) -
					getAtIndex(8) * getAtIndex(5) * getAtIndex(15) +
					getAtIndex(8) * getAtIndex(7) * getAtIndex(13) +
					getAtIndex(12) * getAtIndex(5) * getAtIndex(11) -
					getAtIndex(12) * getAtIndex(7) * getAtIndex(9);

				inv[12] = -getAtIndex(4) * getAtIndex(9) * getAtIndex(14) +
					getAtIndex(4) * getAtIndex(10) * getAtIndex(13) +
					getAtIndex(8) * getAtIndex(5) * getAtIndex(14) -
					getAtIndex(8) * getAtIndex(6) * getAtIndex(13) -
					getAtIndex(12) * getAtIndex(5) * getAtIndex(10) +
					getAtIndex(12) * getAtIndex(6) * getAtIndex(9);

				inv[1] = -getAtIndex(1) * getAtIndex(10) * getAtIndex(15) +
					getAtIndex(1) * getAtIndex(11) * getAtIndex(14) +
					getAtIndex(9) * getAtIndex(2) * getAtIndex(15) -
					getAtIndex(9) * getAtIndex(3) * getAtIndex(14) -
					getAtIndex(13) * getAtIndex(2) * getAtIndex(11) +
					getAtIndex(13) * getAtIndex(3) * getAtIndex(10);

				inv[5] = getAtIndex(0) * getAtIndex(10) * getAtIndex(15) -
					getAtIndex(0) * getAtIndex(11) * getAtIndex(14) -
					getAtIndex(8) * getAtIndex(2) * getAtIndex(15) +
					getAtIndex(8) * getAtIndex(3) * getAtIndex(14) +
					getAtIndex(12) * getAtIndex(2) * getAtIndex(11) -
					getAtIndex(12) * getAtIndex(3) * getAtIndex(10);

				inv[9] = -getAtIndex(0) * getAtIndex(9) * getAtIndex(15) +
					getAtIndex(0) * getAtIndex(11) * getAtIndex(13) +
					getAtIndex(8) * getAtIndex(1) * getAtIndex(15) -
					getAtIndex(8) * getAtIndex(3) * getAtIndex(13) -
					getAtIndex(12) * getAtIndex(1) * getAtIndex(11) +
					getAtIndex(12) * getAtIndex(3) * getAtIndex(9);

				inv[13] = getAtIndex(0) * getAtIndex(9) * getAtIndex(14) -
					getAtIndex(0) * getAtIndex(10) * getAtIndex(13) -
					getAtIndex(8) * getAtIndex(1) * getAtIndex(14) +
					getAtIndex(8) * getAtIndex(2) * getAtIndex(13) +
					getAtIndex(12) * getAtIndex(1) * getAtIndex(10) -
					getAtIndex(12) * getAtIndex(2) * getAtIndex(9);

				inv[2] = getAtIndex(1) * getAtIndex(6) * getAtIndex(15) -
					getAtIndex(1) * getAtIndex(7) * getAtIndex(14) -
					getAtIndex(5) * getAtIndex(2) * getAtIndex(15) +
					getAtIndex(5) * getAtIndex(3) * getAtIndex(14) +
					getAtIndex(13) * getAtIndex(2) * getAtIndex(7) -
					getAtIndex(13) * getAtIndex(3) * getAtIndex(6);

				inv[6] = -getAtIndex(0) * getAtIndex(6) * getAtIndex(15) +
					getAtIndex(0) * getAtIndex(7) * getAtIndex(14) +
					getAtIndex(4) * getAtIndex(2) * getAtIndex(15) -
					getAtIndex(4) * getAtIndex(3) * getAtIndex(14) -
					getAtIndex(12) * getAtIndex(2) * getAtIndex(7) +
					getAtIndex(12) * getAtIndex(3) * getAtIndex(6);

				inv[10] = getAtIndex(0) * getAtIndex(5) * getAtIndex(15) -
					getAtIndex(0) * getAtIndex(7) * getAtIndex(13) -
					getAtIndex(4) * getAtIndex(1) * getAtIndex(15) +
					getAtIndex(4) * getAtIndex(3) * getAtIndex(13) +
					getAtIndex(12) * getAtIndex(1) * getAtIndex(7) -
					getAtIndex(12) * getAtIndex(3) * getAtIndex(5);

				inv[14] = -getAtIndex(0) * getAtIndex(5) * getAtIndex(14) +
					getAtIndex(0) * getAtIndex(6) * getAtIndex(13) +
					getAtIndex(4) * getAtIndex(1) * getAtIndex(14) -
					getAtIndex(4) * getAtIndex(2) * getAtIndex(13) -
					getAtIndex(12) * getAtIndex(1) * getAtIndex(6) +
					getAtIndex(12) * getAtIndex(2) * getAtIndex(5);

				inv[3] = -getAtIndex(1) * getAtIndex(6) * getAtIndex(11) +
					getAtIndex(1) * getAtIndex(7) * getAtIndex(10) +
					getAtIndex(5) * getAtIndex(2) * getAtIndex(11) -
					getAtIndex(5) * getAtIndex(3) * getAtIndex(10) -
					getAtIndex(9) * getAtIndex(2) * getAtIndex(7) +
					getAtIndex(9) * getAtIndex(3) * getAtIndex(6);

				inv[7] = getAtIndex(0) * getAtIndex(6) * getAtIndex(11) -
					getAtIndex(0) * getAtIndex(7) * getAtIndex(10) -
					getAtIndex(4) * getAtIndex(2) * getAtIndex(11) +
					getAtIndex(4) * getAtIndex(3) * getAtIndex(10) +
					getAtIndex(8) * getAtIndex(2) * getAtIndex(7) -
					getAtIndex(8) * getAtIndex(3) * getAtIndex(6);

				inv[11] = -getAtIndex(0) * getAtIndex(5) * getAtIndex(11) +
					getAtIndex(0) * getAtIndex(7) * getAtIndex(9) +
					getAtIndex(4) * getAtIndex(1) * getAtIndex(11) -
					getAtIndex(4) * getAtIndex(3) * getAtIndex(9) -
					getAtIndex(8) * getAtIndex(1) * getAtIndex(7) +
					getAtIndex(8) * getAtIndex(3) * getAtIndex(5);

				inv[15] = getAtIndex(0) * getAtIndex(5) * getAtIndex(10) -
					getAtIndex(0) * getAtIndex(6) * getAtIndex(9) -
					getAtIndex(4) * getAtIndex(1) * getAtIndex(10) +
					getAtIndex(4) * getAtIndex(2) * getAtIndex(9) +
					getAtIndex(8) * getAtIndex(1) * getAtIndex(6) -
					getAtIndex(8) * getAtIndex(2) * getAtIndex(5);

				float det = getAtIndex(0) * inv[0] + getAtIndex(1) * inv[4] + getAtIndex(2) * inv[8] + getAtIndex(3) * inv[12];

				if (det == 0.0f)
					return Matrix4x4<T>().setIdentity();

				det = 1.0f / det;

				Matrix4x4<T> result;

				for (int i = 0; i < 16; i++)
					result.m[i % 4][i >> 2] = inv[i] * det;

				return result;
			}

			inline void print()
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						std::cout << m[i][j] << ", ";
					}

					std::cout << std::endl;
				}
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