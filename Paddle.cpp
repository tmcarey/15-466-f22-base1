#include "Paddle.hpp"

#include <algorithm>

#include "ITickable.hpp"

Paddle::Paddle(bool *isup, 
		   bool *isdown, 
		   uint8_t column,
		   uint8_t margin,
		   float speed,
		   uint8_t pallette,
		   PPU466::Sprite *sprite,
		   uint8_t noSwingTile, 
		   uint8_t swingTile) {
	this->isup = isup;
	this->isdown = isdown;
	this->sprite = sprite;
	this->noSwingTile = noSwingTile;
	this->swingTile = swingTile;
	this->column = column;
	this->margin = margin;
	this->speed = speed;
	sprite->attributes = pallette;
	sprite->index = noSwingTile;
	position = glm::vec2((float)column, (float)margin);
	sprite->x = column;
	sprite->y = margin;
}

Rect Paddle::GetRect(){
	return Rect(position, position + glm::vec2(8,8));
}

void Paddle::OnCollisionEnter(Collision coll){
	printf("Entering\n");
}

void Paddle::OnCollisionExit(Collision coll){
	printf("Exiting\n");
}

void Paddle::Tick(float elapsed){
	if(*isdown){
		position.y = std::max(position.y - (speed * elapsed), (float)margin);
	}else if(*isup){
		position.y = std::min(position.y + (speed * elapsed), PPU466::ScreenHeight - 8 - (float)margin);
	}

	sprite->x = uint8_t(position.x);
	sprite->y = uint8_t(position.y);
}
