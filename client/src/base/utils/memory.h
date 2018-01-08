#ifndef MEMORY_H
#define MEMORY_H

#pragma once

namespace Nixie
{
	template<typename T> void safe_release(T p)
	{
		if (p)
		{
			p->Release();
			p = 0;
		}
	}

	template<typename T> void safe_delete(T p)
	{
		if (p)
		{
			delete p;
			p = 0;
		}
	}

	template<typename T> void safe_delete_arr(T p)
	{
		if (p)
		{
			delete[] p;
			p = 0;
		}
	}
}

#endif