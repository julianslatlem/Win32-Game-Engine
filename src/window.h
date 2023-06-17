#pragma once

#include "win32_window.h"
#include "renderer.h"
#include "input.h"

namespace GameEngine {
	class Window {
	private:
		int m_width;
		int m_height;
		LPCWSTR m_name;

		HINSTANCE hInstance;
		HINSTANCE hPrevInstance;
		LPWSTR lpCmdLine;
		int nCmdShow;

		HWND window;

	public:
		int backgroundColor = 0x000000;

		void Init(int width, int height, LPCWSTR name, bool actualSize = false)
		{
			this->m_width = width;
			this->m_height = height;
			this->m_name = name;

			this->hInstance = GetModuleHandle(0);
			this->hPrevInstance = GetModuleHandle(0);
			this->lpCmdLine = 0;
			this->nCmdShow = 0;

			this->window = WindowsWindow::InitializeWindow(this->hInstance, this->hPrevInstance, this->lpCmdLine, this->nCmdShow, this->m_width, this->m_height, this->m_name, actualSize);
		}

		void SetSize(int width, int height, bool actualSize = false)
		{
			RECT windowRect;
			RECT clientRect;
			GetWindowRect(this->window, &windowRect);
			GetClientRect(this->window, &clientRect);

			if (!actualSize)
			{
				int borderSizeX = ((clientRect.right - clientRect.left) - (windowRect.right - windowRect.left));
				int borderSizeY = ((clientRect.bottom - clientRect.top) - (windowRect.bottom - windowRect.top));

				int clientWidth = width - borderSizeX;
				int clientHeight = height - borderSizeY;

				MoveWindow(this->window, windowRect.left, windowRect.top, clientWidth, clientHeight, true);
			}
			else if (actualSize)
			{
				MoveWindow(this->window, windowRect.left, windowRect.top, width, height, true);
			}
		}

		int GetWidth()
		{
			RECT windowRect;
			GetClientRect(this->window, &windowRect);

			return windowRect.right;
		}

		int GetHeight()
		{
			RECT windowRect;
			GetClientRect(this->window, &windowRect);

			return windowRect.bottom;
		}

		int GetActualWidth()
		{
			RECT windowRect;
			GetWindowRect(this->window, &windowRect);

			return windowRect.right - windowRect.left;
		}

		int GetActualHeight()
		{
			RECT windowRect;
			GetWindowRect(this->window, &windowRect);

			return windowRect.bottom - windowRect.top;
		}

		void SetName(LPCWSTR name)
		{
			this->m_name = name;

			SetWindowTextW(this->window, name);
		}

		void Terminate()
		{

		}

		void Poll()
		{
			WindowsWindow::ManageMessages(this->window);

			Renderer::ClearScreen(backgroundColor);
		}
	};



	class Script {
	public:
		Input Input;

		void Start() {}
		void Update() {}
	};
}