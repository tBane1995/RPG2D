#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class HitText {
public:
	sf::Vector2f position;
	sf::Text text;
	sf::Time startTime;

	HitText(sf::Vector2f position, std::string value, sf::Color color);

	~HitText() { }

	void update() {
		short deleter = (currentTime-startTime).asMilliseconds()*0.1;
		text.setPosition(position.x, position.y-deleter);
	}

	void draw() {
		window->draw(text);
	}

};

class HitTextsManager {
public:
	std::vector < HitText* > hits;

	HitTextsManager() {
		hits.clear();
	}

	void addHitText(sf::Vector2f position, string value, sf::Color color = dialoguesColor) {

		hits.push_back(new HitText(position, value, color));
		
	}

	void deleteOldHits();
	void update();
	void draw();
};

extern HitTextsManager* hits;
