#include "ImageIO.h"
#include "stb_image.h"

void Enco3D::IO::ImageIO::loadImage(const std::string &filename, __ImageIO_Output *output)
{
	int width, height, bytesPerPixel;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &bytesPerPixel, 4);
	
	int numPixels = (width * height) << 2;
	float *pixels = new float[numPixels];

	float factor = 1.0f / 255.0f;

	for (int i = 0; i < numPixels; i++)
		pixels[i] = data[i] * factor;
	
	output->filename = filename;
	output->width = width;
	output->height = height;
	output->pixels = pixels;

	stbi_image_free(data);
}

void Enco3D::IO::ImageIO::freeImage(__ImageIO_Output *output)
{
	delete[] output->pixels;
}