#ifndef _ENCO3D_VERTEX_H_
#define _ENCO3D_VERTEX_H_

struct Vertex
{
	float x, y, z;
	float u, v;
	float nx, ny, nz;

	inline Vertex()
	{
	}

	inline Vertex(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{
	}

	inline Vertex(float _x, float _y, float _z, float _u, float _v) : x(_x), y(_y), z(_z), u(_u), v(_v)
	{
	}

	inline Vertex(float _x, float _y, float _z, float _u, float _v, float _nx, float _ny, float _nz) : x(_x), y(_y), z(_z), u(_u), v(_v), nx(_nx), ny(_ny), nz(_nz)
	{
	}

	inline Vertex(const Vertex &v) : x(v.x), y(v.y), z(v.z), u(v.u), v(v.v), nx(v.nx), ny(v.ny), nz(v.nz)
	{
	}

	inline Vertex& SetPosition(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
		return *this;
	}

	inline Vertex& SetTexCoord(float _u, float _v)
	{
		u = _u;
		v = _v;
		return *this;
	}

	inline Vertex& SetNormal(float _nx, float _ny, float _nz)
	{
		nx = _nx;
		ny = _ny;
		nz = _nz;
		return *this;
	}
};

#endif