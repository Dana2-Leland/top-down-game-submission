#include "Tiles.h"
#include <iostream>

void Tiles::init() {

}

Tiles::Tiles(int ID, int xStart, int yStart, int rectWidth, sf::Texture& spriteMapTex)
{
	sprite.setTexture(spriteMapTex);
	sprite.setTextureRect({ xStart, yStart, rectWidth, rectWidth });
	id = ID;
}

sf::Vector2f Tiles::getCenter() 
{
	int xCoord = sprite.getGlobalBounds().left + (sprite.getGlobalBounds().width / 2);
	int yCoord = sprite.getGlobalBounds().top + (sprite.getGlobalBounds().height / 2);
	return sf::Vector2f(xCoord, yCoord);
}








