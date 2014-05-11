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
		enum ShaderType : unsigned int
		{
			VertexShader                 = 0x000001,
			FragmentShader               = 0x000010,
			GeometryShader               = 0x000100,
			TessellationControlShader    = 0x001000,
			TessellationEvaluationShader = 0x010000,
		};

		typedef struct __TypedData
		{
			std::string name;
			std::string type;

		} TypedData;

		typedef struct __UniformStruct
		{
			std::string name;
			std::vector<__TypedData> memberNames;

		} UniformStruct;

		class Shader
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
			void AddProgram(const string &text, int type);
			string LoadShader(const string &filename);
			void CheckShaderError(int shader, int flag, bool isProgram, const string &errorMsg);
			
			std::vector<__UniformStruct> FindUniformStructs(const std::string &shaderText);
			std::string FindUniformStructName(const std::string &structStartToOpeningBrace);
			std::vector<__TypedData> FindUniformStructComponents(const std::string &openingBraceToClosingBrace);

			void AddAllAttributes(const std::string &vertexShaderText);
			void AddShaderUniforms(const std::string &shaderText);
			void AddUniform(const std::string &uniformName, const std::string &uniformType, const std::vector<__UniformStruct>& structs);

		public:
			Shader();
			Shader(const string &filename, unsigned int shaderTypes);
			Shader(const string &vertexFilename, const string &fragmentFilename);
			virtual ~Shader();

			void Bind() const;

			void AddVertexShader(const string &text);
			void AddFragmentShader(const string &text);
			void AddGeometryShader(const string &text);
			void AddTessellationControlShader(const string &text);
			void AddTessellationEvaluationShader(const string &text);

			void AddVertexShaderFromFile(const string &filename);
			void AddFragmentShaderFromFile(const string &filename);
			void AddGeometryShaderFromFile(const string &filename);
			void AddTessellationControlShaderFromFile(const string &filename);
			void AddTessellationEvaluationShaderFromFile(const string &filename);

			void CompileShader();

			void SetAttribLocation(const string &attributeName, int location);
			void SetUniformInt(const string &name, int value);
			void SetUniformFloat(const string &name, float value);

			void SetUniformVector2f(const string &name, const Core::Vector2f &v);
			void SetUniformVector3f(const string &name, const Core::Vector3f &v);
			void SetUniformVector4f(const string &name, const Core::Vector4f &v);

			void SetUniformMatrix3x3f(const string &name, const Core::Matrix3x3f &v);
			void SetUniformMatrix4x4f(const string &name, const Core::Matrix4x4f &v);

			void SetUniformDirectionalLight(const string &name, const Component::DirectionalLight *directionalLight);
			void SetUniformPointLight(const string &name, const Component::PointLight *pointLight);
			void SetUniformSpotLight(const string &name, const Component::SpotLight *spotLight);

			void UpdateUniforms(Core::Transform *transform, const Component::Camera *camera, RenderingEngine *renderingEngine, Material *material);
		};
	}
}

#endif