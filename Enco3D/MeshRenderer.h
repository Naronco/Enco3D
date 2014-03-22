#ifndef _ENCO3D_MESHRENDERER_H_
#define _ENCO3D_MESHRENDERER_H_

#include "IGameComponent.h"
#include "Mesh.h"
#include "Material.h"
#include "LightGlobalAmbientShader.h"

class MeshRenderer : public IGameComponent
{
private:
	Mesh *m_mesh{ nullptr };
	Material *m_material{ nullptr };

public:
	MeshRenderer();
	MeshRenderer(Mesh *mesh, Material *material);

	void Render(Shader *shader);
};

#endif