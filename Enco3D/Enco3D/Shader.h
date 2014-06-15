#ifndef _ENCO3D_SHADER_H_
#define _ENCO3D_SHADER_H_

#include <GL\glew.h>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Material.h"
#include "RenderingEngine.h"
#include "Camera.h"
#include "Transform.h"
#include "DebugLogger.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Component
	{
		class DirectionalLight;
		class PointLight;
		class SpotLight;
	}
}

namespace Enco3D
{
	namespace Rendering
	{
		enum DLL_EXPORT ShaderType : unsigned int
		{
			VertexShader = 0x000001,
			FragmentShader = 0x000010,
			GeometryShader = 0x000100,
			TessellationControlShader = 0x001000,
			TessellationEvaluationShader = 0x010000,
		};

		typedef struct DLL_EXPORT __TypedData
		{
			std::string name;
			std::string type;
		} TypedData;

		typedef struct DLL_EXPORT __UniformStruct
		{
			std::string name;
			std::vector<__TypedData> memberNames;
		} UniformStruct;

		class DLL_EXPORT Shader
		{
		private:
			GLuint m_program;
			std::vector<int> m_shaders;
			std::vector<std::string> m_uniformNames;
			std::vector<std::string> m_uniformTypes;
			std::map<std::string, unsigned int> m_uniformMap;

		private:
			static const Shader *s_lastBind;

		private:
			void addProgram(const std::string &text, int type);
			std::string loadShader(const std::string &filename);
			void checkShaderError(int shader, int flag, bool isProgram, const std::string &errorMsg);

			std::vector<__UniformStruct> findUniformStructs(const std::string &shaderText);
			std::string findUniformStructName(const std::string &structStartToOpeningBrace);
			std::vector<__TypedData> findUniformStructComponents(const std::string &openingBraceToClosingBrace);

			void addAllAttributes(const std::string &vertexShaderText);
			void addShaderUniforms(const std::string &shaderText);
			void addUniform(const std::string &uniformName, const std::string &uniformType, const std::vector<__UniformStruct>& structs);

		public:
			Shader();
			Shader(const std::string &filename, unsigned int shaderTypes);
			Shader(const std::string &vertexFilename, const std::string &fragmentFilename);
			virtual ~Shader();

			void bind() const;

			void addVertexShader(const std::string &text);
			void addFragmentShader(const std::string &text);
			void addGeometryShader(const std::string &text);
			void addTessellationControlShader(const std::string &text);
			void addTessellationEvaluationShader(const std::string &text);

			void addVertexShaderFromFile(const std::string &filename);
			void addFragmentShaderFromFile(const std::string &filename);
			void addGeometryShaderFromFile(const std::string &filename);
			void addTessellationControlShaderFromFile(const std::string &filename);
			void addTessellationEvaluationShaderFromFile(const std::string &filename);

			void compileShader();

			void setAttribLocation(const std::string &attributeName, int location);
			void setUniformInt(const std::string &name, int value);
			void setUniformFloat(const std::string &name, float value);

			void setUniformVector2f(const std::string &name, const Core::Vector2f &v);
			void setUniformVector3f(const std::string &name, const Core::Vector3f &v);
			void setUniformVector4f(const std::string &name, const Core::Vector4f &v);

			void setUniformMatrix3x3f(const std::string &name, const Core::Matrix3x3f &v);
			void setUniformMatrix4x4f(const std::string &name, const Core::Matrix4x4f &v);

			void setUniformDirectionalLight(const std::string &name, const Component::DirectionalLight *directionalLight);
			void setUniformPointLight(const std::string &name, const Component::PointLight *pointLight);
			void setUniformSpotLight(const std::string &name, const Component::SpotLight *spotLight);

			void updateUniforms(Core::Transform *transform, const Component::Camera *camera, RenderingEngine *renderingEngine, const Material &material);
		};
	}
}

#endif