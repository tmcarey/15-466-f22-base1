#pragma once

#include "ICollidable.hpp"
#include "ITickable.hpp"
#include "Entity.hpp"
#include "SpriteGroup.hpp"

struct EnemyPlane : ICollidable, ITickable, Entity {
	EnemyPlane(SpriteGroup group, uint8_t redPallette);

	virtual void Tick(float elapsed) override;
	virtual void OnCollisionEnter(Collision coll) override;
	virtual Rect GetRect() override;
	void SpawnAt(glm::vec2 position);
	
	private:
		uint8_t redPallette;
		SpriteGroup planeGroup;
		glm::vec2 position;
		glm::vec2 velocity;
		float time = 0;
		bool isAlive = false;
		int hitPoints = 3;
		float timeSinceHit = 0;
		float timeSinceShot = 0;
		bool isRed = false;
};
