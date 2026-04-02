#include "PathFinding.h"
#include <iostream>

/*
PATHFINDING TIME:
Priority 1: find where player can and cannot move -- whether each tile in grid is collideable or not
Priority 2: find a path to where player clicked, going around collideable objects

method: get numbers for each tile on the map and how far they are
*/


/*
std::vector<int> PathFinding::getTileValues(sf::Sprite playerCharacter)
{
	//getTempTileValues(playerCharacter.getPosition().y/tileSize, playerCharacter.getPosition().y/tileSize, playerCharacter.getPosition().x/tileSize, playerCharacter.getPosition().x/tileSize);
	std::vector <int> tileValuesLeft(mapWidth);
	std::vector <int> tileValuesRight(mapWidth);
	std::vector <int> tileValuesRight(mapWidth * mapHeight);
	getTempTileValuesbyRow(0, playerCharacter.getPosition().x / tileSize);
	return tileValues;
}


//Establish all values left of player position in row
//(i.e. if player is at (4, 5), assign values from 0-4)
std::vector<int> PathFinding::getTempTileValuesLeft(int playerPos = 0, int count = 0)
{
	bool isLeft = false;

	if (playerPos - count > 0) {
		count++;
		tileValuesLeft.emplace_back(count); // 1 | 2, 1 | 3, 2, 1 | 4, 3, 2, 1
		isLeft = true;
	}
	if (isLeft) {
		getTempTileValuesLeft(playerPos, count);
	}
	return tileValuesLeft;
}

//Establish all values right of player position in row
//(i.e. if player is at (4, 5), assign values from 4-mapWidth)
std::vector<int> PathFinding::getTempTileValuesRight(int playerPos = 0, int count = 0)
{
	bool isRight = false;

	if (playerPos + count <= mapWidth) { // 1 | 2, 1 | 3, 2, 1 | 4, 3, 2, 1
		count++;
		tileValuesRight.emplace_back(count);
		isRight = true;
	}
	if (isRight) {
		getTempTileValuesRight(playerPos, count);
	}
	return tileValuesRight;
}

std::vector<int> PathFinding::getTempTileValuesbyRow(int row = 0, int playerPos = 0) {
	getTempTileValuesLeft(playerPos, 0);
	getTempTileValuesRight(playerPos, 0);

	for (int i = tileValuesLeft.size(); i > 0; i--) {       //4, 3, 2, 1
															//1 | 2, 1 | 3, 2, 1 | 4, 3, 2, 1
		rowTileValues.emplace_back(tileValuesLeft[i]);
	}

	rowTileValues.emplace_back(0); // 4, 3, 2, 1, 0

	for (int i = 0; i < tileValuesRight.size(); i++) {       //4, 3, 2, 1
		//1 | 2, 1 | 3, 2, 1 | 4, 3, 2, 1
		rowTileValues.emplace_back(tileValuesRight[i]);
	}

	for (int i = 0; i < tileValues.size(); i++) {
		std::cout << tileValues[i] << ", ";
	}

	return tileValues;
}
*/

std::vector<int> PathFinding::getTileVals(sf::Sprite playerCharacter)
{
	std::vector<int> tileVals(mapWidth * mapHeight);
	int tempX = playerCharacter.getPosition().x;
	int tempY = playerCharacter.getPosition().y;
	int xPos = playerCharacter.getPosition().x / tileSize;
	int yPos = playerCharacter.getPosition().y / tileSize;

	int index = xPos * yPos;

	int maxCol = mapWidth - xPos; //how many to the right we can go
	int maxRow = mapHeight - yPos; //how far down we can go
	int currentX = playerCharacter.getPosition().x;

	int currTileVal = playerCharacter.getPosition().x / tileSize + playerCharacter.getPosition().y / tileSize;



	//as left as possible
	int leftPos = xPos;
	int count = 0;
	while (leftPos > 0) {
		tileVals[index - count] = count += 1;
		//as up as possible

		leftPos--;
	}

	//as right as possible
	int rightPos = xPos;
	count = 0;
	while (rightPos < maxCol - 1) {
		tileVals[index + count] = count += 1;
		rightPos++;
	}

	

	std::cout << "xPos: " << xPos << "| yPos: " << yPos << "| maxRight: " << maxCol << "| maxDown: " << maxRow << "\n \n";
	

	printTileVals(tileVals);


	return tileVals;
}

void PathFinding::printTileVals(std::vector<int> tileVals)
{
	
	for (int i = 0; i < tileVals.size(); i++) {
		std::cout << "at " << i << ": " << tileVals[i] << "// ";
	}
}