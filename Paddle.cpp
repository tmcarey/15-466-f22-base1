#include "Paddle.hpp"

#include <algorithm>

#include "ITickable.hpp"

Paddle::Paddle(bool *isup, 
		   bool *isdown, 
		   uint8_t column,
		   uint8_t margin,
		   float speed,
		   PlayMode *playMode,
		   uint8_t noSwingTile, 
		   uint8_t swingTile) {
	this->isup = isup;
	this->isdown = isdown;
	this->playMode = playMode;
	this->sprite = playMode->assetManager->getNextSprite();
	this->noSwingTile = noSwingTile;
	this->swingTile = swingTile;
	this->column = column;
	this->margin = margin;
	this->speed = speed;
	sprite->x = column;
	sprite->y = margin;
	sprite->attributes = 0;
	sprite->index = noSwingTile;
	playMode->RegisterTickable(this);
	position = glm::vec2((float)column, (float)margin);
}

void Paddle::Tick(float elapsed){
	if(*isdown){
		position.y = std::max(sprite->x - speed * elapsed, (float)margin);
	}else if(*isup){
		position.y = std::min(sprite->x + speed * elapsed, 256 - (float)margin);
	}

	sprite->x = (uint8_t)position.x;
	sprite->y = (uint8_t)position.y;
}
