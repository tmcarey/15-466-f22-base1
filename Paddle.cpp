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
		   uint8_t topTile, 
		   uint8_t centerTile, 
		   uint8_t bottomTile) {
	this->isup = isup;
	this->isdown = isdown;
	this->sprites = sprite;
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
	Rect ourRect = GetRect();
	Rect otherRect = coll.ball->GetRect();
	float minGap = 1000;
	glm::vec2 resolver(0);
	float right = ourRect.topRight.x - otherRect.bottomLeft.x;
	if(right < minGap){
		resolver = glm::vec2(right, 0);
		minGap = right;
	}
	float left = otherRect.topRight.x - ourRect.bottomLeft.x;
	if(left < minGap){
		resolver = glm::vec2(-left, 0);
		minGap = left;
	}
	float up = ourRect.topRight.y - otherRect.bottomLeft.y;
	if(up < minGap){
		resolver = glm::vec2(0, up);
		minGap = up;
	}
	float down = otherRect.topRight.y - ourRect.bottomLeft.y;
	if(down < minGap){
		resolver = glm::vec2(0, -down);
		minGap = down;
	}
	coll.ball->position += resolver;
	coll.ball->velocity = glm::reflect(coll.ball->velocity, glm::normalize(resolver));
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

	sprites->x = uint8_t(position.x);
	sprites->y = uint8_t(position.y);
}
