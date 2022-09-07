#include "EnemyPlane.hpp"

EnemyPlane::EnemyPlane(){
	planeGroup = SpriteGroup({
				SpriteGroup::IntPair(2, 11),
				SpriteGroup::IntPair(2, 10),
				SpriteGroup::IntPair(2, 9),
				SpriteGroup::IntPair(2, 8),
				SpriteGroup::IntPair(0, 9),
				SpriteGroup::IntPair(1, 9),
				SpriteGroup::IntPair(3, 9),
				SpriteGroup::IntPair(4, 9),
			},
			SpriteGroup::IntPair(2, 11)
			);
	layer = ICollidable::ENEMY;
	position = glm::vec2(100, 200);
	velocity = glm::vec2(0, 0);
	isAlive = true;
}

Rect EnemyPlane::GetRect(){
	return Rect(position + glm::vec2(-16.0f, -32.0f), position + glm::vec2(24.0f, 8.0f));
}

void EnemyPlane::Tick(float elapsed){
	if(!isAlive)
		return;

	time += elapsed;
	velocity = glm::vec2(std::sin(time), 0) * 30.0f;

	position += velocity * elapsed;

	if(velocity.x > 0){
		planeGroup.SetOffset(5);
	}else if(velocity.x < 0){
		planeGroup.SetOffset(10);
	}else if(velocity.x == 0){
		planeGroup.SetOffset(0);
	}

	planeGroup.DrawAt(position);
}

void EnemyPlane::OnCollisionEnter(Collision coll){
	printf("something entered\n");
	if(isAlive && coll.collider->layer == ICollidable::LAYER::PLAYER){
		planeGroup.Hide();
		isAlive = false;
	}
}
