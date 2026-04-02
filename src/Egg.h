#pragma once
#include <SFML/Graphics.hpp>

class Egg {
public:
	Egg(sf::Vector2f position, std::string texPath);
	
	sf::Vector2f getCenter();

	sf::Sprite getSprite() { return eggSprite; };


	void destroyEgg();
	void renewEgg();


private:
	sf::Sprite eggSprite;
	sf::Texture eggTexture;
	sf::Vector2f eggPos;

};