#pragma once

#include <string>

#include "PPU466.hpp"

#include <unordered_map>
#include <vector>

#include "Util.hpp"

struct AssetManager {
	AssetManager(PPU466 *ppu);
	void loadTileMap(std::string path);
	void fillNextBackgroundLine();
	uint8_t addPallette(std::array<glm::vec4, 4> colors);
	void clearRemainingSprites();
	PPU466::Sprite *getNextSprite();
	std::array<std::array<std::pair<uint8_t, uint8_t>,16>, 16> tilemap;
	std::array<std::pair<uint8_t, uint8_t>, 8> backgroundTiles;
	uint8_t spriteCount = 0;
	
	private:
		uint8_t tileCount = 0;
		uint8_t palletteCount = 0;
		PPU466 *ppu;
		std::vector<std::vector<std::pair<glm::u8vec4, uint8_t>>> pallettes;
		uint16_t *lastLine = nullptr;
		uint16_t lastLineIndex = uint16_t(0);
};
