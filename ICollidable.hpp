#include "Ball.hpp"

struct ICollidable {
	virtual void DoCollision(Ball coll);
};
