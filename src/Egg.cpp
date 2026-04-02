#include "Egg.h"
#include <iostream>;

Egg::Egg(sf::Vector2f position, std::string texPath)
{
	if (!eggTexture.loadFromFile(texPath)) {
		std::cout << "egg texture " + texPath + " could not be loaded";
	}
	eggSprite.setTexture(eggTexture);
	eggSprite.setScale(10, 10);
	eggPos = position;
	eggSprite.setPosition(position);
}

sf::Vector2f Egg::getCenter() {
	return(sf::Vector2f((eggSprite.getGlobalBounds().left + eggSprite.getGlobalBounds().width / 2),
		eggSprite.getGlobalBounds().top + eggSprite.getGlobalBounds().height / 2));
}

void Egg::destroyEgg()
{
	eggSprite.setScale(0.1, 0.1);
	eggSprite.setPosition(100000, 100000);
}

void Egg::renewEgg() {
	eggSprite.setScale(10, 10);
	eggSprite.setPosition(eggPos);

}

