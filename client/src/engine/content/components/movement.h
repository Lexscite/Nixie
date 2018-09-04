#ifndef MOVEMENT_H
#define MOVEMENT_H

#pragma once

#include "../component.h"

namespace Nixie
{
	class Movement : public Component
	{
	private:
		virtual void OnInit() override;
		virtual void OnUpdate() override;

	private:
		float movement_speed;
		float rotation_speed;
	};
}

#endif