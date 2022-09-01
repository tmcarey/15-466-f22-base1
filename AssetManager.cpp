#include "AssetManager.hpp"

#include "load_save_png.hpp"

#include <stdexcept>

AssetManager::AssetManager(PPU466 *_ppu){
	ppu = _ppu;
}

int findColor(std::array<glm::u8vec4, 4> colorArr, glm::u8vec4 color){
	for (int it = 0; it < colorArr.size(); it++){
		if(colorArr[it] == color){
			return it;
		}
	}
	return -1;
}

PPU466::Sprite *AssetManager::getNextSprite(){
	return &(ppu->sprites[spriteCount++]);
}

uint8_t AssetManager::loadTile(std::string path){
	glm::uvec2 size;
	std::vector<glm::u8vec4> data;
	uint8_t colorCount = 0;
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
		ppu->tile_table[tileCount].bit0[y] = val0;
		ppu->tile_table[tileCount].bit1[y] = val1;
		printf("running\n");
	}
	for(int i = 0; i < 2; i++){
		ppu->palette_table[palletteCount][i] = colors[i];
	}
	printf("%p\n", &(ppu));
	return tileCount++;
}

