#pragma once

#include "Rectangle.h"
#include "Weapon.h"
#include "../includes/InputHandler.h"
#include "../includes/Constants.h"
#include "../includes/Game.h"

#include <memory>
#include <unordered_map>

struct InputData;

class Game;
class Weapon;

enum eDirection
{
    LEFT,
    RIGHT
};

class Player : public Rectangle
{
public:
    Player(Game* pGame);
    virtual ~Player() {}
    
    bool initialise(int i);
    void move(InputData inputData, float deltaTime);
    void attack();
    void update(float deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool isDead() const { return m_isDead; }
    void setIsDead(bool isDead) { m_isDead = isDead; }

	void initKeybinds(int i);
	std::unordered_map<sf::Keyboard::Key, std::string>& getKeybinds() { return m_keybinds; }

    Weapon* getWeapon() { return m_pWeapon.get(); }

private:
    bool    m_isDead = false;
    eDirection m_direction = LEFT;
    Game*   m_pGame;
    std::unique_ptr<Weapon> m_pWeapon;
	std::unordered_map<sf::Keyboard::Key, std::string>	m_keybinds;
};
