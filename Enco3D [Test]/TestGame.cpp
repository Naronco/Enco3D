#include "TestGame.h"

void TestGame::Init()
{
	float fieldSize = 8.0f;
	float textureSize = fieldSize * 2.0f;

	Vertex fieldVertices[4] =
	{
		Vertex(-fieldSize, 0,  fieldSize).SetTexCoord(0,           0          ).SetNormal(0, 1, 0),
		Vertex(-fieldSize, 0, -fieldSize).SetTexCoord(0,           textureSize).SetNormal(0, 1, 0),
		Vertex( fieldSize, 0,  fieldSize).SetTexCoord(textureSize, 0          ).SetNormal(0, 1, 0),
		Vertex( fieldSize, 0, -fieldSize).SetTexCoord(textureSize, textureSize).SetNormal(0, 1, 0),
	};

	unsigned int fieldIndices[6] =
	{
		0, 1, 2,
		1, 3, 2,
	};

	Mesh *fieldMesh = new Mesh(fieldVertices, 4, fieldIndices, 6);

	Material *fieldMaterial = new Material;
	fieldMaterial->AddTexture("diffuse", Texture("texture/test.png", TextureTarget::Texture2D, TextureFilter::Nearest));
	fieldMaterial->AddFloat("specularIntensity", 1.0f);
	fieldMaterial->AddFloat("specularExponent", 64.0f);

	GameObject *fieldMeshObject = new GameObject;
	fieldMeshObject->GetTransform()->Translate(Vector3f(0, -4, 0));
	fieldMeshObject->AddComponent(new MeshRenderer(fieldMesh, fieldMaterial));

	Vertex cubeVertices[24] =
	{
		Vertex(-1, -1, -1).SetTexCoord(0, 0).SetNormal( 0, -1,  0),
		Vertex( 1, -1, -1).SetTexCoord(1, 0).SetNormal( 0, -1,  0),
		Vertex( 1, -1,  1).SetTexCoord(1, 1).SetNormal( 0, -1,  0),
		Vertex(-1, -1,  1).SetTexCoord(0, 1).SetNormal( 0, -1,  0),
		
		Vertex(-1,  1, -1).SetTexCoord(0, 0).SetNormal( 0,  1,  0),
		Vertex( 1,  1, -1).SetTexCoord(1, 0).SetNormal( 0,  1,  0),
		Vertex( 1,  1,  1).SetTexCoord(1, 1).SetNormal( 0,  1,  0),
		Vertex(-1,  1,  1).SetTexCoord(0, 1).SetNormal( 0,  1,  0),

		Vertex(-1, -1, -1).SetTexCoord(0, 0).SetNormal( 0,  0, -1),
		Vertex( 1, -1, -1).SetTexCoord(1, 0).SetNormal( 0,  0, -1),
		Vertex( 1,  1, -1).SetTexCoord(1, 1).SetNormal( 0,  0, -1),
		Vertex(-1,  1, -1).SetTexCoord(0, 1).SetNormal( 0,  0, -1),

		Vertex(-1, -1,  1).SetTexCoord(0, 0).SetNormal( 0,  0,  1),
		Vertex( 1, -1,  1).SetTexCoord(1, 0).SetNormal( 0,  0,  1),
		Vertex( 1,  1,  1).SetTexCoord(1, 1).SetNormal( 0,  0,  1),
		Vertex(-1,  1,  1).SetTexCoord(0, 1).SetNormal( 0,  0,  1),

		Vertex(-1, -1, -1).SetTexCoord(0, 0).SetNormal(-1,  0,  0),
		Vertex(-1,  1, -1).SetTexCoord(1, 0).SetNormal(-1,  0,  0),
		Vertex(-1,  1,  1).SetTexCoord(1, 1).SetNormal(-1,  0,  0),
		Vertex(-1, -1,  1).SetTexCoord(0, 1).SetNormal(-1,  0,  0),

		Vertex( 1, -1, -1).SetTexCoord(0, 0).SetNormal( 1,  0,  0),
		Vertex( 1,  1, -1).SetTexCoord(1, 0).SetNormal( 1,  0,  0),
		Vertex( 1,  1,  1).SetTexCoord(1, 1).SetNormal( 1,  0,  0),
		Vertex( 1, -1,  1).SetTexCoord(0, 1).SetNormal( 1,  0,  0),
	};

	unsigned int cubeIndices[36] =
	{
		 0,  1,  2,  0,  2,  3,
		 4,  5,  6,  4,  6,  7,
		 8,  9, 10,  8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};

	Mesh *cubeMesh = new Mesh(cubeVertices, 24, cubeIndices, 36);

	Material *cubeMaterial = new Material;
	cubeMaterial->AddTexture("diffuse", Texture("texture/test.png", TextureTarget::Texture2D, TextureFilter::Nearest));
	cubeMaterial->AddFloat("specularIntensity", 1.0f);
	cubeMaterial->AddFloat("specularExponent", 16.0f);

	GameObject *cubeMeshObject = new GameObject;
	cubeMeshObject->GetTransform()->Translate(Vector3f(20, -4, 20));
	cubeMeshObject->AddComponent(new MeshRenderer(cubeMesh, cubeMaterial));
	//cubeMeshObject->AddComponent(new ChaseComponent);

/*	string models[] =
	{
		"applejack/applejack_eyelashes.obj",
		"applejack/applejack_hair_back_lower.obj",
		"applejack/applejack_hair_back_upper.obj",
		"applejack/applejack_hair_front.obj",
		"applejack/applejack_hairband_hair.obj",
		"applejack/applejack_hairband_tail.obj",
		"applejack/applejack_hat.obj",
		"applejack/applejack_tail_lower.obj",
		"applejack/applejack_tail_upper.obj",
		"pony_body.obj",
		"pony_eyes.obj",
		"pony_teeth_lower.obj",
		"pony_teeth_upper.obj",
		"pony_tongue.obj",
	};

	string textures[] =
	{
		"",
		"applejack/applejack_hair_back_lower.png",
		"applejack/applejack_hair_back_upper.png",
		"applejack/applejack_hair_front.png",
		"applejack/applejack_hairband.png",
		"applejack/applejack_hairband.png",
		"applejack/applejack_hat.png",
		"applejack/applejack_tail_lower.png",
		"applejack/applejack_tail_upper.png",
		"applejack/applejack_body.png",
		"applejack/applejack_eyes.png",
		"",
		"",
		"pony_tongue.png",
	};

	Vector3f colors[] =
	{
		Vector3Template::Zero,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
	};*/

	string models[] =
	{
		"rainbow_dash/rainbow_dash_eyelashes.obj",
		"rainbow_dash/rainbow_dash_hair_back.obj",
		"rainbow_dash/rainbow_dash_hair_front.obj",
		"rainbow_dash/rainbow_dash_tail.obj",
		"pony_wing_folded.obj",
		"pony_body.obj",
		"pony_eyes.obj",
		"pony_teeth_lower.obj",
		"pony_teeth_upper.obj",
		"pony_tongue.obj",
	};

	string textures[] =
	{
		"",
		"rainbow_dash/rainbow_dash_hair_back.png",
		"rainbow_dash/rainbow_dash_hair_front.png",
		"rainbow_dash/rainbow_dash_tail.png",
		"rainbow_dash/rainbow_dash_wings.png",
		"rainbow_dash/rainbow_dash_body.png",
		"rainbow_dash/rainbow_dash_eyes.png",
		"",
		"",
		"pony_tongue.png",
	};

	Vector3f colors[] =
	{
		Vector3Template::Zero,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
		Vector3Template::One,
	};

	GameObject *ponyObject = new GameObject;
	
	for (unsigned int i = 0; i < 10; i++)
	{
		Mesh *ponyMesh = new Mesh(string("models/") + models[i]);

		Material *ponyMaterial = new Material;
		ponyMaterial->AddVector3f("diffuse", colors[i]);
		ponyMaterial->AddFloat("specularIntensity", 0.0f);
		ponyMaterial->AddFloat("specularExponent", 64.0f);

		if (textures[i].length() > 0)
		{
			ponyMaterial->AddTexture("diffuse", Texture(string("texture/") + textures[i], TextureTarget::Texture2D, TextureFilter::Linear));
		}

		ponyObject->AddComponent(new MeshRenderer(ponyMesh, ponyMaterial));
	}

	AddGameObject(ponyObject);
	AddGameObject(fieldMeshObject);
	//GetRootObject()->AddChild(cubeMeshObject);

	GetRootObject()->AddComponent(new FirstPersonController);

	//GetRenderingEngine()->SetClearColor(0.5f, 0.8f, 1.0f);
	//GetRenderingEngine()->SetGlobalAmbientColor(Vector3f(0.4f, 0.4f, 0.4f));

	GetRenderingEngine()->GetMainCamera()->SetPerspectiveProjection(ToRadians(70.0f), (float)GetWindow()->GetWidth() / (float)GetWindow()->GetHeight(), 0.01f, 100.0f);
	GetRenderingEngine()->GetMainCamera()->Move(Vector3f(0, 0, -1), 5);

	for (int i = 0; i < 30; i++)
	{
		PointLight *pointLight = new PointLight;
		pointLight->color = Vector3f(Random::NextFloat(), Random::NextFloat(), Random::NextFloat());
		pointLight->intensity = 3.0f;
		pointLight->position = Vector3f(Random::NextFloat() * 12.0f - 6.0f, -3.9f, Random::NextFloat() * 12.0f - 6.0f);
		pointLight->range = Random::NextFloat() * 5.0f + 5.0f;

		GetRenderingEngine()->AddLight(pointLight);
	}

	m_spotLight = new SpotLight;
	m_spotLight->color = Vector3f(1, 1, 1);
	m_spotLight->intensity = 3.0f;
	m_spotLight->position = GetRenderingEngine()->GetMainCamera()->GetTranslation();
	m_spotLight->direction = GetRenderingEngine()->GetMainCamera()->GetForward();
	m_spotLight->range = 20.0f;
	m_spotLight->cutoff = DegreesToSpotCutoff(35.0f);

	GetRenderingEngine()->AddLight(m_spotLight);
	
	DirectionalLight *directionalLight = new DirectionalLight;
	directionalLight->color = Vector3f(1, 1, 1);
	directionalLight->direction = Vector3f(-1, -1, -1).Normalize();
	directionalLight->intensity = 1.0f;

	//GetRenderingEngine()->AddLight(directionalLight);
}

void TestGame::Deinit()
{
}

void TestGame::Update()
{
	m_spotLight->position = GetRenderingEngine()->GetMainCamera()->GetTranslation();
	m_spotLight->direction = GetRenderingEngine()->GetMainCamera()->GetForward();
}

void TestGame::Render()
{
}