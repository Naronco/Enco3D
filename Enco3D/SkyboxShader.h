#ifndef _ENCO3D_SKYBOXSHADER_H_
#define _ENCO3D_SKYBOXSHADER_H_

#include "Shader.h"

namespace Enco3D
{
	namespace Rendering
	{
		class SkyboxShader : public Shader
		{
		private:
			Vector3f m_eyePos;

		public:
			SkyboxShader();

			void UpdateUniforms(const Matrix4x4f &worldMatrix, const Matrix4x4f &projectedMatrix, Material &material) const;

			inline void SetEyePos(const Vector3f &eyePos) { m_eyePos.Set(eyePos); }
			inline Vector3f GetEyePos() const { return m_eyePos; }

		public:
			inline static SkyboxShader *GetInstance()
			{
				static SkyboxShader *instance = nullptr;

				if (instance == nullptr)
				{
					instance = new SkyboxShader;
				}

				return instance;
			}
		};
	}
}

#endif