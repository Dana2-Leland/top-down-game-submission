#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "TileMap.h"
#include "nlohmann/json.hpp"
#include <stdexcept>

class JsonLoader
{
public:
	static nlohmann::json loadJson(const std::string& path);
	static TileMap LoadMapFromJson(std::string path, TileMap& map);
	int getTileSize() { return tile_Size; };
	int getMapWidth() { return map_Width; };
	int getMapHeight() { return map_Height; };


private:
	int tile_Size;
	int map_Width;
	int map_Height;

};