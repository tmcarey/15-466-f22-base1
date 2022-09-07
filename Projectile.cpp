#include "Projectile.hpp"

#include "PlayMode.hpp"

Projectile::Projectile(
			) {

	explosionGroup = SpriteGroup({
				SpriteGroup::IntPair(0,5)
			},
			SpriteGroup::IntPair(0, 5));
	projectileGroup = SpriteGroup({
				SpriteGroup::IntPair(13,1)
			},
			SpriteGroup::IntPair(13, 1));

	position = glm::vec2(0, PPU466::ScreenHeight);
	explosionGroup.DrawAt(glm::vec2(0, PPU466::ScreenHeight));
	shouldDie = false;
	isExplosionOver = true;
}

Rect Projectile::GetRect(){
	return Rect(position, position + glm::vec2(8,8));
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


	projectileGroup.DrawAt(_position);
	explosionGroup.DrawAt(_position);
	if(_direction.y < 0){
		explosionGroup.SetOffset(1);
	}else{
		explosionGroup.SetOffset(0);
	}
}

void Projectile::Tick(float elapsed){
	if(isFiring){
		position += direction * speed * elapsed;
	}

	if(!isExplosionOver && timeSinceFire > 0.1f){
		explosionGroup.DrawAt(glm::vec2(0, PPU466::ScreenHeight));
		isExplosionOver = true;
	}else if(!isExplosionOver){
		timeSinceFire += elapsed;
	}


	if(shouldDie || position.y < 0 || position.y > PPU466::ScreenHeight){
		isFiring = false;
		position = glm::vec2(0, PPU466::ScreenHeight);
	}

	projectileGroup.DrawAt(position);
}

void Projectile::OnCollisionEnter(Collision coll){
	if(coll.collider->layer != DISABLED){
		shouldDie = true;
	}
}
