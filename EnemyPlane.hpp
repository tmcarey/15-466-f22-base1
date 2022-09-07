#include "ICollidable.hpp"
#include "ITickable.hpp"
#include "Entity.hpp"
#include "SpriteGroup.hpp"

struct EnemyPlane : ICollidable, ITickable, Entity {
	EnemyPlane();

	virtual void Tick(float elapsed) override;
	virtual void OnCollisionEnter(Collision coll) override;
	virtual Rect GetRect() override;
	
	private:
		SpriteGroup planeGroup;
		glm::vec2 position;
		glm::vec2 velocity;
		float time = 0;
		bool isAlive = false;
};
