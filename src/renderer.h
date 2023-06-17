#pragma once

#include <windows.h>
#include "maths.h"

namespace Renderer {
	struct RenderState {
		int height, width;
		void* memory;

		BITMAPINFO bitmapInfo;
	};

	static RenderState renderState;

	static void ClearScreen(unsigned int color)
	{
		unsigned int* pixel = (unsigned int*)renderState.memory;
		for (int y = 0; y < renderState.height; y++) {
			for (int x = 0; x < renderState.width; x++) {
				*pixel++ = color;
			}
		}
	}

	static void DrawRectPixels(int x0, int y0, int x1, int y1, unsigned int color)
	{
		x0 = GameEngine::Clamp(0, x0, renderState.width);
		x1 = GameEngine::Clamp(0, x0 + x1, renderState.width);
		y0 = GameEngine::Clamp(0, y0, renderState.height);
		y1 = GameEngine::Clamp(0, y0 + y1, renderState.height);

		for (int y = y0; y < y1; y++) {
			unsigned int* pixel = (unsigned int*)renderState.memory + x0 + y * renderState.width;
			for (int x = x0; x < x1; x++) {
				*pixel++ = color;
			}
		}
	}

	static float renderScale = 0.01f;

	static void DrawRect(float x, float y, float sizeX, float sizeY, unsigned int color, int anchor = 0)
	{
		x *= renderState.height * renderScale;
		y *= renderState.height * renderScale;
		sizeX *= renderState.height * renderScale;
		sizeY *= renderState.height * renderScale;

		switch (anchor) {
		case BOTTOM_LEFT: break;
		case BOTTOM_CENTER: {
			x += renderState.width / 2;
		} break;
		case BOTTOM_RIGHT: {
			x += renderState.width;
		} break;
		case CENTER_LEFT: {
			y += renderState.height / 2;
		} break;
		case CENTER: {
			x += renderState.width / 2;
			y += renderState.height / 2;
		} break;
		case CENTER_RIGHT: {
			x += renderState.width;
			y += renderState.height / 2;
		} break;
		case TOP_LEFT: {
			y += renderState.height;
		} break;
		case TOP_CENTER: {
			x += renderState.width / 2;
			y += renderState.height;
		} break;
		case TOP_RIGHT: {
			x += renderState.width;
			y += renderState.height;
		} break;

		default: {
			x += renderState.width / 2;
			y += renderState.height / 2;
		} break;
		}

		int x0 = x - sizeX / 2.0f;
		int x1 = x + sizeX / 2.0f;
		int y0 = y - sizeY / 2.0f;
		int y1 = y + sizeY / 2.0f;

		DrawRectPixels(x0, y0, x1, y1, color);
	}

	static void DrawLine(int x0, int y0, int x1, int y1, unsigned int color)
	{
		x0 = GameEngine::Clamp(0, x0, renderState.width);
		x1 = GameEngine::Clamp(0, x0 + x1, renderState.width);
		y0 = GameEngine::Clamp(0, y0, renderState.height);
		y1 = GameEngine::Clamp(0, y0 + y1, renderState.height);

		int dx, dy, p, x, y;

		dx = x1 - x0;
		dy = y1 - y0;

		x = x0;
		y = y0;

		p = 2 * dy - dx;

		while (x < x1)
		{
			if (p >= 0)
			{
				unsigned int* pixel = (unsigned int*)renderState.memory + x + y * renderState.width;
				*pixel = color;

				y = y + 1;
				p = p + 2 * dy - 2 * dx;
			}
			else
			{
				unsigned int* pixel = (unsigned int*)renderState.memory + x + y * renderState.width;
				*pixel = color;

				p = p + 2 * dy;
			}
			x = x + 1;
		}
	}
}