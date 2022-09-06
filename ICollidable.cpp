#include "ICollidable.hpp"

void ICollidable::CheckCollision(Ball *ball){
	bool currentlyColliding = Collision::RectRectCollide(ball->rect, GetRect());

	if(currentlyColliding && !isColliding){
		OnCollisionEnter(Collision(ball));
	}else if(!currentlyColliding && isColliding){
		OnCollisionExit(Collision(ball));
	}

	isColliding = currentlyColliding;
}
