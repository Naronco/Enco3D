#ifndef _ENCO3D_POINTLIGHTSHADER_H_
#define _ENCO3D_POINTLIGHTSHADER_H_

#include "Shader.h"

namespace Enco3D
{
	namespace Rendering
	{
		class PointLightShader : public Shader
		{
		private:
			Vector3f m_color;
			float m_intensity;
			Vector3f m_position;
			float m_range;
			Vector3f m_eyePos;

		public:
			PointLightShader();

			void UpdateUniforms(const Matrix4x4f &worldMatrix, const Matrix4x4f projectedMatrix, Material &material) const;

			inline void SetEyePos(const Vector3f &eyePos) { m_eyePos = eyePos; }
			inline void SetPointLight(const Vector3f &color, float intensity, const Vector3f &position, float range) { m_color = color; m_intensity = intensity; m_position = position; m_range = range; }

			inline Vector3f GetEyePos() const { return m_eyePos; }

		public:
			inline static PointLightShader *GetInstance()
			{
				static PointLightShader *instance = nullptr;

				if (instance == nullptr)
				{
					instance = new PointLightShader;
				}

				return instance;
			}
		};
	}
}

#endif