#include "ICollidable.hpp"

#include "PlayMode.hpp"

void ICollidable::CheckCollision(ICollidable *other){
	bool currentlyColliding = Collision::RectRectCollide(other->GetRect(), GetRect());

	if(currentlyColliding && !isColliding){
		OnCollisionEnter(Collision(other));
	}else if(!currentlyColliding && isColliding){
		OnCollisionExit(Collision(other));
	}

	isColliding = currentlyColliding;
}

ICollidable::ICollidable(){
	PlayMode::Instance->colliders.push_back(this);
}

bool ICollidable::Collision::RectRectCollide(Rect a, Rect b){
	if(a.bottomLeft.x < b.bottomLeft.x + b.width &&
			a.bottomLeft.x + a.width > b.bottomLeft.x &&
			a.bottomLeft.y < b.bottomLeft.y + b.height && 
			a.bottomLeft.y + a.height > b.bottomLeft.y){
		return true;
	}else {
		return false;
	}

}
