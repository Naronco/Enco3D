#ifndef _ENCO3D_GEOMETRYPASSSHADER_H_
#define _ENCO3D_GEOMETRYPASSSHADER_H_

#include "Shader.h"

namespace Enco3D
{
	namespace Rendering
	{
		class GeometryPassShader : public Shader
		{
		public:
			GeometryPassShader();

			void UpdateUniforms(const Matrix4x4f &worldMatrix, const Matrix4x4f &projectedMatrix, Material &material) const;

		public:
			inline static GeometryPassShader *GetInstance()
			{
				static GeometryPassShader *instance = nullptr;

				if (instance == nullptr)
				{
					instance = new GeometryPassShader;
				}

				return instance;
			}
		};
	}
}

#endif