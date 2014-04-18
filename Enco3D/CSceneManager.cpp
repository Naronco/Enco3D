#include "CSceneManager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void enco::core::CSceneManager::create(IGraphicsDevice *graphicsDevice)
{
	m_graphicsDevice = graphicsDevice;

	m_forwardAmbientShader.create(m_graphicsDevice, "shaders/forwardAmbient.vs", "shaders/forwardAmbient.ps");

	m_forwardDirectionalLightShader.create(m_graphicsDevice, "shaders/forwardDirectionalLight.vs", "shaders/forwardDirectionalLight.ps");
	m_forwardPointLightShader.create(m_graphicsDevice, "shaders/forwardPointLight.vs", "shaders/forwardPointLight.ps");
	m_forwardSpotLightShader.create(m_graphicsDevice, "shaders/forwardSpotLight.vs", "shaders/forwardSpotLight.ps");

	m_forwardNormalMappingDirectionalLightShader.create(m_graphicsDevice, "shaders/forwardDirectionalLight_normalMapping.vs", "shaders/forwardDirectionalLight_normalMapping.ps");
	m_forwardNormalMappingPointLightShader.create(m_graphicsDevice, "shaders/forwardPointLight_normalMapping.vs", "shaders/forwardPointLight_normalMapping.ps");
	m_forwardNormalMappingSpotLightShader.create(m_graphicsDevice, "shaders/forwardSpotLight_normalMapping.vs", "shaders/forwardSpotLight_normalMapping.ps");

	m_forwardBasicShader.create(m_graphicsDevice, "shaders/forwardBasic.vs", "shaders/forwardBasic.ps");
}

void enco::core::CSceneManager::release()
{
	for (uint32 i = 0; i < m_cameras.size(); i++)
		__SAFEDELETE(m_cameras[i]);

	for (uint32 i = 0; i < m_lights.size(); i++)
		__SAFEDELETE(m_lights[i]);

	for (uint32 i = 0; i < m_sceneNodes.size(); i++)
	{
		m_sceneNodes[i]->release();
		__SAFEDELETE(m_sceneNodes[i]);
	}

	m_forwardBasicShader.release(m_graphicsDevice);

	m_forwardNormalMappingSpotLightShader.release(m_graphicsDevice);
	m_forwardNormalMappingPointLightShader.release(m_graphicsDevice);
	m_forwardNormalMappingDirectionalLightShader.release(m_graphicsDevice);

	m_forwardSpotLightShader.release(m_graphicsDevice);
	m_forwardPointLightShader.release(m_graphicsDevice);
	m_forwardDirectionalLightShader.release(m_graphicsDevice);

	m_forwardAmbientShader.release(m_graphicsDevice);
}

void enco::core::CSceneManager::renderAll()
{
	for (uint32 c = 0; c < m_cameras.size(); c++)
	{
		math::Matrix4x4f32 viewProjectionMatrix = m_cameras[c]->getViewProjectionMatrix();

		for (uint32 i = 0; i < m_sceneNodes.size(); i++)
		{
			math::Matrix4x4f32 worldMatrix = m_sceneNodes[i]->getTransform()->getTransformationMatrix();
			math::Matrix4x4f32 worldViewProjectionMatrix = viewProjectionMatrix * worldMatrix;

			if (m_sceneNodes[i]->isMaterialFlagEnabled(eMATERIALFLAG_LIGHTING))
			{
				m_graphicsDevice->setActiveTexture2D(m_sceneNodes[i]->getMaterialTexture(eMATERIALTEXTURE_DIFFUSE), eTEXTURESLOT_SLOT0);

				m_graphicsDevice->setActiveShader(m_forwardAmbientShader.shader);
				m_graphicsDevice->setUniformMatrix4x4f32(m_forwardAmbientShader.shader, "worldViewProjectionMatrix", worldViewProjectionMatrix);
				m_graphicsDevice->setUniformColor4f32(m_forwardAmbientShader.shader, "globalAmbientLightColor", m_globalAmbientLightColor);
				m_graphicsDevice->setUniformColor4f32(m_forwardAmbientShader.shader, "diffuseColor", m_sceneNodes[i]->getMaterialColor(eMATERIALCOLOR_DIFFUSE));
				m_graphicsDevice->setUniformTexture2D(m_forwardAmbientShader.shader, "diffuseTexture", eTEXTURESLOT_SLOT0);

				m_sceneNodes[i]->render();
			}
			else
			{
				m_graphicsDevice->setActiveTexture2D(m_sceneNodes[i]->getMaterialTexture(eMATERIALTEXTURE_DIFFUSE), eTEXTURESLOT_SLOT0);

				m_graphicsDevice->setActiveShader(m_forwardBasicShader.shader);
				m_graphicsDevice->setUniformMatrix4x4f32(m_forwardBasicShader.shader, "worldViewProjectionMatrix", worldViewProjectionMatrix);
				m_graphicsDevice->setUniformColor4f32(m_forwardBasicShader.shader, "diffuseColor", m_sceneNodes[i]->getMaterialColor(eMATERIALCOLOR_DIFFUSE));
				m_graphicsDevice->setUniformTexture2D(m_forwardBasicShader.shader, "diffuseTexture", eTEXTURESLOT_SLOT0);

				m_sceneNodes[i]->render();
			}
		}

		m_graphicsDevice->setDepthWritingEnabled(false);
		m_graphicsDevice->setBlendingMode(eBLENDINGMODE_ADD);

		for (uint32 l = 0; l < m_lights.size(); l++)
		{
			ILight *light = m_lights[l];

			switch (light->lightType)
			{
			case eLIGHTTYPE_DIRECTIONAL:
				for (uint32 i = 0; i < m_sceneNodes.size(); i++)
				{
					math::Matrix4x4f32 worldMatrix = m_sceneNodes[i]->getTransform()->getTransformationMatrix();
					math::Matrix4x4f32 worldViewProjectionMatrix = viewProjectionMatrix * worldMatrix;

					if (m_sceneNodes[i]->isMaterialFlagEnabled(eMATERIALFLAG_LIGHTING))
					{
						if (m_sceneNodes[i]->isMaterialFlagEnabled(eMATERIALFLAG_NORMALMAPPING))
						{
							m_graphicsDevice->setActiveTexture2D(m_sceneNodes[i]->getMaterialTexture(eMATERIALTEXTURE_DIFFUSE), eTEXTURESLOT_SLOT0);
							m_graphicsDevice->setActiveTexture2D(m_sceneNodes[i]->getMaterialTexture(eMATERIALTEXTURE_NORMAL), eTEXTURESLOT_SLOT1);

							m_graphicsDevice->setActiveShader(m_forwardNormalMappingDirectionalLightShader.shader);
							m_graphicsDevice->setUniformMatrix4x4f32(m_forwardNormalMappingDirectionalLightShader.shader, "worldMatrix", worldMatrix);
							m_graphicsDevice->setUniformMatrix4x4f32(m_forwardNormalMappingDirectionalLightShader.shader, "worldViewProjectionMatrix", worldViewProjectionMatrix);

							// Directional light uniforms
							m_graphicsDevice->setUniformColor4f32(m_forwardNormalMappingDirectionalLightShader.shader, "directionalLight.color", light->color);
							m_graphicsDevice->setUniformFloat32(m_forwardNormalMappingDirectionalLightShader.shader, "directionalLight.intensity", light->intensity);
							m_graphicsDevice->setUniformVector3f32(m_forwardNormalMappingDirectionalLightShader.shader, "directionalLight.direction", light->direction);

							// Material uniforms
							m_graphicsDevice->setUniformColor4f32(m_forwardNormalMappingDirectionalLightShader.shader, "material.diffuseColor", m_sceneNodes[i]->getMaterialColor(eMATERIALCOLOR_DIFFUSE));
							m_graphicsDevice->setUniformTexture2D(m_forwardNormalMappingDirectionalLightShader.shader, "material.diffuseTexture", eTEXTURESLOT_SLOT0);
							m_graphicsDevice->setUniformTexture2D(m_forwardNormalMappingDirectionalLightShader.shader, "material.normalTexture", eTEXTURESLOT_SLOT1);
							m_graphicsDevice->setUniformFloat32(m_forwardNormalMappingDirectionalLightShader.shader, "material.specularIntensity", m_sceneNodes[i]->getMaterialFloat(eMATERIALFLOAT_SPECULARINTENSITY));
							m_graphicsDevice->setUniformFloat32(m_forwardNormalMappingDirectionalLightShader.shader, "material.specularExponent", m_sceneNodes[i]->getMaterialFloat(eMATERIALFLOAT_SPECULAREXPONENT));

							// Light-needed uniforms
							m_graphicsDevice->setUniformVector3f32(m_forwardNormalMappingDirectionalLightShader.shader, "eyePos", m_cameras[c]->getTranslation());

							m_sceneNodes[i]->render();
						}
						else
						{
							m_graphicsDevice->setActiveTexture2D(m_sceneNodes[i]->getMaterialTexture(eMATERIALTEXTURE_DIFFUSE), eTEXTURESLOT_SLOT0);

							m_graphicsDevice->setActiveShader(m_forwardDirectionalLightShader.shader);
							m_graphicsDevice->setUniformMatrix4x4f32(m_forwardDirectionalLightShader.shader, "worldMatrix", worldMatrix);
							m_graphicsDevice->setUniformMatrix4x4f32(m_forwardDirectionalLightShader.shader, "worldViewProjectionMatrix", worldViewProjectionMatrix);

							// Directional light uniforms
							m_graphicsDevice->setUniformColor4f32(m_forwardDirectionalLightShader.shader, "directionalLight.color", light->color);
							m_graphicsDevice->setUniformFloat32(m_forwardDirectionalLightShader.shader, "directionalLight.intensity", light->intensity);
							m_graphicsDevice->setUniformVector3f32(m_forwardDirectionalLightShader.shader, "directionalLight.direction", light->direction);

							// Material uniforms
							m_graphicsDevice->setUniformColor4f32(m_forwardDirectionalLightShader.shader, "material.diffuseColor", m_sceneNodes[i]->getMaterialColor(eMATERIALCOLOR_DIFFUSE));
							m_graphicsDevice->setUniformTexture2D(m_forwardDirectionalLightShader.shader, "material.diffuseTexture", eTEXTURESLOT_SLOT0);
							m_graphicsDevice->setUniformFloat32(m_forwardDirectionalLightShader.shader, "material.specularIntensity", m_sceneNodes[i]->getMaterialFloat(eMATERIALFLOAT_SPECULARINTENSITY));
							m_graphicsDevice->setUniformFloat32(m_forwardDirectionalLightShader.shader, "material.specularExponent", m_sceneNodes[i]->getMaterialFloat(eMATERIALFLOAT_SPECULAREXPONENT));

							// Light-needed uniforms
							m_graphicsDevice->setUniformVector3f32(m_forwardDirectionalLightShader.shader, "eyePos", m_cameras[c]->getTranslation());

							m_sceneNodes[i]->render();
						}
					}
				}
				break;

			case eLIGHTTYPE_POINT:
				for (uint32 i = 0; i < m_sceneNodes.size(); i++)
				{
					math::Matrix4x4f32 worldMatrix = m_sceneNodes[i]->getTransform()->getTransformationMatrix();
					math::Matrix4x4f32 worldViewProjectionMatrix = viewProjectionMatrix * worldMatrix;

					if (m_sceneNodes[i]->isMaterialFlagEnabled(eMATERIALFLAG_LIGHTING))
					{
						if (m_sceneNodes[i]->isMaterialFlagEnabled(eMATERIALFLAG_NORMALMAPPING))
						{
							m_graphicsDevice->setActiveTexture2D(m_sceneNodes[i]->getMaterialTexture(eMATERIALTEXTURE_DIFFUSE), eTEXTURESLOT_SLOT0);
							m_graphicsDevice->setActiveTexture2D(m_sceneNodes[i]->getMaterialTexture(eMATERIALTEXTURE_NORMAL), eTEXTURESLOT_SLOT1);

							m_graphicsDevice->setActiveShader(m_forwardNormalMappingPointLightShader.shader);
							m_graphicsDevice->setUniformMatrix4x4f32(m_forwardNormalMappingPointLightShader.shader, "worldMatrix", worldMatrix);
							m_graphicsDevice->setUniformMatrix4x4f32(m_forwardNormalMappingPointLightShader.shader, "worldViewProjectionMatrix", worldViewProjectionMatrix);

							// Point light uniforms
							m_graphicsDevice->setUniformColor4f32(m_forwardNormalMappingPointLightShader.shader, "pointLight.color", light->color);
							m_graphicsDevice->setUniformFloat32(m_forwardNormalMappingPointLightShader.shader, "pointLight.intensity", light->intensity);
							m_graphicsDevice->setUniformVector3f32(m_forwardNormalMappingPointLightShader.shader, "pointLight.position", light->position);
							m_graphicsDevice->setUniformFloat32(m_forwardNormalMappingPointLightShader.shader, "pointLight.range", light->range);

							// Material uniforms
							m_graphicsDevice->setUniformColor4f32(m_forwardNormalMappingPointLightShader.shader, "material.diffuseColor", m_sceneNodes[i]->getMaterialColor(eMATERIALCOLOR_DIFFUSE));
							m_graphicsDevice->setUniformTexture2D(m_forwardNormalMappingPointLightShader.shader, "material.diffuseTexture", eTEXTURESLOT_SLOT0);
							m_graphicsDevice->setUniformTexture2D(m_forwardNormalMappingPointLightShader.shader, "material.normalTexture", eTEXTURESLOT_SLOT1);
							m_graphicsDevice->setUniformFloat32(m_forwardNormalMappingPointLightShader.shader, "material.specularIntensity", m_sceneNodes[i]->getMaterialFloat(eMATERIALFLOAT_SPECULARINTENSITY));
							m_graphicsDevice->setUniformFloat32(m_forwardNormalMappingPointLightShader.shader, "material.specularExponent", m_sceneNodes[i]->getMaterialFloat(eMATERIALFLOAT_SPECULAREXPONENT));

							// Light-needed uniforms
							m_graphicsDevice->setUniformVector3f32(m_forwardNormalMappingPointLightShader.shader, "eyePos", m_cameras[c]->getTranslation());

							m_sceneNodes[i]->render();
						}
						else
						{
							m_graphicsDevice->setActiveTexture2D(m_sceneNodes[i]->getMaterialTexture(eMATERIALTEXTURE_DIFFUSE), eTEXTURESLOT_SLOT0);

							m_graphicsDevice->setActiveShader(m_forwardPointLightShader.shader);
							m_graphicsDevice->setUniformMatrix4x4f32(m_forwardPointLightShader.shader, "worldMatrix", worldMatrix);
							m_graphicsDevice->setUniformMatrix4x4f32(m_forwardPointLightShader.shader, "worldViewProjectionMatrix", worldViewProjectionMatrix);

							// Point light uniforms
							m_graphicsDevice->setUniformColor4f32(m_forwardPointLightShader.shader, "pointLight.color", light->color);
							m_graphicsDevice->setUniformFloat32(m_forwardPointLightShader.shader, "pointLight.intensity", light->intensity);
							m_graphicsDevice->setUniformVector3f32(m_forwardPointLightShader.shader, "pointLight.position", light->position);
							m_graphicsDevice->setUniformFloat32(m_forwardPointLightShader.shader, "pointLight.range", light->range);

							// Material uniforms
							m_graphicsDevice->setUniformColor4f32(m_forwardPointLightShader.shader, "material.diffuseColor", m_sceneNodes[i]->getMaterialColor(eMATERIALCOLOR_DIFFUSE));
							m_graphicsDevice->setUniformTexture2D(m_forwardPointLightShader.shader, "material.diffuseTexture", eTEXTURESLOT_SLOT0);
							m_graphicsDevice->setUniformFloat32(m_forwardPointLightShader.shader, "material.specularIntensity", m_sceneNodes[i]->getMaterialFloat(eMATERIALFLOAT_SPECULARINTENSITY));
							m_graphicsDevice->setUniformFloat32(m_forwardPointLightShader.shader, "material.specularExponent", m_sceneNodes[i]->getMaterialFloat(eMATERIALFLOAT_SPECULAREXPONENT));

							// Light-needed uniforms
							m_graphicsDevice->setUniformVector3f32(m_forwardPointLightShader.shader, "eyePos", m_cameras[c]->getTranslation());

							m_sceneNodes[i]->render();
						}
					}
				}
				break;

			case eLIGHTTYPE_SPOT:
				for (uint32 i = 0; i < m_sceneNodes.size(); i++)
				{
					math::Matrix4x4f32 worldMatrix = m_sceneNodes[i]->getTransform()->getTransformationMatrix();
					math::Matrix4x4f32 worldViewProjectionMatrix = viewProjectionMatrix * worldMatrix;

					if (m_sceneNodes[i]->isMaterialFlagEnabled(eMATERIALFLAG_LIGHTING))
					{
						if (m_sceneNodes[i]->isMaterialFlagEnabled(eMATERIALFLAG_NORMALMAPPING))
						{
							m_graphicsDevice->setActiveTexture2D(m_sceneNodes[i]->getMaterialTexture(eMATERIALTEXTURE_DIFFUSE), eTEXTURESLOT_SLOT0);
							m_graphicsDevice->setActiveTexture2D(m_sceneNodes[i]->getMaterialTexture(eMATERIALTEXTURE_NORMAL), eTEXTURESLOT_SLOT1);

							m_graphicsDevice->setActiveShader(m_forwardNormalMappingSpotLightShader.shader);
							m_graphicsDevice->setUniformMatrix4x4f32(m_forwardNormalMappingSpotLightShader.shader, "worldMatrix", worldMatrix);
							m_graphicsDevice->setUniformMatrix4x4f32(m_forwardNormalMappingSpotLightShader.shader, "worldViewProjectionMatrix", worldViewProjectionMatrix);

							// Spot light uniforms
							m_graphicsDevice->setUniformColor4f32(m_forwardNormalMappingSpotLightShader.shader, "spotLight.color", light->color);
							m_graphicsDevice->setUniformFloat32(m_forwardNormalMappingSpotLightShader.shader, "spotLight.intensity", light->intensity);
							m_graphicsDevice->setUniformVector3f32(m_forwardNormalMappingSpotLightShader.shader, "spotLight.position", light->position);
							m_graphicsDevice->setUniformVector3f32(m_forwardNormalMappingSpotLightShader.shader, "spotLight.direction", light->direction);
							m_graphicsDevice->setUniformFloat32(m_forwardNormalMappingSpotLightShader.shader, "spotLight.range", light->range);
							m_graphicsDevice->setUniformFloat32(m_forwardNormalMappingSpotLightShader.shader, "spotLight.cutoff", light->cosCutoff);

							// Material uniforms
							m_graphicsDevice->setUniformColor4f32(m_forwardNormalMappingSpotLightShader.shader, "material.diffuseColor", m_sceneNodes[i]->getMaterialColor(eMATERIALCOLOR_DIFFUSE));
							m_graphicsDevice->setUniformTexture2D(m_forwardNormalMappingSpotLightShader.shader, "material.diffuseTexture", eTEXTURESLOT_SLOT0);
							m_graphicsDevice->setUniformTexture2D(m_forwardNormalMappingSpotLightShader.shader, "material.normalTexture", eTEXTURESLOT_SLOT1);
							m_graphicsDevice->setUniformFloat32(m_forwardNormalMappingSpotLightShader.shader, "material.specularIntensity", m_sceneNodes[i]->getMaterialFloat(eMATERIALFLOAT_SPECULARINTENSITY));
							m_graphicsDevice->setUniformFloat32(m_forwardNormalMappingSpotLightShader.shader, "material.specularExponent", m_sceneNodes[i]->getMaterialFloat(eMATERIALFLOAT_SPECULAREXPONENT));

							// Light-needed uniforms
							m_graphicsDevice->setUniformVector3f32(m_forwardNormalMappingSpotLightShader.shader, "eyePos", m_cameras[c]->getTranslation());

							m_sceneNodes[i]->render();
						}
						else
						{
							m_graphicsDevice->setActiveTexture2D(m_sceneNodes[i]->getMaterialTexture(eMATERIALTEXTURE_DIFFUSE), eTEXTURESLOT_SLOT0);

							m_graphicsDevice->setActiveShader(m_forwardSpotLightShader.shader);
							m_graphicsDevice->setUniformMatrix4x4f32(m_forwardSpotLightShader.shader, "worldMatrix", worldMatrix);
							m_graphicsDevice->setUniformMatrix4x4f32(m_forwardSpotLightShader.shader, "worldViewProjectionMatrix", worldViewProjectionMatrix);

							// Spot light uniforms
							m_graphicsDevice->setUniformColor4f32(m_forwardSpotLightShader.shader, "spotLight.color", light->color);
							m_graphicsDevice->setUniformFloat32(m_forwardSpotLightShader.shader, "spotLight.intensity", light->intensity);
							m_graphicsDevice->setUniformVector3f32(m_forwardSpotLightShader.shader, "spotLight.position", light->position);
							m_graphicsDevice->setUniformVector3f32(m_forwardSpotLightShader.shader, "spotLight.direction", light->direction);
							m_graphicsDevice->setUniformFloat32(m_forwardSpotLightShader.shader, "spotLight.range", light->range);
							m_graphicsDevice->setUniformFloat32(m_forwardSpotLightShader.shader, "spotLight.cutoff", light->cosCutoff);

							// Material uniforms
							m_graphicsDevice->setUniformColor4f32(m_forwardSpotLightShader.shader, "material.diffuseColor", m_sceneNodes[i]->getMaterialColor(eMATERIALCOLOR_DIFFUSE));
							m_graphicsDevice->setUniformTexture2D(m_forwardSpotLightShader.shader, "material.diffuseTexture", eTEXTURESLOT_SLOT0);
							m_graphicsDevice->setUniformFloat32(m_forwardSpotLightShader.shader, "material.specularIntensity", m_sceneNodes[i]->getMaterialFloat(eMATERIALFLOAT_SPECULARINTENSITY));
							m_graphicsDevice->setUniformFloat32(m_forwardSpotLightShader.shader, "material.specularExponent", m_sceneNodes[i]->getMaterialFloat(eMATERIALFLOAT_SPECULAREXPONENT));

							// Light-needed uniforms
							m_graphicsDevice->setUniformVector3f32(m_forwardSpotLightShader.shader, "eyePos", m_cameras[c]->getTranslation());

							m_sceneNodes[i]->render();
						}
					}
				}
				break;
			}
		}

		m_graphicsDevice->setBlendingMode(eBLENDINGMODE_DISABLED);
		m_graphicsDevice->setDepthWritingEnabled(true);
	}
}

enco::core::CCamera<enco::core::float32> *enco::core::CSceneManager::addPerspectiveCamera(float32 fov, float32 aspectRatio, float32 zNear, float32 zFar)
{
	CCamera<float32> *camera = 0;

	camera = new CCamera<float32>;
	camera->setPerspectiveProjection(fov, aspectRatio, zNear, zFar);

	m_cameras.push_back(camera);

	return camera;
}

enco::core::CCamera<enco::core::float32> *enco::core::CSceneManager::addOrthographicCamera(float32 left, float32 right, float32 bottom, float32 top, float32 zNear, float32 zFar)
{
	CCamera<float32> *camera = 0;

	camera = new CCamera<float32>;
	camera->setOrthographicProjection(left, right, bottom, top, zNear, zFar);

	m_cameras.push_back(camera);

	return camera;
}

enco::core::ILight *enco::core::CSceneManager::addDirectionalLight(float32 intensity, const Color4f32 &color, const math::Vector3f32 &direction)
{
	ILight *light = 0;

	light = new ILight;
	light->lightType = eLIGHTTYPE_DIRECTIONAL;
	light->intensity = intensity;
	light->color = color;
	light->direction = direction;

	m_lights.push_back(light);

	return light;
}

enco::core::ILight *enco::core::CSceneManager::addPointLight(float32 intensity, const Color4f32 &color, const math::Vector3f32 &position, float32 range)
{
	ILight *light = 0;

	light = new ILight;
	light->lightType = eLIGHTTYPE_POINT;
	light->intensity = intensity;
	light->color = color;
	light->position = position;
	light->range = range;

	m_lights.push_back(light);

	return light;
}

enco::core::ILight *enco::core::CSceneManager::addSpotLight(float32 intensity, const Color4f32 &color, const math::Vector3f32 &position, const math::Vector3f32 &direction, float32 range, float32 cutoff)
{
	ILight *light = 0;

	float64 sin_cos[2];
	math::sin_cos((float64)cutoff, sin_cos);
	float32 cosCutoff = (float32)sin_cos[__COS_INDEX];

	light = new ILight;
	light->lightType = eLIGHTTYPE_SPOT;
	light->intensity = intensity;
	light->color = color;
	light->position = position;
	light->direction = direction;
	light->range = range;
	light->cosCutoff = cosCutoff;

	m_lights.push_back(light);

	return light;
}

enco::core::CCodedMesh *enco::core::CSceneManager::buildCodedMesh(uint32 vertexSizeInBytes, void *vertexData, sint32 vertexComponents, uint32 indexSizeInBytes, void *indexData, uint32 indexCount)
{
	CCodedMesh *codedMesh = 0;

	codedMesh = new CCodedMesh;
	codedMesh->setGraphicsDevice(m_graphicsDevice);
	codedMesh->create(vertexSizeInBytes, vertexData, vertexComponents, indexSizeInBytes, indexData, indexCount);

	return codedMesh;
}

void enco::core::CSceneManager::releaseCodedMesh(CCodedMesh *codedMesh)
{
	__ASSERT(codedMesh != 0);
	codedMesh->release();
	delete codedMesh;
}

enco::core::CCodedMeshSceneNode *enco::core::CSceneManager::addCodedMeshSceneNode(CCodedMesh *codedMesh)
{
	CCodedMeshSceneNode *codedMeshSceneNode = 0;

	codedMeshSceneNode = new CCodedMeshSceneNode;
	codedMeshSceneNode->setCodedMesh(codedMesh);
	codedMeshSceneNode->create(m_graphicsDevice);

	m_sceneNodes.push_back(codedMeshSceneNode);

	return codedMeshSceneNode;
}