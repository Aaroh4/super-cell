#include "../includes/Player.h"
#include "../includes/MathUtils.h"

Player::Player(Game* pGame) :
    m_pGame(pGame)
{
}

bool Player::initialise(int i)
{
	m_lastTimeShot = 0;
	m_collision.setRadius(20);
	m_collision.setOutlineColor(sf::Color::Red);
	m_collision.setFillColor(sf::Color::Magenta);
    setIsDead(false);
	if (i % 2 == 0)
		m_collision.setPosition(40, 40);
	else
    	m_collision.setPosition(1500, 1100);
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
		m_keybinds[sf::Keyboard::R] = "ATTACK";
	}
	else // surely coders have more than a 60% keyboard
	{
		m_keybinds[sf::Keyboard::Left] = "MOVE_LEFT";
		m_keybinds[sf::Keyboard::Right] = "MOVE_RIGHT";
		m_keybinds[sf::Keyboard::Up] = "MOVE_UP";
		m_keybinds[sf::Keyboard::Down] = "MOVE_DOWN";
		m_keybinds[sf::Keyboard::M] = "ATTACK";
	}
}

void Player::move(InputData inputData, float deltaTime, std::map<std::pair<int, int>, std::vector<sf::RectangleShape>> map)
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
	finalMovement *= deltaTime;

	finalMovement.x = checkCollisionX(finalMovement.x, map[{(m_collision.getPosition().x + finalMovement.x) / ChunkSize, m_collision.getPosition().y / ChunkSize}]);
	finalMovement.y = checkCollisionY(finalMovement.y, map[{m_collision.getPosition().x / ChunkSize, (m_collision.getPosition().y + finalMovement.y) / ChunkSize}]);

  	m_collision.move(finalMovement);
	if (finalMovement.x != 0 || finalMovement.y != 0)
		m_lastDir = finalMovement;
}

float Player::checkCollisionX(float  x, const std::vector<sf::RectangleShape> &blocks)
{
	sf::CircleShape futureBounds;
	futureBounds.setRadius(m_collision.getRadius());
	futureBounds.setPosition(m_collision.getPosition());

    float direction = (x > 0) ? 1.f : -1.f;

	float pos = 0.f;

	while (abs(pos) <= abs(x))
	{
		pos += direction;
		futureBounds.move(direction, 0);
		for (size_t i = 0; i < blocks.size(); i++)
		{
			if (futureBounds.getGlobalBounds().intersects(blocks[i].getGlobalBounds())) 
			{																			
				return (pos - direction);											
			}
		}
	}
	return (x);
}

float Player::checkCollisionY(float y, const std::vector<sf::RectangleShape> &blocks)
{
	sf::CircleShape futureBounds;
	futureBounds.setRadius(m_collision.getRadius());
	futureBounds.setPosition(m_collision.getPosition());

	float direction = (y > 0) ? 1.f : -1.f;

	float pos = 0.f;

	while (abs(pos) <= abs(y))
	{
		pos += direction;
		futureBounds.move(0, direction);
		for (size_t i = 0; i < blocks.size(); i++)
		{
			if (futureBounds.getGlobalBounds().intersects(blocks[i].getGlobalBounds()))
			{	
				return (pos - direction);
			}
		}
	}
	return (y);
}

void Player::attack(sf::Clock clock)
{
	if (m_lastTimeShot + 0.5f < clock.getElapsedTime().asSeconds())
	{
		Bullet temp(m_collision.getPosition() + m_lastDir * 50.f, 5, 10, m_lastDir * 500.f);
		m_pGame->pushBullet(temp);
		m_lastTimeShot = clock.getElapsedTime().asSeconds();
	}
}


const sf::CircleShape  &Player::getCollider() const
{
	return (m_collision);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// Drawing bullets
	target.draw(m_collision);
}