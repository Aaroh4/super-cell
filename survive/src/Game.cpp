#include "../includes/Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "../includes/ResourceManager.h"
#include "../includes/InputHandler.h"
#include "../includes/Weapon.h"
#include "../includes/Player.h"
#include "../includes/Rectangle.h"

Game::Game() :
    m_state(State::WAITING),
    m_pClock(std::make_unique<sf::Clock>()),
    m_pPlayers(),
	m_pPlayArea(std::make_unique<PlayArea>(TileSize))
{
	// Adding players and their movements
	m_pPlayers.push_back(std::make_unique<Player>(this));
	m_pGameInputs.push_back(std::make_unique<GameInput>(this, m_pPlayers[0].get()));
    m_pPlayers.push_back(std::make_unique<Player>(this));
	m_pGameInputs.push_back(std::make_unique<GameInput>(this, m_pPlayers[1].get()));
}

Game::~Game()
{
}

bool Game::initialise()
{
    /*
        PAY ATTENTION HIVER!
            If you want to load any assets (fonts, textures) please use the pattern shown below
    */

    if (!m_font.loadFromFile(ResourceManager::getFilePath("Lavigne.ttf")))
    {
        std::cerr << "Unable to load font" << std::endl;
        return false;
    }
    if (!m_playerTexture.loadFromFile(ResourceManager::getFilePath("player.png")))
    {
        std::cerr << "Unable to load texture" << std::endl;
        return false;
    }

    resetLevel();
    return true;
}

void Game::resetInputs()
{
	for (size_t i = 0; i < m_pGameInputs.size(); i++)
		m_pGameInputs[i].get()->resetInputs();
}

void Game::resetLevel()
{
	int	i = 0;
	for (auto& player : m_pPlayers)
	{
		i++;
   		player->initialise(i);
	}
	m_pPlayArea->build();
	m_pClock->restart();
}

void Game::update(float deltaTime)
{
    switch (m_state)
    {
        case State::WAITING:
        {
            if (m_pClock->getElapsedTime().asSeconds() >= 3.f)
            {
                m_state = State::ACTIVE;
                m_pClock->restart();
            }
        }
        break;
            
        case State::ACTIVE:
        {
			for (size_t i = 0; i < m_pPlayers.size(); i++)
			{
			  	m_pGameInputs[i]->update(deltaTime, m_pPlayArea->getMap());
            	m_pPlayers[i]->update(deltaTime);
			}
            //if (m_pPlayer->isDead())
            //{
            //    m_state = State::WAITING;
            //    resetLevel();
            //}
        }
        break;
    }
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //  Draw texts.
    if (m_state == State::WAITING)
    {
        sf::Text startText;
        startText.setFont(m_font);
        startText.setString("Game Start!");
        startText.setFillColor(sf::Color::White);
        startText.setPosition(80.0f, 80.0f);
        startText.setStyle(sf::Text::Bold);
        target.draw(startText);
    }
    else
    {
        sf::Text timerText;
        timerText.setFont(m_font);
        timerText.setFillColor(sf::Color::White);
        timerText.setStyle(sf::Text::Bold);
        timerText.setString(std::to_string((int)m_pClock->getElapsedTime().asSeconds()));
        timerText.setPosition(sf::Vector2f((ScreenWidth - timerText.getLocalBounds().getSize().x) * 0.5, 20));
        target.draw(timerText);
    }

    // Draw player.
	for (auto& player : m_pPlayers)
		player->draw(target, states);
	
	// Draw Map/PlayArea
	m_pPlayArea->draw(target, states);
}


void Game::onKeyPressed(std::string key, size_t i)
{
    m_pGameInputs[i]->onKeyPressed(key);
}

void Game::onKeyReleased(std::string key, size_t i)
{
    m_pGameInputs[i]->onKeyReleased(key);
}

Player* Game::getPlayer(const int &i) const 
{
    return m_pPlayers[i].get();
}
