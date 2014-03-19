#ifndef _ENCO3D_MATHUTIL_H_
#define _ENCO3D_MATHUTIL_H_

#include <math.h>

/// <summary>Constant to convert degrees to radians</summary>
static const double DEGTORAD = 0.0174532925;

/// <summary>Constant to convert radians to degrees</summary>
static const double RADTODEG = 57.2957795;

/// <summary>Converts degrees to radians</summary>
/// <param name="degrees">Degree value to convert</param>
template <typename T>
inline static T ToRadians(T degrees)
{
	return (T)(degrees * DEGTORAD);
}

/// <summary>Converts radians to degrees</summary>
/// <param name="radians">Radian value to convert</param>
template <typename T>
inline static T ToDegrees(T radians)
{
	return (T)(radians * RADTODEG);
}

/// <summary>Converts a degree value to the cutoff of a spotlight</summary>
/// <param name="degrees">Degree value to convert</param>
template <typename T>
inline static T DegreesToSpotCutoff(T degrees)
{
	return (T)cos(ToRadians(degrees));
}

/// <summary>Converts a radian value to the cutoff of a spotlight</summary>
/// <param name="radians">Radian value to convert</param>
template <typename T>
inline static T RadiansToSpotCutoff(T radians)
{
	return (T)cos(radians);
}

#endif