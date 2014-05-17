#include <Enco3D/Enco3D.h>

using namespace Enco3D::Core;
using namespace Enco3D::Component;
using namespace Enco3D::Rendering;
using namespace Enco3D::Physics;
using namespace Enco3D::Audio;

class TestGame : public IGame
{
public:
	void init()
	{
		/*		float f = 8.0f;
		Vertex vertices[4] =
		{
		Vertex(-f, 0, +f).SetTexCoord(0, 0, 0).SetNormal(0, 1, 0),
		Vertex(+f, 0, +f).SetTexCoord(1, 0, 0).SetNormal(0, 1, 0),
		Vertex(+f, 0, -f).SetTexCoord(1, 1, 0).SetNormal(0, 1, 0),
		Vertex(-f, 0, -f).SetTexCoord(0, 1, 0).SetNormal(0, 1, 0),
		};
		unsigned int indices[6] =
		{
		0, 1, 2, 0, 2, 3,
		};
		Mesh *floorMesh = new Mesh(vertices, 4, indices, 6);
		Material *floorMaterial = new Material;
		floorMaterial->AddTexture2D("diffuseTexture", new Texture2D("texture/colorGrid.png", TextureFilter::Nearest));
		floorMaterial->AddVector3f("diffuseColor", Vector3f(1, 1, 1));
		floorMaterial->AddFloat("specularIntensity", 1.0f);
		floorMaterial->AddFloat("specularExponent", 32.0f);
		DefaultMesh *floorMeshComponent = new DefaultMesh;
		floorMeshComponent->SetMesh(floorMesh);
		floorMeshComponent->SetMaterial(floorMaterial);
		RigidBody *floorRigidBody = new RigidBody(0, 0.8f, 1.0f, 0.2f, 0.1f, new StaticPlaneCollisionShape(Vector3f(0, 1, 0)));
		GameObject *floorObject = new GameObject;
		floorObject->AddComponent(floorMeshComponent);
		floorObject->AddComponent(floorRigidBody);
		AddGameObject(floorObject);*/

		/*		Material *sphereMaterial = new Material;
		sphereMaterial->AddTexture("diffuseTexture", new Texture("texture/test.png", TextureTarget::Texture2D, TextureFilter::Nearest));
		sphereMaterial->AddVector3f("diffuseColor", Vector3f(1, 1, 1));
		sphereMaterial->AddFloat("specularIntensity", 1.0f);
		sphereMaterial->AddFloat("specularExponent", 32.0f);
		WavefrontMesh *sphereMesh = new WavefrontMesh("models/sphere.obj", sphereMaterial);
		RigidBody *sphereRigidBody = new RigidBody(1, 0.8f, 1.0f, 0.2f, 0.1f, new SphereCollisionShape(1));
		GameObject *sphereObject = new GameObject("sphere");
		sphereObject->GetTransform()->Translate(Vector3f(0, 10, 0));
		sphereObject->AddComponent(sphereMesh);
		sphereObject->AddComponent(sphereRigidBody);
		AddGameObject(sphereObject);*/

		WavefrontMaterialMesh *houseMesh = new WavefrontMaterialMesh("models/house/house.obj");
		StaticConcaveMeshCollisionShape *houseCollisionShape = houseMesh->getStaticConcaveMeshCollisionShape();
		RigidBody *rigidBody = new RigidBody(0, 0.8f, 1.0f, 0.2f, 0.1f, houseCollisionShape);
		GameObject *houseObject = new GameObject;
		houseObject->addComponent(houseMesh);
		houseObject->addComponent(rigidBody);
		addGameObject(houseObject);

		SSAOPostProcessEffect *ssaoPostProcessEffect = new SSAOPostProcessEffect;
		Camera *mainCamera = getRenderingEngine()->createPerspectiveCamera(MathUtil::toRadians(70.0f), 0.01f, 100.0f);
		//		BloomPostProcessEffect *bloomPostProcessEffect = new BloomPostProcessEffect;
		//		bloomPostProcessEffect->SetThreshold(0.86f);
		//	SpotLight *spotLight = new SpotLight;
		//	spotLight->SetColor(Vector3f(1, 1, 1));
		//	spotLight->SetCutoff(MathUtil::DegreesToSpotCutoff(60.0f));
		//	spotLight->SetIntensity(1.0f);
		//	spotLight->SetRange(10.0f);
		FreeLook *freeLook = new FreeLook;
		FreeMove *freeMove = new FreeMove;
		//	MouseLock *mouseLock = new MouseLock;
		Skybox *skybox = new Skybox("texture/skybox/sunny_ocean");
		GameObject *mainCameraObject = new GameObject("Main Camera");
		mainCameraObject->addComponent(mainCamera);
		mainCamera->addPostProcessEffect(ssaoPostProcessEffect);
//		mainCameraObject->addComponent(bloomPostProcessEffect);
		mainCameraObject->addComponent(freeLook);
		mainCameraObject->addComponent(freeMove);
		//	mainCameraObject->AddComponent(mouseLock);
		mainCameraObject->addComponent(skybox);
		//	mainCameraObject->AddComponent(spotLight);
		addGameObject(mainCameraObject);

		WavefrontMaterialMesh *linkMesh = new WavefrontMaterialMesh("models/link.obj");
		GameObject *linkObject = new GameObject;
		linkObject->addComponent(linkMesh);
		//		linkObject->GetTransform()->Translate(Vector3f(0.0f, 0.0f, 0.0f));
		//		linkObject->GetTransform()->SetBillboardEnabled(true);
		//		linkObject->GetTransform()->SetBillboardCamera(mainCamera);
		addGameObject(linkObject);

		DirectionalLight *sunLight = new DirectionalLight;
		sunLight->setColor(Vector3f(1, 1, 1));
		sunLight->setIntensity(2.0f);
		GameObject *sunLightObject = new GameObject("Directional light");
		sunLightObject->addComponent(sunLight);
		sunLightObject->getTransform()->setRotation(Quaternionf(MathUtil::toRadians(135.0f), MathUtil::toRadians(-45.0f), 0.0f));
		addGameObject(sunLightObject);

		for (int i = 0; i < 10; i++)
		{
			PointLight *pointLight = new PointLight;
			pointLight->setColor(Vector3f(Random::nextFloat(), Random::nextFloat(), Random::nextFloat()));
			pointLight->setIntensity(3.0f);
			pointLight->setRange(Random::nextFloat() * 5.0f + 5.0f);

			GameObject *pointLightObject = new GameObject("Point light");
			pointLightObject->getTransform()->setTranslation(Vector3f(Random::nextFloat() * 12.0f - 6.0f, 0.1f, Random::nextFloat() * 12.0f - 6.0f));
			pointLightObject->addComponent(pointLight);

			addGameObject(pointLightObject);
		}

		for (unsigned int j = 0; j < 1; j++)
		{
			for (unsigned int i = 0; i < 3; i++)
			{
				GUITexture *heartTexture = new GUITexture("texture/heart.png");
				GameObject *heartObject = new GameObject("GUI texture");
				heartObject->addComponent(heartTexture);
				heartObject->getTransform()->scale(Vector3f(40.0f, 40.0f, 1.0f));
				heartObject->getTransform()->setTranslation(Vector3f(40.0f + 35.0f * i, 40.0f + 35.0f * j, 0.0f));
				addGameObject(heartObject);
			}
		}

		GUIText *guiText = new GUIText("Enco3D [Prototype] - test", GetFont("font/arial", FontType::Default));
		GameObject *guiTextObject = new GameObject("GUI text");
		guiTextObject->addComponent(guiText);
		guiTextObject->getTransform()->scale(Vector3f(0.8f, 0.8f, 0.8f));
		guiTextObject->getTransform()->setTranslation(Vector3f(0.0f, getWindow()->getHeight() - 32.0f * 0.8f, 0.0f));
		addGameObject(guiTextObject);

		//	GetAudioEngine()->MusicLoad("sounds/kokiri_forest.wav", 10);
		//	GetAudioEngine()->MusicPlay();

		//	GetAudioEngine()->SoundLoad("sounds/test.wav", 50);
		//	GetAudioEngine()->SoundPlay();
	}

	void update()
	{
		static bool flag = true;

		if (Input::isKeyDown(Keyboard::E) && flag)
		{
			flag = false;

			for (int i = 0; i < 15; i++)
			{
				Material *greenRupeeMaterial = new Material;
				greenRupeeMaterial->addTexture2D("diffuseTexture", new Texture2D("texture/Rupee.0.png", TextureFilter::Nearest));
				greenRupeeMaterial->addVector3f("diffuseColor", Vector3f(1, 1, 1));
				greenRupeeMaterial->addFloat("specularIntensity", 2.0f);
				greenRupeeMaterial->addFloat("specularExponent", 16.0f);
				WavefrontMesh *greenRupeeMesh = new WavefrontMesh("models/rupee.obj", greenRupeeMaterial);
				CapsuleCollisionShape *greenRupeeCollisionShape = new CapsuleCollisionShape(0.3f, 1.0f);
				RigidBody *greenRupeeRigidBody = new RigidBody(1, 0.8f, 1.0f, 0.2f, 0.1f, greenRupeeCollisionShape);
				GameObject *greenRupeeObject = new GameObject("greenRupee");
				greenRupeeObject->addComponent(greenRupeeMesh);
				greenRupeeObject->addComponent(greenRupeeRigidBody);
				greenRupeeObject->getTransform()->translate(Vector3f(Random::nextFloat() * 2.0f - 1.0f, 9.0f + Random::nextFloat() * 2.0f, Random::nextFloat() * 2.0f - 1.0f));
				addGameObject(greenRupeeObject);
			}
		}
	}
};

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