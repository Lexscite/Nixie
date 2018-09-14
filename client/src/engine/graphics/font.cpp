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
		width_ = 321;
		height_ = 120;

		characters_ = {
			{' ', { 278, 102, 3, 3, 1, 1} },
			{'!', { 112, 34, 8, 24, -5, 23} },
			{'"', { 185, 102, 13, 9, -2, 23} },
			{'#', { 252, 34, 20, 22, 1, 21} },
			{'$', { 119, 0, 18, 29, 0, 24} },
			{'%', { 211, 0, 20, 24, 1, 23} },
			{'&', { 191, 0, 20, 24, 1, 23} },
			{'\'', { 198, 102, 7, 9, -5, 23} },
			{'(', { 49, 0, 12, 31, -3, 24} },
			{')', { 36, 0, 13, 31, -2, 24} },
			{'*', { 123, 102, 16, 15, -1, 23} },
			{'+', { 105, 102, 18, 16, 0, 16} },
			{',', { 157, 102, 11, 12, -2, 6} },
			{'-', { 265, 102, 13, 4, -2, 10} },
			{'.', { 224, 102, 9, 7, -4, 6} },
			{'/', { 174, 0, 17, 27, 0, 23} },
			{'0', { 146, 58, 18, 22, 0, 21} },
			{'1', { 17, 80, 17, 22, 0, 21} },
			{'2', { 285, 58, 17, 22, -1, 21} },
			{'3', { 51, 80, 16, 22, -1, 21} },
			{'4', { 272, 34, 20, 22, 1, 21} },
			{'5', { 83, 80, 16, 22, -1, 21} },
			{'6', { 110, 58, 18, 22, 0, 21} },
			{'7', { 302, 58, 17, 22, 0, 21} },
			{'8', { 182, 58, 18, 22, 0, 21} },
			{'9', { 0, 80, 17, 22, 0, 21} },
			{':', { 97, 102, 8, 18, -5, 17} },
			{';', { 138, 34, 11, 23, -2, 17} },
			{'<', { 159, 80, 16, 20, 0, 19} },
			{'=', { 168, 102, 17, 9, 0, 13} },
			{'>', { 175, 80, 15, 20, -2, 19} },
			{'?', { 99, 34, 13, 24, -3, 23} },
			{'@', { 83, 0, 21, 30, 2, 23} },
			{'A', { 170, 34, 21, 22, 2, 21} },
			{'B', { 251, 58, 17, 22, -1, 21} },
			{'C', { 234, 58, 17, 22, 0, 21} },
			{'D', { 128, 58, 18, 22, 0, 21} },
			{'E', { 67, 80, 16, 22, -1, 21} },
			{'F', { 115, 80, 15, 22, -1, 21} },
			{'G', { 0, 58, 19, 22, 1, 21} },
			{'H', { 74, 58, 18, 22, 0, 21} },
			{'I', { 99, 80, 16, 22, -1, 21} },
			{'J', { 145, 80, 14, 22, -1, 21} },
			{'K', { 34, 80, 17, 22, -1, 21} },
			{'L', { 130, 80, 15, 22, -2, 21} },
			{'M', { 292, 34, 20, 22, 1, 21} },
			{'N', { 92, 58, 18, 22, 0, 21} },
			{'O', { 19, 58, 19, 22, 1, 21} },
			{'P', { 217, 58, 17, 22, -1, 21} },
			{'Q', { 137, 0, 20, 28, 1, 21} },
			{'R', { 268, 58, 17, 22, -1, 21} },
			{'S', { 200, 58, 17, 22, 0, 21} },
			{'T', { 164, 58, 18, 22, 0, 21} },
			{'U', { 38, 58, 18, 22, 0, 21} },
			{'V', { 191, 34, 21, 22, 2, 21} },
			{'W', { 232, 34, 20, 22, 1, 21} },
			{'X', { 212, 34, 20, 22, 1, 21} },
			{'Y', { 149, 34, 21, 22, 2, 21} },
			{'Z', { 56, 58, 18, 22, 0, 21} },
			{'[', { 72, 0, 11, 31, -4, 24} },
			{'\\', { 157, 0, 17, 27, -1, 23} },
			{']', { 61, 0, 11, 31, -3, 24} },
			{'^', { 139, 102, 18, 12, 0, 21} },
			{'_', { 244, 102, 21, 4, 2, -3} },
			{'`', { 233, 102, 11, 6, -1, 24} },
			{'a', { 0, 102, 17, 18, 0, 17} },
			{'b', { 287, 0, 17, 24, -1, 23} },
			{'c', { 49, 102, 16, 18, -1, 17} },
			{'d', { 304, 0, 17, 24, 0, 23} },
			{'e', { 301, 80, 17, 18, 0, 17} },
			{'f', { 231, 0, 19, 24, 1, 23} },
			{'g', { 269, 0, 18, 24, 0, 17} },
			{'h', { 51, 34, 16, 24, -1, 23} },
			{'i', { 67, 34, 16, 24, -1, 23} },
			{'j', { 104, 0, 15, 30, 0, 23} },
			{'k', { 34, 34, 17, 24, -1, 23} },
			{'l', { 83, 34, 16, 24, -1, 23} },
			{'m', { 266, 80, 18, 18, 0, 17} },
			{'n', { 81, 102, 16, 18, -1, 17} },
			{'o', { 248, 80, 18, 18, 0, 17} },
			{'p', { 0, 34, 17, 24, -1, 17} },
			{'q', { 17, 34, 17, 24, 0, 17} },
			{'r', { 284, 80, 17, 18, -1, 17} },
			{'s', { 17, 102, 16, 18, -1, 17} },
			{'t', { 120, 34, 18, 23, 1, 22} },
			{'u', { 65, 102, 16, 18, -1, 17} },
			{'v', { 210, 80, 19, 18, 1, 17} },
			{'w', { 190, 80, 20, 18, 1, 17} },
			{'x', { 229, 80, 19, 18, 1, 17} },
			{'y', { 250, 0, 19, 24, 1, 17} },
			{'z', { 33, 102, 16, 18, -1, 17} },
			{'{', { 21, 0, 15, 31, -1, 24} },
			{'|', { 0, 0, 6, 34, -6, 27} },
			{'}', { 6, 0, 15, 31, -2, 24} },
			{'~', { 205, 102, 19, 8, 1, 13} },
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