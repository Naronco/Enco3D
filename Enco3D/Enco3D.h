#ifndef _ENCO3D_ENCO3D_H_
#define _ENCO3D_ENCO3D_H_

#ifdef main
#	undef main
#endif

namespace Enco3D
{
}

// HEADER FILE INCLUDES

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

// Rendering Engine Headers
#include "BaseLight.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "DirectionalLightShader.h"
#include "IndexedModel.h"
#include "LightGlobalAmbientShader.h"
#include "Material.h"
#include "Mesh.h"
#include "OBJModel.h"
#include "PointLight.h"
#include "PointLightShader.h"
#include "RenderingEngine.h"
#include "Shader.h"
#include "SpotLight.h"
#include "SpotLightShader.h"
#include "Texture.h"
#include "TextureShader.h"
#include "Vertex.h"

// Physics Engine Headers

// Audio Engine Headers

// Component Headers
#include "FirstPersonController.h"
#include "MeshRenderer.h"

#endif