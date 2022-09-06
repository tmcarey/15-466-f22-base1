#include "ICollidable.hpp"

void ICollidable::CheckCollision(Ball *ball){
	bool currentlyColliding = Collision::RectRectCollide(ball->GetRect(), GetRect());

	if(currentlyColliding && !isColliding){
		OnCollisionEnter(Collision(ball));
	}else if(!currentlyColliding && isColliding){
		OnCollisionExit(Collision(ball));
	}

	isColliding = currentlyColliding;
}
