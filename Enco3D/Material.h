#ifndef _ENCO3D_MATERIAL_H_
#define _ENCO3D_MATERIAL_H_

#include <map>

#include "Vector3.h"
#include "Texture.h"

using namespace std;

namespace Enco3D
{
	namespace Rendering
	{
		using namespace Core;

		struct Material
		{
			map<char *, float> floatValues;
			map<char *, Vector3f> vector3fValues;
			map<char *, Texture *> textureValues;

			inline void AddFloat(char *name, float value)
			{
				floatValues.insert(pair<char *, float>(name, value));
			}

			inline void AddVector3f(char *name, const Vector3f &vector)
			{
				vector3fValues.insert(pair<char *, Vector3f>(name, vector));
			}

			inline void AddTexture(char *name, Texture *texture)
			{
				textureValues.insert(pair<char *, Texture *>(name, texture));
			}

			inline void SetFloat(char *name, float value)
			{
				floatValues[name] = value;
			}

			inline void SetVector3f(char *name, const Vector3f &vector)
			{
				vector3fValues[name] = vector;
			}

			inline void SetTexture(char *name, Texture *texture)
			{
				textureValues[name] = texture;
			}

			inline float GetFloat(char *name)
			{
				map<char *, float>::iterator it = floatValues.find(name);
				if (it != floatValues.end())
				{
					return floatValues.at(name);
				}
				else
				{
					return 0.0f;
				}
			}

			inline Vector3f &GetVector3f(char *name)
			{
				map<char *, Vector3f>::iterator it = vector3fValues.find(name);
				if (it != vector3fValues.end())
				{
					return vector3fValues.at(name);
				}
				else
				{
					return Vector3Template::One;
				}
			}

			inline Texture *GetTexture(char *name)
			{
				map<char *, Texture *>::iterator it = textureValues.find(name);
				if (it != textureValues.end())
				{
					return textureValues.at(name);
				}
				else
				{
					return Texture::GetBlankTexture();
				}
			}
		};
	}
}

#endif