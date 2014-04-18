#ifndef __ENCO3D_SDIMENSION2_H_INCLUDED__
#define __ENCO3D_SDIMENSION2_H_INCLUDED__

#include "Enco3DDatatypes.h"

namespace enco
{
	namespace core
	{
		template <typename T>
		struct Dimension2
		{
			T x, y;

			inline Dimension2() : x(0), y(0) {}
			inline Dimension2(T _x, T _y) : x(_x), y(_y) {}
			inline Dimension2(const Dimension2<T> &o) : x(o.x), y(o.y) {}
		};

		typedef Dimension2<sint8>   Dimension2s8;
		typedef Dimension2<sint16>  Dimension2s16;
		typedef Dimension2<sint32>  Dimension2s32;
		typedef Dimension2<sint64>  Dimension2s64;

		typedef Dimension2<uint8>   Dimension2u8;
		typedef Dimension2<uint16>  Dimension2u16;
		typedef Dimension2<uint32>  Dimension2u32;
		typedef Dimension2<uint64>  Dimension2u64;

		typedef Dimension2<float32> Dimension2f32;
		typedef Dimension2<float64> Dimension2f64;
	}
}

#endif