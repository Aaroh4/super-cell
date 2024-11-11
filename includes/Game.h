#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <vector>
#include "Constants.h"

class Player;
class Game;
class GameInput;

namespace sf { class Clock; }

class Game : public sf::Drawable
{
public:
    
    enum class State
    {
        WAITING,
        ACTIVE,
    };
    
    Game();
    ~Game();
    
    bool initialise();
    void update(float deltaTime);
    void resetLevel();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    State getState() const { return m_state; }
    
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);

    Player* getPlayer(const int &i) const;
    sf::Texture* getPlayerTexture() { return &m_playerTexture; }
private:
    std::vector<std::unique_ptr<Player>> m_pPlayers;


    State m_state;
    std::unique_ptr<sf::Clock> m_pClock;
    std::unique_ptr<GameInput> m_pGameInput;

    
    sf::Font m_font;
    sf::Texture m_playerTexture;
};
