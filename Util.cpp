#include "Util.hpp"

#define PI 3.14159265f

float Util::SampleUnit() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

glm::vec2 Util::SampleUnitCircle(){
	return glm::vec2(std::cos(SampleUnit() * PI * 2), 
			std::sin(SampleUnit() * PI * 2));
}
