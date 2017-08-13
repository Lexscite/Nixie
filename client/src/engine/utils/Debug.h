#ifndef __DEBUG_H__
#define __DEBUG_H__

#pragma once

#include <exception>
#include <windows.h>
#include <stdio.h>
#include <iostream>

class CException : public std::exception
{
public:
	CException(HRESULT hr) : result(hr) {}

	virtual const char* what() const override
	{
		static char s_str[64] = { 0 };
		sprintf_s(s_str, "Failure with HRESULT of %08X",
			static_cast<unsigned int>(result));
		return s_str;
	}

private:
	HRESULT result;
};

inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
		throw CException(hr);
	}
}

#endif