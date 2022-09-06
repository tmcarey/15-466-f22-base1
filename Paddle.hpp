#include "ITickable.hpp"

#include "PlayMode.hpp"

#include "PPU466.hpp"
#include <cstdint>
#include "ICollidable.hpp"

struct Paddle : ITickable, ICollidable, Entity {
	Paddle(bool *isup, 
		   bool *isdown, 
		   uint8_t column,
		   uint8_t margin,
		   float speed,
		   uint8_t pallette,
		   PPU466::Sprite *sprite,
		   uint8_t noSwingTile, 
		   uint8_t swingTile);

	virtual void Tick(float elapsed) override;
	virtual void OnCollisionEnter(Collision coll) override;
	virtual void OnCollisionExit(Collision coll) override;
	virtual Rect GetRect() override;

	private:
		bool *isup;
		bool *isdown;
		uint8_t column;
		uint8_t margin;
		float speed;
		PPU466::Sprite *sprite;
		uint8_t noSwingTile;
		uint8_t swingTile;
		glm::vec2 position;
};
