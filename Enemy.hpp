#include "ITickable.hpp"

#include "ICollidable.hpp"

#include "Entity.hpp"

struct Enemy : ITickable, ICollidable, Entity {
	Enemy(uint8_t spriteId, uint8_t pallette, PPU466::Sprite *sprite, float speed, float startColumn);

	virtual void OnCollisionEnter(Collision coll) override;
	virtual void Tick(float elapsed) override;
	virtual Rect GetRect() override;

	private:
		PPU466::Sprite *sprite;
		float speed;
		glm::vec2 position;
};
