#include "engine.h"
#include <thread>
#include <chrono>

namespace GameEngine {
	class Game : public Script {
	public:

		Window window;

		Rectangle player1;
		Rectangle player2;
		Rectangle ball;

		Rectangle line;

		int score1;
		int score2;

		Vector2 ballVelocity{
			-5.0f,
			2.0f,
		};

		float player1Y;

		float player1YOffset;

		float player2Y;

		float player2YOffset;

		float getCurrentTime()
		{
			auto now = std::chrono::high_resolution_clock::now();
			auto duration = now.time_since_epoch();
			return std::chrono::duration_cast<std::chrono::microseconds>(duration).count() / 1000000.0f;
		}

		void Start()
		{
			window.Init(1920, 1080, L"Dong");

			player1.SetSize(10, 200);

			player1.SetPosition(20, (window.GetHeight() / 2) - (player1.height / 2));

			player2.SetSize(10, 200);

			player2.position.x = window.GetWidth() - (20 + player2.width / 2);
			player2Y = (window.GetHeight() / 2) - (player2.height / 2);

			ball.SetSize(10, 10);

			ball.SetPosition(window.GetWidth() / 2 - ball.height / 2, window.GetHeight() / 2 - ball.width / 2);
		}

		void Update()
		{
			static const float MAX_FRAME_RATE = 400.0f;
			static const float MIN_FRAME_TIME = 1.0f / MAX_FRAME_RATE;

			static float lastFrameTime = getCurrentTime();

			float currentTime = getCurrentTime();
			float deltaTime = currentTime - lastFrameTime;

			if (deltaTime < MIN_FRAME_TIME) {
				float delayTime = MIN_FRAME_TIME - deltaTime;
				std::chrono::microseconds delayMicros((int)(delayTime * 1000000));
				std::this_thread::sleep_for(delayMicros);
				currentTime = getCurrentTime();
				deltaTime = currentTime - lastFrameTime;
			}

			lastFrameTime = currentTime;

			if (Input.GetKeyDown(W) && player1.position.y < window.GetHeight() - player1.height)
			{
				player1YOffset += 4;
			}
			if (Input.GetKeyDown(S) && player1.position.y > 0)
			{
				player1YOffset -= 4;
			}

			if (Input.GetKeyDown(UP) && player2.position.y < window.GetHeight() - player2.height)
			{
				player2YOffset += 4;
			}
			if (Input.GetKeyDown(DOWN) && player2.position.y > 0)
			{
				player2YOffset -= 4;
			}

			if (ball.position.y >= window.GetHeight() - ball.height || ball.position.y <= 0)
			{
				ballVelocity.y *= -1;
			}

			if (ball.position.x <= 0 + player1.width + ball.width && ball.position.x > 0)
			{
				if (ball.position.y >= player1.position.y && ball.position.y + ball.height < player1.position.y + player1.height)
				{
					ballVelocity.x *= -1;
				}
				else
				{
					ball.position.x = (window.GetWidth() / 2) - (ball.height / 2);
					ball.position.y = (window.GetHeight() / 2) - (ball.width / 2);

					ballVelocity.x *= -1;
					ballVelocity.y *= -1;

					score2++;

					std::cout << "\33[2K\r";

					std::cout << "Player 1: " << score1 << " Player 2: " << score2;
				}
			}

			if (ball.right >= (window.GetWidth() - (window.GetWidth() - player2.position.x)))
			{
				if (ball.position.y >= player2.position.y && ball.top < player2.position.y + player2.height)
				{
					ballVelocity.x *= -1;
				}
				else
				{
					ball.position.x = (window.GetWidth() / 2) - (ball.height / 2);
					ball.position.y = (window.GetHeight() / 2) - (ball.width / 2);

					ballVelocity.x *= -1;
					ballVelocity.y *= -1;

					score1++;

					std::cout << "\33[2K\r";
					std::cout << "Player 1: " << score1 << " Player 2: " << score2;
				}
			}

			player1.SetPosition(20, player1Y + player1YOffset);

			player2.SetPosition(window.GetWidth() - (20 + player2.width / 2), player2Y + player2YOffset);

			ball.SetPosition(ball.position.x + ballVelocity.x, ball.position.y + ballVelocity.y);

			line.SetSize(1, window.GetHeight());
			line.SetPosition(window.GetWidth() / 2 - line.width, 0);

			line.Draw(0xffffff);

			player1.Draw(0xffffff);
			player2.Draw(0xffffff);

			ball.Draw(0xffffff);

			lastFrameTime = currentTime;
		}
	};
}