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

PlayMode::PlayMode() {
	Util::InitRandom();
	assetManager = new AssetManager(&ppu);
	uint8_t paddle1Tile = assetManager->loadTile("paddle1.png");
	uint8_t paddle2Tile = assetManager->loadTile("paddle2.png");
	uint8_t ballTile = assetManager->loadTile("ball.png");
	tickers = std::vector<ITickable*>();
	entities = std::vector<Entity*>();
	colliders = std::vector<ICollidable*>();

	Paddle *paddle1 = new Paddle(
			&up1.pressed,
			&down1.pressed,
			20,
			20,
			90.0f,
			1,
			&(ppu.sprites[0]),
			paddle1Tile,
			paddle1Tile);
	tickers.push_back(paddle1);
	entities.push_back(paddle1);
	colliders.push_back(paddle1);

	Paddle *paddle2 =new Paddle(
			&up2.pressed,
			&down2.pressed,
			ppu.ScreenWidth - 8 - 20,
			20,
			90.0f,
			2,
			&(ppu.sprites[1]),
			paddle2Tile,
			paddle2Tile);
	tickers.push_back(paddle2);
	entities.push_back(paddle2);
	colliders.push_back(paddle2);

	ball = new Ball(
				ballTile,
				3,
				90.0f,
				&(ppu.sprites[2])
				);
	entities.push_back(ball);
	tickers.push_back(ball);
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
			up1.downs += 1;
			up1.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_s) {
			down1.downs += 1;
			down1.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_UP) {
			up2.downs += 1;
			up2.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_DOWN) {
			down2.downs += 1;
			down2.pressed = true;
			return true;
		}
	} else if (evt.type == SDL_KEYUP) {
		if (evt.key.keysym.sym == SDLK_w) {
			up1.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_s) {
			down1.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_UP) {
			up2.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_DOWN) {
			down2.pressed = false;
			return true;
		}
	}

	return false;
}

void PlayMode::update(float elapsed) {
	auto color = ppu.palette_table[1][0];

	//slowly rotates through [0,1):
	// (will be used to set background color)
	background_fade += elapsed / 10.0f;
	background_fade -= std::floor(background_fade);

	/* constexpr float PlayerSpeed = 30.0f; */
	/* if (up1.pressed) player_at.x -= PlayerSpeed * elapsed; */
	/* if (up2.pressed) player_at.x += PlayerSpeed * elapsed; */
	/* if (down1.pressed) player_at.y -= PlayerSpeed * elapsed; */
	/* if (down2.pressed) player_at.y += PlayerSpeed * elapsed; */

	for(auto it = tickers.begin(); it < tickers.end(); it++){
		((ITickable*)*it)->Tick(elapsed);
	}

	for(auto it = colliders.begin(); it < colliders.end(); it++){
		((ITickable*)*it)->Tick(elapsed);
	}
	//reset button press counters:
	up1.downs = 0;
	up2.downs = 0;
	down1.downs = 0;
	down2.downs = 0;
}

void PlayMode::draw(glm::uvec2 const &drawable_size) {
	//--- set ppu state based on game state ---

	//background color will be some hsv-like fade:
	ppu.background_color = glm::u8vec4(
		std::min(255,std::max(0,int32_t(255 * 0.5f * (0.5f + std::sin( 2.0f * M_PI * (background_fade + 0.0f / 3.0f) ) ) ))),
		std::min(255,std::max(0,int32_t(255 * 0.5f * (0.5f + std::sin( 2.0f * M_PI * (background_fade + 1.0f / 3.0f) ) ) ))),
		std::min(255,std::max(0,int32_t(255 * 0.5f * (0.5f + std::sin( 2.0f * M_PI * (background_fade + 2.0f / 3.0f) ) ) ))),
		0xff
	);

	//tilemap gets recomputed every frame as some weird plasma thing:
	//NOTE: don't do this in your game! actually make a map or something :-)
	/* for (uint32_t y = 0; y < PPU466::BackgroundHeight; ++y) { */
	/* 	for (uint32_t x = 0; x < PPU466::BackgroundWidth; ++x) { */
	/* 		//TODO: make weird plasma thing */
	/* 		ppu.background[x+PPU466::BackgroundWidth*y] = ((x+y)%16); */
	/* 	} */
	/* } */

	//background scroll:
	ppu.background_position.x = int32_t(-0.5f * player_at.x);
	ppu.background_position.y = int32_t(-0.5f * player_at.y);

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
