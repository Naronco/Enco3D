#ifndef _ENCO3D_SHADERPOOL_H_
#define _ENCO3D_SHADERPOOL_H_

#include "TSingleton.h"
#include "Shader.h"
#include "DLLExport.h"

#include <map>
#include <string>

namespace Enco3D
{
	namespace Rendering
	{
		class ShaderPool : public TSingleton < ShaderPool >
		{
		private:
			std::map<std::string, Shader*> m_loadedShaders;

		public:
			Shader *getShader(const std::string &filename, unsigned int shaderTypes);
			void release();
		};
	}
}

#endif