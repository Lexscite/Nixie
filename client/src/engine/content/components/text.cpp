#include "../../../stdafx.h"

#include "text.h"


namespace nixie
{
	Text::Text(std::string text, std::string vs_path, std::string ps_path, std::string texture_path) :
		text_(text),
		vs_path_(vs_path),
		ps_path_(ps_path),
		texture_path_(texture_path)
	{}


	bool Text::OnInit()
	{
		font_ = std::make_shared<Font>();
		if (!font_->Init(texture_path_))
		{
			return false;
		}

		mesh_ = std::make_shared<Mesh>(font_->BuildVertexArray(text_));
		if (!mesh_->Init())
		{
			return false;
		}

		material_ = std::make_shared<Material>();
		if (!material_->Init(vs_path_, ps_path_, texture_path_, false))
		{
			return false;
		}

		return true;
	}


	bool Text::OnUpdate()
	{
		if (!material_->Update(GetTransform()->CalculateWorldMatrix()))
		{
			return false;
		}

		mesh_->Render();

		return true;
	}
}