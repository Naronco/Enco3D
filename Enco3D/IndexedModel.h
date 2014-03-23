#ifndef _ENCO3D_INDEXEDMODEL_H_
#define _ENCO3D_INDEXEDMODEL_H_

#include "Vector2.h"
#include "Vector3.h"

#include <vector>

using namespace std;

namespace Enco3D
{
	namespace Rendering
	{
		using namespace Core;

		class IndexedModel
		{
		private:
			vector<Vector3f> m_positions;
			vector<Vector2f> m_texCoords;
			vector<Vector3f> m_normals;
			vector<unsigned int> m_indices;

		public:
			IndexedModel();

			void CalcNormals();

			inline void AddPosition(const Vector3f &position) { m_positions.push_back(position); }
			inline void AddTexCoord(const Vector2f &texCoord) { m_texCoords.push_back(texCoord); }
			inline void AddNormal(const Vector3f &normal) { m_normals.push_back(normal); }
			inline void AddIndex(unsigned int index) { m_indices.push_back(index); }

			inline vector<Vector3f> GetPositions() const { return m_positions; }
			inline vector<Vector2f> GetTexCoords() const { return m_texCoords; }
			inline vector<Vector3f> GetNormals() const { return m_normals; }
			inline vector<unsigned int> GetIndices() const { return m_indices; }
		};
	}
}

#endif