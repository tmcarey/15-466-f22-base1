#pragma once

#include "PPU466.hpp"

#include "ITickable.hpp"

#include "Rect.hpp"

#include "Entity.hpp"

struct Ball : ITickable, Entity {
	Ball(uint8_t tile,
		uint8_t pallette,
		float speed,
		PPU466::Sprite *sprite
		);


	virtual void Tick(float elapsed) override;
	Rect GetRect();
	glm::vec2 position;
	glm::vec2 velocity;

	private:
		float speed;
		PPU466::Sprite *sprite;
};
