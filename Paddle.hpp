#include "ITickable.hpp"

#include "PlayMode.hpp"

#include "PPU466.hpp"
#include <cstdint>

struct Paddle : ITickable, Entity {
	Paddle(bool *isup, 
		   bool *isdown, 
		   uint8_t column,
		   uint8_t margin,
		   float speed,
		   uint8_t pallette,
		   PPU466::Sprite *sprite,
		   PlayMode *playMode,
		   uint8_t noSwingTile, 
		   uint8_t swingTile);

	virtual void Tick(float elapsed) override;

	private:
		bool *isup;
		bool *isdown;
		PlayMode *playMode;
		uint8_t column;
		uint8_t margin;
		float speed;
		PPU466::Sprite *sprite;
		uint8_t noSwingTile;
		uint8_t swingTile;
		glm::vec2 position;
};
