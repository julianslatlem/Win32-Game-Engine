#pragma once
#include <iostream>
#include "win32_window.h"

namespace GameEngine {
	enum KeyCode {
		BACKSPACE = 8,
		TAB = 9,
		ENTER = 13,
		SHIFT = 16,
		CTRL = 17,
		ALT = 18,
		PAUSE = 19,
		CAPS = 20,
		ESCAPE = 27,
		PG_UP = 33,
		PG_DOWN = 24,
		END = 35,
		HOME = 36,
		LEFT = 37,
		UP = 38,
		RIGHT = 39,
		DOWN = 40,

		S = 83,

		W = 87,

		A = 65,
		D = 68,
	};

	class Input {
	public:
		bool GetKeyDown(KeyCode key)
		{
			if (WindowsWindow::keyCode == key && WindowsWindow::isDown)
			{
				return true;
			}

			return false;
		}

		bool pressed = false;

		bool GetKey(KeyCode key) 
		{
			if (WindowsWindow::keyCode == key)
			{
				if (!pressed) {
					pressed = true;
					return true;
				}
				else return false;
				pressed = true;
			}
			else if (WindowsWindow::keyCode == NULL)
			{
				pressed = false;
				return false;
			}

			return false;
		}
	};
}