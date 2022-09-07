#pragma once

#include "Entity.hpp"
#include "ICollidable.hpp"
#include "ITickable.hpp"
#include "SpriteGroup.hpp"

struct Projectile : Entity, ICollidable, ITickable {
	Projectile();
	~Projectile(){};

	virtual void FireAt(glm::vec2 position, glm::vec2 direction, float speed, ICollidable::LAYER layer);
	virtual void OnCollisionEnter(Collision coll) override;
	virtual void Tick(float e) override;
	virtual Rect GetRect() override;

	private:
		SpriteGroup explosionGroup;
		SpriteGroup projectileGroup;
		bool isFiring;
		glm::vec2 direction;
		glm::vec2 position;
		float speed;
		bool shouldDie;
		bool isExplosionOver;
		float timeSinceFire;
};
