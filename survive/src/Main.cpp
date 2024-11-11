#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "../includes/Game.h"
#include "../includes/Player.h"
#include <memory>
#include <iostream>

#include "../includes/ResourceManager.h"

int main(int argc, char* argv[])
{
    // ResourceManager Must be Instantiated here -- DO NOT CHANGE
    ResourceManager::init(argv[0]);

    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Super&Cell", sf::Style::Fullscreen | sf::Style::Titlebar);
    window.setKeyRepeatEnabled(false);
    
    std::unique_ptr<Game> pGame = std::make_unique<Game>();
    if (!pGame->initialise())
    {
        std::cerr << "Game Failed to initialise" << std::endl;
        return 1;
    }
    
    sf::Clock clock;
	window.setFramerateLimit(144);
    // run the program as long as the window is open
    while (window.isOpen())
    {
		// Deltatime
		float dt = clock.restart().asSeconds();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    // "close requested" event: we close the window
                    window.close();
                    break;
                case sf::Event::KeyPressed:
					for (int i = 0; i < 2; i++)
					{
						if (pGame.get()->getPlayer(i)->getKeybinds().count(event.key.code))
   							 pGame->onKeyPressed(pGame.get()->getPlayer(i)->getKeybinds()[event.key.code], i);
					}
                    break;
                case sf::Event::KeyReleased:
                    for (int i = 0; i < 2; i++)
					{
						if (pGame.get()->getPlayer(i)->getKeybinds().count(event.key.code))
   							 pGame->onKeyReleased(pGame.get()->getPlayer(i)->getKeybinds()[event.key.code], i);
					}
                    break;
				case sf::Event::LostFocus:
					pGame.get()->resetInputs();
                default:
                    break;
            }
        }
        pGame->update(dt);
        
        // clear the window with black color
        window.clear(sf::Color::Black);
        
        window.draw(*pGame.get());
        
        // end the current frame
        window.display();
    }
    
    return 0;
}
