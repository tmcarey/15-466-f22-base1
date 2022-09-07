#include "Explosion.hpp"
#include "SpriteGroup.hpp"

Explosion::Explosion(){
	explosionGroup = SpriteGroup(
			{
			SpriteGroup::IntPair(1, 7),
			SpriteGroup::IntPair(0, 7),
			SpriteGroup::IntPair(1, 8),
			SpriteGroup::IntPair(0, 7)
			},
			SpriteGroup::IntPair(1, 7)
			);
}

void Explosion::ExplodeAt(glm::vec2 position){
	explosionGroup.DrawAt(position);
	timeSinceStateChange = 0.0f;
	animState = 0;
	doesExist = true;
}

void Explosion::Tick(float elapsed){
	if(!doesExist)
		return;

	if(timeSinceStateChange > 0.5f){
		animState++;
		if(animState == 3){
			explosionGroup.Hide();
			doesExist = false;
		}else{
			explosionGroup.SetOffset(uint8_t(animState*2));
		}
	}else{
		timeSinceStateChange += elapsed;
	}


}
