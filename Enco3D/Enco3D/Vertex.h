#ifndef _ENCO3D_VERTEX_H_
#define _ENCO3D_VERTEX_H_

#include "Vector2.h"
#include "Vector3.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Rendering
	{
		struct DLL_EXPORT Vertex
		{
			float x, y, z;
			float u, v, w;
			float nx, ny, nz;

			inline Vertex()
			{
			}

			inline Vertex(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
			{
			}

			inline Vertex(const Core::Vector3f& position) : x(position.x), y(position.y), z(position.z)
			{
			}

			inline Vertex(float _x, float _y, float _z, float _u, float _v, float _w) : x(_x), y(_y), z(_z), u(_u), v(_v), w(_w)
			{
			}

			inline Vertex(const Core::Vector3f& position, const Core::Vector3f& texture) : x(position.x), y(position.y), z(position.z), u(texture.x), v(texture.y), w(texture.z)
			{
			}

			inline Vertex(const Core::Vector3f& position, const Core::Vector2f& texture) : x(position.x), y(position.y), z(position.z), u(texture.x), v(texture.y), w(0)
			{
			}

			inline Vertex(float _x, float _y, float _z, float _u, float _v, float _w, float _nx, float _ny, float _nz) : x(_x), y(_y), z(_z), u(_u), v(_v), w(_w), nx(_nx), ny(_ny), nz(_nz)
			{
			}

			inline Vertex(const Core::Vector3f& position, const Core::Vector3f& texture, const Core::Vector3f& normal) : x(position.x), y(position.y), z(position.z), u(texture.x), v(texture.y), w(texture.z), nx(normal.x), ny(normal.y), nz(normal.z)
			{
			}

			inline Vertex(const Core::Vector3f& position, const Core::Vector2f& texture, const Core::Vector3f& normal) : x(position.x), y(position.y), z(position.z), u(texture.x), v(texture.y), w(0), nx(normal.x), ny(normal.y), nz(normal.z)
			{
			}

			inline Vertex(const Vertex &v) : x(v.x), y(v.y), z(v.z), u(v.u), v(v.v), w(v.w), nx(v.nx), ny(v.ny), nz(v.nz)
			{
			}

			inline Vertex& setPosition(float _x, float _y, float _z)
			{
				x = _x;
				y = _y;
				z = _z;
				return *this;
			}

			inline Vertex& setTexCoord(float _u, float _v, float _w = 0.0f)
			{
				u = _u;
				v = _v;
				w = _w;
				return *this;
			}

			inline Vertex& setNormal(float _nx, float _ny, float _nz)
			{
				nx = _nx;
				ny = _ny;
				nz = _nz;
				return *this;
			}

			inline Vertex& setNormal(const Core::Vector3f& normal)
			{
				nx = normal.x;
				ny = normal.y;
				nz = normal.z;
				return *this;
			}

			inline Core::Vector3f getPosition()
			{
				return Core::Vector3f(x, y, z);
			}

			inline Core::Vector3f getNormal()
			{
				return Core::Vector3f(nx, ny, nz);
			}

			inline Core::Vector3f getTextureCoords()
			{
				return Core::Vector3f(u, v, w);
			}

			inline Core::Vector2f getTextureCoordsUV()
			{
				return Core::Vector2f(u, v);
			}
		};
	}
}

#endif