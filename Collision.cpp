#include "Collision.hpp"

bool Collision::RectRectCollide(Rect a, Rect b){
	if(a.bottomLeft.x < b.bottomLeft.x + b.width &&
			a.bottomLeft.x + a.width > b.bottomLeft.x &&
			a.bottomLeft.y < b.bottomLeft.y + b.height && 
			a.bottomLeft.y + a.height > b.bottomLeft.y){
		return true;
	}else {
		return false;
	}

}
