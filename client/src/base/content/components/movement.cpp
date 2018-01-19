#include "movement.h"

namespace Nixie
{
	void Movement::OnUpdate()
	{
		if (Input::IsKeyDown(DirectX::Keyboard::Keys::W) && !Input::IsKeyDown(DirectX::Keyboard::Keys::S))
			GetTransform()->Translate(GetTransform()->GetForward() * Time::GetDeltaTime());

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::S) && !Input::IsKeyDown(DirectX::Keyboard::Keys::W))
			GetTransform()->Translate(GetTransform()->GetBackward() * Time::GetDeltaTime());

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::D) && !Input::IsKeyDown(DirectX::Keyboard::Keys::A))
			GetTransform()->Rotate(Quaternion(0, 1 * Time::GetDeltaTime(), 0, 1));

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::A) && !Input::IsKeyDown(DirectX::Keyboard::Keys::D))
			GetTransform()->Rotate(Quaternion(0, -1 * Time::GetDeltaTime(), 0, 1));
	}
}