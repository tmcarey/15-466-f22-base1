#include "ICollidable.hpp"

#include "ITickable.hpp"

#include "Entity.hpp"

#include "SpriteGroup.hpp"

struct Plane : ICollidable, ITickable, Entity {
	Plane(
			uint8_t shadowPallette,
			float speed,
			bool *isDown,
			bool *isUp,
			bool *isLeft,
			bool *isRight);

	virtual void OnCollisionEnter(Collision coll) override;

	virtual void Tick(float elapsed) override;

	private:
		SpriteGroup spriteGroup;
		SpriteGroup shadowSpriteGroup;

		glm::vec2 position;

		void UpdatePosition();
		bool *isDown;
		bool *isUp;
		bool *isLeft;
		bool *isRight;
		float speed;
};
