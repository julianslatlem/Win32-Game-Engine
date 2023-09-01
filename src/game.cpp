#include "engine.h"

namespace GameEngine {
	class Game : public Script {
	public:
		
		Window window;

		Rectangle testRect;
		Rectangle testRect2;

		Vector2Int grid {
			10,
			20,
		};

		Vector2Int shape1[3]{
			(0, 0),
			(1, 0),
			(2, 0),
		};

		const char* testShape = {
			"dd"
			"dd"
		};

		Rectangle gridX[10];
		Rectangle gridY[20];

		int offsetTestY = 5;
		int offsetTestX = 5;

		void Start() {
			window.Init(360, 720, L"Tettfis");
		}

		int y = 0;

		void Update() {

			if (y >= 1500) {
				//offsetTestY -= 1;
				y = 0;
			}
			y++;

			if (Input.GetKeyDown(DOWN)) {
				y += 5;
			}

			if (Input.GetKey(DOWN) && testRect.position.y > 0 || Input.GetKey(S) && testRect.position.y > 0) {
				offsetTestY -= 1;
			}
			if (Input.GetKey(UP) && testRect.position.y < window.GetHeight() - testRect.height || Input.GetKey(W) && testRect.position.y < window.GetHeight() - testRect.height) {
				offsetTestY += 1;
			}
			if (Input.GetKey(RIGHT) && testRect.position.x < window.GetWidth() - testRect.width || Input.GetKey(D) && testRect.position.x < window.GetWidth() - testRect.width) {
				offsetTestX += 1;
			}
			if (Input.GetKey(LEFT) && testRect.position.x > 0 || Input.GetKey(A) && testRect.position.x > 0) {
				offsetTestX -= 1;
			}

			testRect.SetSize(window.GetWidth() / grid.x * 1, window.GetHeight() / grid.y);
			testRect.SetPosition(offsetTestX * (window.GetWidth() / grid.x), offsetTestY * (window.GetHeight() / grid.y));

			testRect2.SetSize(window.GetWidth() / grid.x, window.GetHeight() / grid.y);
			testRect2.SetPosition(1 * (window.GetWidth() / grid.x), 3 * (window.GetHeight() / grid.y));

			int i = 1;
			while (i < grid.x) {
				gridX[i].SetPosition(i * (window.GetWidth() / grid.x), 0);
				gridX[i].SetSize(1, window.GetHeight());
				gridX[i].Draw(0x1f1f1f);
				i++;
			}

			int x = 1;
			while (x < grid.y) {
				gridY[x].SetPosition(0, x * (window.GetHeight() / grid.y));
				gridY[x].SetSize(window.GetWidth(), 1);
				gridY[x].Draw(0x1f1f1f);
				x++;
			}

			testRect.Draw(0xffffff);
		}
	};
}