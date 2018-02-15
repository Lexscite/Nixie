#include "movement.h"

namespace Nixie
{
	void Movement::OnInit()
	{
		movement_speed = 3;
	}

	void Movement::OnUpdate()
	{
		if (Input::IsKeyPressed(DirectX::Keyboard::Keys::OemPlus))
		{
			if (movement_speed != 10.0f)
			{
				movement_speed = Math::Clampf(movement_speed + 1.0f, 1.0f, 10.0f);
				std::cout << "Movement speed: " << movement_speed << std::endl;
			}
			else
			{
				std::cout << "Movement speed is max" << std::endl;
			}
		}

		if (Input::IsKeyPressed(DirectX::Keyboard::Keys::OemMinus))
		{
			if (movement_speed != 1.0f)
			{
				movement_speed = Math::Clampf(movement_speed - 1.0f, 1.0f, 10.0f);
				std::cout << "Movement speed: " << movement_speed << std::endl;
			}
			else
			{
				std::cout << "Movement speed is min" << std::endl;
			}
		}

		Vector3 movement = Vector3();

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::W) && !Input::IsKeyDown(DirectX::Keyboard::Keys::S))
			movement += Vector3(GetTransform()->GetForward());

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::S) && !Input::IsKeyDown(DirectX::Keyboard::Keys::W))
			movement += Vector3(GetTransform()->GetBackward());

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::D) && !Input::IsKeyDown(DirectX::Keyboard::Keys::A))
			movement += Vector3(GetTransform()->GetRight());

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::A) && !Input::IsKeyDown(DirectX::Keyboard::Keys::D))
			movement += Vector3(GetTransform()->GetLeft());

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::E) && !Input::IsKeyDown(DirectX::Keyboard::Keys::Q))
			GetTransform()->Rotate(0, 3 * Time::GetDeltaTime(), 0);

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::Q) && !Input::IsKeyDown(DirectX::Keyboard::Keys::E))
			GetTransform()->Rotate(0, -3 * Time::GetDeltaTime(), 0);

		GetTransform()->Translate(movement.Normalize() * movement_speed * Time::GetDeltaTime());
	}
}