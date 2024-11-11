#include "../includes/Player.h"
#include "../includes/MathUtils.h"

Player::Player(Game* pGame) :
    Rectangle(sf::Vector2f(PlayerWidth, PlayerHeight)),
    m_pGame(pGame),
    m_pWeapon(std::make_unique<Weapon>())
{
    setOrigin(sf::Vector2f(0.0f, 0.0f));
}

bool Player::initialise(int i)
{
    m_sprite.setTexture(*m_pGame->getPlayerTexture());
    m_sprite.setScale(3.5f, 3.5f);
    setIsDead(false);
    setPosition(ScreenWidth / 2, ScreenHeight / 2);
    m_sprite.setPosition(getPosition());
	initKeybinds(i);
    return true;
}

void Player::initKeybinds(int i)
{
	if (i % 2 == 0)
	{
		m_keybinds[sf::Keyboard::A] = "MOVE_LEFT";
		m_keybinds[sf::Keyboard::D] = "MOVE_RIGHT";
		m_keybinds[sf::Keyboard::W] = "MOVE_UP";
		m_keybinds[sf::Keyboard::S] = "MOVE_DOWN";
		m_keybinds[sf::Keyboard::C] = "ATTACK";
	}
	else
	{
		m_keybinds[sf::Keyboard::Left] = "MOVE_LEFT";
		m_keybinds[sf::Keyboard::Right] = "MOVE_RIGHT";
		m_keybinds[sf::Keyboard::Up] = "MOVE_UP";
		m_keybinds[sf::Keyboard::Down] = "MOVE_DOWN";
		m_keybinds[sf::Keyboard::M] = "ATTACK";
	}
}

void Player::move(InputData inputData, float deltaTime, const std::map<std::pair<int, int>, std::vector<sf::RectangleShape>> &map)
{
    float xSpeed = 0.0f;
    float ySpeed = 0.0f;
    
    xSpeed -= inputData.m_movingLeft * PlayerSpeed;
    xSpeed += inputData.m_movingRight * PlayerSpeed;

    ySpeed -= inputData.m_movingUp * PlayerSpeed;
    ySpeed += inputData.m_movingDown * PlayerSpeed;
    
	sf::Vector2f movement(xSpeed, ySpeed);

	sf::Vector2f normalizedMovement = VecNormalized(movement);

	sf::Vector2f finalMovement = normalizedMovement * PlayerSpeed;

    sf::Transformable::move(finalMovement * deltaTime);
    setPosition(std::clamp(getPosition().x, 0.0f, (float)ScreenWidth), getPosition().y);

    if (m_pWeapon->isActive() == false)
    {
        if (inputData.m_movingLeft == true && inputData.m_movingRight == false)
            m_direction = LEFT;
        else if (inputData.m_movingLeft == false && inputData.m_movingRight == true)
            m_direction = RIGHT;
    }
}

void Player::attack()
{
    m_pWeapon->setActive(true);
}

void Player::update(float deltaTime)
{
    sf::Vector2f weaponSize = m_pWeapon->getSize();

    m_sprite.setPosition(getPosition());
    m_pWeapon->setPosition(sf::Vector2f(
        getCenter().x - (m_direction == LEFT ? weaponSize.x : 0.0f),
        getCenter().y - weaponSize.y / 2.0f));
    m_pWeapon->update(deltaTime);
	m_chunkPosX = getPosition().x / ChunkSize;
	m_chunkPosY = getPosition().x / ChunkSize;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Rectangle::draw(target, states);
    m_pWeapon->draw(target, states);
}