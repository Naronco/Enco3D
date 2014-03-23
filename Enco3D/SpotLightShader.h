#ifndef _ENCO3D_SPOTLIGHTSHADER_H_
#define _ENCO3D_SPOTLIGHTSHADER_H_

#include "Shader.h"

namespace Enco3D
{
	namespace Rendering
	{
		class SpotLightShader : public Shader
		{
		private:
			Vector3f m_color;
			float m_intensity;
			Vector3f m_position, m_direction;
			float m_range, m_cutoff;
			Vector3f m_eyePos;

		public:
			SpotLightShader();

			void UpdateUniforms(const Matrix4x4f &worldMatrix, const Matrix4x4f projectedMatrix, Material &material) const;

			inline void SetSpotLight(const Vector3f &color, float intensity, const Vector3f &position, const Vector3f &direction, float range, float cutoff) { m_color = color; m_intensity = intensity; m_position = position; m_direction = direction; m_range = range; m_cutoff = cutoff; }
			inline void SetEyePos(const Vector3f &eyePos) { m_eyePos = eyePos; }

			inline Vector3f GetEyePos() const { return m_eyePos; }

		public:
			inline static SpotLightShader *GetInstance()
			{
				static SpotLightShader *instance = nullptr;

				if (instance == nullptr)
				{
					instance = new SpotLightShader;
				}

				return instance;
			}
		};
	}
}

#endif