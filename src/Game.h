
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include "PlayerCharacter.h"
#include "TileMap.h"
#include "JsonLoader.h"
#include "Egg.h"
#include <vector>

class Game
{
	public:
		Game(sf::RenderWindow& window);
		~Game();
		bool init();
		void update(float dt);
		void render();
		void mouseButtonPressed(sf::Event event, sf::Vector2f cursor_location);

		std::unique_ptr<PlayerCharacter> main_character;
		void createSpritesheet();

		void startMenu();
		void endMenu();

		sf::Texture map_texture_in_game;


	private:
		bool in_menu_start = true;
		bool play_selected = false;
		bool in_menu_end = false;



		sf::RenderWindow& window;
		JsonLoader json;
		std::shared_ptr<TileMap> map;

		sf::Sprite main_character_sprite;
		sf::Texture main_character_texture;
		
		std::vector<std::shared_ptr<Tiles>> currTilesBack;
		std::vector<std::shared_ptr<Tiles>> currTilesFront;

		sf::Font font;
		sf::Text title_text;
		sf::Text menu_text;

		sf::Text play_option;
		sf::Text quit_option;


};

#endif // PLATFORMER_GAME_H
