#include "TileMap.h"
#include <iostream>
#include <vector>
/*
	TileMap needs to load in tiles (each 16 x 16 pixels), then store them in a vector array, then place them correctly in the world.
	Tiles should be stored in a vector array. Position will be found by row and column -- row by division, column by modular
*/

TileMap::TileMap() {
	tileSize = -1;
	mapWidth = -1;
	mapHeight = -1;
}

void TileMap::setValues(int tSize, int mWidth, int mHeight)
{
	tileSize = tSize;
	mapWidth = mWidth;
	mapHeight = mHeight;
}

void TileMap::setSpriteMapValues(int mWidth, int mHeight)
{
	spriteMapHeight = mHeight;
	spriteMapWidth = mWidth;
}

void TileMap::SetSpritesheet(std::string pathname)
{
	if (!mapFileTexture.loadFromFile(pathname)) {
		std::cout << "tilemap could not be loaded";
	}
	mapFileSprite.setTexture(mapFileTexture);
}

TileMap::TileMap(int tSize =-1, int mWidth =-1, int mHeight =-1)
{
	tileSize = tSize;
	mapWidth = mWidth;
	mapHeight = mHeight;
}

/*
	Adds tile to currMap -- uses ID to get sprite to add. Currently Tile's x and y are useless
*/
void TileMap::addTileBack(int id, int x, int y)
{
	Tiles currSprite = *spritesheetTiles[id];
	currSprite.getSprite().setPosition(x * tileSize * scale, y * tileSize * scale);
	currTilesBack.emplace_back(std::make_shared<Tiles>(currSprite)); //add sprite by tile id to front
}

void TileMap::addTileFront(int id, int x, int y)
{
	Tiles currSprite = *spritesheetTiles[id];
	currSprite.getSprite().setPosition(x * tileSize * scale, y * tileSize * scale);
	currTilesFront.emplace_back(std::make_shared<Tiles>(currSprite)); //add sprite by tile id to back
}



std::vector<std::shared_ptr<Tiles>> TileMap::genSpritesheet()
{
	genSpritesheetTemp(0, 0);
	return spritesheetTiles;
}

void TileMap::genSpritesheetTemp(int y, int id)
{

	int prevX = -tileSize;
	for (int x = 0; x < spriteMapWidth * tileSize; x+=tileSize) //192
	{
		spritesheetTiles.emplace_back(std::make_shared<Tiles>(id, prevX += tileSize, y, tileSize, mapFileTexture));

		spritesheetTiles.back()->getSprite().setScale(scale, scale);
		spritesheetTiles.back()->getSprite().setPosition((id % spriteMapWidth) * (tileSize * scale), y / tileSize * (tileSize * scale));
		
		id += 1;
	}

	if (y < (spriteMapHeight * tileSize) - tileSize) { //176
		genSpritesheetTemp(y += tileSize, id);

	}
}
