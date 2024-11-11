#include "../includes/Bullet.h"

Bullet::Bullet(sf::Vector2f pos, float radius, int damage, sf::Vector2f movement)
{
	m_damage = damage;
	m_sprite.setPosition(pos);
	m_sprite.setRadius(radius);
	m_sprite.setFillColor(sf::Color::Yellow);
	m_movement = movement;
}
		
Bullet::Bullet(float x, float y, float radius, int damage, float xMov, float yMov)
{
	m_damage = damage;
	m_sprite.setPosition(x, y);
	m_sprite.setRadius(radius);
	m_sprite.setFillColor(sf::Color::Yellow);
	m_movement = {xMov, yMov};
}

void Bullet::move(float deltaTime)
{
	m_sprite.move(m_movement * deltaTime);
}

void Bullet::setMovement(const sf::Vector2f &input)
{
	m_movement = input;
}
const sf::CircleShape &Bullet::getSprite() const
{
	return(m_sprite);
}
