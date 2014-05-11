#include "ShaderPool.h"

Enco3D::Rendering::Shader *Enco3D::Rendering::ShaderPool::GetShader(const std::string &filename, unsigned int shaderTypes)
{
	std::map<std::string, Shader*>::iterator it = m_loadedShaders.find(filename);
	if (it != m_loadedShaders.end())
	{
		return it->second;
	}
	else
	{
		Shader *shader = new Shader(filename, shaderTypes);
		m_loadedShaders.insert(std::pair<std::string, Shader*>(filename, shader));

		return shader;
	}
}

void Enco3D::Rendering::ShaderPool::Release()
{
	for (std::map<std::string, Shader*>::iterator it = m_loadedShaders.begin(); it != m_loadedShaders.end(); it++)
		delete it->second;
}