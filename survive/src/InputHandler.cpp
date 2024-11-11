#include "../includes/InputHandler.h"
#include "../includes/Weapon.h"
#include "../includes/Player.h"

GameInput::GameInput(Game* pGame, Player* pPlayer) :
    m_pGame(pGame), m_pPlayer(pPlayer)
{

    
}

GameInput::~GameInput()
{
    
}
void GameInput::resetInputs()
{
	m_inputData.m_movingUp = false;
	m_inputData.m_movingDown = false;
	m_inputData.m_movingLeft = false;
	m_inputData.m_movingRight = false;
	m_inputData.m_space = false;
	m_inputData.m_spaceReleased = true;
}

void GameInput::update(float deltaTime, const std::map<std::pair<int, int>, std::vector<sf::RectangleShape>> &map)
{
    if (m_inputData.hasInputs())
    {
        m_pPlayer->move(m_inputData, deltaTime, map);
    }

    if (m_inputData.m_space)
    {
        m_pPlayer->attack();
    }
}

void GameInput::onKeyPressed(std::string key)
{
    if (key == "MOVE_UP")
    {
        m_inputData.m_movingUp = true;
    }
    else if (key == "MOVE_DOWN")
    {
        m_inputData.m_movingDown = true;
    }
    else if (key == "MOVE_LEFT")
    {
        m_inputData.m_movingLeft = true;
    }
    else if (key == "MOVE_RIGHT")
    {
        m_inputData.m_movingRight = true;
    }
    else if (key == "ATTACK")
    {
        if (m_inputData.m_spaceReleased)
        {
            m_inputData.m_space = true;
        }
        m_inputData.m_spaceReleased = false;
    }
}

void GameInput::onKeyReleased(std::string key)
{
    if (key == "MOVE_UP")
    {
        m_inputData.m_movingUp = false;
    }
    else if (key == "MOVE_DOWN")
    {
        m_inputData.m_movingDown = false;
    }
    else if (key == "MOVE_LEFT")
    {
        m_inputData.m_movingLeft = false;
    }
    else if (key == "MOVE_RIGHT")
    {
        m_inputData.m_movingRight = false;
    }
    else if (key == "ATTACK")
    {
        m_inputData.m_space = false;
        m_inputData.m_spaceReleased = true;
    }
}
