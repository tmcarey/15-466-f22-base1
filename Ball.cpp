#include "Ball.hpp"

#include "Util.hpp"

Ball::Ball(
		uint8_t tile,
		uint8_t pallette,
		float speed,
		PPU466::Sprite *sprite) : sprite(sprite), 
					  speed(speed), 
					  position(PPU466::ScreenHeight / 2, PPU466::ScreenWidth / 2),
					  velocity(Util::SampleUnitCircle() * speed) {
	sprite->index = tile;
	sprite->attributes = pallette;
	sprite->x = uint8_t(position.x);
	sprite->y = uint8_t(position.y);
}

Rect Ball::GetRect() {
	return Rect(position, position + glm::vec2(8, 8));
}

void Ball::Tick(float elapsed){
	position += velocity * elapsed;

	if(position.x <= 0){
		position.x = 0;
		velocity = glm::reflect(velocity, glm::vec2(1.0, 0.0f));
	}else if(position.y <= 0){
		position.y = 0;
		velocity = glm::reflect(velocity, glm::vec2(0.0, 1.0f));
	}else if(position.x >= PPU466::ScreenWidth - 8){
		position.x = PPU466::ScreenWidth - 8;
		velocity = glm::reflect(velocity, glm::vec2(-1.0, 0.0f));
	}else if(position.y >= PPU466::ScreenHeight - 8){
		position.y = PPU466::ScreenHeight - 8;
		velocity = glm::reflect(velocity, glm::vec2(0.0, -1.0f));
	}

	sprite->x = uint8_t(position.x);
	sprite->y = uint8_t(position.y);
}
