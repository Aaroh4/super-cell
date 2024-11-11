#include "../includes/Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "../includes/ResourceManager.h"
#include "../includes/InputHandler.h"
#include "../includes/Player.h"

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

    resetLevel();
    return true;
}

void Game::resetInputs()
{
	for (size_t i = 0; i < m_pGameInputs.size(); i++)
		m_pGameInputs[i].get()->resetInputs();
}

void Game::pushBullet(Bullet input)
{
	m_bullets.push_back(input);
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

#include <iostream>

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
				if (m_pPlayers[i]->isDead())
				{
					m_state = State::WAITING;
					resetLevel();
				}
			  	m_pGameInputs[i]->update(deltaTime, m_pPlayArea->getMap(), *m_pClock.get());
			}
			for (size_t i = 0; i < m_bullets.size(); i++)
			{
				if (m_bullets[i].getSprite().getPosition().x >= ScreenWidth || m_bullets[i].getSprite().getPosition().y >= ScreenHeight
				|| m_bullets[i].getSprite().getPosition().x < 0 || m_bullets[i].getSprite().getPosition().y < 0)
				{
					m_bullets.erase(m_bullets.begin() + i);
					i--;
					continue;
				}
				else
					m_bullets[i].move(deltaTime);
				if (m_pPlayers[0].get()->getCollider().getGlobalBounds().intersects(m_bullets[i].getSprite().getGlobalBounds()))
				{
					m_pPlayers[0].get()->setIsDead(true);
					break ;
				}
			}            
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

    // Draw player.
	for (auto& player : m_pPlayers)
		player->draw(target, states);
	
	for (size_t i = 0; i < m_bullets.size(); i++)
		target.draw(m_bullets[i].getSprite());
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
