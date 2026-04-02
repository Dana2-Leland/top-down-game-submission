#pragma once
#include <SFML/Graphics.hpp>

//This tile object structure directly correlates to the layout present in the json file. There are multiple tiles in each layer
class Tiles {
public:
	void init();
	Tiles(int ID, int xStart, int yStart, int rectWidth, sf::Texture& spriteMapTex);


	//Getters for the private variables of tile
	int getId() const { return id; };
	sf::Sprite& getSprite() { return sprite; };
	sf::Sprite getSpriteObj() { return sprite; };

	sf::Vector2f getCenter();




private:
	int id;
	sf::Sprite sprite;
};