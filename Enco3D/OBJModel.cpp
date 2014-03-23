#include "OBJModel.h"

inline static bool CompareOBJIndexPtr(const Enco3D::Rendering::OBJIndex *a, const Enco3D::Rendering::OBJIndex *b);
inline static unsigned int FindNextChar(unsigned int start, const char *str, unsigned int length, char token);
inline static unsigned int ParseOBJIndexValue(const string &token, unsigned int start, unsigned int end);
inline static float ParseOBJFloatValue(const string &token, unsigned int start, unsigned int end);
inline static vector<string> SplitString(const string &s, char delim);

inline static Enco3D::Core::Vector2f ParseOBJVec2(const string &line);
inline static Enco3D::Core::Vector3f ParseOBJVec3(const string &line);
inline static Enco3D::Rendering::OBJIndex ParseOBJIndex(const string &token, bool *hasTexCoords, bool *hasNormals);

Enco3D::Rendering::OBJModel::OBJModel()
{
}

Enco3D::Rendering::OBJModel::OBJModel(const string &filename)
{
	m_hasTexCoords = false;
	m_hasNormals = false;

	ifstream file;
	file.open(filename.c_str());

	string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);

			if (line.length() < 2)
			{
				continue;
			}

			const char *lineCStr = line.c_str();

			switch (lineCStr[0])
			{
			case 'v':
				if (lineCStr[1] == 't')
				{
					AddTexCoord(ParseOBJVec2(line));
				}
				else if (lineCStr[1] == 'n')
				{
					AddNormal(ParseOBJVec3(line));
				}
				else if (lineCStr[1] == ' ' || lineCStr[1] == '\t')
				{
					AddPosition(ParseOBJVec3(line));
				}
				break;

			case 'f':
				CreateOBJFace(line);
				break;

			default:
				break;
			}
		}

		cout << "Successfully loaded OBJ model " << filename << " with " << m_indices.size() << " vertices" << endl;
	}
	else
	{
		cerr << "[ERROR] Failed to load mesh: " << filename << endl;
		return;
	}
}

Enco3D::Rendering::IndexedModel Enco3D::Rendering::OBJModel::ToIndexedModel()
{
	IndexedModel result, normalModel;
	vector<OBJIndex *> indexLookup;

	for (unsigned int i = 0; i < m_indices.size(); i++)
	{
		indexLookup.push_back(&m_indices[i]);
	}

	sort(indexLookup.begin(), indexLookup.end(), CompareOBJIndexPtr);

	map<OBJIndex, unsigned int> normalModelIndexMap;
	map<unsigned int, unsigned int> indexMap;

	for (unsigned int i = 0; i < m_indices.size(); i++)
	{
		OBJIndex *currentIndex = &m_indices[i];

		Vector3f currentPosition = m_positions[currentIndex->vertexIndex];
		Vector2f currentTexCoord;
		Vector3f currentNormal;

		if (m_hasTexCoords)
		{
			currentTexCoord = m_texCoords[currentIndex->texCoordIndex];
		}
		else
		{
			currentTexCoord.Set(0, 0);
		}

		if (m_hasNormals)
		{
			currentNormal = m_normals[currentIndex->normalIndex];
		}
		else
		{
			currentNormal.Set(0, 0, 0);
		}

		unsigned int normalModelIndex, resultModelIndex;

		map<OBJIndex, unsigned int>::iterator it = normalModelIndexMap.find(*currentIndex);
		if (it == normalModelIndexMap.end())
		{
			normalModelIndex = (unsigned int)normalModel.GetPositions().size();

			normalModelIndexMap.insert(pair<OBJIndex, unsigned int>(*currentIndex, normalModelIndex));
			normalModel.AddPosition(currentPosition);
			normalModel.AddTexCoord(currentTexCoord);
			normalModel.AddNormal(currentNormal);
		}
		else
		{
			normalModelIndex = it->second;
		}

		unsigned int previousVertexLocation = FindLastVertexIndex(indexLookup, currentIndex, result);

		if (previousVertexLocation == (unsigned int)-1)
		{
			resultModelIndex = (unsigned int)result.GetPositions().size();

			result.AddPosition(currentPosition);
			result.AddTexCoord(currentTexCoord);
			result.AddNormal(currentNormal);
		}
		else
		{
			resultModelIndex = previousVertexLocation;
		}

		normalModel.AddIndex(normalModelIndex);
		result.AddIndex(resultModelIndex);
		indexMap.insert(pair<unsigned int, unsigned int>(resultModelIndex, normalModelIndex));
	}

	if (!m_hasNormals)
	{
		normalModel.CalcNormals();

		for (unsigned int i = 0; i < result.GetPositions().size(); i++)
		{
			result.GetNormals()[i] = normalModel.GetNormals()[indexMap[i]];
		}
	}

	return result;
}

unsigned int Enco3D::Rendering::OBJModel::FindLastVertexIndex(const vector<OBJIndex *> &indexLookup, const OBJIndex *currentIndex, const IndexedModel &result) const
{
	unsigned int start = 0;
	unsigned int end = (unsigned int)indexLookup.size();
	unsigned int current = ((end - start) >> 1) + start;
	unsigned int previous = start;

	while (current != previous)
	{
		OBJIndex *testIndex = indexLookup[current];

		if (testIndex->vertexIndex == currentIndex->vertexIndex)
		{
			unsigned int countStart = current;

			for (unsigned int i = 0; i < current; i++)
			{
				OBJIndex *possibleIndex = indexLookup[current - i];
				
				if (possibleIndex == currentIndex)
				{
					continue;
				}

				if (possibleIndex->vertexIndex != currentIndex->vertexIndex)
				{
					break;
				}

				countStart--;
			}

			for (unsigned int i = countStart; i < indexLookup.size() - countStart; i++)
			{
				OBJIndex *possibleIndex = indexLookup[current + i];

				if (possibleIndex == currentIndex)
				{
					continue;
				}

				if (possibleIndex->vertexIndex != currentIndex->vertexIndex)
				{
					break;
				}
				else if ((!m_hasTexCoords || possibleIndex->texCoordIndex == currentIndex->texCoordIndex) && (!m_hasNormals || possibleIndex->normalIndex == currentIndex->normalIndex))
				{
					Vector3f currentPosition = m_positions[currentIndex->vertexIndex];
					Vector2f currentTexCoord;
					Vector3f currentNormal;

					if (m_hasTexCoords)
					{
						currentTexCoord = m_texCoords[currentIndex->texCoordIndex];
					}
					else
					{
						currentTexCoord.Set(0, 0);
					}

					if (m_hasNormals)
					{
						currentNormal = m_normals[currentIndex->normalIndex];
					}
					else
					{
						currentNormal.Set(0, 0, 0);
					}

					for (unsigned int j = 0; j < result.GetPositions().size(); j++)
					{
						if (currentPosition == result.GetPositions()[j] && ((!m_hasTexCoords || currentTexCoord == result.GetTexCoords()[j]) && (!m_hasNormals || currentNormal == result.GetNormals()[j])))
						{
							return j;
						}
					}
				}
			}

			return (unsigned int)-1;
		}
		else
		{
			if (testIndex->vertexIndex < currentIndex->vertexIndex)
			{
				start = current;
			}
			else
			{
				end = current;
			}
		}

		previous = current;
		current = ((end - start) >> 1) + start;
	}

	return (unsigned int)-1;
}

void Enco3D::Rendering::OBJModel::CreateOBJFace(const string &line)
{
	vector<string> tokens = SplitString(line, ' ');

	for (unsigned int i = 0; i < tokens.size() - 3; i++)
	{
		AddOBJIndex(ParseOBJIndex(tokens[1], &m_hasTexCoords, &m_hasNormals));
		AddOBJIndex(ParseOBJIndex(tokens[2 + i], &m_hasTexCoords, &m_hasNormals));
		AddOBJIndex(ParseOBJIndex(tokens[3 + i], &m_hasTexCoords, &m_hasNormals));
	}
}

inline static Enco3D::Rendering::OBJIndex ParseOBJIndex(const string &token, bool *hasTexCoords, bool *hasNormals)
{
	unsigned int vertIndexStart = 0;
	unsigned int vertIndexEnd = FindNextChar(vertIndexStart, token.c_str(), token.length(), '/');

	Enco3D::Rendering::OBJIndex result;
	result.vertexIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
	result.texCoordIndex = 0;
	result.normalIndex = 0;

	if (vertIndexEnd >= token.length())
	{
		return result;
	}

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, token.c_str(), token.length(), '/');

	result.texCoordIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
	*hasTexCoords = true;

	if (vertIndexEnd >= token.length())
	{
		return result;
	}

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, token.c_str(), token.length(), '/');

	result.normalIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
	*hasNormals = true;

	return result;
}

inline static Enco3D::Core::Vector3f ParseOBJVec3(const std::string& line)
{
	unsigned int tokenLength = (unsigned int)line.length();
	const char* tokenString = line.c_str();

	unsigned int vertIndexStart = 2;

	while (vertIndexStart < tokenLength)
	{
		if (tokenString[vertIndexStart] != ' ')
		{
			break;
		}

		vertIndexStart++;
	}

	unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float x = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float y = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float z = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	return Enco3D::Core::Vector3f(x, y, z);
}

inline static Enco3D::Core::Vector2f ParseOBJVec2(const std::string& line)
{
	unsigned int tokenLength = (unsigned int)line.length();
	const char* tokenString = line.c_str();

	unsigned int vertIndexStart = 3;

	while (vertIndexStart < tokenLength)
	{
		if (tokenString[vertIndexStart] != ' ')
			break;
		vertIndexStart++;
	}

	unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float x = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float y = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	return Enco3D::Core::Vector2f(x, y);
}

inline static bool CompareOBJIndexPtr(const Enco3D::Rendering::OBJIndex* a, const Enco3D::Rendering::OBJIndex* b)
{
	return a->vertexIndex < b->vertexIndex;
}

inline static unsigned int FindNextChar(unsigned int start, const char* str, unsigned int length, char token)
{
	unsigned int result = start;
	while (result < length)
	{
		result++;
		if (str[result] == token)
		{
			break;
		}
	}

	return result;
}

inline static unsigned int ParseOBJIndexValue(const std::string& token, unsigned int start, unsigned int end)
{
	return (unsigned int)(atoi(token.substr(start, end - start).c_str()) - 1);
}

inline static float ParseOBJFloatValue(const std::string& token, unsigned int start, unsigned int end)
{
	return (float)atof(token.substr(start, end - start).c_str());
}

inline static std::vector<std::string> SplitString(const std::string &s, char delim)
{
	vector<string> elems;

	const char* cstr = s.c_str();
	unsigned int strLength = (unsigned int)s.length();
	unsigned int start = 0;
	unsigned int end = 0;

	while (end <= strLength)
	{
		while (end <= strLength)
		{
			if (cstr[end] == delim)
			{
				break;
			}

			end++;
		}

		elems.push_back(s.substr(start, end - start));
		start = end + 1;
		end = start;
	}

	return elems;
}