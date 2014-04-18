#ifndef _ENCO3D_ENCO3D_H_
#define _ENCO3D_ENCO3D_H_

#ifdef main
#	undef main
#endif

// HEADER FILE INCLUDES

// Audio Engine Headers
#include "AudioEngine.h"

// Component Headers
#include "Camera.h"
#include "DirectionalLight.h"
#include "FirstPersonController.h"
#include "GUIText.h"
#include "GUITexture.h"
#include "ILight.h"
#include "MeshRenderer.h"
#include "PointLight.h"
#include "RigidBody.h"
#include "Skybox.h"
#include "SpotLight.h"
#include "WavefrontMesh.h"

// Core Engine Headers
#include "Enco3DEngine.h"
#include "Error.h"
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
#include "Timer.h"
#include "Transform.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

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
#include "FontDatabase.h"
#include "GBuffer.h"
#include "IndexedModel.h"
#include "Material.h"
#include "Mesh.h"
#include "OBJModel.h"
#include "RenderingEngine.h"
#include "Shader.h"
#include "Texture.h"
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
	Enco3D::Core::Enco3DEngine::GetInstance()->Init(info->windowTitle, info->windowWidth, info->windowHeight, info->multisampleEnabled, info->aaSamples, game);
	Enco3D::Core::Enco3DEngine::GetInstance()->MainLoop();
	Enco3D::Core::Enco3DEngine::GetInstance()->Deinit();

	return 0;
}

#endif