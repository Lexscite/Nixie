#ifndef NIXIE_MATH_H_
#define NIXIE_MATH_H_

#pragma once

#include "mathfu/utilities.h"
#include "mathfu/constants.h"


namespace Nixie
{
	template<class T>
	const auto Clamp = mathfu::Clamp<T>;
}

#endif