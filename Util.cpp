#include "Util.hpp"
#include <time.h>

#define PI 3.14159265f

void Util::InitRandom(){
	srand((unsigned int)(time(NULL)) * 10000);
}

float Util::SampleUnit() {
	float val = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	return val;
}

glm::vec2 Util::SampleUnitCircle(){
	float t = SampleUnit() * PI * 2;
	return glm::vec2(std::cos(t), 
			std::sin(t));
}
