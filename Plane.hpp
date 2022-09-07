#pragma once

#include "ICollidable.hpp"

#include "ITickable.hpp"

#include "Entity.hpp"

#include "SpriteGroup.hpp"

struct Plane : ICollidable, ITickable, Entity {
	Plane(
			uint8_t redPallette,
			uint8_t shadowPallette,
			float speed,
			bool *isSpace,
			bool *isDown,
			bool *isUp,
			bool *isLeft,
			bool *isRight);

	virtual void OnCollisionEnter(Collision coll) override;

	virtual void Tick(float elapsed) override;
	virtual Rect GetRect() override;

	private:
		SpriteGroup spriteGroup;
		SpriteGroup shadowSpriteGroup;

		glm::vec2 position;

		void UpdatePosition();
		bool lastSpace;
		bool *isSpace;
		bool *isDown;
		bool *isUp;
		bool *isLeft;
		bool *isRight;
		float speed;
		int healthPoints;
		float timeSinceHit;
		bool isRed;

		bool isAlive =  true;

		static float FIRE_TIME;
		float timeSinceFire;
};
