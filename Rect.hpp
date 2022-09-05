#include "glm/glm.hpp"

struct Rect {
	Rect() : bottomLeft(0), topRight(0) {
		Rect(bottomLeft, topRight);
	}
	Rect(glm::vec2 bl, glm::vec2 tr) : bottomLeft(bl), topRight(tr) {
		center = (bl + tr) / 2.0f;
		width = tr.x - bl.x;
		height = tr.y - bl.y;
	}
	glm::vec2 bottomLeft;
	glm::vec2 topRight;
	glm::vec2 center;
	float width;
	float height;
};
