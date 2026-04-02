#include "JsonLoader.h"
#include <vector>

//This function opens the map file in our repository
//and loads it into the specific format of nlohmann::json filetype and returns it.

nlohmann::json JsonLoader::loadJson(const std::string& path)
{
	//We try and open a file at the specified path
	std::ifstream file(path);
	if (!file) {
		//And throw an error if the file can't be opened
		std::cout << "couldn't open map file" << std::endl;
	}
	//If the file opened correctly we stream its contents into the nlohmann:json variable and return it
	nlohmann::json j;
	file >> j;
	return j;
}

//This function goes through the json file and converts (parses) the information inside into our Map->Layer->Tile data structure.
TileMap JsonLoader::LoadMapFromJson(std::string path, TileMap& map)
{
	//we use the loadJson function to create a json file j to use in our parsing operations
	nlohmann::json j = loadJson(path);

	//You can access each parameter inside the json file by using the .at() function, specifying the string of parameter name.
	//You have to then further specify a type of variable you are looking for using .get<type>(); In our case mostly ints.

	//This is a for loop that will go through each layer in the json file.
	//Notice the "auto&" which automatically decides on the variable type by using the container variable type.


	//After getting the map parameters we use them to create an instance of Map and set its spritesheet
	//TileMap map(tileSize, mapWidth, mapHeight);
	int tileSize = j.at("tileSize").get<int>();

	int mapWidth = j.at("mapWidth").get<int>();
	int mapHeight = j.at("mapHeight").get<int>();

	int spriteMapWidth = j.at("spriteMapWidth").get<int>();
	int spriteMapHeight = j.at("spriteMapHeight").get<int>();

	map.setSpriteMapValues(spriteMapWidth, spriteMapHeight);
	map.setValues(tileSize, mapWidth, mapHeight);


	map.SetSpritesheet("../Data/Images/kenney_tiny-town/Tilemap/tilemap_packed.png");
	map.genSpritesheet();

	/*
		We only ever will use two layers -- front and back. have a loop for adding front layer, and a loop for adding back layer
	*/
	for (auto& jsonLayer : j.at("layers")) 
	{
		//Loop through each tile in each layer of map
		
		if (jsonLayer.at("name") == "Background") 
		{
			for (auto& jsonTile : jsonLayer.at("tiles")) {

				int id = (jsonTile.at("attributes").at("id").get<int>());
				int x = (jsonTile.at("x").get<int>());
				int y = (jsonTile.at("y").get<int>());
				map.addTileBack(id, x, y);
			}
		}

		if (jsonLayer.at("name") == "Additionals") 
		{
			for (auto& jsonTile : jsonLayer.at("tiles")) {

				int id = (jsonTile.at("attributes").at("id").get<int>());
				int x = (jsonTile.at("x").get<int>());
				int y = (jsonTile.at("y").get<int>());
				map.addTileFront(id, x, y);
			}
		}
	}

	//Once all the layers are proccessed and assigned to the map we return the map object.
	return map;
}

