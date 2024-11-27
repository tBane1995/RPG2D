#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Borders : public sf::Drawable, public sf::Transformable
{
public:
	sf::Vector2i coords;

	sf::VertexArray outlines;

	std::vector < short > tiles;

	Borders()
	{
	}

	void generate(Terrain* terrain, Terrain* topTerrain, Terrain* bottomTerrain, Terrain* leftTerrain, Terrain* rightTerrain);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(outlines, states);
	}
};
