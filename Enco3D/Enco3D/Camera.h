#ifndef _ENCO3D_CAMERA_H_
#define _ENCO3D_CAMERA_H_

#include "Vector3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
#include "IGameComponent.h"
#include <vector>
#include "DLLExport.h"

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

		class DLL_EXPORT Camera : public Core::IGameComponent
		{
		private:
			Core::Matrix4x4f m_projection, m_inverseProjection;
			Core::Matrix4x4f m_view, m_prevView, m_inverseView;
			Core::Matrix4x4f m_viewProjection, m_prevViewProjection, m_inverseViewProjection;
			Core::Matrix4x4f m_rotationMatrix;

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

			void initRendering();
			void update();
			void resize(unsigned int width, unsigned int height);

			void addPostProcessEffect(IPostProcessEffect *effect);
			void removePostProcessEffect(IPostProcessEffect *effect);

			void setPerspectiveProjection(float fov, float aspect, float zNear, float zFar);
			void setOrthographicProjection(float left, float right, float bottom, float top, float zNear, float zFar);

			inline void setProjection(const Core::Matrix4x4f &projection) { m_projection.set(projection); }
			inline void setTranslation(const Core::Vector3f &translation) { getTransform()->setTranslation(translation); }
			inline void setRotation(const Core::Quaternionf &rotation) { getTransform()->setRotation(rotation); }
			inline void setScaling(const Core::Vector3f &scaling) { getTransform()->setScaling(scaling); }

			inline void setDepth(unsigned int depth) { m_depth = depth; }

			inline Core::Matrix4x4f getProjection() const { return m_projection; }
			inline Core::Matrix4x4f getInverseProjection() const { return m_inverseProjection; }

			inline Core::Matrix4x4f getView() const { return m_view; }
			inline Core::Matrix4x4f getPrevView() const { return m_prevView; }
			inline Core::Matrix4x4f getInverseView() const { return m_inverseView; }

			inline Core::Matrix4x4f getViewProjection() const { return m_viewProjection; }
			inline Core::Matrix4x4f getPrevViewProjection() const { return m_prevViewProjection; }
			inline Core::Matrix4x4f getInverseViewProjection() const { return m_inverseViewProjection; }

			inline Core::Matrix4x4f getRotationMatrix() const { return m_rotationMatrix; }

			inline Core::Vector3f getForward() const { return getTransform()->getRotation().getForward(); }
			inline Core::Vector3f getUp() const { return getTransform()->getRotation().getUp(); }
			inline Core::Vector3f getRight() const { return getTransform()->getRotation().getRight(); }

			inline float getFov() const { return m_fov; }
			inline float getTanHalfFov() const { return m_tanHalfFov; }
			inline float getAspectRatio() const { return m_aspectRatio; }
			inline float getZNearClippingPlane() const { return m_zNearClippingPlane; }
			inline float getZFarClippingPlane() const { return m_zFarClippingPlane; }

			inline unsigned int getDepth() const { return m_depth; }
			inline unsigned int getProjectionMode() const { return m_projectionMode; }

			inline std::vector<IPostProcessEffect*> getPostProcessEffects() const { return m_postProcessEffects; }
		};
	}
}

#endif