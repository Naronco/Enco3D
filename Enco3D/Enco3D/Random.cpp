#include "Random.h"

Enco3D::Core::Random::Random()
{
	time_t t;
	time(&t);
	srand(t);
	setSeed(rand());
}

Enco3D::Core::Random::Random(unsigned long seed)
{
	setSeed(seed);
}

Enco3D::Core::Random::Random(unsigned long seed1, unsigned long seed2, unsigned long seed3)
{
	x = seed1 + 1; // Make sure they are not zero
	y = seed2 + 1;
	z = seed3 + 1;
}

Enco3D::Core::Random::~Random()
{
}