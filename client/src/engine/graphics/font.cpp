#include "../../stdafx.h"

#include "font.h"
#include "mesh.h"

#include <algorithm>


namespace Nixie
{
	Font::Font() :
		name_(),
		characters_(),
		texture_(nullptr)
	{}


	bool Font::Init(std::string texture_path)
	{
		width_ = 156;
		height_ = 72;

		characters_ = {
			{ ' ',{ 105, 63, 3, 3, 1, 1 } },
		{ '!',{ 136, 40, 4, 12, 0, 11 } },
		{ '"',{ 49, 63, 7, 5, 1, 11 } },
		{ '#',{ 140, 40, 11, 11, 1, 11 } },
		{ '$',{ 34, 0, 9, 14, 1, 12 } },
		{ '%',{ 135, 0, 14, 12, 1, 11 } },
		{ '&',{ 121, 0, 14, 12, 1, 11 } },
		{ '\'',{ 56, 63, 5, 5, 1, 11 } },
		{ '(',{ 59, 0, 7, 14, 1, 11 } },
		{ ')',{ 85, 0, 6, 14, 1, 11 } },
		{ '*',{ 31, 63, 8, 7, 1, 11 } },
		{ '+',{ 79, 52, 10, 9, 0, 9 } },
		{ ',',{ 61, 63, 5, 5, 1, 3 } },
		{ '-',{ 97, 63, 8, 3, 1, 5 } },
		{ '.',{ 82, 63, 5, 4, 1, 3 } },
		{ '/',{ 25, 0, 9, 14, 2, 11 } },
		{ '0',{ 90, 28, 10, 12, 1, 11 } },
		{ '1',{ 130, 28, 10, 12, 1, 11 } },
		{ '2',{ 28, 40, 9, 12, 1, 11 } },
		{ '3',{ 37, 40, 9, 12, 1, 11 } },
		{ '4',{ 93, 16, 11, 12, 2, 11 } },
		{ '5',{ 10, 40, 9, 12, 1, 11 } },
		{ '6',{ 20, 28, 10, 12, 1, 11 } },
		{ '7',{ 0, 28, 10, 12, 1, 11 } },
		{ '8',{ 10, 28, 10, 12, 1, 11 } },
		{ '9',{ 40, 28, 10, 12, 1, 11 } },
		{ ':',{ 16, 63, 5, 9, 1, 8 } },
		{ ';',{ 7, 52, 5, 10, 1, 8 } },
		{ '<',{ 99, 52, 10, 9, 0, 9 } },
		{ '=',{ 39, 63, 10, 6, 0, 7 } },
		{ '>',{ 89, 52, 10, 9, 0, 9 } },
		{ '?',{ 97, 40, 8, 12, 1, 11 } },
		{ '@',{ 91, 0, 15, 13, 1, 11 } },
		{ 'A',{ 26, 16, 12, 12, 1, 11 } },
		{ 'B',{ 55, 40, 9, 12, 0, 11 } },
		{ 'C',{ 49, 16, 11, 12, 1, 11 } },
		{ 'D',{ 60, 16, 11, 12, 0, 11 } },
		{ 'E',{ 105, 40, 8, 12, 0, 11 } },
		{ 'F',{ 89, 40, 8, 12, 0, 11 } },
		{ 'G',{ 71, 16, 11, 12, 1, 11 } },
		{ 'H',{ 50, 28, 10, 12, 0, 11 } },
		{ 'I',{ 120, 40, 6, 12, 1, 11 } },
		{ 'J',{ 81, 40, 8, 12, 2, 11 } },
		{ 'K',{ 80, 28, 10, 12, 0, 11 } },
		{ 'L',{ 73, 40, 8, 12, 0, 11 } },
		{ 'M',{ 0, 16, 13, 12, 0, 11 } },
		{ 'N',{ 104, 16, 11, 12, 0, 11 } },
		{ 'O',{ 13, 16, 13, 12, 1, 11 } },
		{ 'P',{ 19, 40, 9, 12, 0, 11 } },
		{ 'Q',{ 5, 0, 13, 15, 1, 11 } },
		{ 'R',{ 140, 28, 10, 12, 0, 11 } },
		{ 'S',{ 46, 40, 9, 12, 1, 11 } },
		{ 'T',{ 146, 16, 10, 12, 1, 11 } },
		{ 'U',{ 115, 16, 11, 12, 1, 11 } },
		{ 'V',{ 38, 16, 11, 12, 1, 11 } },
		{ 'W',{ 106, 0, 15, 12, 1, 11 } },
		{ 'X',{ 82, 16, 11, 12, 1, 11 } },
		{ 'Y',{ 60, 28, 10, 12, 1, 11 } },
		{ 'Z',{ 30, 28, 10, 12, 1, 11 } },
		{ '[',{ 73, 0, 6, 14, 0, 11 } },
		{ '\\',{ 43, 0, 9, 14, 2, 11 } },
		{ ']',{ 79, 0, 6, 14, 1, 11 } },
		{ '^',{ 21, 63, 10, 8, 0, 11 } },
		{ '_',{ 87, 63, 10, 3, 2, 0 } },
		{ '`',{ 76, 63, 6, 4, 1, 11 } },
		{ 'a',{ 145, 52, 9, 9, 1, 8 } },
		{ 'b',{ 0, 40, 10, 12, 1, 11 } },
		{ 'c',{ 136, 52, 9, 9, 1, 8 } },
		{ 'd',{ 136, 16, 10, 12, 1, 11 } },
		{ 'e',{ 39, 52, 10, 9, 1, 8 } },
		{ 'f',{ 113, 40, 7, 12, 1, 11 } },
		{ 'g',{ 126, 16, 10, 12, 1, 8 } },
		{ 'h',{ 120, 28, 10, 12, 1, 11 } },
		{ 'i',{ 131, 40, 5, 12, 1, 11 } },
		{ 'j',{ 18, 0, 7, 15, 3, 11 } },
		{ 'k',{ 110, 28, 10, 12, 1, 11 } },
		{ 'l',{ 126, 40, 5, 12, 1, 11 } },
		{ 'm',{ 12, 52, 14, 9, 1, 8 } },
		{ 'n',{ 69, 52, 10, 9, 1, 8 } },
		{ 'o',{ 59, 52, 10, 9, 1, 8 } },
		{ 'p',{ 100, 28, 10, 12, 1, 8 } },
		{ 'q',{ 70, 28, 10, 12, 1, 8 } },
		{ 'r',{ 8, 63, 8, 9, 1, 8 } },
		{ 's',{ 0, 63, 8, 9, 1, 8 } },
		{ 't',{ 0, 52, 7, 11, 1, 10 } },
		{ 'u',{ 49, 52, 10, 9, 1, 8 } },
		{ 'v',{ 127, 52, 9, 9, 1, 8 } },
		{ 'w',{ 26, 52, 13, 9, 1, 8 } },
		{ 'x',{ 118, 52, 9, 9, 1, 8 } },
		{ 'y',{ 64, 40, 9, 12, 1, 8 } },
		{ 'z',{ 109, 52, 9, 9, 1, 8 } },
		{ '{',{ 52, 0, 7, 14, 1, 11 } },
		{ '|',{ 0, 0, 5, 16, 1, 12 } },
		{ '}',{ 66, 0, 7, 14, 1, 11 } },
		{ '~',{ 66, 63, 10, 4, 0, 6 } },
		};

		if (!LoadTexture(texture_path))
		{
			return false;
		}

		return true;
	}


	bool Font::LoadTexture(std::string texture_path)
	{
		texture_ = std::make_unique<Texture>();
		if (!texture_->Init(texture_path))
		{
			return false;
		}

		return true;
	}


	std::vector<Vertex> Font::BuildVertexArray(std::string s)
	{
		std::vector<Vertex> vertices;
		Vector3<float> pos = Vector3<float>(0.0f);

		for (auto& c : s)
		{
			auto fc = characters_[c];
			auto v = CreateCharPlane(fc, pos);
			vertices.insert(vertices.begin(), v.begin(), v.end());
			pos += Vector3<float>(static_cast<float>(fc.width), 0, 0);
		}

		return vertices;
	}


	std::vector<Vertex> Font::CreateCharPlane(const CharData& c, const Vector3<float>& pos)
	{
		auto v = std::vector<Vertex>();
		v.resize(6);

		float t_left = static_cast<float>(c.x) / static_cast<float>(width_);
		float t_right = (static_cast<float>(c.x) + static_cast<float>(c.width)) / static_cast<float>(width_);
		float t_top = static_cast<float>(c.y) / static_cast<float>(height_);
		float t_bottom = (static_cast<float>(c.y) + static_cast<float>(c.height)) / static_cast<float>(height_);

		v[0] = {
			pos,
			Vector2<float>(t_left, t_top),
			Vector3<float>(0.0f)
		};
		v[1] = {
			Vector3<float>(pos.x + static_cast<float>(c.width), pos.y + static_cast<float>(c.height), pos.z),
			Vector2<float>(t_right, t_bottom),
			Vector3<float>(0.0f)
		};
		v[2] = {
			Vector3<float>(pos.x, pos.y + static_cast<float>(c.height), pos.z),
			Vector2<float>(t_left, t_bottom),
			Vector3<float>(0.0f)
		};

		v[3] = v[0];
		v[4] = {
			Vector3<float>(pos.x + static_cast<float>(c.width), pos.y, pos.z),
			Vector2<float>(t_right, t_top),
			Vector3<float>(0.0f)
		};
		v[5] = v[1];

		return v;
	}
}