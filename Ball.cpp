#include "Ball.hpp"

#include "Util.hpp"

Ball::Ball(
		uint8_t tile,
		uint8_t pallette,
		float speed,
		PlayMode *playMode,
		PPU466::Sprite *sprite) : sprite(sprite), 
					  speed(speed), 
					  position(PPU466::ScreenHeight / 2, PPU466::ScreenWidth / 2),
					  velocity(Util::SampleUnitCircle() * speed) {
	sprite->index = tile;
	sprite->attributes = pallette;
	sprite->x = uint8_t(position.x);
	sprite->y = uint8_t(position.y);
	playMode->RegisterTickable(this);
	printf("%f, %f\n", velocity.x, velocity.y);
}

void Ball::Tick(float elapsed){
	position += velocity * elapsed;

	if(position.x <= 0){
		position.x = 0;
		velocity = -velocity;
	}else if(position.y <= 0){
		position.y = 0;
		velocity = -velocity;
	}else if(position.x >= PPU466::ScreenWidth - 8){
		position.x = PPU466::ScreenWidth - 8;
		velocity = -velocity;
	}else if(position.y >= PPU466::ScreenHeight - 8){
		position.y = PPU466::ScreenHeight - 8;
		velocity = -velocity;
	}
	

	sprite->x = uint8_t(position.x);
	sprite->y = uint8_t(position.y);
}
