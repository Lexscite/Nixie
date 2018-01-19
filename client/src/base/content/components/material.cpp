#include "material.h"
#include "../../app.h"

namespace Nixie
{
	Material::Material() :
		shader(nullptr),
		texture(nullptr) {}

	void Material::OnInit()
	{
		LoadTexture(L"../data/textures/placeholder.jpg");

		shader = new Shader;
		shader->Init(L"../data/shaders/default_vs.hlsl.", L"../data/shaders/default_ps.hlsl.");
		shader->SetTexture(texture->GetTextureView());
	}

	void Material::OnUpdate()
	{
		Vector3 position = GetTransform()->GetPosition();
		Quaternion rotation = GetTransform()->GetRotation();
		Vector3 scale = GetTransform()->GetScale();

		auto dx_position = DirectX::SimpleMath::Vector3(position.x, position.y, position.z);
		auto dx_rotation = DirectX::SimpleMath::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
		auto dx_scale = DirectX::SimpleMath::Vector3(scale.x, scale.y, scale.z);

		auto translation_matrix = DirectX::SimpleMath::Matrix::CreateTranslation(dx_position);
		auto rotation_matrix = DirectX::SimpleMath::Matrix::CreateFromQuaternion(dx_rotation);
		auto scaling_matrix = DirectX::SimpleMath::Matrix::CreateScale(dx_scale);

		auto world_matrix = scaling_matrix * rotation_matrix * translation_matrix;
		auto view_matrix = App::GetSingleton()->GetScene()->GetCamera()->GetViewMatrix();
		auto projection_matrix = D3D::GetSingleton()->GetProjectionMatrix();

		shader->Update(world_matrix, view_matrix, projection_matrix);
	}

	bool Material::LoadTexture(const wchar_t* file_path)
	{
		texture = new Texture;
		if (!texture->Init(file_path))
			return false;

		return true;
	}

	Shader* Material::GetShader()
	{
		return shader;
	}
}