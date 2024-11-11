#pragma once

#include "../includes/InputHandler.h"
#include "../includes/Constants.h"
#include "../includes/Game.h"
#include "../includes/Bullet.h"

#include <memory>
#include <unordered_map>

struct InputData;

class Game;
class Weapon;

enum eDirection
{
    LEFT,
    RIGHT,
	UP,
	DOWN
};

class Player
{
public:
    Player(Game* pGame);
    ~Player() {}
    
    bool initialise(int i);
    void move(InputData inputData, float deltaTime, std::map<std::pair<int, int>, std::vector<sf::RectangleShape>> map);
    void attack(sf::Clock clock);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool isDead() const { return m_isDead; }
    void setIsDead(bool isDead) { m_isDead = isDead; }

	float checkCollisionX(float x,const std::vector<sf::RectangleShape> &blocks);
	float checkCollisionY(float y,const std::vector<sf::RectangleShape> &blocks);

	const sf::CircleShape  &getCollider() const;

	void initKeybinds(int i);
	std::unordered_map<sf::Keyboard::Key, std::string>& getKeybinds() { return m_keybinds; }

private:
	sf::CircleShape	m_collision;
    bool    m_isDead = false;
    eDirection m_direction = LEFT;
    Game*   m_pGame;
	std::unordered_map<sf::Keyboard::Key, std::string>	m_keybinds;
	sf::Vector2f		m_lastDir;
	float				m_lastTimeShot;
};
