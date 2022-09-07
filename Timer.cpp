#include "Timer.hpp"

Timer::Timer(glm::vec2 _pos) : position(_pos), totalTime(99) {
	digit1 = SpriteGroup({
				SpriteGroup::IntPair(6, 2)
			},
			SpriteGroup::IntPair(6,2));
	digit2 = SpriteGroup({
				SpriteGroup::IntPair(6, 2)
			},
			SpriteGroup::IntPair(6,2));
}

void Timer::Tick(float elapsed){
	totalTime -= elapsed;

	if(totalTime <= 0.0f){
		totalTime = 0.0f;
	}

	digit2.SetOffset(uint8_t(int(glm::floor(totalTime)) % 10));
	digit1.SetOffset(uint8_t(int(glm::floor(totalTime)) / 10));

	digit1.DrawAt(position);
	digit2.DrawAt(position + glm::vec2(10, 0));
}

float Timer::getTimeRemaining(){
	return totalTime;
}
