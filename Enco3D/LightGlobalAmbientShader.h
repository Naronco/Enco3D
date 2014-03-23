#ifndef _ENCO3D_LIGHTGLOBALAMBIENTSHADER_H_
#define _ENCO3D_LIGHTGLOBALAMBIENTSHADER_H_

#include "Shader.h"

namespace Enco3D
{
	namespace Rendering
	{
		class LightGlobalAmbientShader : public Shader
		{
		private:
			Vector3f m_globalAmbientLight;

		public:
			LightGlobalAmbientShader();

			void UpdateUniforms(const Matrix4x4f &worldMatrix, const Matrix4x4f projectedMatrix, Material &material) const;

			inline void SetGlobalAmbientLight(const Vector3f &globalAmbientLight) { m_globalAmbientLight = globalAmbientLight; }
			inline Vector3f GetGlobalAmbientLight() const { return m_globalAmbientLight; }

		public:
			inline static LightGlobalAmbientShader *GetInstance()
			{
				static LightGlobalAmbientShader *instance = nullptr;

				if (instance == nullptr)
				{
					instance = new LightGlobalAmbientShader;
				}

				return instance;
			}
		};
	}
}

#endif