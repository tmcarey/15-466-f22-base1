#include "Enemy.hpp"

#include <algorithm>

#include "ITickable.hpp"

Enemy::Enemy(uint8_t tile,
		uint8_t pallette,
	   PPU466::Sprite *sprite,
	   float speed,
	   float startColumn) : speed(speed), sprite(sprite), ITickable() {
	sprite->attributes = pallette;
	sprite->index = tile;
	position = glm::vec2((float)startColumn, (float)PPU466::ScreenHeight);
	sprite->x = uint8_t(position.x);
	sprite->y = uint8_t(position.y);
}

Rect Enemy::GetRect(){
	return Rect(position, position + glm::vec2(8,8));
}

void Enemy::OnCollisionEnter(Collision coll){
	position.y = 250;
	printf("Entering\n");
}

void Enemy::Tick(float elapsed){
	position.y -= this->speed * elapsed;

	sprite->x = uint8_t(position.x);
	sprite->y = uint8_t(position.y);
}

