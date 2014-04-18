#include "TestGame.h"

void TestGame::Init()
{
/*	Mesh *fieldMesh = new Mesh("models/field.obj");

	Material *fieldMaterial = new Material;
	fieldMaterial->AddTexture("diffuse", Texture("texture/test.png", TextureTarget::Texture2D, TextureFilter::Nearest));
	fieldMaterial->AddFloat("specularIntensity", 1.0f);
	fieldMaterial->AddFloat("specularExponent", 64.0f);

	GameObject *fieldMeshObject = new GameObject("field");
	fieldMeshObject->GetTransform()->Translate(Vector3f(0, -4, 0));
	fieldMeshObject->AddComponent(new MeshRenderer(fieldMesh, fieldMaterial));
	fieldMeshObject->AddComponent(new RigidBody(0, 0.8f, 1.0f, 0.2f, 0.1f, new StaticPlaneCollisionShape(Vector3f(0, 1, 0))));

/*	Camera *mainCamera = new Camera;
	mainCamera->SetName("camera");
	mainCamera->SetPerspectiveProjection(MathUtil::ToRadians(70.0f), (float)GetWindow()->GetWidth() / (float)GetWindow()->GetHeight(), 0.01f, 100.0f);
	
	GameObject *cameraObject = new GameObject("mainCamera");
	cameraObject->AddComponent(mainCamera);
	cameraObject->GetTransform()->SetTranslation(Vector3f(0.0f, 5.0f, -5.0f));
	cameraObject->GetTransform()->SetRotation(Quaternionf(Vector3f(1, 0, 0), MathUtil::ToRadians(45.0f)));

	SpotLight *flashLight = new SpotLight;
	flashLight->SetColor(Vector3f(1, 1, 1));
	flashLight->SetIntensity(3.0f);
	flashLight->SetRange(20.0f);
	flashLight->SetCutoff(MathUtil::DegreesToSpotCutoff(35.0f));

	Player *playerComponent = new Player;

	//RigidBody *playerRigidBody = new RigidBody(1, 0.8f, 1.0f, 0.2f, 0.1f, new CapsuleCollisionShape(1, 2));
	RigidBody *playerRigidBody = new RigidBody(1, 0.0f, 1.0f, 0.0f, 0.0f, new CapsuleCollisionShape(1, 2));
	playerRigidBody->SetAlwaysStanding(true);
	playerRigidBody->SetName("rigidBody");

	WavefrontMesh *playerMesh = new WavefrontMesh("models/link.obj");

	GameObject *playerObject = new GameObject("player");
	playerObject->AddComponent(playerComponent);
	playerObject->AddComponent(playerRigidBody);
	playerObject->AddComponent(flashLight);
	playerObject->AddComponent(playerMesh);

	playerObject->AddChild(cameraObject);
	*/

	GameObject *linkObject = new GameObject;
	linkObject->AddComponent(new WavefrontMesh("models/link.obj"));

	Camera *mainCamera = new Camera;
	mainCamera->SetName("camera");
	mainCamera->SetPerspectiveProjection(MathUtil::ToRadians(70.0f), (float)GetWindow()->GetWidth() / (float)GetWindow()->GetHeight(), 0.01f, 100.0f);

	GameObject *mainCameraObject = new GameObject("mainCamera");
	mainCameraObject->AddComponent(mainCamera);
	mainCameraObject->AddComponent(new FirstPersonController);
	mainCameraObject->AddComponent(new Skybox("texture/skybox/sunny_evening"));

	AddGameObject(linkObject);
	AddGameObject(mainCameraObject);

	DirectionalLight *sunLight = new DirectionalLight;
	sunLight->SetColor(Vector3f(1, 1, 1));
	sunLight->SetIntensity(2.0f);

	GameObject *sunLightObject = new GameObject;
	sunLightObject->AddComponent(sunLight);
	sunLightObject->GetTransform()->SetRotation(Quaternionf(MathUtil::ToRadians(135.0f), MathUtil::ToRadians(-45.0f), 0.0f));

	AddGameObject(sunLightObject);

	GetRenderingEngine()->SetClearColor(0.5f, 0.8f, 1.0f);
	GetRenderingEngine()->SetGlobalAmbientColor(Vector3f(0.2f, 0.2f, 0.2f));
	
//	GetRenderingEngine()->GetMainCamera()->Move(Vector3f(0, 0, -1), 5);

	for (int i = 0; i < 10; i++)
	{
		PointLight *pointLight = new PointLight;
		pointLight->SetColor(Vector3f(Random::NextFloat(), Random::NextFloat(), Random::NextFloat()));
		pointLight->SetIntensity(3.0f);
		pointLight->SetRange(Random::NextFloat() * 5.0f + 5.0f);

		GameObject *pointLightObject = new GameObject("pointLight");
		pointLightObject->GetTransform()->SetTranslation(Vector3f(Random::NextFloat() * 12.0f - 6.0f, -3.9f, Random::NextFloat() * 12.0f - 6.0f));
		pointLightObject->AddComponent(pointLight);

		AddGameObject(pointLightObject);
	}

	for (unsigned int j = 0; j < 1; j++)
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			GUITexture *heartTexture = new GUITexture("texture/heart.png");

			GameObject *heartObject = new GameObject("heart");
			heartObject->AddComponent(heartTexture);
			heartObject->GetTransform()->Scale(Vector3f(40.0f, 40.0f, 1.0f));
			heartObject->GetTransform()->SetTranslation(Vector3f(40.0f + 35.0f * i, 40.0f + 35.0f * j, 0.0f));

			AddGameObject(heartObject);
		}
	}

	GUIText *guiText = new GUIText("Enco3D [Prototype] - test", GetFont("font/arial", FontType::Default));

	GameObject *guiTextObject = new GameObject("guiText");
	guiTextObject->AddComponent(guiText);
	guiTextObject->GetTransform()->Scale(Vector3f(0.8f, 0.8f, 0.8f));
	guiTextObject->GetTransform()->SetTranslation(Vector3f(0.0f, GetWindow()->GetHeight() - 32.0f * 0.8f, 0.0f));

	AddGameObject(guiTextObject);
	
//	GetAudioEngine()->MusicLoad("sounds/kokiri_forest.wav", 10);
//	GetAudioEngine()->MusicPlay();

//	GetAudioEngine()->SoundLoad("sounds/test.wav", 50);
//	GetAudioEngine()->SoundPlay();
}

void TestGame::Deinit()
{
}

void TestGame::Update()
{
/*	static float timeout = 0.0f;

	if (Input::IsKeyDown(SDLK_e) && timeout < 0.1f)
	{
		int rand = Random::NextInt(6);

		switch (rand)
		{
		case 0:
		{
				  Mesh *boxMesh = new Mesh("models/box.obj");

				  static Material *boxMaterial = nullptr;

				  if (boxMaterial == nullptr)
				  {
					  boxMaterial = new Material;
					  boxMaterial->AddTexture("diffuse", Texture("texture/test.png", TextureTarget::Texture2D, TextureFilter::Nearest));
					  boxMaterial->AddFloat("specularIntensity", 1.0f);
					  boxMaterial->AddFloat("specularExponent", 64.0f);
				  }

				  GameObject *boxObject = new GameObject("box");
				  boxObject->GetTransform()->Translate(Vector3f(Random::NextFloat() * 4.0f - 2.0f, 10, Random::NextFloat() * 4.0f - 2.0f));
				  boxObject->AddComponent(new MeshRenderer(boxMesh, boxMaterial));
				  boxObject->AddComponent(new RigidBody(1, 0.8f, 1.0f, 0.2f, 0.1f, new BoxCollisionShape(Vector3f(2, 2, 2))));

				  AddGameObject(boxObject);
				  break;
		}

		case 1:
		{
				  Mesh *capsuleMesh = new Mesh("models/capsule.obj");

				  static Material *capsuleMaterial = nullptr;

				  if (capsuleMaterial == nullptr)
				  {
					  capsuleMaterial = new Material;
					  capsuleMaterial->AddTexture("diffuse", Texture("texture/test.png", TextureTarget::Texture2D, TextureFilter::Nearest));
					  capsuleMaterial->AddFloat("specularIntensity", 1.0f);
					  capsuleMaterial->AddFloat("specularExponent", 64.0f);
				  }

				  GameObject *capsuleObject = new GameObject("capsule");
				  capsuleObject->GetTransform()->Translate(Vector3f(Random::NextFloat() * 4.0f - 2.0f, 10, Random::NextFloat() * 4.0f - 2.0f));
				  capsuleObject->AddComponent(new MeshRenderer(capsuleMesh, capsuleMaterial));
				  capsuleObject->AddComponent(new RigidBody(1, 0.8f, 1.0f, 0.2f, 0.1f, new CapsuleCollisionShape(1, 2)));

				  AddGameObject(capsuleObject);
				  break;
		}

		case 2:
		{
				  Mesh *coneMesh = new Mesh("models/cone.obj");

				  static Material *coneMaterial = nullptr;

				  if (coneMaterial == nullptr)
				  {
					  coneMaterial = new Material;
					  coneMaterial->AddTexture("diffuse", Texture("texture/test.png", TextureTarget::Texture2D, TextureFilter::Nearest));
					  coneMaterial->AddFloat("specularIntensity", 1.0f);
					  coneMaterial->AddFloat("specularExponent", 64.0f);
				  }

				  GameObject *coneObject = new GameObject("cone");
				  coneObject->GetTransform()->Translate(Vector3f(Random::NextFloat() * 4.0f - 2.0f, 10, Random::NextFloat() * 4.0f - 2.0f));
				  coneObject->AddComponent(new MeshRenderer(coneMesh, coneMaterial));
				  coneObject->AddComponent(new RigidBody(1, 0.8f, 1.0f, 0.2f, 0.1f, new ConeCollisionShape(1, 2)));

				  AddGameObject(coneObject);
				  break;
		}

		case 3:
		{
				  Mesh *cylinderMesh = new Mesh("models/cylinder.obj");

				  static Material *cylinderMaterial = nullptr;

				  if (cylinderMaterial == nullptr)
				  {
					  cylinderMaterial = new Material;
					  cylinderMaterial->AddTexture("diffuse", Texture("texture/test.png", TextureTarget::Texture2D, TextureFilter::Nearest));
					  cylinderMaterial->AddFloat("specularIntensity", 1.0f);
					  cylinderMaterial->AddFloat("specularExponent", 64.0f);
				  }

				  GameObject *cylinderObject = new GameObject("cylinder");
				  cylinderObject->GetTransform()->Translate(Vector3f(Random::NextFloat() * 4.0f - 2.0f, 10, Random::NextFloat() * 4.0f - 2.0f));
				  cylinderObject->AddComponent(new MeshRenderer(cylinderMesh, cylinderMaterial));
				  cylinderObject->AddComponent(new RigidBody(1, 0.8f, 1.0f, 0.2f, 0.1f, new CylinderCollisionShape(Vector3f(2, 2, 2))));

				  AddGameObject(cylinderObject);
				  break;
		}

		case 4:
		{
				  Mesh *sphereMesh = new Mesh("models/sphere.obj");

				  static Material *sphereMaterial = nullptr;

				  if (sphereMaterial == nullptr)
				  {
					  sphereMaterial = new Material;
					  sphereMaterial->AddTexture("diffuse", Texture("texture/test.png", TextureTarget::Texture2D, TextureFilter::Nearest));
					  sphereMaterial->AddFloat("specularIntensity", 1.0f);
					  sphereMaterial->AddFloat("specularExponent", 64.0f);
				  }

				  GameObject *sphereObject = new GameObject("sphere");
				  sphereObject->GetTransform()->Translate(Vector3f(Random::NextFloat() * 4.0f - 2.0f, 10, Random::NextFloat() * 4.0f - 2.0f));
				  sphereObject->AddComponent(new MeshRenderer(sphereMesh, sphereMaterial));
				  sphereObject->AddComponent(new RigidBody(1, 0.8f, 1.0f, 0.2f, 0.1f, new SphereCollisionShape(1)));

				  AddGameObject(sphereObject);
				  break;
		}

		case 5:
		{
				  Mesh *convexMesh = new Mesh("models/convex.obj");

				  static Material *convexMaterial = nullptr;

				  if (convexMaterial == nullptr)
				  {
					  convexMaterial = new Material;
					  convexMaterial->AddTexture("diffuse", Texture("texture/test.png", TextureTarget::Texture2D, TextureFilter::Nearest));
					  convexMaterial->AddFloat("specularIntensity", 1.0f);
					  convexMaterial->AddFloat("specularExponent", 64.0f);
				  }

				  GameObject *convexObject = new GameObject("convex");
				  convexObject->GetTransform()->Translate(Vector3f(Random::NextFloat() * 4.0f - 2.0f, 10, Random::NextFloat() * 4.0f - 2.0f));
				  convexObject->AddComponent(new MeshRenderer(convexMesh, convexMaterial));
				  convexObject->AddComponent(new RigidBody(1, 0.8f, 1.0f, 0.2f, 0.1f, new ConvexMeshCollisionShape(convexMesh)));

				  AddGameObject(convexObject);
				  break;
		}
		}

		timeout = 1.0f;
	}

	if (timeout > 0.0f)
	{
		timeout -= GetTimer()->GetDeltaTime();
	}*/
}

void TestGame::Render()
{
}