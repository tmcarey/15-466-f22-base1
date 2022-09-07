#pragma once

#include "Ball.hpp"

#include "Collision.hpp"

struct ICollidable {
	struct Collision {
		Collision(ICollidable *collider) : collider(collider) {};
		ICollidable *collider;
		static bool RectRectCollide(Rect a, Rect b);
	};

	ICollidable();

	virtual void OnCollisionEnter(Collision coll) {};
	virtual void OnCollisionExit(Collision coll) {};
	virtual Rect GetRect() { return Rect(); };

	void CheckCollision(ICollidable *other);

	private:
		bool isColliding = false;

};
