#ifndef _ENCO3D_ENCO3D_H_
#define _ENCO3D_ENCO3D_H_

#ifdef main
#	undef main
#endif

// HEADER FILE INCLUDES

// Audio Engine Headers

// Component Headers
#include "Camera.h"
#include "DirectionalLight.h"
#include "FirstPersonController.h"
#include "Light.h"
#include "MeshRenderer.h"
#include "PointLight.h"
#include "RigidBody.h"
#include "SpotLight.h"

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
#include "PhysicsEngine.h"
#include "PhysicsHelper.h"
#include "SphereCollisionShape.h"
#include "StaticPlaneCollisionShape.h"

// Rendering Engine Headers
#include "DirectionalLightShader.h"
#include "GBuffer.h"
#include "GeometryPassShader.h"
#include "IndexedModel.h"
#include "LightGlobalAmbientShader.h"
#include "Material.h"
#include "Mesh.h"
#include "OBJModel.h"
#include "PointLightShader.h"
#include "PostProcessShader.h"
#include "RenderingEngine.h"
#include "Shader.h"
#include "SpotLightShader.h"
#include "Texture.h"
#include "TextureShader.h"
#include "Vertex.h"

#endif