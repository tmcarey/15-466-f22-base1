#pragma once

#include <cstdint>
#include <utility>
#include <vector>

#include "PPU466.hpp"

#include "glm/glm.hpp"

typedef std::pair<uint8_t, uint8_t> intPair;

struct SpriteGroup{
	SpriteGroup(std::vector<std::pair<uint8_t, uint8_t>> tileCoords, std::pair<uint8_t, uint8_t> anchorPoint);
	SpriteGroup() {};

	void OverridePallette(uint8_t pallette);

	void DrawAt(glm::vec2 position);
	void SetOffset(uint8_t offset);
	void Hide();
	void ResetPallette();

	static intPair IntPair(int i, int j) {
		return intPair(uint8_t(i), uint8_t(j));
	}

	private:
		std::vector<std::pair<uint8_t, uint8_t>> tileCoords;
		std::vector<std::pair<PPU466::Sprite *, intPair>> sprites;
		std::pair<uint8_t, uint8_t> anchorPoint;
		uint8_t offset;
};
