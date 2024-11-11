#pragma once

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <utility>
#include "../includes/Constants.h"

class PlayArea
{
	public:
		PlayArea(float inputTileSize);
		~PlayArea() {}

		void build();
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		std::map<std::pair<int, int>, std::vector<sf::RectangleShape>>	getMap();
	private:
		std::map<std::pair<int, int>, std::vector<sf::RectangleShape>> m_map;
		float	m_tileSize;
		sf::VertexArray								m_vertices;

};