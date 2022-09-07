#include "Projectile.hpp"

#include "PlayMode.hpp"

Projectile::Projectile(
			) {

	explosionGroup = SpriteGroup({
				SpriteGroup::IntPair(0,0)
			},
			SpriteGroup::IntPair(0, 0));

	position = glm::vec2(0, PPU466::ScreenHeight);
	explosionGroup.DrawAt(glm::vec2(0, PPU466::ScreenHeight));
	bullet = PlayMode::Instance->assetManager->getNextSprite();
	shouldDie = false;
	isExplosionOver = true;
}

void Projectile::FireAt(glm::vec2 _position, glm::vec2 _direction, float _speed, ICollidable::LAYER _layer){
	isExplosionOver = false;
	timeSinceFire = 0.0f;
	shouldDie = false;
	this->layer = _layer;

	isFiring = true;

	this->position = _position;
	this->speed = _speed;
	this->direction = _direction;

	bullet->x = uint8_t(_position.x);
	bullet->y = uint8_t(_position.y);

	explosionGroup.DrawAt(_position);
}

void Projectile::Tick(float elapsed){
	if(isFiring){
		position += direction * speed * elapsed;
	}

	if(!isExplosionOver && timeSinceFire > 0.5f){
		explosionGroup.DrawAt(glm::vec2(0, PPU466::ScreenHeight));
		isExplosionOver = true;
	}else if(!isExplosionOver){
		timeSinceFire += elapsed;
	}


	if(shouldDie || position.y < 0 || position.y > PPU466::ScreenHeight){
		isFiring = false;
		position = glm::vec2(0, PPU466::ScreenHeight);
	}

	bullet->x = uint8_t(position.x);
	bullet->y = uint8_t(position.y);

}

void Projectile::OnCollisionEnter(Collision coll){
	shouldDie = true;
}
