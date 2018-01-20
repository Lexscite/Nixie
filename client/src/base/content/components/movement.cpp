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
				movement_speed = Math::ClampFloat(movement_speed + 1.0f, 1.0f, 10.0f);
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
				movement_speed = Math::ClampFloat(movement_speed - 1.0f, 1.0f, 10.0f);
				std::cout << "Movement speed: " << movement_speed << std::endl;
			}
			else
			{
				std::cout << "Movement speed is min" << std::endl;
			}
		}

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::W) && !Input::IsKeyDown(DirectX::Keyboard::Keys::S))
			GetTransform()->Translate(GetTransform()->GetForward() * movement_speed * Time::GetDeltaTime());

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::S) && !Input::IsKeyDown(DirectX::Keyboard::Keys::W))
			GetTransform()->Translate(GetTransform()->GetBackward() * movement_speed * Time::GetDeltaTime());

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::D) && !Input::IsKeyDown(DirectX::Keyboard::Keys::A))
			GetTransform()->Rotate(0, 3 * Time::GetDeltaTime(), 0);

		if (Input::IsKeyDown(DirectX::Keyboard::Keys::A) && !Input::IsKeyDown(DirectX::Keyboard::Keys::D))
			GetTransform()->Rotate(0, -3 * Time::GetDeltaTime(), 0);
	}
}