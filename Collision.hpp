#include "glm/glm.hpp"

#include "Ball.hpp"

struct Collision {
	static bool RectRectCollide(Rect a, Rect b, glm::vec2 *resolver);
};
