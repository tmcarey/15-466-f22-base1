#include "ITickable.hpp"

#include "PlayMode.hpp"

ITickable::ITickable(){
	PlayMode::Instance->tickers.push_back(this);
}
