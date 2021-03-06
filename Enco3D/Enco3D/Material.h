#ifndef _ENCO3D_MATERIAL_H_
#define _ENCO3D_MATERIAL_H_

#include <map>
#include <string>

#include "Vector3.h"
#include "Texture2D.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Rendering
	{
		struct DLL_EXPORT Material
		{
			std::map<std::string, float> floatValues;
			std::map<std::string, Core::Vector3f> vector3fValues;
			std::map<std::string, Texture2D*> texture2dValues;
			std::map<std::string, bool> boolValues;

			Material()
			{
			}

			Material(Texture2D *diffuseTexture)
			{
				addTexture2D("diffuseTexture", diffuseTexture);
				addBool("lightingEnabled", false);
			}

			Material(Texture2D *diffuseTexture, const Core::Vector3f &diffuseColor)
			{
				addTexture2D("diffuseTexture", diffuseTexture);
				addVector3f("diffuseColor", diffuseColor);
				addBool("lightingEnabled", false);
			}

			Material(const Core::Vector3f &diffuseColor)
			{
				addVector3f("diffuseColor", diffuseColor);
				addBool("lightingEnabled", false);
			}

			Material(Texture2D *diffuseTexture, const Core::Vector3f &diffuseColor, float specularIntensity, float specularExponent)
			{
				addTexture2D("diffuseTexture", diffuseTexture);
				addVector3f("diffuseColor", diffuseColor);
				addFloat("specularIntensity", specularIntensity);
				addFloat("specularExponent", specularExponent);
				addBool("lightingEnabled", true);
			}

			Material(const Core::Vector3f &diffuseColor, float specularIntensity, float specularExponent)
			{
				addVector3f("diffuseColor", diffuseColor);
				addFloat("specularIntensity", specularIntensity);
				addFloat("specularExponent", specularExponent);
				addBool("lightingEnabled", true);
			}

			~Material()
			{
				for (std::map<std::string, Texture2D*>::iterator it = texture2dValues.begin(); it != texture2dValues.end(); it++)
					if (it->second)
						delete it->second;
			}

			inline void addFloat(const std::string &name, float value)
			{
				floatValues.insert(std::pair<std::string, float>(name, value));
			}

			inline void addVector3f(const std::string &name, const Core::Vector3f &vector)
			{
				vector3fValues.insert(std::pair<std::string, Core::Vector3f>(name, vector));
			}

			inline void addTexture2D(const std::string &name, Texture2D *texture)
			{
				texture2dValues.insert(std::pair<std::string, Texture2D*>(name, texture));
			}

			inline void addBool(const std::string &name, bool value)
			{
				boolValues.insert(std::pair<std::string, bool>(name, value));
			}

			inline void setFloat(const std::string &name, float value)
			{
				floatValues[name] = value;
			}

			inline void setVector3f(const std::string &name, const Core::Vector3f &vector)
			{
				vector3fValues[name] = vector;
			}

			inline void setTexture2D(const std::string &name, Texture2D *texture)
			{
				texture2dValues[name] = texture;
			}

			inline void setBool(const std::string &name, bool value)
			{
				boolValues[name] = value;
			}

			inline float getFloat(const std::string &name) const
			{
				std::map<std::string, float>::const_iterator it = floatValues.find(name);
				if (it != floatValues.end())
					return it->second;
				else
					return 0.0f;
			}

			inline Core::Vector3f getVector3f(const std::string &name) const
			{
				std::map<std::string, Core::Vector3f>::const_iterator it = vector3fValues.find(name);
				if (it != vector3fValues.end())
					return it->second;
				else
					return Core::Vector3Template::One;
			}

			inline Texture2D *getTexture2D(const std::string &name) const
			{
				std::map<std::string, Texture2D *>::const_iterator it = texture2dValues.find(name);
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

			inline bool getBool(const std::string &name) const
			{
				std::map<std::string, bool>::const_iterator it = boolValues.find(name);
				if (it != boolValues.end())
					return it->second;
				else
					return false;
			}
		};
	}
}

#endif