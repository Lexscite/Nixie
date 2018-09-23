#include "../../stdafx_core.h"
#include "text_mesh.h"


namespace nixie
{
	TextMesh::TextMesh(std::shared_ptr<Font> font) :
		font_(font)
	{}

	void TextMesh::Generate(std::string text)
	{
		v_.clear();
		i_.clear();

		float offset = 0;

		for (auto& c : text)
		{
			auto c_data = font_->GetCharData(c);
			auto v = GenerateChar(c_data, offset);
			v_.insert(v_.begin(), v.begin(), v.end());
			offset += c_data.width;
		}

		v_count_ = i_count_ = static_cast<unsigned long>(v_.size());

		for (unsigned long i = 0; i < i_count_; i++)
		{
			i_.push_back(i);
		}

		CreateVertexBuffer();
		CreateIndexBuffer();
	}

	std::vector<VertexPTN> TextMesh::GenerateChar(Font::CharData c, float offset)
	{
		float t_width = font_->GetWidth();
		float t_height = font_->GetHeight();

		float t_left = c.x / t_width;
		float t_right = (c.x + c.width) / t_width;
		float t_top = c.y / t_height;
		float t_bottom = (c.y + c.height) / t_height;

		auto v_left_top = VertexPTN(
			Vector3f(offset, 0, 0),
			Vector2f(t_left, t_top),
			Vector3f(0.0f, 0.0f, 1.0f));

		auto v_left_bottom = VertexPTN(
			Vector3f(offset, c.height, 0),
			Vector2f(t_left, t_bottom),
			Vector3f(0.0f, 0.0f, 1.0f));

		auto v_right_top = VertexPTN(
			Vector3f(offset + c.width, 0, 0),
			Vector2f(t_right, t_top),
			Vector3f(0.0f, 0.0f, 1.0f));

		auto v_right_bottom = VertexPTN(
			Vector3f(offset, c.height, 0),
			Vector2f(t_left, t_bottom),
			Vector3f(0.0f, 0.0f, 1.0f));

		return std::vector<VertexPTN>({
				v_left_top,
				v_right_bottom,
				v_left_bottom,
				v_left_top,
				v_right_top,
				v_right_bottom
			});
	}
}