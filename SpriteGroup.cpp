#include "SpriteGroup.hpp"

#include "PlayMode.hpp"

void SpriteGroup::Hide(){
	for(int i = 0; i < sprites.size(); i++){
		sprites[i].first->x =0;
		sprites[i].first->y = PPU466::ScreenHeight;
	}
}

SpriteGroup::SpriteGroup(std::vector<std::pair<uint8_t, uint8_t>> tileCoords, std::pair<uint8_t, uint8_t> anchorPoint) : tileCoords(tileCoords), sprites(), anchorPoint(anchorPoint), offset(0)  {
	for(auto it = tileCoords.begin(); it < tileCoords.end(); it++){
		PPU466::Sprite *sprite = PlayMode::Instance->assetManager->getNextSprite();
		std::pair<uint8_t, uint8_t> tileInfo = PlayMode::Instance->assetManager->tilemap[it->first][it->second];
		sprite->index = tileInfo.first;
		sprite->attributes = tileInfo.second;

		sprites.push_back(std::pair<PPU466::Sprite*, intPair>(sprite, IntPair(tileInfo.first, tileInfo.second)));
	}
}

void SpriteGroup::OverridePallette(uint8_t pallette){
	for(auto it = sprites.begin(); it < sprites.end(); it++){
		it->first->attributes = pallette;
	}
}

void SpriteGroup::ResetPallette(){
	for(auto it = sprites.begin(); it < sprites.end(); it++){
		it->first->attributes = it->second.second;
	}
}

void SpriteGroup::DrawAt(glm::vec2 position){
	for(int i = 0; i < sprites.size(); i++){
		sprites[i].first->x = uint8_t(position.x) + (8 * (tileCoords[i].first - tileCoords[0].first));
		sprites[i].first->y = uint8_t(position.y) + (8 * (tileCoords[i].second - tileCoords[0].second));
	}
}

void SpriteGroup::SetOffset(uint8_t _offset){
	if(_offset != this->offset){
		this->offset = _offset;
		for(int i = 0; i < sprites.size(); i++){
			sprites[i].first->index = sprites[i].second.first + offset;
		}
	}
}
