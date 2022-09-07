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

#include "Plane.hpp"

#include "Enemy.hpp"

PlayMode *PlayMode::Instance;

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
	assetManager->loadTileMap("tilemap.png");

	tickers = std::vector<ITickable*>();
	entities = std::vector<Entity*>();
	colliders = std::vector<ICollidable*>();
	for(int i = 0; i < ppu.BackgroundHeight;i++){
		assetManager->fillNextBackgroundLine();
	}
	yScroll = 0;

	/* Enemy *enemy = new Enemy( */
	/* 		enemyTile, */
	/* 		0, */
	/* 		&(ppu.sprites[3]), */
	/* 		30.0f, */
	/* 		120.0f */
	/* 		); */
	
	new Plane(
			shadowPallette,
			30.0f,
			&down.pressed,
			&up.pressed,
			&left.pressed,
			&right.pressed
			);
}

PlayMode::~PlayMode() {
	for(auto it = entities.begin(); it < entities.end(); it++){
		delete *it;
	}
	entities.clear();
	delete assetManager;
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
		}
	}

	return false;
}

void PlayMode::update(float elapsed) {
	auto color = ppu.palette_table[1][0];

	//slowly rotates through [0,1):
	// (will be used to set background color)

	/* constexpr float PlayerSpeed = 30.0f; */
	/* if (up1.pressed) player_at.x -= PlayerSpeed * elapsed; */
	/* if (up2.pressed) player_at.x += PlayerSpeed * elapsed; */
	/* if (down1.pressed) player_at.y -= PlayerSpeed * elapsed; */
	/* if (down2.pressed) player_at.y += PlayerSpeed * elapsed; */

	for(auto it = tickers.begin(); it < tickers.end(); it++){
		((ITickable*)*it)->Tick(elapsed);
	}

	for(auto it = colliders.begin(); it < colliders.end(); it++){
		for(auto it2 = colliders.begin(); it2 < colliders.end(); it2++){
			if(it != it2){
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
	ppu.background_color = glm::u8vec4(0,255,0,255);
	//tilemap gets recomputed every frame as some weird plasma thing:
	//NOTE: don't do this in your game! actually make a map or something :-)
	/* for (uint32_t y = 0; y < PPU466::BackgroundHeight; ++y) { */
	/* 	for (uint32_t x = 0; x < PPU466::BackgroundWidth; ++x) { */
	/* 		//TODO: make weird plasma thing */
	/* 		ppu.background[x+PPU466::BackgroundWidth*y] = ((x+y)%16); */
	/* 	} */
	/* } */

	//background scroll:
	/* ppu.background_position.x = int32_t(-0.5f * player_at.x); */

	//player sprite:
	/* ppu.sprites[0].x = int8_t(player_at.x); */
	/* ppu.sprites[0].y = int8_t(player_at.y); */
	/* ppu.sprites[0].index = 0; */
	/* ppu.sprites[0].attributes = 0; */

	//some other misc sprites:
	/* for (uint32_t i = 1; i < 63; ++i) { */
	/* 	float amt = (i + 2.0f * background_fade) / 62.0f; */
	/* 	ppu.sprites[i].x = int8_t(0.5f * PPU466::ScreenWidth + std::cos( 2.0f * M_PI * amt * 5.0f + 0.01f * player_at.x) * 0.4f * PPU466::ScreenWidth); */
	/* 	ppu.sprites[i].y = int8_t(0.5f * PPU466::ScreenHeight + std::sin( 2.0f * M_PI * amt * 3.0f + 0.01f * player_at.y) * 0.4f * PPU466::ScreenWidth); */
	/* 	ppu.sprites[i].index = 32; */
	/* 	ppu.sprites[i].attributes = 6; */
	/* 	if (i % 2) ppu.sprites[i].attributes |= 0x80; //'behind' bit */
	/* } */

	//--- actually draw ---
	ppu.draw(drawable_size);
}
