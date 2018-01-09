#include "material.h"
#include "../../app.h"

namespace Nixie
{
	Material::Material() :
		shader_(nullptr),
		texture_(nullptr) {}

	void Material::OnInit()
	{
		LoadTexture(L"../data/textures/placeholder.jpg");

		shader_ = new Shader;
		shader_->Init(L"../data/shaders/default_vs.hlsl.", L"../data/shaders/default_ps.hlsl.");
		shader_->SetTexture(texture_->GetTextureView());
	}

	void Material::OnUpdate()
	{
		Vector3 position = GetPosition();
		Quaternion rotation = GetRotation();
		Vector3 scale = GetScale();

		DirectX::SimpleMath::Matrix translation_matrix = DirectX::XMMatrixTranslation(
			position.x,
			position.y,
			position.z);
		DirectX::SimpleMath::Matrix rotation_matrix = DirectX::XMMatrixRotationQuaternion(DirectX::SimpleMath::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w));
		DirectX::SimpleMath::Matrix scaling_matrix = DirectX::XMMatrixScaling(
			scale.x,
			scale.y,
			scale.z);

		shader_->Update(
			translation_matrix * rotation_matrix * scaling_matrix,
			App::GetSingleton()->GetScene()->GetCamera()->GetViewMatrix(),
			D3D::GetSingleton()->GetProjectionMatrix());
	}

	bool Material::LoadTexture(const wchar_t* file_path)
	{
		texture_ = new Texture;
		if (!texture_->Init(file_path))
			return false;

		return true;
	}

	Shader* Material::GetShader()
	{
		return shader_;
	}
}