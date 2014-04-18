#ifndef __ENCO3D_SCOLOR4_H_INCLUDED__
#define __ENCO3D_SCOLOR4_H_INCLUDED__

#include "Enco3DDatatypes.h"

namespace enco
{
	namespace core
	{
		template <typename T> struct Color4
		{
			T r, g, b, a;

			inline Color4() : r(0), g(0), b(0), a(0) {}
			inline Color4(T _r, T _g, T _b, T _a) : r(_r), g(_g), b(_b), a(_a) {}
			inline Color4(const Color4<T> &c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
		};

		typedef Color4<float32> Color4f32;
		typedef Color4<float64> Color4f64;
	}
}

#endif