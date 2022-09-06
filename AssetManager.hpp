#pragma once

#include <string>

#include "PPU466.hpp"

struct AssetManager {
	AssetManager(PPU466 *ppu);
	uint8_t loadTile(std::string path);
	uint8_t addPallette(std::array<glm::vec4, 4> colors);
	void clearRemainingSprites();
	PPU466::Sprite *getNextSprite();

	private:
		uint8_t tileCount = 0;
		uint8_t palletteCount = 0;
		uint8_t spriteCount = 0;
		PPU466 *ppu;
};
