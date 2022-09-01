#pragma once

struct ITickable {
	virtual void Tick(float elapsed) = 0;
};
