#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <vector>
#include "Constants.h"
#include "PlayArea.h"
#include "../includes/Bullet.h"

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
	void resetInputs();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    State getState() const { return m_state; }
    
    void onKeyPressed(std::string key, size_t i);
    void onKeyReleased(std::string key, size_t i);

	void pushBullet(Bullet input);

    Player* getPlayer(const int &i) const;
private:
    std::vector<std::unique_ptr<Player>> m_pPlayers;
	std::unique_ptr<PlayArea>	m_pPlayArea;

    State m_state;
    std::unique_ptr<sf::Clock> m_pClock;
    std::vector<std::unique_ptr<GameInput>> m_pGameInputs;

	std::vector<Bullet>	m_bullets;
    sf::Font m_font;
};
