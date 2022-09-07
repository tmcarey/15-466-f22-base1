#include "Entity.hpp"

#include "PlayMode.hpp"

Entity::Entity(){
	PlayMode::Instance->entities.push_back(this);
}
