#ifndef _ENCO3D_MATERIAL_H_
#define _ENCO3D_MATERIAL_H_

#include <map>
#include <string>

#include "Vector3.h"
#include "Texture.h"

namespace Enco3D
{
	namespace Rendering
	{
		using namespace Core;

		struct Material
		{
			std::map<std::string, float> floatValues;
			std::map<std::string, Vector3f> vector3fValues;
			std::map<std::string, Texture*> textureValues;

			inline void AddFloat(const std::string &name, float value)
			{
				floatValues.insert(std::pair<std::string, float>(name, value));
			}

			inline void AddVector3f(const std::string &name, const Vector3f &vector)
			{
				vector3fValues.insert(std::pair<std::string, Vector3f>(name, vector));
			}

			inline void AddTexture(const std::string &name, Texture *texture)
			{
				textureValues.insert(std::pair<std::string, Texture*>(name, texture));
			}

			inline void SetFloat(const std::string &name, float value)
			{
				floatValues[name] = value;
			}

			inline void SetVector3f(const std::string &name, const Vector3f &vector)
			{
				vector3fValues[name] = vector;
			}

			inline void SetTexture(const std::string &name, Texture *texture)
			{
				textureValues[name] = texture;
			}

			inline float GetFloat(const std::string &name)
			{
				std::map<std::string, float>::iterator it = floatValues.find(name);
				if (it != floatValues.end())
				{
					return it->second;
				}
				else
				{
					return 0.0f;
				}
			}

			inline Vector3f &GetVector3f(const std::string &name)
			{
				std::map<std::string, Vector3f>::iterator it = vector3fValues.find(name);
				if (it != vector3fValues.end())
				{
					return it->second;
				}
				else
				{
					return Vector3Template::One;
				}
			}

			inline Texture *GetTexture(const std::string &name)
			{
				std::map<std::string, Texture *>::iterator it = textureValues.find(name);
				if (it != textureValues.end())
				{
					return it->second;
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