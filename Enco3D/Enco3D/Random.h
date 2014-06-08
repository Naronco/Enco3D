#ifndef _ENCO3D_RANDOM_H_
#define _ENCO3D_RANDOM_H_

#include <limits.h>
#include <time.h>
#include <random>

namespace Enco3D
{
	namespace Core
	{
		/// <summary>Random class, need to be instanced</summary>
		class Random
		{
		private:
			/// <summary> Random values (internal use) </summary>
			unsigned long x = 455615615;
			/// <summary> Random values (internal use) </summary>
			unsigned long y = 789623456;
			/// <summary> Random values (internal use) </summary>
			unsigned long z = 651561538;

		public:
			/// <summary>Creates a new Random with random values</summary>
			Random();
			/// <summary>
			/// Creates a new Random with defined seed
			/// <param name="seed">The maximum value of the returned integer</param>
			/// </summary>
			Random(unsigned long seed);
			/// <summary>Creates a new Random with all defined seeds</summary>
			Random(unsigned long seed1, unsigned long seed2, unsigned long seed3);
			~Random();

			/// <summary>
			/// Sets a new seed
			/// <param name="seed">The new seed as an <see cref="unsigned long">unsigned long</see></param>
			/// </summary>
			inline void setSeed(unsigned long seed)
			{
				x = seed + 1; // Make sure they are not zero
				y = x + 2;
				z = y + 3;
			}

			/// <summary>
			/// Calculates a random unsigned Long
			/// <returns>Random unsigned Long from 0 to 0xffffffffUL</returns>
			/// <seealso cref="Random::nextInt"/>
			/// </summary>
			inline unsigned long nextLong()
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

			/// <summary>
			/// Calculates a random unsigned Integer
			/// <returns>Random unsigned Integer from 0 to 0xffffffff</returns>
			/// <seealso cref="Random::nextInt"/>
			/// </summary>
			inline unsigned int nextInt()
			{
				return (nextLong() % UINT_MAX);
			}

			/// <summary>
			/// Calculates a random Integer
			/// <param name="max">The maximum value of the returned integer</param>
			/// <returns>Random Integer from 0 to <see cref="max">max</see></returns>
			/// <seealso cref="Random::nextInt"/>
			/// </summary>
			inline unsigned int nextInt(unsigned int max)
			{
				return (nextInt() % max);
			}

			/// <summary>
			/// Calculates a random Float
			/// <returns>Random Float from 0.0 to 1.0</returns>
			/// </summary>
			inline float nextFloat()
			{
				return (nextLong() % ULONG_MAX) / (long float)ULONG_MAX;
			}

			/// <summary>
			/// Calculates a random Double
			/// <returns>Random Double from 0.0 to 1.0</returns>
			/// </summary>
			inline double NextDouble()
			{
				return (nextLong() % ULONG_MAX) / (long double)ULONG_MAX;
			}

			/// <summary>
			/// Calculates a random Boolean
			/// <returns>Random Boolean</returns>
			/// </summary>
			inline bool NextBool()
			{
				return (nextInt(2) == 0);
			}
		};
	}
}

#endif