#include "TestGame.h"

int main(int argc, char *argv[])
{
	Enco3D_StartInstruction startInstruction;
	startInstruction.windowTitle = "Naronco Enco3D";
	startInstruction.windowWidth = 1024;
	startInstruction.windowHeight = 576;
	startInstruction.multisampleEnabled = true;
	startInstruction.aaSamples = 16;

	IGame *game = new TestGame;

	return Enco3D_Main(&startInstruction, game);
}

/*
#include <Enco3D.h>

using namespace enco::core;

#define __ENCO3D_DEBUG

#if !defined(__ENCO3D_DEBUG) && defined(__ENCO3D_WIN32)
#	pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

struct Vertex
{
	math::Vector3f32 position;
	math::Vector2f32 texCoord;
	math::Vector3f32 normal;
	math::Vector3f32 tangent;
	math::Vector3f32 binormal;
};

int main(int argc, char *argv[])
{
	Enco3DDevice *device = createDevice(eENCO3DDRIVERTYPE_SDL2_OPENGL15, Dimension2u32(1024, 576), "Enco3D Preview", 16);

	IGraphicsDevice *graphicsDevice = device->getGraphicsDevice();
	IWindow *window = device->getWindow();
	CSceneManager *sceneManager = device->getSceneManager();
	CTimer *timer = device->getTimer();

	sceneManager->setGlobalAmbientLightColor(Color4f32(0.0f, 0.0f, 0.0f, 1.0f));

	float32 fieldRadius = 5.0f;
	float32 fieldDiameter = fieldRadius * 2.0f;

	Vertex vertices[4] =
	{
		{ math::Vector3f32(-fieldRadius, 0.0f, -fieldRadius),  math::Vector2f32(0.0f,          0.0f         ),  math::Vector3f32(0.0f, 1.0f, 0.0f), math::Vector3f32(), math::Vector3f32() },
		{ math::Vector3f32(+fieldRadius, 0.0f, -fieldRadius),  math::Vector2f32(fieldDiameter, 0.0f         ),  math::Vector3f32(0.0f, 1.0f, 0.0f), math::Vector3f32(), math::Vector3f32() },
		{ math::Vector3f32(+fieldRadius, 0.0f, +fieldRadius),  math::Vector2f32(fieldDiameter, fieldDiameter),  math::Vector3f32(0.0f, 1.0f, 0.0f), math::Vector3f32(), math::Vector3f32() },
		{ math::Vector3f32(-fieldRadius, 0.0f, +fieldRadius),  math::Vector2f32(0.0f,          fieldDiameter),  math::Vector3f32(0.0f, 1.0f, 0.0f), math::Vector3f32(), math::Vector3f32() },
	};

	vertices[0].tangent  = renderutil::calculateTangent (vertices[0].position, vertices[0].texCoord, vertices[1].position, vertices[1].texCoord, vertices[2].position, vertices[2].texCoord);
	vertices[0].binormal = renderutil::calculateBinormal(vertices[0].position, vertices[0].texCoord, vertices[1].position, vertices[1].texCoord, vertices[2].position, vertices[2].texCoord);
	vertices[1].tangent  = renderutil::calculateTangent (vertices[1].position, vertices[1].texCoord, vertices[2].position, vertices[2].texCoord, vertices[3].position, vertices[3].texCoord);
	vertices[1].binormal = renderutil::calculateBinormal(vertices[1].position, vertices[1].texCoord, vertices[2].position, vertices[2].texCoord, vertices[3].position, vertices[3].texCoord);
	vertices[2].tangent  = renderutil::calculateTangent (vertices[2].position, vertices[2].texCoord, vertices[3].position, vertices[3].texCoord, vertices[0].position, vertices[0].texCoord);
	vertices[2].binormal = renderutil::calculateBinormal(vertices[2].position, vertices[2].texCoord, vertices[3].position, vertices[3].texCoord, vertices[0].position, vertices[0].texCoord);
	vertices[3].tangent  = renderutil::calculateTangent (vertices[3].position, vertices[3].texCoord, vertices[0].position, vertices[0].texCoord, vertices[1].position, vertices[1].texCoord);
	vertices[3].binormal = renderutil::calculateBinormal(vertices[3].position, vertices[3].texCoord, vertices[0].position, vertices[0].texCoord, vertices[1].position, vertices[1].texCoord);
	
	sint32 vertexComponents = eVERTEXCOMPONENT_POSITION3F32 | eVERTEXCOMPONENT_TEXCOORD2F32 | eVERTEXCOMPONENT_NORMAL3F32 | eVERTEXCOMPONENT_TANGENT3F32 | eVERTEXCOMPONENT_BINORMAL3F32;
	uint32 vertexSizeInBytes = sizeof(Vertex)* 4;

	uint32 indices[6] = { 0, 1, 2, 0, 2, 3 };
	uint32 indexSizeInBytes = sizeof(uint32)* 6;
	
	CCodedMesh *codedMesh = sceneManager->buildCodedMesh(vertexSizeInBytes, vertices, vertexComponents, indexSizeInBytes, indices, 6);
	CCodedMeshSceneNode *codedMeshSceneNode = sceneManager->addCodedMeshSceneNode(codedMesh);
	codedMeshSceneNode->setMaterialFlag(eMATERIALFLAG_LIGHTING, true);
//	codedMeshSceneNode->setMaterialFlag(eMATERIALFLAG_NORMALMAPPING, true);
	codedMeshSceneNode->setMaterialColor(eMATERIALCOLOR_DIFFUSE, Color4f32(1, 1, 1, 1));
	codedMeshSceneNode->setMaterialTexture(eMATERIALTEXTURE_DIFFUSE, "texture/stone.png", eTEXTUREFILTER_LINEAR);
	codedMeshSceneNode->setMaterialTexture(eMATERIALTEXTURE_NORMAL, "texture/stone_NRM.png", eTEXTUREFILTER_LINEAR);
	codedMeshSceneNode->setMaterialFloat(eMATERIALFLOAT_SPECULARINTENSITY, 1.0f);
	codedMeshSceneNode->setMaterialFloat(eMATERIALFLOAT_SPECULAREXPONENT, 64.0f);
	
//	IShape *planeShape = device->getPhysicsDevice()->createStaticPlaneShape();

	codedMeshSceneNode->setPhysicsFlag(ePHYSICSFLAG_USERIGIDBODY, true);
//	codedMeshSceneNode->setPhysicsShape(planeShape);
	codedMeshSceneNode->setPhysicsFloat(ePHYSICSFLOAT_MASS, 0);

	RigidBodyData planeShapeBodyData;
	codedMeshSceneNode->buildRigidBodyData(&planeShapeBodyData);
	std::cout << device->getPhysicsDevice() << std::endl;
//	IRigidBody *planeRigidBody = device->getPhysicsDevice()->addRigidBody(planeShapeBodyData);

	math::Vector3f32 cameraPosition(0, 5, 0);
	math::Vector3f32 cameraRotation(0, 0, 0);
	bool mouseLocked = false;

	CCamera<float32> *mainCamera = sceneManager->addPerspectiveCamera(__TO_RADIANS_f32(70.0f), (float32)device->getDisplayDim().x / (float32)device->getDisplayDim().y, 0.01f, 100.0f);
	mainCamera->setTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	ILight *directionalLight = sceneManager->addDirectionalLight(1.0f, Color4f32(1, 1, 0, 1), math::Vector3f32(1, -1, 1).getNormalized());
	ILight *pointLight = sceneManager->addPointLight(1.0f, Color4f32(0, 1, 1, 1), math::Vector3f32(0, 2, 0), 5.0f);
	ILight *spotLight = sceneManager->addSpotLight(1.0f, Color4f32(1, 1, 0, 1), cameraPosition, mainCamera->getForward(), 20.0f, __TO_RADIANS_f32(20.0f));

	while (device->run())
	{
		{
			float32 movementSpeed = 4.0f;
			float32 rotateSpeed = 0.1f;

			if (window->isButtonDown(input::LEFT_MOUSE) && !mouseLocked)
			{
				mouseLocked = true;
				window->setCursor(false);
				window->setCursorPosition(math::Vector2s32((sint32)device->getDisplayDim().x >> 1, (sint32)device->getDisplayDim().y >> 1));
			}

			if (window->isKeyDown(input::KEY_ESCAPE) && mouseLocked)
			{
				mouseLocked = false;
				window->setCursor(true);
			}

			if (mouseLocked)
			{
				sint32 relativeX = window->getCursorPosition().x - ((sint32)device->getDisplayDim().x >> 1);
				sint32 relativeY = window->getCursorPosition().y - ((sint32)device->getDisplayDim().y >> 1);

				bool rotateY = relativeY != 0;
				bool rotateX = relativeX != 0;

				if (rotateY)
					cameraRotation.y -= __TO_RADIANS_f32(relativeY * rotateSpeed);
				if (rotateX)
					cameraRotation.x += __TO_RADIANS_f32(relativeX * rotateSpeed);

				__CLAMP_RADIANS_f32(cameraRotation.x);
				__CLAMP_RADIANS_f32(cameraRotation.y);

				if (rotateY || rotateX)
					window->setCursorPosition(math::Vector2s32((sint32)device->getDisplayDim().x >> 1, (sint32)device->getDisplayDim().y >> 1));
			
				math::Vector3f32 movement;

				if (device->getWindow()->isKeyDown(input::KEY_W))
					movement += mainCamera->getForward();
				if (device->getWindow()->isKeyDown(input::KEY_S))
					movement -= mainCamera->getForward();
				if (device->getWindow()->isKeyDown(input::KEY_SPACE))
					movement.y += 1.0f;
				if (device->getWindow()->isKeyDown(input::KEY_LSHIFT))
					movement.y -= 1.0f;
				if (device->getWindow()->isKeyDown(input::KEY_A))
					movement -= mainCamera->getRight();
				if (device->getWindow()->isKeyDown(input::KEY_D))
					movement += mainCamera->getRight();

				if (movement.getSquaredLength() > 0.0f)
				{
					movement = movement.getNormalized();

					movement *= timer->getDeltaTime() * movementSpeed;
					cameraPosition += movement;
				}

				mainCamera->setTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);
				mainCamera->setRotation(cameraRotation.x, cameraRotation.y, cameraRotation.z);

				spotLight->position = cameraPosition;
				spotLight->direction = mainCamera->getForward();
			}
		}

		graphicsDevice->beginScene(Color4f32(0.5f, 0.8f, 1.0f, 1.0f));
		sceneManager->renderAll();
		graphicsDevice->endScene();
	}

	sceneManager->releaseCodedMesh(codedMesh);

	releaseDevice(device);

	return 0;
}*/