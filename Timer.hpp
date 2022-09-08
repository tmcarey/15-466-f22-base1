#pragma once

#include "ITickable.hpp"

#include "SpriteGroup.hpp"

struct Timer : ITickable {
	Timer(glm::vec2 position);
	virtual void Tick(float elapsed) override;
	float getTimeRemaining();

	private:
		glm::vec2 position;
		float totalTime;
		SpriteGroup digit1;
		SpriteGroup digit2;
};
