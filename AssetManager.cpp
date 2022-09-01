#include "AssetManager.hpp"

#include "load_save_png.hpp"

#include <stdexcept>

AssetManager::AssetManager(PPU466 ppu){
	this->ppu = ppu;
}

int findColor(std::array<glm::u8vec4, 4> colorArr, glm::u8vec4 color){
	for (int it = 0; it < colorArr.size(); it++){
		if(colorArr[it] == color){
			return it;
		}
	}
	return -1;
}

int AssetManager::loadTile(std::string path){
	glm::uvec2 size;
	std::vector<glm::u8vec4> data;
	std::array<uint8_t, 8> bit0 = { };
	std::array<uint8_t, 8> bit1 = { };
	int colorCount = 0;
	std::array<glm::u8vec4, 4> colors = { };

	load_png(path, &size, &data, LowerLeftOrigin);
	if(size.x != 8 || size.y != 8){
		printf("Wrong size of image %s", path.c_str());
		throw std::invalid_argument("Failed to load image");
	}
	for (uint8_t y = 0; y < 8; y++){
		uint8_t val0 = 0;
		uint8_t val1 = 0;
		for (uint8_t x = 0; x < 8; x++){
			glm::u8vec4 color = data[x + (y * 8)];
			int colorIdx = findColor(colors, color);
			if(colorIdx == -1){
				if(colorCount == 4){
					printf("Too many colors in %s", path.c_str());
					throw std::invalid_argument("Failed to load image");
				}
				colors[colorCount] = color;
				colorIdx = colorCount++;
			}
			val0 |= (colorIdx % 2) << y;
			val1 |= ((colorIdx >> 1) % 2) << y;
		}
		bit0[y] = val0;
		bit1[y] = val1;
	}
	ppu.palette_table[palletteCount] = colors;
	printf("%d, %d, %d\n", colors[0].x, colors[0].y, colors[0].z);

	ppu.tile_table[tileCount].bit0 = bit0;
	ppu.tile_table[tileCount].bit1 = bit1;
	printf("%d\n", ppu.tile_table[0].bit0[0]);
	return tileCount++;
}

