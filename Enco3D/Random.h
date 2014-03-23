#ifndef _ENCO3D_RANDOM_H_
#define _ENCO3D_RANDOM_H_

#include <Windows.h>
#include <limits.h>

namespace Enco3D
{
	namespace Core
	{
		/// <summary>Random class, doesn't need to be instanced</summary>
		class Random
		{
		private:
			/// <summary>Random values (internal use)</summary>
			static unsigned long x, y, z;

		public:
			/// <summary>Sets a new seed</summary>
			/// <param name="seed">The new seed as an unsigned long</param>
			inline static void SetSeed(unsigned long seed)
			{
				x = seed;
				y = x + 34575425;
				z = y + 97565462;
			}

			/// <summary>Returns a random unsigned long</summary>
			inline static unsigned long NextLong()
			{
				x ^= x << 16;
				x ^= x >> 5;
				x ^= x << 1;

				unsigned long t = x;
				x = y;
				y = z;
				z = t ^ x ^ y;

				return z;
			}

			/// <summary>Returns a random int >= 0</summary>
			inline static int NextInt()
			{
				return (NextLong() % LONG_MAX);
			}

			/// <summary>Returns a random int from 0 to the max value</summary>
			/// <param name="max">The maximum value of the returned integer</param>
			inline static int NextInt(int max)
			{
				return (NextInt() % max);
			}

			/// <summary>Returns a random float from 0.0f to 1.0f</summary>
			inline static float NextFloat()
			{
				return (NextLong() % LONG_MAX) / (float)LONG_MAX;
			}

			/// <summary>Returns a random double from 0.0 to 1.0</summary>
			inline static double NextDouble()
			{
				return (NextLong() % LONG_MAX) / (double)LONG_MAX;
			}

			/// <summary>Returns a random boolean (true or false)</summary>
			inline static bool NextBool()
			{
				return (NextInt(2) == 0);
			}
		};
	}
}

#endif