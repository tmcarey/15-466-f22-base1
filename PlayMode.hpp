#pragma once

#include "PPU466.hpp"
#include "Mode.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

#include "AssetManager.hpp"

#include "ITickable.hpp"
#include "ICollidable.hpp"
#include "Explosion.hpp"

#include "Projectile.hpp"
#include "EnemyPlane.hpp"

#include "Entity.hpp"

struct PlayMode : Mode {
	static PlayMode *Instance;

	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	AssetManager *assetManager;

	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		bool pressed = false;
	} up, down, left, right, space;

	float yScroll = 0.0f;

	//----- drawing handled by PPU466 -----

	PPU466 ppu;

	void FireBullet(glm::vec2 position, glm::vec2 direction, float speed, ICollidable::LAYER layer);
	void DoExplosion(glm::vec2 position);

	std::vector<ITickable*> tickers;
	std::vector<Entity*> entities;
	std::vector<ICollidable*> colliders;
	size_t nextProjectileIdx = 0;
	std::array<Projectile*, 4> projectiles;
	std::array<EnemyPlane*, 2> enemyPlanes;
	Explosion *explosion;
};
