#include "AssetManager.hpp"

#include "load_save_png.hpp"

#include <stdexcept>

#include <algorithm>

AssetManager::AssetManager(PPU466 *_ppu) : pallettes() {
	ppu = _ppu;
}

int findColor(glm::u8vec4 color){
	glm::vec4 COLOR_0(0,0,0,1);
	glm::vec4 COLOR_1(1,0,0,1);
	glm::vec4 COLOR_2(0,1,0,1);
	glm::vec4 COLOR_3(0,0,1,1);

	if(color.x == 255){
		return 1;
	}else if(color.y == 255){
		return 2;
	}else if(color.z == 255){
		return 3;
	}
	return 0;
}

PPU466::Sprite *AssetManager::getNextSprite(){
	return &(ppu->sprites[spriteCount++]);
}

bool CompareWithForgiveness(glm::u8vec4 a, glm::u8vec4 b){
	return 
		(std::abs(a.x - b.x) < 10 &&
		std::abs(a.y - b.y) < 10 &&
		std::abs(a.z - b.z) < 10 &&
		std::abs(a.w - b.w) < 10) || 
		(a.w == 0 && b.w == 0);

}

void AssetManager::fillNextBackgroundLine(){
	if(lastLine == nullptr){
		lastLine = &(ppu->background[ppu->BackgroundWidth * (ppu->BackgroundHeight - 1)]);
		lastLineIndex = ppu->BackgroundHeight - 1;
	}

	uint16_t nextLineIdx;
	uint16_t *nextLine;
	if(lastLineIndex == ppu->BackgroundHeight - 1){
		nextLine = &ppu->background[0];
		nextLineIdx = 0;
	}else{
		nextLine = lastLine + ppu->BackgroundWidth;
		nextLineIdx = lastLineIndex + 1;
	}

	for(uint16_t i = 0; i < ppu->BackgroundWidth; i++){
		std::pair<uint8_t, uint8_t> backgroundTile = backgroundTiles[Util::RandomUpTo((int)backgroundTiles.size())];
		std::pair<uint8_t, uint8_t> tileInfo = tilemap[backgroundTile.first][backgroundTile.second];
		nextLine[i] =(tileInfo.second << 8) | tileInfo.first;
	}

	lastLine = nextLine;
	lastLineIndex = nextLineIdx;
}

void AssetManager::loadTileMap(std::string path){
	glm::uvec2 size;

	std::vector<glm::u8vec4> data;

	load_png(path, &size, &data, LowerLeftOrigin);

	glm::u8vec4 colorI = data[15 * 8 * 128 + 20];

	for(uint8_t i = 0; i < 16; i++){
		for(uint8_t j = 0; j < 16; j++){
			std::vector<std::pair<glm::u8vec4, uint8_t>> colors;
			for (uint8_t y = 0; y < 8; y++){
				for (uint8_t x = 0; x < 8; x++){
					glm::u8vec4 color = data[(((i * 8) + y) * 128) + ((j * 8) + x)];
					if(find_if(colors.begin(), colors.end(), [color] (std::pair<glm::u8vec4, uint8_t> pair) { return CompareWithForgiveness(color, pair.first); }) == colors.end()){
						if(colors.size() >= 4){
							colors.push_back(std::pair<glm::u8vec4, uint8_t>(color, uint8_t(3)));
						}else{
							colors.push_back(std::pair<glm::u8vec4, uint8_t>(color, uint8_t(colors.size())));
						}
					}
				}
			}
			uint8_t palletteIdx = 0;
			bool did_replace = false;
			for (auto it = pallettes.begin(); it < pallettes.end(); it++){
				bool is_subset = true;
				for (auto color_it = colors.begin(); color_it != colors.end(); color_it++){
					glm::u8vec4 color = color_it->first;
					if(find_if(it->begin(), it->end(), [color] (std::pair<glm::u8vec4, uint8_t> pair) { return CompareWithForgiveness(color, pair.first); }) == it->end()){
						is_subset = false;
						break;
					}
				}
				if(is_subset){
					colors = *it;
					did_replace = true;
					break;
				}
				palletteIdx++;
			}
			if(!did_replace){
				if(palletteCount < 7){
					for (auto color_it = colors.begin(); color_it != colors.end(); color_it++){
						ppu->palette_table[palletteCount][color_it->second] = color_it->first;
					}
					pallettes.push_back(colors);
					palletteIdx = palletteCount;
					palletteCount++;
				}
			}
			for (uint8_t y = 0; y < 8; y++){
				uint8_t val0 = 0;
				uint8_t val1 = 0;
				for (uint8_t x = 0; x < 8; x++){
					glm::u8vec4 color = data[(((i * 8) + y) * 128) + ((j * 8) + x)];
					uint8_t colorIdx = find_if(colors.begin(), colors.end(), [color] (std::pair<glm::u8vec4, uint8_t> pair) { return CompareWithForgiveness(color, pair.first); })->second;
					val0 |= (colorIdx % 2) << x;
					val1 |= ((colorIdx >> 1) % 2) << x;
				}
				ppu->tile_table[tileCount].bit0[y] = val0;
				ppu->tile_table[tileCount].bit1[y] = val1;
			}
			tilemap[j][i] = std::pair<uint8_t, uint8_t>(tileCount, palletteIdx);
			tileCount++;
		}
	}

	int idx = 0;
	printf("Pallettes:\n");
	for(auto it = pallettes.begin(); it < pallettes.end(); it++){
		printf("pallette %d:\n", idx++);
		for(auto it2 = it->begin(); it2 != it->end(); it2++){
			printf("Color: %d, %d, %d, %d\n", it2->first.x,it2->first.y,it2->first.z,it2->first.w);
		}
	}
}


void AssetManager::clearRemainingSprites(){
	for(uint8_t i = spriteCount; i < 64; i++){
		ppu->sprites[i].y = 250;
	}
}

uint8_t AssetManager::addPallette(std::array<glm::vec4, 4> colors){
	std::vector<std::pair<glm::u8vec4, uint8_t>> pallette;
	for(uint8_t i = 0; i < 4; i++){
		ppu->palette_table[palletteCount][i] = colors[i];
		pallette.push_back(std::pair<glm::u8vec4, uint8_t>(colors[i], i));
	}
	pallettes.push_back(pallette);
	return palletteCount++;
}
