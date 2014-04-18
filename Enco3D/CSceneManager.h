#ifndef __ENCO3D_CSCENEMANAGER_H_INCLUDED__
#define __ENCO3D_CSCENEMANAGER_H_INCLUDED__

#include <vector>
#include "IGraphicsDevice.h"
#include "CCodedMesh.h"
#include "ISceneNode.h"
#include "CCodedMeshSceneNode.h"
#include "CCamera.h"
#include "ILight.h"

namespace enco
{
	namespace core
	{
		class CSceneManager
		{
		private:
			typedef struct __internal_shaderpack
			{
				IShader *shader;
				IShaderType *vertexShader, *pixelShader;

				void create(IGraphicsDevice *dev, const char *vfile, const char *pfile) {
					shader = dev->buildShader();
					vertexShader = dev->buildShaderType(vfile, eSHADERTYPE_VERTEXSHADER);
					pixelShader = dev->buildShaderType(pfile, eSHADERTYPE_PIXELSHADER);

					dev->appendShaderType(shader, vertexShader);
					dev->appendShaderType(shader, pixelShader);
					dev->compileShader(shader);
				}

				void release(IGraphicsDevice *dev) {
					dev->releaseShaderType(pixelShader);
					dev->releaseShaderType(vertexShader);
					dev->releaseShader(shader);
				}

			} scenemanager_shaderpack;

			IGraphicsDevice *m_graphicsDevice;
			std::vector<ISceneNode*> m_sceneNodes;
			
			// Rendering
			std::vector<CCamera<float32>*> m_cameras;

			Color4f32 m_globalAmbientLightColor;

			std::vector<ILight*> m_lights;

			// ##### SHADERS #####
			// -lighting
			//		-ambient
			scenemanager_shaderpack m_forwardAmbientShader;
			//      -basic
			scenemanager_shaderpack m_forwardDirectionalLightShader;
			scenemanager_shaderpack m_forwardPointLightShader;
			scenemanager_shaderpack m_forwardSpotLightShader;
			//		-normalmapping
			scenemanager_shaderpack m_forwardNormalMappingDirectionalLightShader;
			scenemanager_shaderpack m_forwardNormalMappingPointLightShader;
			scenemanager_shaderpack m_forwardNormalMappingSpotLightShader;
			// -other
			scenemanager_shaderpack m_forwardBasicShader;

//			IShader *m_forwardAmbientShader; IShaderType *m_forwardAmbientVertexShader, *m_forwardAmbientPixelShader;
//			IShader *m_forwardDirectionalLightShader; IShaderType *m_forwardDirectionalLightVertexShader, *m_forwardDirectionalLightPixelShader;
//			IShader *m_forwardPointLightShader; IShaderType *m_forwardPointLightVertexShader, *m_forwardPointLightPixelShader;
//			IShader *m_forwardSpotLightShader; IShaderType *m_forwardSpotLightVertexShader, *m_forwardSpotLightPixelShader;
//			IShader *m_forwardBasicShader; IShaderType *m_forwardBasicVertexShader, *m_forwardBasicPixelShader;

		public:
			void create(IGraphicsDevice *graphicsDevice);
			void release();

			void renderAll();

			CCamera<float32> *addPerspectiveCamera(float32 fov, float32 aspectRatio, float32 zNear, float32 zFar);
			CCamera<float32> *addOrthographicCamera(float32 left, float32 right, float32 bottom, float32 top, float32 zNear, float32 zFar);

			ILight *addDirectionalLight(float32 intensity, const Color4f32 &color, const math::Vector3f32 &direction);
			ILight *addPointLight(float32 intensity, const Color4f32 &color, const math::Vector3f32 &position, float32 range);
			ILight *addSpotLight(float32 intensity, const Color4f32 &color, const math::Vector3f32 &position, const math::Vector3f32 &direction, float32 range, float32 cutoff);

			CCodedMesh *buildCodedMesh(uint32 vertexSizeInBytes, void *vertexData, sint32 vertexComponents, uint32 indexSizeInBytes, void *indexData, uint32 indexCount);
			void releaseCodedMesh(CCodedMesh *codedMesh);

			CCodedMeshSceneNode *addCodedMeshSceneNode(CCodedMesh *codedMesh);

			inline void setGlobalAmbientLightColor(const Color4f32 &globalAmbientLightColor) { m_globalAmbientLightColor = globalAmbientLightColor; }
			inline Color4f32 getGlobalAmbientLightColor() const { return m_globalAmbientLightColor; }
		};
	}
}

#endif