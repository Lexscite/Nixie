#ifndef VOODOO_VERTEX_H_
#define VOODOO_VERTEX_H_

#include "math/vector.h"


namespace voodoo
{
	struct VertexP
	{
		VertexP() = default;

		VertexP(const Vector3<float>& position) :
			position(position)
		{}

		Vector3<float> position;
	};

	struct VertexPT : public VertexP
	{
		VertexPT() = default;

		VertexPT(const Vector3<float>& position, const Vector2<float>& texture) :
			VertexP(position),
			texture(texture)
		{}

		Vector2<float> texture;
	};

	struct VertexPTN : public VertexPT
	{
		VertexPTN() = default;

		VertexPTN(const Vector3<float>& position, const Vector2<float>& texture, const Vector3<float>& normal) :
			VertexPT(position, texture),
			normal(normal)
		{}

		Vector3<float> normal;
	};
}

#endif