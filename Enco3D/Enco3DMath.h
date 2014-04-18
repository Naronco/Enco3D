#ifndef __ENCO3D_ENCO3DMATH_H_INCLUDED__
#define __ENCO3D_ENCO3DMATH_H_INCLUDED__

#include "Enco3DDatatypes.h"

#include <math.h>

#define __MIN(a, b) ((a) < (b) ? (a) : (b))
#define __MAX(a, b) ((a) > (b) ? (a) : (b))

#define __TO_RADIANS_f32(x) ((x) * enco::core::math::degrees_to_radians_f32)
#define __TO_RADIANS_f64(x) ((x) * enco::core::math::degrees_to_radians_f64)
#define __TO_DEGREES_f32(x) ((x) * enco::core::math::radians_to_degrees_f32)
#define __TO_DEGREES_f64(x) ((x) * enco::core::math::radians_to_degrees_f64)

#define __CLAMP_RADIANS_f32(x) {while(x>enco::core::math::pi_mul_2_f32)x-=enco::core::math::pi_mul_2_f32;while(x<-enco::core::math::pi_mul_2_f32)x+=enco::core::math::pi_mul_2_f32;}
#define __CLAMP_RADIANS_f64(x) {while(x>enco::core::math::pi_mul_2_f64)x-=enco::core::math::pi_mul_2_f64;while(x<-enco::core::math::pi_mul_2_f64)x+=enco::core::math::pi_mul_2_f64;}

#define __SIN_INDEX 1
#define __COS_INDEX 0

namespace enco
{
	namespace core
	{
		namespace math
		{
			const float64 pi_f64 = 3.14159265358979323846264338327950288419716939937510;
			const float64 pi_mul_2_f64 = 3.14159265358979323846264338327950288419716939937510 * 2.0;
			const float64 pi_div_2_f64 = 3.14159265358979323846264338327950288419716939937510 * 0.5;

			const float32 pi_f32 = 3.14159265358979323846264338327950288419716939937510f;
			const float32 pi_mul_2_f32 = 3.14159265358979323846264338327950288419716939937510f * 2.0f;
			const float32 pi_div_2_f32 = 3.14159265358979323846264338327950288419716939937510f * 0.5f;

			const float32 degrees_to_radians_f32 = pi_f32 / 180.0f;
			const float64 degrees_to_radians_f64 = pi_f64 / 180.0;
			const float32 radians_to_degrees_f32 = 180.0f / pi_f32;
			const float64 radians_to_degrees_f64 = 180.0 / pi_f64;

			float64 __forceinline __declspec (naked) __fastcall sqrt(float64 n)
			{
				__asm
				{
					fld qword ptr[esp + 4]
						fsqrt
						ret 8
				}
			}

			void __forceinline __fastcall sin_cos(float64 angle, float64 *out_sinCos)
			{
				__asm
				{
					fld qword ptr angle
						fsincos
						mov eax, out_sinCos
						fstp qword ptr[eax]
						fstp qword ptr[eax+8]
				}
			}

			float64 inline tan(float64 angle)
			{
				return (float64)tanf((float32)angle);
			}

			float64 inline asin(float64 angle)
			{
				return (float64)asinf((float32)angle);
			}

			float64 inline atan2(float64 y, float64 x)
			{
				return (float64)atan2f((float32)y, (float32)x);
			}
		}
	}
}

#endif