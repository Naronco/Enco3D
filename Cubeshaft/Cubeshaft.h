#ifndef __CUBESHAFT_H_INCLUDED__
#define __CUBESHAFT_H_INCLUDED__

#include <Enco3D\Enco3D.h>
#include "TextureBuilder.h"

using namespace Enco3D::Core;
using namespace Enco3D::Component;
using namespace Enco3D::Rendering;

class Cubeshaft : public IGame
{
public:
	void init()
	{
		Camera *mainCamera = getRenderingEngine()->createPerspectiveCamera(MathUtil::toRadians(70.0f), 0.01f, 100.0f);

		GameObject *mainCameraObject = createGameObject("mainCamera");
		mainCameraObject->addComponent(mainCamera);
		mainCameraObject->addComponent(new FreeLook);
		mainCameraObject->addComponent(new FreeMove);
		addGameObject(mainCameraObject);

		float tx0 = 0.0f;
		float ty0 = 0.0f;
		float tx1 = 1.0f;
		float ty1 = 1.0f;

		Vertex vertices[] =
		{
			Vertex(+1, -1, +1).setTexCoord(tx1, ty1).setNormal(0, -1, 0),
			Vertex(-1, -1, +1).setTexCoord(tx0, ty1).setNormal(0, -1, 0),
			Vertex(-1, -1, -1).setTexCoord(tx0, ty0).setNormal(0, -1, 0),
			Vertex(+1, -1, -1).setTexCoord(tx1, ty0).setNormal(0, -1, 0),

			Vertex(-1, +1, +1).setTexCoord(tx1, ty1).setNormal(0, 1, 0),
			Vertex(+1, +1, +1).setTexCoord(tx0, ty1).setNormal(0, 1, 0),
			Vertex(+1, +1, -1).setTexCoord(tx0, ty0).setNormal(0, 1, 0),
			Vertex(-1, +1, -1).setTexCoord(tx1, ty0).setNormal(0, 1, 0),

			Vertex(-1, -1, +1).setTexCoord(tx1, ty1).setNormal(0, 0, 1),
			Vertex(+1, -1, +1).setTexCoord(tx0, ty1).setNormal(0, 0, 1),
			Vertex(+1, +1, +1).setTexCoord(tx0, ty0).setNormal(0, 0, 1),
			Vertex(-1, +1, +1).setTexCoord(tx1, ty0).setNormal(0, 0, 1),

			Vertex(+1, -1, -1).setTexCoord(tx1, ty1).setNormal(0, 0, -1),
			Vertex(-1, -1, -1).setTexCoord(tx0, ty1).setNormal(0, 0, -1),
			Vertex(-1, +1, -1).setTexCoord(tx0, ty0).setNormal(0, 0, -1),
			Vertex(+1, +1, -1).setTexCoord(tx1, ty0).setNormal(0, 0, -1),

			Vertex(+1, +1, +1).setTexCoord(tx1, ty0).setNormal(-1, 0, 0),
			Vertex(+1, -1, +1).setTexCoord(tx1, ty1).setNormal(-1, 0, 0),
			Vertex(+1, -1, -1).setTexCoord(tx0, ty1).setNormal(-1, 0, 0),
			Vertex(+1, +1, -1).setTexCoord(tx0, ty0).setNormal(-1, 0, 0),

			Vertex(-1, +1, -1).setTexCoord(tx1, ty0).setNormal(1, 0, 0),
			Vertex(-1, -1, -1).setTexCoord(tx1, ty1).setNormal(1, 0, 0),
			Vertex(-1, -1, +1).setTexCoord(tx0, ty1).setNormal(1, 0, 0),
			Vertex(-1, +1, +1).setTexCoord(tx0, ty0).setNormal(1, 0, 0),
		};

		unsigned int indices[36] =
		{
			0, 1, 2, 0, 2, 3,
			4, 5, 6, 4, 6, 7,
			8, 9, 10, 8, 10, 11,
			12, 13, 14, 12, 14, 15,
			16, 17, 18, 16, 18, 19,
			20, 21, 22, 20, 22, 23,
		};

		std::string neededTextures[] =
		{
			"texture/terrain/block/dirt.png",
			"texture/terrain/block/grass.png",
			"texture/terrain/block/sand.png",
			"texture/terrain/block/stone.png",
		};

		Texture2D *terrainTexture = TextureBuilder().buildTexture2D(neededTextures, 4, 2, 2, 16, 16);
		//		Texture2D *terrainTexture = new Texture2D("texture/terrain/block/___.png");

		Mesh *blockMesh = new Mesh(vertices, 24, indices, 36);
		Material *blockMaterial = new Material(terrainTexture);

		{
			GameObject *blockObject = createGameObject("block");
			blockObject->addComponent(new DefaultMesh(blockMesh, blockMaterial));
			addGameObject(blockObject);
		}
		{
			GameObject *blockObject = createGameObject("block");
			blockObject->addComponent(new DefaultMesh(blockMesh, blockMaterial));
			blockObject->getTransform()->translate(Vector3f(2, 0, 0));
			addGameObject(blockObject);
		}

		getRenderingEngine()->setClearColor(0.5f, 0.8f, 1.0f);
		getRenderingEngine()->setGlobalAmbientColor(0.11f, 0.18f, 0.22f);

		Matrix4x4f rotationMatrix;
		rotationMatrix.setOrthographicProjection(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 1.0f);

		Matrix4x4f invRot = rotationMatrix.getInverse();
		(rotationMatrix * invRot).print();
	}
};

#endif