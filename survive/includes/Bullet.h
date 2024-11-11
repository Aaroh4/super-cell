#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
	public:
		Bullet(sf::Vector2f pos, float radius, int damage, sf::Vector2f movement);
		Bullet(float x, float y, float radius, int damage, float xMov, float yMov);
		~Bullet() {};
		Bullet(const Bullet &input) = default;
		Bullet& operator=(const Bullet &input) = default;

		const sf::CircleShape &getSprite() const;
		void move(float deltaTime);
		void setMovement(const sf::Vector2f &input);
	private:
		sf::CircleShape m_sprite;
		int				m_damage;
		sf::Vector2f	m_movement;
};