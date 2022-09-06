#pragma once

#include "glm/glm.hpp"

#include "Ball.hpp"

struct Collision {
	Collision(Ball *ball) : ball(ball) {};
	Ball *ball;
	static bool RectRectCollide(Rect a, Rect b);
};
