#include "SpriteGroup.hpp"
#include "glm/glm.hpp"
#include "ITickable.hpp"
#include "Entity.hpp"

struct Explosion : Entity, ITickable {
	Explosion();

	void ExplodeAt(glm::vec2 position);
	virtual void Tick(float elapsed) override;

	private:
		SpriteGroup explosionGroup;
		int animState =0;
		float timeSinceStateChange = 0;
		bool doesExist = false;
};
