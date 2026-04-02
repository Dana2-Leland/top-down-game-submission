#include "PlayerCharacter.h"
#include <iostream>


void PlayerCharacter::init() {
	PathFinding thisPath;
	tileValues = thisPath.getTileVals(*up_sprite);
}


void PlayerCharacter::replaceWaypoints(sf::Vector2f waypoint)
{
	waypoints.clear();
	waypoints.push_back(waypoint);
}

void PlayerCharacter::move(float dt, std::vector<std::shared_ptr<Tiles>> currTilesFront)
{
	if (!waypoints.empty()) { // Check if there's a waypoint
		// Calculate distance and direction from character to waypoint
		sf::Vector2f direction = waypoints.front() - up_sprite->getPosition();
		float distance = sqrt((direction.x * direction.x) + (direction.y * direction.y));

		if (distance < 1) { // If player's already at the waypoint
			waypoints.pop_front(); // Remove the first waypoint from the deque
		}
		else {
			// Normalize direction 
			direction.x = direction.x / distance;
			direction.y = direction.y / distance;
			if (canMove(currTilesFront, direction)) { // If the player's not at waypoint
				checkHitEgg(direction);
				up_sprite->move(direction * speed * dt); //recursive call
				//while loop for can move?
			}
		}
		
	}
}



sf::Sprite PlayerCharacter::makeCharacter()
{
	up_sprite = std::make_unique<sf::Sprite>();
	updateCharaceterPose();
	return *up_sprite;
}

sf::Texture PlayerCharacter::updateCharaceterPose(std::string newPose)
{
	if (!up_sprite_texture.loadFromFile(newPose)) {
		std::cout << "character position " + newPose + " could not be loaded";
	}
	up_sprite->setTexture(up_sprite_texture);
	return up_sprite_texture;
}

sf::Sprite& PlayerCharacter::getSprite()
{
	return *up_sprite;
}

bool PlayerCharacter::canMove(std::vector<std::shared_ptr<Tiles>> currTilesFront, sf::Vector2f direction)
{
	//check each tile on front layer, if intersecting, disable player movement
	for (int i = 0; i < currTilesFront.size(); i++) {
		//if no collision currently
		if (currColl == none) {
			//if collision founnd
			if (currTilesFront[i]->getSprite().getGlobalBounds().intersects(up_sprite->getGlobalBounds())) {
				collIndex = i;
				int tileLeftBound = currTilesFront[collIndex]->getSprite().getGlobalBounds().left;
				int tileRightBound = tileLeftBound + currTilesFront[collIndex]->getSprite().getGlobalBounds().width;
				int tileUpBound = currTilesFront[collIndex]->getSprite().getGlobalBounds().top;
				int tileBottomBound = tileUpBound + currTilesFront[collIndex]->getSprite().getGlobalBounds().height;

				int spriteLeftBound = up_sprite->getGlobalBounds().left;
				int spriteRightBound = spriteLeftBound + up_sprite->getGlobalBounds().width;
				int spriteTopBound = up_sprite->getGlobalBounds().top;
				int spriteBottomBound = spriteTopBound + up_sprite->getGlobalBounds().height;


				//if intersection to right of player
				if (abs(spriteRightBound - tileLeftBound) < 5) {
					currColl = right;
				}
				//if intersection to left of player
				else if (abs(tileRightBound - spriteLeftBound) < 5) {
					currColl = left;
				}
				//if intersection to up of player
				else if (abs(spriteTopBound - tileBottomBound) < 5) {
					currColl = up;
				}
				//if intersection to left of player
				else if (abs(tileUpBound - spriteBottomBound) < 5) {
					currColl = down;
				}

				return false;
			}
		}
		//if a collision has been recorded
		else {
			//allow movement in direction other than collided variable
			if (currColl == right) {
				if (direction.x < 0) { //if moving left
					currColl = none;
					return true;
				}
				return false;
			}
			if (currColl == left) {
				if (direction.x > 0) { //if moving right
					currColl = none;
					return true;
				}
				return false;
			}
			if (currColl == up) {
				if (direction.y > 0) { //if moving down
					currColl = none;
					return true;
				}
				return false;
			}
			if (currColl == down) {
				if (direction.y < 0) { //if moving up
					currColl = none;
					return true;
				}
				return false;
			}
			return false;
		}
	}

	return true;
}

bool PlayerCharacter::canCollect(std::vector<std::shared_ptr<Tiles>> collectTiles, sf::Vector2f direction)
{
	return false;
}

void PlayerCharacter::checkHitEgg(sf::Vector2f direction)
{
	for (int i = 0; i < sizeof(eggs)/sizeof(eggs[0]); i++) {
		if (eggs[i].getSprite().getGlobalBounds().intersects(up_sprite->getGlobalBounds())) {
			addScore(i);
		}
	}
}

void PlayerCharacter::addScore(int eggIndex)
{
	eggs[eggIndex].destroyEgg();
	if (score < 4) {
		score++;
	}
	else {
		in_end = true;
	}
}

sf::Text& PlayerCharacter::getScoreText(int xPos, int yPos)
{
	if (!font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf")) {
		std::cout << "font did not load \n";
	}
	scoreText.setString(std::to_string(score));
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color(255, 255, 255, 128));
	scoreText.setPosition(xPos, yPos);
	return scoreText;
}



