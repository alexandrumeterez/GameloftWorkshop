#pragma once
#include "../Utilities/Math.h"

struct Vertex
{
	Vector3 pos;
	Vector3 norm;
	Vector3 binorm;
	Vector3 tgt;
	Vector2 uv;
	Vertex() {}

	Vertex(const Vertex &v)
	{
		pos.x = v.pos.x;
		pos.y = v.pos.y;
		pos.z = v.pos.z;

		norm.x = v.norm.x;
		norm.y = v.norm.y;
		norm.z = v.norm.z;

		binorm.x = v.binorm.x;
		binorm.y = v.binorm.y;
		binorm.z = v.binorm.z;

		tgt.x = v.tgt.x;
		tgt.y = v.tgt.y;
		tgt.z = v.tgt.z;

		uv.x = v.uv.x;
		uv.y = v.uv.y;
	}
};
