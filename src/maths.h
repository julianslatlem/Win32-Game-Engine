#pragma once

#define CENTER 0
#define BOTTOM_LEFT 1
#define BOTTOM_CENTER 2
#define BOTTOM_RIGHT 3
#define CENTER_LEFT 4
#define CENTER_RIGHT 5
#define TOP_LEFT 6
#define TOP_CENTER 7
#define TOP_RIGHT 8

class Vector2 {
public:
	float x;
	float y;
};

class Vector2Int {
public:
	int x;
	int y;
};

class Vector3Int {
public:
	int x;
	int y;
	int z;
};

namespace GameEngine {


	int Add(int x, int y)
	{
		return x + y;
	}

	inline int Clamp(int min, int val, int max)
	{
		if (val < min) return min;
		if (val > max) return max;
		return val;
	}
}