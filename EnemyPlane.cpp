#include "EnemyPlane.hpp"

#include "PlayMode.hpp"

EnemyPlane::EnemyPlane(SpriteGroup group, uint8_t redPallette) : redPallette(redPallette) {
	planeGroup = group;
	velocity = glm::vec2(0, 0);
}

Rect EnemyPlane::GetRect(){
	return Rect(position + glm::vec2(-8.0f, -8.0f), position + glm::vec2(16.0f, 8.0f));
}

void EnemyPlane::SpawnAt(glm::vec2 _position, int hitPoints_, float speed_, float fireRate_){
	if(!isAlive){
		PlayMode::Instance->planesCurrentlyAlive++;
	}
	this->hitPoints = hitPoints_;
	this->speed = speed_;
	this->fireRate = fireRate_;
	layer = ICollidable::ENEMY;
	position = _position;
	isAlive = true;
}

void EnemyPlane::Tick(float elapsed){
	if(!isAlive)
		return;

	if(timeSinceShot >= (2.0f / fireRate)){
		PlayMode::Instance->FireBullet(position + glm::vec2(0, -26), glm::vec2(0, -1), 90.0f, ENEMY);
		timeSinceShot = 0.0f;
	}else{
		timeSinceShot += elapsed;
	}

	if(isRed){
		timeSinceHit += elapsed;
		if(timeSinceHit > 0.3f){
			planeGroup.ResetPallette();
			isRed = false;
		}
	}

	time += elapsed;
	velocity = glm::vec2(std::sin(time), 0) * 30.0f * speed;

	position += velocity * elapsed;

	if(velocity.x > 0){
		planeGroup.SetOffset(3);
	}else if(velocity.x < 0){
		planeGroup.SetOffset(6);
	}else if(velocity.x == 0){
		planeGroup.SetOffset(0);
	}

	planeGroup.DrawAt(position);
}

void EnemyPlane::OnCollisionEnter(Collision coll){
	if(!isAlive)
		return;

	if(isAlive && coll.collider->layer == ICollidable::LAYER::PLAYER){
		hitPoints--;
		isRed = true;
		planeGroup.OverridePallette(redPallette);
		timeSinceHit = 0.0f;
	}
	if(hitPoints <= 0){
		isAlive = false;
		if(!isAlive){
			PlayMode::Instance->planesCurrentlyAlive--;
		}
		PlayMode::Instance->DoExplosion(position + glm::vec2(0, -20));
		planeGroup.Hide();
		layer = ICollidable::DISABLED;
	}
}
