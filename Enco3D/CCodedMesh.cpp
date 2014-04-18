#include "CCodedMesh.h"

void enco::core::CCodedMesh::create(uint32 vertexSizeInBytes, void *vertexData, sint32 vertexComponents, uint32 indexSizeInBytes, void *indexData, uint32 indexCount)
{
	m_vertexBuffer = m_graphicsDevice->buildVertexBuffer(vertexSizeInBytes, vertexData, vertexComponents);
	m_indexBuffer = m_graphicsDevice->buildIndexBuffer(indexSizeInBytes, indexData, indexCount);
}

void enco::core::CCodedMesh::release()
{
	m_graphicsDevice->releaseIndexBuffer(m_indexBuffer);
	m_graphicsDevice->releaseVertexBuffer(m_vertexBuffer);
}