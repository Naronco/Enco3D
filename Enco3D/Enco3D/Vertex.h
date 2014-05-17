#ifndef _ENCO3D_VERTEX_H_
#define _ENCO3D_VERTEX_H_

namespace Enco3D
{
	namespace Rendering
	{
		struct Vertex
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

			inline Vertex(float _x, float _y, float _z, float _u, float _v, float _w) : x(_x), y(_y), z(_z), u(_u), v(_v), w(_w)
			{
			}

			inline Vertex(float _x, float _y, float _z, float _u, float _v, float _w, float _nx, float _ny, float _nz) : x(_x), y(_y), z(_z), u(_u), v(_v), w(_w), nx(_nx), ny(_ny), nz(_nz)
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
		};
	}
}

#endif