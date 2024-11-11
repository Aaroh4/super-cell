#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <vector>

class Player;
class Game;

struct InputData
{
    bool m_movingUp = false;
    bool m_movingDown = false;
    bool m_movingLeft = false;
    bool m_movingRight = false;
    bool m_space = false;
    bool m_spaceReleased = true;

    bool hasInputs() { return m_movingUp || m_movingDown || m_movingLeft || m_movingRight || m_space;}
};

class GameInput
{
public:
    GameInput(Game* pGame, Player* pPlayer);
    ~GameInput();
    
    void update(float deltaTime, const std::map<std::pair<int, int>, std::vector<sf::RectangleShape>> &map);
    void onKeyPressed(std::string key);
    void onKeyReleased(std::string key);
	void resetInputs();
    
    
private:
    InputData m_inputData;
    Game* m_pGame;
    Player* m_pPlayer;
};
