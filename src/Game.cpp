
#include "Game.h"
#include <iostream>
#include <vector>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
	srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
	main_character = std::make_unique<PlayerCharacter>();
	main_character->makeCharacter();
	createSpritesheet();

	return true;
}

void Game::createSpritesheet() 
{
	map = std::make_shared<TileMap>();
	json.LoadMapFromJson("../Data/map.json", *map);
	currTilesBack = map->getCurrMapBack();
}

void Game::startMenu()
{
	if (!font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf")) {
		std::cout << "font did not load \n";
	}

	title_text.setString("Top Down");
	title_text.setFont(font);
	title_text.setCharacterSize(18);
	title_text.setFillColor(sf::Color(255, 255, 255, 128));
	title_text.setPosition(
		window.getSize().x / 2 - title_text.getGlobalBounds().width / 2, 100 );


	menu_text.setString("Welcome to Top Down. Please select an option");
	menu_text.setFont(font);
	menu_text.setCharacterSize(18);
	menu_text.setFillColor(sf::Color(0, 255, 255));
	menu_text.setPosition(
		window.getSize().x / 2 - title_text.getGlobalBounds().left / 4, 200);

	play_option.setString("Play");
	play_option.setFont(font);
	play_option.setCharacterSize(18);
	play_option.setFillColor(sf::Color(0, 255, 255));
	play_option.setPosition(
		(window.getSize().x / 2 - title_text.getGlobalBounds().left / 4) + play_option.getGlobalBounds().width, 400);



	quit_option.setString("Quit");
	quit_option.setFont(font);
	quit_option.setCharacterSize(18);
	quit_option.setFillColor(sf::Color(0, 255, 255));
	quit_option.setPosition(
		(title_text.getGlobalBounds().left + title_text.getGlobalBounds().width) + quit_option.getGlobalBounds().width, 400);

}

void Game::endMenu()
{
	if (!font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf")) {
		std::cout << "font did not load \n";
	}

	title_text.setString("Top Down");
	title_text.setFont(font);
	title_text.setCharacterSize(18);
	title_text.setFillColor(sf::Color(255, 255, 255, 128));
	title_text.setPosition(
		window.getSize().x / 2 - title_text.getGlobalBounds().width / 2, 100);


	menu_text.setString("You Win! Please select an option");
	menu_text.setFont(font);
	menu_text.setCharacterSize(18);
	menu_text.setFillColor(sf::Color(0, 255, 255));
	menu_text.setPosition(
		window.getSize().x / 2 - title_text.getGlobalBounds().left / 4, 200);

	play_option.setString("rePlay");
	play_option.setFont(font);
	play_option.setCharacterSize(18);
	play_option.setFillColor(sf::Color(0, 255, 255));
	play_option.setPosition(
		(window.getSize().x / 2 - title_text.getGlobalBounds().left / 4) + play_option.getGlobalBounds().width, 400);



	quit_option.setString("Quit");
	quit_option.setFont(font);
	quit_option.setCharacterSize(18);
	quit_option.setFillColor(sf::Color(0, 255, 255));
	quit_option.setPosition(
		(title_text.getGlobalBounds().left + title_text.getGlobalBounds().width) + quit_option.getGlobalBounds().width, 400);
}



void Game::update(float dt)
{
	main_character->move(dt, map->getCurrMapFront());
	in_menu_end = main_character->in_end;

}

void Game::render()
{
	if (in_menu_start) {
		startMenu();
		window.draw(title_text);
		window.draw(menu_text);
		window.draw(play_option);
		window.draw(quit_option);
	}
	else if (in_menu_end) {
		endMenu();
		window.draw(title_text);
		window.draw(menu_text);
		window.draw(play_option);
		window.draw(quit_option);
	}
	else {
		for (int i = 0; i < map->getCurrMapBack().size(); i++) {
			window.draw(map->getCurrMapBack()[i]->getSprite());
		}
		for (int i = 0; i < map->getCurrMapFront().size(); i++) {
			window.draw(map->getCurrMapFront()[i]->getSprite());
		}


	
		for (int i = 0; i < sizeof(main_character->eggs) / sizeof(main_character->eggs[0]); i++) {
			window.draw(main_character->eggs[i].getSprite());
		}

		window.draw(main_character->getScoreText(window.getSize().x-40, 40));
		window.draw(main_character->getSprite());
	}
	
}

void Game::mouseButtonPressed(sf::Event event, sf::Vector2f cursor_location)
{
	if (in_menu_start) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			//if intersecting with play button
			if (play_option.getGlobalBounds().contains(cursor_location)) {
				in_menu_start = false;
			}
			if (quit_option.getGlobalBounds().contains(cursor_location)) {
				window.close();
			}
		}
	}
	else if (in_menu_end) {
		if (play_option.getGlobalBounds().contains(cursor_location)) {

			//reset game
			for (int i = 0; i < sizeof(main_character->eggs) / sizeof(main_character->eggs[0]); i++) {
				main_character->eggs[i].renewEgg();
			}
			main_character->resetScore();
			main_character->getSprite().setPosition(0, 0);
			//leave end menu
			main_character->setInEnd(false);
			in_menu_end = false;

		}
		if (quit_option.getGlobalBounds().contains(cursor_location)) {
			window.close();
		}
	
	}
	else {
		if (event.mouseButton.button == sf::Mouse::Left) {
			main_character->replaceWaypoints(cursor_location);		
		}
	}
	
}



