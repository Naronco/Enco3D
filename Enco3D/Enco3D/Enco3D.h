#ifndef _ENCO3D_ENCO3D_H_
#define _ENCO3D_ENCO3D_H_

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
	char *windowTitle;
	unsigned int windowWidth, windowHeight;
	bool multisampleEnabled;
	unsigned int aaSamples;

} Enco3D_StartInstruction;

inline static int Enco3D_Main(const __Enco3D_StartInstruction *info, Enco3D::Core::IGame *game)
{
	Enco3D::Core::Enco3DEngine::getInstance()->init(info->windowTitle, info->windowWidth, info->windowHeight, info->multisampleEnabled, info->aaSamples, game);
	Enco3D::Core::Enco3DEngine::getInstance()->mainLoop();
	Enco3D::Core::Enco3DEngine::getInstance()->deinit();

	return 0;
}

#endif