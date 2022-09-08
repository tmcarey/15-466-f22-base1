#include "PlayMode.hpp"

//for the GL_ERRORS() macro:
#include "gl_errors.hpp"
#include "load_save_png.hpp"

//for glm::value_ptr() :
#include <glm/gtc/type_ptr.hpp>

#include <random>

#include "Paddle.hpp"

#include "Ball.hpp"

#include "Util.hpp"

PlayMode *PlayMode::Instance;

void PlayMode::DoExplosion(glm::vec2 position){
	explosion->ExplodeAt(position);
}

PlayMode::PlayMode() {

	Instance = this;
	Util::InitRandom();
	assetManager = new AssetManager(&ppu);
	assetManager->backgroundTiles = {
		std::pair<uint8_t, uint8_t>(uint8_t(0), uint8_t(0)), 
		std::pair<uint8_t, uint8_t>(uint8_t(1), uint8_t(0)), 
		std::pair<uint8_t, uint8_t>(uint8_t(2), uint8_t(0)), 
		std::pair<uint8_t, uint8_t>(uint8_t(3), uint8_t(0)), 
		std::pair<uint8_t, uint8_t>(uint8_t(4), uint8_t(0)), 
	};
	uint8_t shadowPallette = assetManager->addPallette({
				glm::vec4(0,0,0,0),
				glm::vec4(0,0,0,255),
				glm::vec4(0,0,0,255),
				glm::vec4(0,0,0,255)
			});
	uint8_t redPallette = assetManager->addPallette({
				glm::vec4(0,0,0,0),
				glm::vec4(200,0,0,255),
				glm::vec4(200,0,0,255),
				glm::vec4(200,0,0,255)
			});
	assetManager->loadTileMap("tilemap.png");

	tickers = std::vector<ITickable*>();
	entities = std::vector<Entity*>();
	colliders = std::vector<ICollidable*>();
	for(int i = 0; i < ppu.BackgroundHeight;i++){
		assetManager->fillNextBackgroundLine();
	}
	yScroll = 0;

	SpriteGroup planeGroup1 = SpriteGroup({
				SpriteGroup::IntPair(1, 11),
				SpriteGroup::IntPair(1, 10),
				SpriteGroup::IntPair(1, 8),
				SpriteGroup::IntPair(0, 9),
				SpriteGroup::IntPair(1, 9),
				SpriteGroup::IntPair(2, 9),
			},
			SpriteGroup::IntPair(1, 10)
			);
	enemyPlanes[0] = new EnemyPlane(planeGroup1, redPallette);
	SpriteGroup planeGroup2 = SpriteGroup({
				SpriteGroup::IntPair(8, 8),
				SpriteGroup::IntPair(8, 7),
				SpriteGroup::IntPair(8, 6),
				SpriteGroup::IntPair(7, 6),
				SpriteGroup::IntPair(8, 5),
				SpriteGroup::IntPair(9, 6),
			},
			SpriteGroup::IntPair(8, 8)
			);
	enemyPlanes[1] = new EnemyPlane(planeGroup2, redPallette);


	for(int i = 0; i < projectiles.size(); i++){
		projectiles[i] = new Projectile();
	}
	explosion = new Explosion();
	timer = new Timer(glm::vec2(PPU466::ScreenWidth / 2 - 10, 230));

	enemyPlanes[0]->SpawnAt(glm::vec2(120,220),
			3,
			1.0,
			1.0
			);
//	enemyPlanes[1]->SpawnAt(glm::vec2(60,220));

	plane = new Plane(
			redPallette,
			shadowPallette,
			30.0f,
			&space.pressed,
			&down.pressed,
			&up.pressed,
			&left.pressed,
			&right.pressed
			);
	loseBoard = SpriteGroup({
				SpriteGroup::IntPair(9, 9),
				SpriteGroup::IntPair(10, 9),
				SpriteGroup::IntPair(11, 9),
				SpriteGroup::IntPair(12, 9),
				SpriteGroup::IntPair(9, 10),
				SpriteGroup::IntPair(10, 10),
				SpriteGroup::IntPair(11, 10),
				SpriteGroup::IntPair(12, 10)
			},
			SpriteGroup::IntPair(9, 9)
			);

	winBoard = SpriteGroup({
				SpriteGroup::IntPair(0, 7),
				SpriteGroup::IntPair(1, 7),
				SpriteGroup::IntPair(2, 7),
				SpriteGroup::IntPair(3, 7),
				SpriteGroup::IntPair(0, 6),
				SpriteGroup::IntPair(1, 6),
				SpriteGroup::IntPair(2, 6),
				SpriteGroup::IntPair(3, 6)
			},
			SpriteGroup::IntPair(0, 7)
			);

	printf("Using %d Sprites.\n", assetManager->spriteCount);
}

PlayMode::~PlayMode() {
	delete assetManager;
	for(int i = 0; i < projectiles.size(); i++){
		delete projectiles[i];
	}

	for(int i = 0; i < enemyPlanes.size(); i++){
		delete enemyPlanes[i];
	}
	delete explosion;
	delete plane;

}

void PlayMode::Win(){
	gameOver = true;
	winBoard.DrawAt(glm::vec2(((float)PPU466::ScreenWidth / 2) - 16.0f,PPU466::ScreenHeight / 2));
}
void PlayMode::Lose(){
	gameOver = true;
	loseBoard.DrawAt(glm::vec2(((float)PPU466::ScreenWidth / 2) - 16.0f,PPU466::ScreenHeight / 2));
}

bool PlayMode::handle_event(SDL_Event const &evt, glm::uvec2 const &window_size) {

	if (evt.type == SDL_KEYDOWN) {
		if (evt.key.keysym.sym == SDLK_w) {
			up.downs += 1;
			up.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_s) {
			down.downs += 1;
			down.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_a) {
			left.downs += 1;
			left.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_d) {
			right.downs += 1;
			right.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_SPACE) {
			space.downs += 1;
			space.pressed = true;
			return true;
		}
	} else if (evt.type == SDL_KEYUP) {
		if (evt.key.keysym.sym == SDLK_w) {
			up.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_s) {
			down.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_a) {
			left.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_d) {
			right.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_SPACE) {
			space.pressed = false;
			return true;
		}
	}

	return false;
}

void PlayMode::update(float elapsed) {
	auto color = ppu.palette_table[1][0];

	if(planesCurrentlyAlive <= 0){
		planesCurrentlyAlive = 0;
		waveNum++;
		enemyPlanes[0]->SpawnAt(
				glm::vec2(100, 200),
				3 + (waveNum / 2),
				1.0f + (0.1f * waveNum),
				1.0f + (0.1f * waveNum)
				);
		if(waveNum > 2){
			enemyPlanes[1]->SpawnAt(
					glm::vec2(140, 160),
					3 + (waveNum / 2),
					1.0f + (0.2f * waveNum),
					1.0f + (0.2f * waveNum)
					);
		}
	}

	for(auto it = tickers.begin(); it < tickers.end(); it++){
		((ITickable*)*it)->Tick(elapsed);
	}

	for(auto it = colliders.begin(); it < colliders.end(); it++){
		for(auto it2 = colliders.begin(); it2 < colliders.end(); it2++){
			if((*it)->layer != (*it2)->layer){
				(*it)->CheckCollision(*it2);
			}
		}
	}

	yScroll -= elapsed * 30.0f;

	ppu.background_position.y = int32_t(yScroll);

	//reset button press counters:
	up.downs = 0;
	down.downs = 0;
	left.downs = 0;
	right.downs = 0;
}

void PlayMode::draw(glm::uvec2 const &drawable_size) {
	//--- set ppu state based on game state ---

	//background color will be some hsv-like fade:
	ppu.background_color = glm::u8vec4(96,153,51,255);

	//--- actually draw ---
	ppu.draw(drawable_size);
}

void PlayMode::FireBullet(glm::vec2 position, glm::vec2 direction, float speed, ICollidable::LAYER layer){
	projectiles[nextProjectileIdx]->FireAt(position, direction, speed, layer);
	nextProjectileIdx ++;
	if(nextProjectileIdx >= projectiles.size()){
		nextProjectileIdx = 0;
	}
}
