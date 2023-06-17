#pragma once

#include "renderer.h"
#include "maths.h"

namespace GameEngine {
	class Rectangle {

	public:
		float width;
		float height;

		float left;
		float right;
		float top;
		float bottom;

		Vector2 position;

		void SetPosition(float x, float y)
		{
			this->position.x = x;
			this->position.y = y;

			this->left = position.x;
			this->right = position.x + this->width;
			this->top = position.y + this->height;
			this->bottom = position.y;
		}

		void SetX(float x)
		{
			this->position.x = x;

			this->left = position.x;
			this->right = position.x + this->width;
		}

		void SetY(float y)
		{
			this->position.y = y;

			this->top = position.y + this->height;
			this->bottom = position.y;
		}

		void SetSize(float width, float height)
		{
			this->width = width;
			this->height = height;

			this->right = position.x + this->width;
			this->top = position.y + this->height;
		}

		void SetWidth(float width)
		{
			this->width = width;

			this->right = position.x + this->width;
		}

		void SetHeight(float height)
		{
			this->height = height;

			this->top = position.y + this->height;
		}

		void Draw(unsigned int color)
		{
			Renderer::DrawRectPixels(this->position.x, this->position.y, this->width, this->height, color);
		}
	};

	class Line {
	public:
		Vector2 a;

		Vector2 b;

		void SetPoints(Vector2 a, Vector2 b)
		{
			this->a = a;
			this->b = b;
		}

		void SetPoints(int x0, int y0, int x1, int y1)
		{
			this->a.x = x0;
			this->a.y = y0;

			this->b.x = x1;
			this->b.y = y1;
		}

		void Draw(unsigned int color)
		{
			Renderer::DrawLine(this->a.x, this->a.y, this->b.x, this->b.y, color);
		}
	};
}