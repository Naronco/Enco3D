#ifndef _ENCO3D_ENCO3D_H_
#define _ENCO3D_ENCO3D_H_

#define WIN32_LEAN_AND_MEAN

#ifdef main
#	undef main
#endif

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long long ulonglong;

typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef signed long long sint64;

typedef signed long long longlong;

// HEADER FILE INCLUDES

// DLL File
#include "DLLExport.h"

// Audio Engine Headers
#include "AudioEngine.h"

// Component Headers
#include "BloomPostProcessEffect.h"
#include "Camera.h"
#include "DefaultMesh.h"
#include "DirectionalLight.h"
#include "FreeLook.h"
#include "FreeMove.h"
#include "GUIText.h"
#include "GUITexture.h"
#include "ILight.h"
#include "IPostProcessEffect.h"
#include "MouseLock.h"
#include "PointLight.h"
#include "RigidBody.h"
#include "Skybox.h"
#include "SpotLight.h"
#include "SSAOPostProcessEffect.h"
#include "WavefrontMaterialMesh.h"
#include "WavefrontMesh.h"
#include "LODMesh.h"
#include "Billboard.h"

// Core Engine Headers
#include "DebugLogger.h"
#include "Enco3DEngine.h"
#include "Event.h"
#include "GameObject.h"
#include "GLWindow.h"
#include "IGame.h"
#include "IGameComponent.h"
#include "Input.h"
#include "MathUtil.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
#include "Random.h"
#include "ReferenceCounter.h"
#include "Timer.h"
#include "Transform.h"
#include "TSingleton.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

// Network Headers
#include "HTTPRequest.h"

// Algorithm Headers
//#include "DiamondSquareAlgorithm.h"
#include "INoise.h"
#include "PerlinNoise.h"

// IO Headers
#include "ImageIO.h"

// Physics Engine Headers
#include "BoxCollisionShape.h"
#include "CapsuleCollisionShape.h"
#include "ConeCollisionShape.h"
#include "CylinderCollisionShape.h"
#include "ICollisionShape.h"
#include "ConvexMeshCollisionShape.h"
#include "PhysicsEngine.h"
#include "PhysicsHelper.h"
#include "SphereCollisionShape.h"
#include "StaticConcaveMeshCollisionShape.h"
#include "StaticPlaneCollisionShape.h"

// Rendering Engine Headers
#include "Font.h"
#include "FontPool.h"
#include "Framebuffer.h"
#include "ITexture.h"
#include "Material.h"
#include "Mesh.h"
#include "MeshResource.h"
#include "RenderingEngine.h"
#include "Shader.h"
#include "ShaderPool.h"
#include "Texture2D.h"
#include "TextureCubeMap.h"
#include "Vertex.h"

typedef struct __Enco3D_StartInstruction
{
	char *windowTitle{ "Enco3D window" };
	unsigned int windowWidth{ 640 }, windowHeight{ 480 };
	bool multisampleEnabled{ false };
	unsigned int aaSamples{ 0 };
	std::string iconSource{ "" };
	Enco3D::Core::Vector3f globalAmbientColor{ Enco3D::Core::Vector3f(0, 0, 0) };
	Enco3D::Core::Vector3f clearColor{ Enco3D::Core::Vector3f(0, 0, 0) };
	uint32 rasterizationMode{ Enco3D::Rendering::RasterizationMode::Solid };
	bool deferredShading{ false };
} Enco3D_StartInstruction;

inline static int Enco3D_Main(const __Enco3D_StartInstruction *info, Enco3D::Core::IGame *game)
{
	Enco3D::Core::Enco3DEngine *engineInstance = Enco3D::Core::Enco3DEngine::getInstance();

	engineInstance->init(info->windowTitle, info->windowWidth, info->windowHeight, info->multisampleEnabled, info->aaSamples, info->iconSource, game);
	engineInstance->getRenderingEngine()->setDeferredShadingEnabled(info->deferredShading);
	engineInstance->getRenderingEngine()->setClearColor(info->clearColor);
	engineInstance->getRenderingEngine()->setGlobalAmbientColor(info->globalAmbientColor);
	engineInstance->getRenderingEngine()->setRasterizationMode(info->rasterizationMode);
	engineInstance->getGame()->init();
	engineInstance->mainLoop();
	engineInstance->deinit();

	return 0;
}

#endif