#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include <vector>
#include "Tiles.h"

class TileMap
{
public:
	TileMap(int tSize, int mWidth, int mHeight);
	TileMap();
	void SetSpritesheet(std::string pathname);
	//sf::Sprite tile(int xStart, int yStart, int rectWidth, int rectHeight); //generates the tile texture, assigns it to sprite, returns it
	std::vector<std::shared_ptr<Tiles>> genSpritesheet();
	void addTileBack(int id, int x, int y);
	void addTileFront(int id, int x, int y);
	void setValues(int tSize, int mWidth, int mHeight);
	void setSpriteMapValues(int mWidth, int mHeight);

	std::vector<std::shared_ptr<Tiles>>&  getCurrMapBack() { return currTilesBack; };
	std::vector<std::shared_ptr<Tiles>>&  getCurrMapFront() { return currTilesFront; };
	std::vector<std::shared_ptr<Tiles>>& getSpritesheetTiles() { return spritesheetTiles; };

	sf::Sprite mapFileSprite;
private:

	void genSpritesheetTemp(int y, int id);

	std::vector<std::shared_ptr<Tiles>> currTilesBack;
	std::vector<std::shared_ptr<Tiles>> currTilesFront;
	std::vector<std::shared_ptr<Tiles>> spritesheetTiles;

	int mapHeight;
	int mapWidth;
	int tileSize;

	int spriteMapHeight;
	int spriteMapWidth;

	int scale = 4;


	sf::Texture mapFileTexture;

};
