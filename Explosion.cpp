#include "Explosion.hpp"
#include "SpriteGroup.hpp"

Explosion::Explosion(){
	explosionGroup = SpriteGroup(
			{
			SpriteGroup::IntPair(1, 3),
			SpriteGroup::IntPair(0, 4),
			SpriteGroup::IntPair(1, 4),
			SpriteGroup::IntPair(0, 3)
			},
			SpriteGroup::IntPair(0, 4)
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

	if(timeSinceStateChange > 0.1f){
		animState++;
		if(animState == 8){
			explosionGroup.Hide();
			doesExist = false;
		}else{
			explosionGroup.SetOffset(uint8_t(animState*2));
		}
		timeSinceStateChange = 0.0f;
	}else{
		timeSinceStateChange += elapsed;
	}


}
