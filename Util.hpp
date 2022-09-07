#pragma once

#include "glm/glm.hpp"

#include <math.h>

#include <functional>

struct Util {
	static glm::vec2 SampleUnitCircle();
	static float SampleUnit();
	static void InitRandom();
	static int RandomUpTo(int N);

	struct ColorHashUtil
	{
		size_t operator()(const glm::u8vec4& k)const
		{
			return std::hash<uint8_t>()(k.x) ^ std::hash<uint8_t>()(k.y) ^ std::hash<uint8_t>()(k.z) ^ std::hash<uint8_t>()(k.w);
		}

		bool operator()(const glm::u8vec4& a, const glm::u8vec4& b)const
		{
				return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
		}
	};
};
