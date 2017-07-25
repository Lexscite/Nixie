#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <windows.h>

#include "DirectX.h"

namespace NixieClient
{
	class Graphics
	{
	public:
		Graphics();
		~Graphics();

		bool Init(HWND hwnd, int clientWidth, int clientHeight, bool fullscreen);
		void Render();

	private:
		DirectX* m_pDirectX;

		bool m_Fullscreen;
	};
}

#endif // !GRAPHICS_H