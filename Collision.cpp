#include "Collision.hpp"

bool Collision::RectRectCollide(Rect a, Rect b){
	if(a.bottomLeft.x < b.bottomLeft.x + b.width &&
			a.bottomLeft.x + a.width > b.bottomLeft.x &&
			a.bottomLeft.y < a.bottomLeft.y + a.height && 
			a.bottomLeft.y + a.height > a.bottomLeft.y){
		return false;

	}else {
		return false;
	}

}
