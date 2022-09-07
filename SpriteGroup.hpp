#include <cstdint>
#include <utility>
#include <vector>

#include "PPU466.hpp"

#include "glm/glm.hpp"

struct SpriteGroup{
	SpriteGroup(std::vector<std::pair<uint8_t, uint8_t>> tileCoords, std::pair<uint8_t, uint8_t> anchorPoint);
	SpriteGroup() {};

	void OverridePallette(uint8_t pallette);

	void DrawAt(glm::vec2 position);
	void SetOffset(uint8_t offset);

	private:
		std::vector<std::pair<uint8_t, uint8_t>> tileCoords;
		std::vector<std::pair<PPU466::Sprite *, uint8_t>> sprites;
		std::pair<uint8_t, uint8_t> anchorPoint;
		uint8_t offset;
};
