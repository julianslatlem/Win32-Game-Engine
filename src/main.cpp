#include "window.h"
#include <iostream>
#include "game.cpp"
#include "renderer.h"

int main()
{
	GameEngine::Game game;

	game.Start();

	while (WindowsWindow::running)
	{
		game.window.Poll();

		game.Update();

		StretchDIBits(WindowsWindow::hdc, 0, 0, Renderer::renderState.width, Renderer::renderState.height,
			0, 0, Renderer::renderState.width, Renderer::renderState.height,
			Renderer::renderState.memory, &Renderer::renderState.bitmapInfo,
			DIB_RGB_COLORS, SRCCOPY);
	}

	return 0;
}