#ifndef __TEXTUREBUILDER_H_INCLUDED__
#define __TEXTUREBUILDER_H_INCLUDED__

#include <Enco3D\Enco3D.h>
#include <string>

using namespace Enco3D::IO;
using namespace Enco3D::Rendering;

class TextureBuilder
{
public:
	Texture2D *buildTexture2D(std::string *textureFilenames, int numTextureFilenames, int texturesPerRow, int texturesPerColumn, int tileWidth, int tileHeight)
	{
		int globalWidth = texturesPerRow * tileWidth;
		int globalHeight = texturesPerColumn * tileHeight;

		float *globalPixels = new float[globalWidth * globalHeight * 4];

		for (int i = 0; i < numTextureFilenames; i++)
		{
			int tileX = i % texturesPerRow;
			int tileY = i / texturesPerRow;

			ImageIO_Output texture;
			ImageIO::loadImage(textureFilenames[i], &texture);

			int pixelStartX = tileX * tileWidth;
			int pixelStartY = tileY * tileHeight;

			int pixelEndX = pixelStartX + tileWidth;
			int pixelEndY = pixelStartY + tileHeight;

			for (int x = pixelStartX; x < pixelEndX; x++)
			{
				for (int y = pixelStartY; y < pixelEndY; y++)
				{
					int globalPixelIndex = (x + y * globalWidth) << 2;
					int texturePixelIndex = ((x - pixelStartX) + (y - pixelStartY) * tileWidth) << 2;

					globalPixels[globalPixelIndex + 0] = texture.pixels[texturePixelIndex + 0];
					globalPixels[globalPixelIndex + 1] = texture.pixels[texturePixelIndex + 1];
					globalPixels[globalPixelIndex + 2] = texture.pixels[texturePixelIndex + 2];
					globalPixels[globalPixelIndex + 3] = texture.pixels[texturePixelIndex + 3];
				}
			}

			ImageIO::freeImage(&texture);
		}

		return new Texture2D(globalWidth, globalHeight, GL_RGBA, GL_RGBA, TextureFilter::Nearest, TextureWrap::Clamp, globalPixels);
	}
};

#endif