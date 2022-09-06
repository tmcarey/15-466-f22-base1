#pragma once

#include "Ball.hpp"

#include "Collision.hpp"

struct ICollidable {
	virtual void OnCollisionEnter(Collision coll) {};
	virtual void OnCollisionExit(Collision coll) {};
	virtual Rect GetRect() { return Rect(); };

	void CheckCollision(Ball *coll);

	private:
		bool isColliding;
};
