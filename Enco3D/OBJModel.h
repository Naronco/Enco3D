#ifndef _ENCO3D_OBJMODEL_H_
#define _ENCO3D_OBJMODEL_H_

#include "Vector2.h"
#include "Vector3.h"
#include "IndexedModel.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

struct OBJIndex
{
	unsigned int vertexIndex, texCoordIndex, normalIndex;

	inline OBJIndex(unsigned int _vertexIndex = 0, unsigned int _texCoordIndex = 0, unsigned int _normalIndex = 0) : vertexIndex(_vertexIndex), texCoordIndex(_texCoordIndex), normalIndex(_normalIndex) {  }
	inline OBJIndex(const OBJIndex &i) : vertexIndex(i.vertexIndex), texCoordIndex(i.texCoordIndex), normalIndex(i.normalIndex) {  }

	inline bool operator <  (const OBJIndex &i) const { return vertexIndex <  i.vertexIndex; }
	inline bool operator <= (const OBJIndex &i) const { return vertexIndex <= i.vertexIndex; }
	inline bool operator >  (const OBJIndex &i) const { return vertexIndex >  i.vertexIndex; }
	inline bool operator >= (const OBJIndex &i) const { return vertexIndex >= i.vertexIndex; }
};

class OBJModel
{
private:
	vector<Vector3f> m_positions;
	vector<Vector2f> m_texCoords;
	vector<Vector3f> m_normals;
	vector<OBJIndex> m_indices;
	bool m_hasTexCoords{ false };
	bool m_hasNormals{ false };

private:
	unsigned int FindLastVertexIndex(const vector<OBJIndex *> &indexLookUp, const OBJIndex *currentIndex, const IndexedModel &result) const;
	void CreateOBJFace(const string &line);

public:
	OBJModel();
	OBJModel(const string &filename);

	IndexedModel ToIndexedModel();

	inline void AddPosition(const Vector3f &position) { m_positions.push_back(position); }
	inline void AddTexCoord(const Vector2f &texCoord) { m_texCoords.push_back(texCoord); }
	inline void AddNormal(const Vector3f &normal) { m_normals.push_back(normal); }
	inline void AddOBJIndex(const OBJIndex &index) { m_indices.push_back(index); }

	inline vector<Vector3f> GetPositions() const { return m_positions; }
	inline vector<Vector2f> GetTexCoords() const { return m_texCoords; }
	inline vector<Vector3f> GetNormals() const { return m_normals; }
	inline vector<OBJIndex> GetIndices() const { return m_indices; }
	inline bool HasTexCoords() const { return m_hasTexCoords; }
	inline bool HasNormals() const { return m_hasNormals; }
};

#endif