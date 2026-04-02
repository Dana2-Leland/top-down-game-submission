#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"


int main()
{
    std::cout << "You should see a window that opens as well as this writing to console..."
        << std::endl;

    // create window and set up
    sf::RenderWindow window(sf::VideoMode(1920, 1760), "Top Down Game");
    window.setFramerateLimit(60);

    sf::Mouse mouse;

    //initialise an instance of the game class
    Game game(window);

    //run the init function of the game class and check it all initialises ok
    if (!game.init())
    {
        return 0;
    }

    // A Clock starts counting as soon as it's created
    sf::Clock clock;

    // Game loop: run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        //calculate delta time
        sf::Time time = clock.restart();
        float dt = time.asSeconds();

        //'process inputs' element of the game loop
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f cursor_location = static_cast<sf::Vector2f>(mouse.getPosition(window));
                game.mouseButtonPressed(event, cursor_location);
            }
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            window.close();
        }

        //'update' element of the game loop
        game.update(dt);       
        

        //'render' element of the game loop
        window.clear(sf::Color::Black);
        game.render();
        window.display();
    }

    return 0;
}
