#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "DirectX.h"

namespace NXGraphics
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