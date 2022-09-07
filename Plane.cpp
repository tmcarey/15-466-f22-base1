#include "Plane.hpp"

#include "PlayMode.hpp"

#include "ITickable.hpp"

float Plane::FIRE_TIME = 2.0f;

Plane::Plane(
		uint8_t redPallette,
		uint8_t shadowPallette,
		float speed,
		bool *isSpace,
		bool *isDown,
		bool *isUp,
		bool *isLeft,
	bool *isRight) : ITickable(), ICollidable(), Entity(), isDown(isDown), isUp(isUp), isLeft(isLeft), isRight(isRight), speed(speed), isSpace(isSpace) {
	std::vector<std::pair<uint8_t, uint8_t>> tiles;
	tiles.push_back(std::pair<uint8_t, uint8_t>((uint8_t)2, (uint8_t)15));
	tiles.push_back(std::pair<uint8_t, uint8_t>((uint8_t)2, (uint8_t)14));
	tiles.push_back(std::pair<uint8_t, uint8_t>((uint8_t)2, (uint8_t)13));
	tiles.push_back(std::pair<uint8_t, uint8_t>((uint8_t)2, (uint8_t)12));
	tiles.push_back(std::pair<uint8_t, uint8_t>((uint8_t)0, (uint8_t)14));
	tiles.push_back(std::pair<uint8_t, uint8_t>((uint8_t)1, (uint8_t)14));
	tiles.push_back(std::pair<uint8_t, uint8_t>((uint8_t)3, (uint8_t)14));
	tiles.push_back(std::pair<uint8_t, uint8_t>((uint8_t)4, (uint8_t)14));
	std::pair<uint8_t, uint8_t> anchorPoint((uint8_t)2,(uint8_t)15);
	shadowSpriteGroup = SpriteGroup(tiles, anchorPoint);
	shadowSpriteGroup.OverridePallette(shadowPallette);
	spriteGroup = SpriteGroup(tiles,anchorPoint);
	timeSinceFire = FIRE_TIME;

	
	position = glm::vec2(100,100);
}

void Plane::Tick(float elapsed) {
	if(*isUp){
		position.y += speed * elapsed;
	}
	if(*isDown){
		position.y -= speed * elapsed;
	}
	if(*isRight){
		spriteGroup.SetOffset(5);
		shadowSpriteGroup.SetOffset(5);
		position.x += speed * elapsed;
	}
	if(*isLeft){
		spriteGroup.SetOffset(10);
		shadowSpriteGroup.SetOffset(10);
		position.x -= speed * elapsed;
	}
	if(!(*isRight) && !(*isLeft)){
		spriteGroup.SetOffset(0);
		shadowSpriteGroup.SetOffset(0);
	}
	if(*isSpace && !lastSpace && timeSinceFire >= FIRE_TIME){
		PlayMode::Instance->FireBullet(position + glm::vec2(16, 0), glm::vec2(0, 1), 120.0f, ICollidable::LAYER::PLAYER);
		PlayMode::Instance->FireBullet(position - glm::vec2(16, 0), glm::vec2(0, 1), 120.0f, ICollidable::LAYER::PLAYER);
		timeSinceFire = 0.0f;
	}
	if(timeSinceFire < FIRE_TIME){
		timeSinceFire += elapsed;
	}
	spriteGroup.DrawAt(position);
	shadowSpriteGroup.DrawAt(position + glm::vec2(13, -13));
	lastSpace = *isSpace;
}

void Plane::OnCollisionEnter(Collision coll){
}
