#ifndef __DSALGO_H_INCLUDED__
#define __DSALGO_H_INCLUDED__

#include <Enco3D\Enco3D.h>

using namespace Enco3D::Core;
using namespace Enco3D::Component;
using namespace Enco3D::Rendering;
using namespace Enco3D::Physics;
using namespace Enco3D::IO;

class DiamondSquare : public IGame
{
public:
	double values[256 * 256];
	int width{ 256 };
	int height{ 256 };

	double sample(int x, int y)
	{
		return values[(x & (width - 1)) + (y & (height - 1)) * width];
	}

	void setSample(int x, int y, double value)
	{
		values[(x & (width - 1)) + (y & (height - 1)) * width] = value;
	}

	double frand()
	{
		return Random::NextDouble() * 2 - 1;
	}

	void sampleSquare(int x, int y, int size, double value)
	{
		int hs = size / 2;

		// a     b
		//
		//    x
		//
		// c     d

		double a = sample(x - hs, y - hs);
		double b = sample(x + hs, y - hs);
		double c = sample(x - hs, y + hs);
		double d = sample(x + hs, y + hs);

		setSample(x, y, ((a + b + c + d) / 4.0) + value);
	}

	void sampleDiamond(int x, int y, int size, double value)
	{
		int hs = size / 2;

		//    c
		//
		// a  x  b
		//
		//    d

		double a = sample(x - hs, y);
		double b = sample(x + hs, y);
		double c = sample(x, y - hs);
		double d = sample(x, y + hs);

		setSample(x, y, ((a + b + c + d) / 4.0) + value);
	}

	void diamondSquare(int stepsize, double scale)
	{
		int halfstep = stepsize / 2;

		for (int y = halfstep; y < height + halfstep; y += stepsize)
		{
			for (int x = halfstep; x < width + halfstep; x += stepsize)
			{
				sampleSquare(x, y, stepsize, frand() * scale);
			}
		}

		for (int y = 0; y < height; y += stepsize)
		{
			for (int x = 0; x < width; x += stepsize)
			{
				sampleDiamond(x + halfstep, y, stepsize, frand() * scale);
				sampleDiamond(x, y + halfstep, stepsize, frand() * scale);
			}
		}
	}

	Vector3f calcNormal(Vector3f a, Vector3f b, Vector3f c)
	{
		Vector3f u = b - a;
		Vector3f v = c - a;

		return u.cross(v).normalize();
	}

	void init()
	{
		Camera *mainCamera = getRenderingEngine()->createPerspectiveCamera(MathUtil::toRadians(70.0f), 0.01f, 100.0f);

		GameObject *mainCameraObject = createGameObject("mainCamera");
		mainCameraObject->addComponent(mainCamera);
		mainCameraObject->addComponent(new FreeLook);
		mainCameraObject->addComponent(new FreeMove);
		addGameObject(mainCameraObject);

		GameObject *heightmap = createGameObject("heightmap");

		int featuresize = 32;

		int samplesize = 128;

		for (int y = 0; y < height; y += featuresize)
			for (int x = 0; x < width; x += featuresize)
			{
			setSample(x, y, frand());
			}

		double scale = 2.0;

		while (samplesize > 1)
		{
			diamondSquare(samplesize, scale);

			samplesize >>= 1;
			scale *= 0.5;
		}
		std::vector<Vertex> vertices;

		double minV = 1;
		double maxV = 0;

		for (int x = 0; x < width - 1; x++)
		{
			for (int y = 0; y < height - 1; y++)
			{
				double height00 = values[x + y * width];
				double height10 = values[x + 1 + y * width];
				double height11 = values[x + 1 + (y + 1) * width];
				double height01 = values[x + (y + 1) * width];

				minV = min(minV, min(height00, min(height10, min(height11, height10))));
				maxV = max(minV, max(height00, max(height10, max(height11, height10))));

				float xscale = 0.1f;
				float yscale = 0.1f;

				Vector3f a = Vector3f(x * xscale, height00, y * yscale);
				Vector3f b = Vector3f(x * xscale + xscale, height10, y * yscale);
				Vector3f c = Vector3f(x * xscale + xscale, height11, y * yscale + yscale);
				Vector3f d = Vector3f(x * xscale, height01, y * yscale + yscale);

				Vector3f n1 = calcNormal(c, b, a);
				Vector3f n2 = calcNormal(d, c, a);

				vertices.push_back(Vertex(c).setNormal(n1));
				vertices.push_back(Vertex(b).setNormal(n1));
				vertices.push_back(Vertex(a).setNormal(n1));

				vertices.push_back(Vertex(d).setNormal(n2));
				vertices.push_back(Vertex(c).setNormal(n2));
				vertices.push_back(Vertex(a).setNormal(n2));
			}
		}

		std::cout << "Min Value: " << (round(minV * 100) / 100) << ", Max Value: " << (round(maxV * 100) / 100) << std::endl;

		float *texValues = new float[width * height * 4];

		minV = abs(minV);

		for (int i = 0; i < width * height * 4; i += 4)
		{
			double val = (minV + values[i / 4]) / (minV + maxV);
			texValues[i] = (float)val;
			texValues[i + 1] = (float)val;
			texValues[i + 2] = (float)val;
			texValues[i + 3] = 1;
		}

		Texture2D* texture = new Texture2D(width, height, GL_RGBA, GL_RGBA, TextureFilter::Linear, TextureWrap::Repeat, texValues);
		GUITexture* guiTex = new GUITexture(texture);
		GameObject* heightmapPreview = createGameObject("Heightmap Preview");
		heightmapPreview->addComponent(guiTex);
		heightmapPreview->getTransform()->scale(128.0f, 128.0f, 1.0f);
		heightmapPreview->getTransform()->translate(64 + 16, 64 + 16, 0);
		addGameObject(heightmapPreview);

		Mesh* heightmesh = new Mesh(&vertices[0], vertices.size());
		Material* mat = new Material(new Texture2D(1, 1, GL_RGB, GL_RGB, TextureFilter::Linear, TextureWrap::Clamp, new float[] { 1, 1, 1 }));
		heightmap->addComponent(new DefaultMesh(heightmesh, mat));
		addGameObject(heightmap);

		GameObject *sun = createGameObject("sun");
		DirectionalLight* sunlight = new DirectionalLight(1, 1, 1, 2);
		sun->addComponent(sunlight);
		sun->getTransform()->setRotation(Quaternionf(0.16306f, -0.90604f, 0.073881f, 0.89615f));
		addGameObject(sun);

		getRenderingEngine()->setGlobalAmbientColor(0.3f, 0.3f, 0.3f);
		getRenderingEngine()->setRasterizationMode(RasterizationMode::Solid);
	}

	void deinit()
	{
	}
};

#endif