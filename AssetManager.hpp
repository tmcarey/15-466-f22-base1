#pragma once

#include <string>

#include "PPU466.hpp"

struct AssetManager {
	AssetManager(PPU466 ppu);
	int loadTile(std::string path);

	private:
		int tileCount = 0;
		int palletteCount = 0;
		PPU466 ppu;
};
