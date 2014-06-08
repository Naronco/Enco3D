#ifndef _ENCO3D_INOISE_H_
#define _ENCO3D_INOISE_H_
namespace Enco3D
{
	namespace Algorithm
	{
		class INoise
		{
		public:
			virtual float noise1D(float x) { return 0; };
			virtual float noise2D(float x, float y) { return 0; };
			virtual float noise3D(float x, float y, float z) { return 0; };
			virtual float noise4D(float x, float y, float z, float w) { return 0; };
			virtual float noiseND(int dimensions, float* coords) { return 0; };
		};
	}
}
#endif