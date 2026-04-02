
#pragma once

#include <SFML/Graphics.hpp>
#include <deque>;
#include <iostream>;
#include "PathFinding.h"
#include "Tiles.h"
#include "Egg.h"
class PlayerCharacter
{
public:
	void init();
	void replaceWaypoints(sf::Vector2f waypoint);
	void move(float dt, std::vector<std::shared_ptr<Tiles>> currTilesFront);


	sf::Sprite makeCharacter();
	sf::Texture updateCharaceterPose(std::string newPose = "../Data/Images/kenney_tooncharacters1/Female adventurer/Poses/character_femaleAdventurer_idle.png");
	std::unique_ptr<sf::Sprite> up_sprite; //unique pointer for now, subject to change
	sf::Texture up_sprite_texture; 
	sf::Sprite& getSprite();

	bool canMove(std::vector<std::shared_ptr<Tiles>> currTilesFront, sf::Vector2f direction);

	bool canCollect(std::vector<std::shared_ptr<Tiles>> collectTiles, sf::Vector2f direction);

	enum collisionDirection { none, up, down, left, right };

	collisionDirection currColl = none;

	void checkHitEgg(sf::Vector2f direction);
	void addScore(int eggIndex);

	Egg eggs[5]{
			Egg(sf::Vector2f(100, 400), "../Data/Images/kenney_tiny-town/Tiles/tile_0093.png"),
			Egg(sf::Vector2f(800, 600), "../Data/Images/kenney_tiny-town/Tiles/tile_0093.png"),
			Egg(sf::Vector2f(200, 400), "../Data/Images/kenney_tiny-town/Tiles/tile_0093.png"),
			Egg(sf::Vector2f(800, 400), "../Data/Images/kenney_tiny-town/Tiles/tile_0093.png"),
			Egg(sf::Vector2f(900, 100), "../Data/Images/kenney_tiny-town/Tiles/tile_0093.png")
	};

	sf::Text& getScoreText(int xPos, int yPos);

	void setInEnd(bool inEnd) { in_end = inEnd; };
	bool in_end = false;

	void resetScore() { score = 0; };

private:
	std::deque<sf::Vector2f> waypoints;
	float speed = 200;

	bool couldMovePrev = true;
	int collIndex = -1;

	int score = 0;
	sf::Text scoreText;
	sf::Font font;

	std::vector<int> tileValues;

	int tileSize = 160;
	int mapWidth = 30;
	int mapHeight = 15;

	
};
