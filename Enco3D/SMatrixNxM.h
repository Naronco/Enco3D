#ifndef __ENCO3D_SMATRIXNXM_H_INCLUDED__
#define __ENCO3D_SMATRIXNXM_H_INCLUDED__

#include "Enco3DMath.h"
#include "Enco3DDatatypes.h"
#include "Enco3DUtil.h"

#include <iostream>

namespace enco
{
	namespace core
	{
		namespace math
		{
			template <typename T, uint32 N, uint32 M> struct MatrixNxM
			{
				T values[N][M];

				inline MatrixNxM() { setIdentity(); }

				inline MatrixNxM(const MatrixNxM<T, N, M> &matrix)
				{
					for (uint32 i = 0; i < N; i++)
						for (uint32 j = 0; j < M; j++)
							values[i][j] = matrix.values[i][j];
				}

				inline void clear()
				{
					for (uint32 i = 0; i < N; i++)
						for (uint32 j = 0; j < M; j++)
							values[i][j] = 0;
				}

				inline void setIdentity()
				{
					clear();

					uint32 len = __MIN(N, M);
					for (uint32 i = 0; i < len; i++)
					{
						values[i][i] = 1;
					}
				}

				inline void setTranslation(T x, T y, T z)
				{
					setIdentity();

					values[0][N - 1] = x;
					values[1][N - 1] = y;
					values[2][N - 1] = z;
				}

				inline void setScaling(T x, T y, T z)
				{
					setIdentity();

					values[0][0] = x;
					values[1][1] = y;
					values[2][2] = z;
				}

				inline void setRotationX(T angle)
				{
					setIdentity();
					
					float64 sin_cos[2];
					math::sin_cos((float64)angle, sin_cos);

					values[1][1] = (T)sin_cos[__COS_INDEX];
					values[1][2] = (T)-sin_cos[__SIN_INDEX];
					values[2][1] = (T)sin_cos[__SIN_INDEX];
					values[2][2] = (T)sin_cos[__COS_INDEX];
				}

				inline void setRotationY(T angle)
				{
					setIdentity();

					float64 sin_cos[2];
					math::sin_cos((float64)angle, sin_cos);

					values[0][0] = (T)sin_cos[__COS_INDEX];
					values[2][0] = (T)sin_cos[__SIN_INDEX];
					values[0][2] = (T)-sin_cos[__SIN_INDEX];
					values[2][2] = (T)sin_cos[__COS_INDEX];
				}

				inline void setRotationZ(T angle)
				{
					setIdentity();

					float64 sin_cos[2];
					math::sin_cos((float64)angle, sin_cos);

					values[0][0] = (T)sin_cos[__COS_INDEX];
					values[1][0] = (T)-sin_cos[__SIN_INDEX];
					values[0][1] = (T)sin_cos[__SIN_INDEX];
					values[1][1] = (T)sin_cos[__COS_INDEX];
				}

				inline void setOrthographicProjection(T left, T right, T bottom, T top, T zNear, T zFar)
				{
					setIdentity();

					T width = right - left;
					T height = top - bottom;
					T depth = zFar - zNear;

					values[0][0]     = (T)(2.0 / width);
					values[0][N - 1] = -(right + left) / width;
					values[1][1]     = (T)(2.0 / height);
					values[1][N - 1] = -(top + bottom) / height;
					values[2][2]     = (T)(-2.0 / depth);
					values[2][N - 1] = -(zFar + zNear) / depth;
				}

				inline void setPerspectiveProjection(T fov, T aspectRatio, T zNear, T zFar)
				{
					setIdentity();

					T tanHalfFov = (T)math::tan((float64)(fov * 0.5));
					T zRange = zNear - zFar;

					values[0][0] = (T)(1.0 / (tanHalfFov * aspectRatio));
					values[1][1] = (T)(1.0 / tanHalfFov);
					values[2][2] = (-zNear - zFar) / zRange;
					values[2][3] = 2 * zFar * zNear / zRange;
					values[3][2] = 1;
					values[3][3] = 0;
				}

#ifdef __ENCO3D_DEBUG
				inline void print()
				{
					for (uint32 i = 0; i < N; i++)
					{
						for (uint32 j = 0; j < M; j++)
						{
							std::cout << values[i][j] << ", ";
						}

						std::cout << std::endl;
					}
				}
#endif
			};

			// Operations
			template <typename T, uint32 N, uint32 M>
			inline MatrixNxM<T, N, M> operator * (const MatrixNxM<T, N, M> &m0, const MatrixNxM<T, N, M> &m1)
			{
				MatrixNxM<T, N, M> result;

				for (uint32 i = 0; i < N; i++)
				{
					for (uint32 j = 0; j < M; j++)
					{
						result.values[i][j] = 0;

						for (uint32 k = 0; k < N; k++)
						{
							result.values[i][j] += m0.values[i][k] * m1.values[k][j];
						}
					}
				}

				return result;
			}

			// 3x3 Matrices
			typedef MatrixNxM<sint8,   3, 3> Matrix3x3s8;
			typedef MatrixNxM<sint16,  3, 3> Matrix3x3s16;
			typedef MatrixNxM<sint32,  3, 3> Matrix3x3s32;
			typedef MatrixNxM<sint64,  3, 3> Matrix3x3s64;

			typedef MatrixNxM<uint8,   3, 3> Matrix3x3u8;
			typedef MatrixNxM<uint16,  3, 3> Matrix3x3u16;
			typedef MatrixNxM<uint32,  3, 3> Matrix3x3u32;
			typedef MatrixNxM<uint64,  3, 3> Matrix3x3u64;

			typedef MatrixNxM<float32, 3, 3> Matrix3x3f32;
			typedef MatrixNxM<float64, 3, 3> Matrix3x3f64;

			// 4x3 Matrices
			typedef MatrixNxM<sint8,   4, 3> Matrix4x3s8;
			typedef MatrixNxM<sint16,  4, 3> Matrix4x3s16;
			typedef MatrixNxM<sint32,  4, 3> Matrix4x3s32;
			typedef MatrixNxM<sint64,  4, 3> Matrix4x3s64;

			typedef MatrixNxM<uint8,   4, 3> Matrix4x3u8;
			typedef MatrixNxM<uint16,  4, 3> Matrix4x3u16;
			typedef MatrixNxM<uint32,  4, 3> Matrix4x3u32;
			typedef MatrixNxM<uint64,  4, 3> Matrix4x3u64;

			typedef MatrixNxM<float32, 4, 3> Matrix4x3f32;
			typedef MatrixNxM<float64, 4, 3> Matrix4x3f64;

			// 4x4 Matrices
			typedef MatrixNxM<sint8,   4, 4> Matrix4x4s8;
			typedef MatrixNxM<sint16,  4, 4> Matrix4x4s16;
			typedef MatrixNxM<sint32,  4, 4> Matrix4x4s32;
			typedef MatrixNxM<sint64,  4, 4> Matrix4x4s64;

			typedef MatrixNxM<uint8,   4, 4> Matrix4x4u8;
			typedef MatrixNxM<uint16,  4, 4> Matrix4x4u16;
			typedef MatrixNxM<uint32,  4, 4> Matrix4x4u32;
			typedef MatrixNxM<uint64,  4, 4> Matrix4x4u64;

			typedef MatrixNxM<float32, 4, 4> Matrix4x4f32;
			typedef MatrixNxM<float64, 4, 4> Matrix4x4f64;
		}
	}
}

#endif