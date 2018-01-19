#ifndef MOVEMENT_H
#define MOVEMENT_H

#pragma once

#include "../component.h"

namespace Nixie
{
	class Movement : public Component
	{
	private:
		virtual void OnUpdate() override;
	};
}

#endif