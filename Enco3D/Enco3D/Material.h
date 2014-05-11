#ifndef _ENCO3D_MATERIAL_H_
#define _ENCO3D_MATERIAL_H_

#include <map>
#include <string>

#include "Vector3.h"
#include "Texture2D.h"

namespace Enco3D
{
	namespace Rendering
	{
		struct Material
		{
			std::map<std::string, float> floatValues;
			std::map<std::string, Core::Vector3f> vector3fValues;
			std::map<std::string, Texture2D*> texture2dValues;

			~Material() {
				for (std::map<std::string, Texture2D*>::iterator it = texture2dValues.begin(); it != texture2dValues.end(); it++) {
					if (it->second) delete it->second;
				}
			}

			inline void AddFloat(const std::string &name, float value)
			{
				floatValues.insert(std::pair<std::string, float>(name, value));
			}

			inline void AddVector3f(const std::string &name, const Core::Vector3f &vector)
			{
				vector3fValues.insert(std::pair<std::string, Core::Vector3f>(name, vector));
			}

			inline void AddTexture2D(const std::string &name, Texture2D *texture)
			{
				texture2dValues.insert(std::pair<std::string, Texture2D*>(name, texture));
			}

			inline void SetFloat(const std::string &name, float value)
			{
				floatValues[name] = value;
			}

			inline void SetVector3f(const std::string &name, const Core::Vector3f &vector)
			{
				vector3fValues[name] = vector;
			}

			inline void SetTexture2D(const std::string &name, Texture2D *texture)
			{
				texture2dValues[name] = texture;
			}

			inline float GetFloat(const std::string &name)
			{
				std::map<std::string, float>::iterator it = floatValues.find(name);
				if (it != floatValues.end())
					return it->second;
				else
					return 0.0f;
			}

			inline Core::Vector3f GetVector3f(const std::string &name)
			{
				std::map<std::string, Core::Vector3f>::iterator it = vector3fValues.find(name);
				if (it != vector3fValues.end())
					return it->second;
				else
					return Core::Vector3Template::One;
			}

			inline Texture2D *GetTexture2D(const std::string &name)
			{
				std::map<std::string, Texture2D *>::iterator it = texture2dValues.find(name);
				if (it != texture2dValues.end())
					return it->second;
				else
				{
					static Texture2D *blankTexture = nullptr;

					if (blankTexture == nullptr)
					{
						float values[16] = { 1.0f, 0.0f, 1.0f, 1.0f,
											 0.0f, 0.0f, 0.0f, 1.0f, 
											 0.0f, 0.0f, 0.0f, 1.0f, 
											 1.0f, 0.0f, 1.0f, 1.0f, };
						blankTexture = new Texture2D(2, 2, GL_RGBA, GL_RGBA, GL_NEAREST, GL_REPEAT, values);
					}

					return blankTexture;
				}
			}
		};
	}
}

#endif