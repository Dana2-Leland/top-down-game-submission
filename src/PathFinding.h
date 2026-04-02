#include <SFML/Graphics.hpp>
#include <deque>;
#pragma once

class PathFinding {
public:
	/*
	std::vector<int> getTileValues(sf::Sprite playerCharacter);
	std::vector<int> getTempTileValuesLeft(int playerPos, int count);
	std::vector<int> getTempTileValuesRight(int playerPos, int count);
	std::vector<int> getTempTileValuesbyRow(int row, int playerpos);
	*/

	std::vector<int> getTileVals(sf::Sprite playerCharacter);
	void printTileVals(std::vector<int> tileVals);

private:
	//l   u   r  d
	int neighborYVals[4]{ -1, 0, 1, 0 };
	int neighborXVals[4]{ 0, -1, 0, 1 };


	/*
	std::vector <int> tileValues;
	std::vector <int> tileValuesLeft;
	std::vector <int> tileValuesRight;
	std::vector <int> rowTileValues;
	*/



	//done by row, so divide by map width to get each value
	int mapHeight = 15;
	int mapWidth = 30;
	int tileSize = 16 * 10;
};