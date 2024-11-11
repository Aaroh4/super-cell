#include "../includes/PlayArea.h"

PlayArea::PlayArea(float inputTileSize): m_vertices(sf::Triangles)
{
	this->m_tileSize = inputTileSize;
}

void PlayArea::build()
{
	//Building the playable map
	for (int i = 0; i <  MapHeight; i++)
	{
		for (int j = 0; j < MapWidth; j++)
		{
			sf::RectangleShape temp;
 
			temp.setSize(sf::Vector2f(TileSize, TileSize));  
			temp.setPosition(j * TileSize, i * TileSize);

			sf::Vector2f pos = temp.getPosition();
            sf::Vector2f size = temp.getSize();

			sf::Vector2f topLeft = pos;
            sf::Vector2f topRight(pos.x + size.x, pos.y);
            sf::Vector2f bottomLeft(pos.x, pos.y + size.y);
            sf::Vector2f bottomRight(pos.x + size.x, pos.y + size.y);

			m_vertices.append(sf::Vertex(topLeft, sf::Color::Blue));
            m_vertices.append(sf::Vertex(topRight, sf::Color::Blue));
            m_vertices.append(sf::Vertex(bottomLeft, sf::Color::Blue));

        	m_vertices.append(sf::Vertex(bottomLeft, sf::Color::Blue));
            m_vertices.append(sf::Vertex(topRight, sf::Color::Blue));
            m_vertices.append(sf::Vertex(bottomRight, sf::Color::Blue));
			this->m_map[{temp.getPosition().x / 120, temp.getPosition().y / 120}].push_back(temp);
			
			if (i != 0 && i != MapHeight - 1)
				j += MapWidth - 2;
		}
	}
}

void PlayArea::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// Drawing with vertices which is faster than with shapes
    target.draw(m_vertices, states);
}

std::map<std::pair<int, int>, std::vector<sf::RectangleShape>>	PlayArea::getMap()
{
	return (m_map);
}
