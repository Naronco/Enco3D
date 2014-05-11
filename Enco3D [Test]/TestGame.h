#ifndef _TESTGAME_H_
#define _TESTGAME_H_

#include <Enco3D/Enco3D.h>

using namespace Enco3D::Core;
using namespace Enco3D::Component;
using namespace Enco3D::Rendering;
using namespace Enco3D::Physics;
using namespace Enco3D::Audio;

class TestGame : public IGame
{
public:
	void Init()
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
		StaticConcaveMeshCollisionShape *houseCollisionShape = houseMesh->GetStaticConcaveMeshCollisionShape();
		RigidBody *rigidBody = new RigidBody(0, 0.8f, 1.0f, 0.2f, 0.1f, houseCollisionShape);
		GameObject *houseObject = new GameObject;
		houseObject->AddComponent(houseMesh);
		houseObject->AddComponent(rigidBody);
		AddGameObject(houseObject);

		Camera *mainCamera = GetRenderingEngine()->CreatePerspectiveCamera(MathUtil::ToRadians(70.0f), 0.01f, 100.0f);
//		BloomPostProcessEffect *bloomPostProcessEffect = new BloomPostProcessEffect;
//		bloomPostProcessEffect->SetThreshold(0.86f);
//		SSAOPostProcessEffect *ssaoPostProcessEffect = new SSAOPostProcessEffect;
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
		mainCameraObject->AddComponent(mainCamera);
//		mainCameraObject->AddComponent(bloomPostProcessEffect);
//		mainCameraObject->AddComponent(ssaoPostProcessEffect);
		mainCameraObject->AddComponent(freeLook);
		mainCameraObject->AddComponent(freeMove);
		//	mainCameraObject->AddComponent(mouseLock);
		mainCameraObject->AddComponent(skybox);
		//	mainCameraObject->AddComponent(spotLight);
		AddGameObject(mainCameraObject);

		WavefrontMaterialMesh *linkMesh = new WavefrontMaterialMesh("models/link.obj");
		GameObject *linkObject = new GameObject;
		linkObject->AddComponent(linkMesh);
//		linkObject->GetTransform()->Translate(Vector3f(0.0f, 0.0f, 0.0f));
//		linkObject->GetTransform()->SetBillboardEnabled(true);
//		linkObject->GetTransform()->SetBillboardCamera(mainCamera);
		AddGameObject(linkObject);

		DirectionalLight *sunLight = new DirectionalLight;
		sunLight->SetColor(Vector3f(1, 1, 1));
		sunLight->SetIntensity(2.0f);
		GameObject *sunLightObject = new GameObject("Directional light");
		sunLightObject->AddComponent(sunLight);
		sunLightObject->GetTransform()->SetRotation(Quaternionf(MathUtil::ToRadians(135.0f), MathUtil::ToRadians(-45.0f), 0.0f));
		AddGameObject(sunLightObject);

		for (int i = 0; i < 10; i++)
		{
			PointLight *pointLight = new PointLight;
			pointLight->SetColor(Vector3f(Random::NextFloat(), Random::NextFloat(), Random::NextFloat()));
			pointLight->SetIntensity(3.0f);
			pointLight->SetRange(Random::NextFloat() * 5.0f + 5.0f);

			GameObject *pointLightObject = new GameObject("Point light");
			pointLightObject->GetTransform()->SetTranslation(Vector3f(Random::NextFloat() * 12.0f - 6.0f, 0.1f, Random::NextFloat() * 12.0f - 6.0f));
			pointLightObject->AddComponent(pointLight);

			AddGameObject(pointLightObject);
		}

		for (unsigned int j = 0; j < 1; j++)
		{
			for (unsigned int i = 0; i < 3; i++)
			{
				GUITexture *heartTexture = new GUITexture("texture/heart.png");
				GameObject *heartObject = new GameObject("GUI texture");
				heartObject->AddComponent(heartTexture);
				heartObject->GetTransform()->Scale(Vector3f(40.0f, 40.0f, 1.0f));
				heartObject->GetTransform()->SetTranslation(Vector3f(40.0f + 35.0f * i, 40.0f + 35.0f * j, 0.0f));
				AddGameObject(heartObject);
			}
		}

		GUIText *guiText = new GUIText("Enco3D [Prototype] - test", GetFont("font/arial", FontType::Default));
		GameObject *guiTextObject = new GameObject("GUI text");
		guiTextObject->AddComponent(guiText);
		guiTextObject->GetTransform()->Scale(Vector3f(0.8f, 0.8f, 0.8f));
		guiTextObject->GetTransform()->SetTranslation(Vector3f(0.0f, GetWindow()->GetHeight() - 32.0f * 0.8f, 0.0f));
		AddGameObject(guiTextObject);

		//	GetAudioEngine()->MusicLoad("sounds/kokiri_forest.wav", 10);
		//	GetAudioEngine()->MusicPlay();

		//	GetAudioEngine()->SoundLoad("sounds/test.wav", 50);
		//	GetAudioEngine()->SoundPlay();
	}
	
	void Update()
	{
		static bool flag = true;

		if (Input::IsKeyDown(Keyboard::E) && flag)
		{
			flag = false;

			for (int i = 0; i < 15; i++)
			{
				Material *greenRupeeMaterial = new Material;
				greenRupeeMaterial->AddTexture2D("diffuseTexture", new Texture2D("texture/Rupee.0.png", TextureFilter::Nearest));
				greenRupeeMaterial->AddVector3f("diffuseColor", Vector3f(1, 1, 1));
				greenRupeeMaterial->AddFloat("specularIntensity", 2.0f);
				greenRupeeMaterial->AddFloat("specularExponent", 16.0f);
				WavefrontMesh *greenRupeeMesh = new WavefrontMesh("models/rupee.obj", greenRupeeMaterial);
				CapsuleCollisionShape *greenRupeeCollisionShape = new CapsuleCollisionShape(0.3f, 1.0f);
				RigidBody *greenRupeeRigidBody = new RigidBody(1, 0.8f, 1.0f, 0.2f, 0.1f, greenRupeeCollisionShape);
				GameObject *greenRupeeObject = new GameObject("greenRupee");
				greenRupeeObject->AddComponent(greenRupeeMesh);
				greenRupeeObject->AddComponent(greenRupeeRigidBody);
				greenRupeeObject->GetTransform()->Translate(Vector3f(Random::NextFloat() * 2.0f - 1.0f, 9.0f + Random::NextFloat() * 2.0f, Random::NextFloat() * 2.0f - 1.0f));
				AddGameObject(greenRupeeObject);
			}
		}
	}
};

#endif