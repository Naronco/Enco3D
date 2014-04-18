#include "CCodedMeshSceneNode.h"

void enco::core::CCodedMeshSceneNode::create(IGraphicsDevice *graphicsDevice)
{
	clearMaterialFlags();
	clearMaterialTextures();
	clearMaterialColors();
	clearMaterialFloats();

	clearPhysicsFlags();
	clearPhysicsFloats();

	m_graphicsDevice = graphicsDevice;

	m_transform = new CTransform<float32>;
}

void enco::core::CCodedMeshSceneNode::release()
{
	releaseMaterialTextures();
	
	__SAFEDELETE(m_transform);
}

void enco::core::CCodedMeshSceneNode::render()
{
	__ASSERT(m_codedMesh != 0);
	m_codedMesh->render();
}