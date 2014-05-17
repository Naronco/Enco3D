#ifndef _ENCO3D_MATHUTIL_H_
#define _ENCO3D_MATHUTIL_H_

#include <math.h>

namespace Enco3D
{
	namespace Core
	{
		namespace MathUtil
		{
			/// <summary>Constant to convert degrees to radians</summary>
			static const double DEGTORAD = 0.0174532925;

			/// <summary>Constant to convert radians to degrees</summary>
			static const double RADTODEG = 57.2957795;

			/// <summary>Converts degrees to radians</summary>
			/// <param name="degrees">Degree value to convert</param>
			template <typename T>
			inline static T toRadians(T degrees)
			{
				return (T)(degrees * DEGTORAD);
			}

			/// <summary>Converts radians to degrees</summary>
			/// <param name="radians">Radian value to convert</param>
			template <typename T>
			inline static T toDegrees(T radians)
			{
				return (T)(radians * RADTODEG);
			}

			/// <summary>Converts a degree value to the cutoff of a spotlight</summary>
			/// <param name="degrees">Degree value to convert</param>
			template <typename T>
			inline static T degreesToSpotCutoff(T degrees)
			{
				return (T)cos(ToRadians(degrees));
			}

			/// <summary>Converts a radian value to the cutoff of a spotlight</summary>
			/// <param name="radians">Radian value to convert</param>
			template <typename T>
			inline static T radiansToSpotCutoff(T radians)
			{
				return (T)cos(radians);
			}
		}
	}
}

#endif