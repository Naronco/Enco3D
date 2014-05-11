#ifndef _ENCO3D_CAMERA_H_
#define _ENCO3D_CAMERA_H_

#include "Vector3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
#include "IGameComponent.h"
#include <vector>

namespace Enco3D
{
	namespace Component
	{
		class IPostProcessEffect;
	}
}

namespace Enco3D
{
	namespace Component
	{
		enum ProjectionMode : unsigned int
		{
			Perspective = 0,
			Orthographic = 1,
		};

		class Camera : public Core::IGameComponent
		{
		private:
			Core::Matrix4x4f m_projection;
			Core::Matrix4x4f m_view, m_prevView;
			Core::Matrix4x4f m_viewProjection, m_prevViewProjection;

			float m_fov{ 0.0f };
			float m_tanHalfFov{ 0.0f };
			float m_aspectRatio{ 0.0f };
			float m_zNearClippingPlane{ 0.0f };
			float m_zFarClippingPlane{ 0.0f };

			float m_left{ 0.0f };
			float m_right{ 0.0f };
			float m_bottom{ 0.0f };
			float m_top{ 0.0f };

			unsigned int m_depth{ 0 };
			unsigned int m_projectionMode{ ProjectionMode::Perspective };

			std::vector<IPostProcessEffect*> m_postProcessEffects;
			
		public:
			Camera();
			Camera(float fov, float aspect, float zNear, float zFar);
			Camera(float left, float right, float bottom, float top, float zNear, float zFar);

			void InitRendering();
			void Update();
			void Resize(unsigned int width, unsigned int height);
			void OnAddComponentToObject(Core::IGameComponent *component);
			void OnRemoveComponentFromObject(Core::IGameComponent *component);

			void SetPerspectiveProjection(float fov, float aspect, float zNear, float zFar);
			void SetOrthographicProjection(float left, float right, float bottom, float top, float zNear, float zFar);

			inline void SetProjection(const Core::Matrix4x4f &projection) { m_projection.Set(projection); }
			inline void SetTranslation(const Core::Vector3f &translation) { GetTransform()->SetTranslation(translation); }
			inline void SetRotation(const Core::Quaternionf &rotation) { GetTransform()->SetRotation(rotation); }
			inline void SetScaling(const Core::Vector3f &scaling) { GetTransform()->SetScaling(scaling); }

			inline void SetDepth(unsigned int depth) { m_depth = depth; }

			inline Core::Matrix4x4f GetProjection() const { return m_projection; }

			inline Core::Matrix4x4f GetView() const { return m_view; }
			inline Core::Matrix4x4f GetPrevView() const { return m_prevView; }

			inline Core::Matrix4x4f GetViewProjection() const { return m_viewProjection; }
			inline Core::Matrix4x4f GetPrevViewProjection() const { return m_prevViewProjection; }

			inline Core::Vector3f GetForward() const { return GetTransform()->GetRotation().GetForward(); }
			inline Core::Vector3f GetUp() const { return GetTransform()->GetRotation().GetUp(); }
			inline Core::Vector3f GetRight() const { return GetTransform()->GetRotation().GetRight(); }

			inline float GetFov() const { return m_fov; }
			inline float GetTanHalfFov() const { return m_tanHalfFov; }
			inline float GetAspectRatio() const { return m_aspectRatio; }
			inline float GetZNearClippingPlane() const { return m_zNearClippingPlane; }
			inline float GetZFarClippingPlane() const { return m_zFarClippingPlane; }

			inline unsigned int GetDepth() const { return m_depth; }
			inline unsigned int GetProjectionMode() const { return m_projectionMode; }
		};
	}
}

#endif