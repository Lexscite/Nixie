#ifndef __MEMORY_H__
#define __MEMORY_H__

#pragma once

template<typename T> void safe_release(T p)
{
	if (p)
	{
		p->Release();
		p = 0;
	}
}

#endif