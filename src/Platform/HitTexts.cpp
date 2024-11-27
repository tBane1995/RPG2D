#include "HitTexts.h"

HitText::HitText(sf::Vector2f position, std::string value, sf::Color color) {
	this->position = position;
	startTime = currentTime;

	text = sf::Text();
	text.setFont(basicFont);
	text.setFillColor(color);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2);
	text.setCharacterSize(20);
	text.setString(value);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		
}

	~HitText() { }

	void update() {
		short deleter = (currentTime-startTime).asMilliseconds()*0.1;
		text.setPosition(position.x, position.y-deleter);
	}

	void draw() {
		window->draw(text);
	}

};


void HitTextsManager::deleteOldHits() {
	std::vector < HitText* > newHits;
	newHits.clear();

	for (auto& hit : hits) {
		if ((currentTime-hit->startTime).asSeconds() < 0.5) {
			newHits.push_back(hit);
		}
	}

	hits = newHits;
}

void HitTextsManager::update() {
		
	deleteOldHits();
		
	for (auto& hit : hits) {
		hit->update();
	}
}

void HitTextsManager::draw() {

	for (auto& hit : hits)
		hit->draw();
}

HitTextsManager* hits = new HitTextsManager();
