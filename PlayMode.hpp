#pragma once

#include "PPU466.hpp"
#include "Mode.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

#include "AssetManager.hpp"

#include "ITickable.hpp"

#include "Entity.hpp"

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	AssetManager *assetManager;

	void RegisterTickable(ITickable *tickable);

	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		bool pressed = false;
	} up1, up2, down1, down2;

	//some weird background animation:
	float background_fade = 0.0f;

	//player position:
	glm::vec2 player_at = glm::vec2(0.0f);

	//----- drawing handled by PPU466 -----

	PPU466 ppu;

	std::vector<ITickable*> tickers;
	std::vector<Entity*> entities;
};
