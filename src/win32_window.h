#ifndef UNICODE
#define UNICODE
#endif

#pragma once

#include <windows.h>
#include "renderer.h"

namespace WindowsWindow {

	bool running = true;

	HDC hdc;

	HWND window;

	LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT result = NULL;
		PAINTSTRUCT ps;

		switch (uMsg) {
			case WM_CLOSE:
			case WM_DESTROY: {
				running = false;
			} break;

			case WM_PAINT:
				BeginPaint(hwnd, &ps);
				EndPaint(hwnd, &ps);
				return 0;

			case WM_SIZE: {
				RECT rect;
				GetClientRect(hwnd, &rect);

				Renderer::renderState.width = rect.right - rect.left;
				Renderer::renderState.height = rect.bottom - rect.top;

				int size = Renderer::renderState.width * Renderer::renderState.height * sizeof(unsigned int);

				if (Renderer::renderState.memory) VirtualFree(Renderer::renderState.memory, NULL, MEM_RELEASE);
				Renderer::renderState.memory = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

				Renderer::renderState.bitmapInfo.bmiHeader.biSize = sizeof(Renderer::renderState.bitmapInfo.bmiHeader);
				Renderer::renderState.bitmapInfo.bmiHeader.biWidth = Renderer::renderState.width;
				Renderer::renderState.bitmapInfo.bmiHeader.biHeight = Renderer::renderState.height;
				Renderer::renderState.bitmapInfo.bmiHeader.biPlanes = 1;
				Renderer::renderState.bitmapInfo.bmiHeader.biBitCount = 32;
				Renderer::renderState.bitmapInfo.bmiHeader.biCompression = BI_RGB;
			} break;

			/*case WM_SETCURSOR: {
				if (LOWORD(lParam) == HTCLIENT) {
					SetCursor(LoadCursor(NULL, IDC_ARROW));
					return TRUE;
				}
			} break;*/

			default: {
				result = DefWindowProc(hwnd, uMsg, wParam, lParam);
			}
		}

		return result;
	}

	MSG message;

	unsigned int keyCode;
	bool isDown;

	void ManageMessages(HWND window)
	{
		while (PeekMessage(&message, window, NULL, NULL, PM_REMOVE)) {
			switch (message.message) {
				case WM_KEYDOWN: {
					keyCode = (unsigned int)message.wParam;
					isDown = ((message.lParam & (1 << 31)) == 0);
				} break;
				case WM_KEYUP: {
					keyCode = NULL;
				}

				default: {
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
			}
		}
	}

	HWND InitializeWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, int width, int height, LPCWSTR name, bool actualSize = false)
	{
		WNDCLASS windowClass = {};
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpszClassName = name;
		windowClass.lpfnWndProc = WindowCallback;
		//windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

		RegisterClass(&windowClass);

		RECT windowRect = {};
		windowRect.right = width;
		windowRect.bottom = height;

		if (!actualSize)
		{
			AdjustWindowRect(&windowRect, WS_MAXIMIZEBOX | WS_SYSMENU | WS_CAPTION, false);
		}

		window = CreateWindow(windowClass.lpszClassName, name, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL, hInstance, NULL);

		hdc = GetDC(window);

		return window;
	}
}