#pragma once

#include "PPU466.hpp"

#include "ITickable.hpp"

#include "PlayMode.hpp"

#include "Rect.hpp"

struct Ball : ITickable, Entity {
	Ball(uint8_t tile,
		uint8_t pallette,
		float speed,
		PlayMode *playMode,
		PPU466::Sprite *sprite
		);


	virtual void Tick(float elapsed) override;
	Rect rect;

	private:
		glm::vec2 position;
		glm::vec2 velocity;
		float speed;
		PPU466::Sprite *sprite;
};
