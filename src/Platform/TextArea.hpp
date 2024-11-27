#ifndef TextArea_hpp
#define TextArea_hpp

class TextArea {
public:
	wstring s;
	sf::Vector2f position;
	float characterSize = 16;
	float line_length;
	std::vector < wstring > lines;
	std::vector < sf::Text > texts;
	sf::RectangleShape rect;
	
	TextArea(wstring s, sf::Vector2f position = sf::Vector2f(0,0), float line_length = 0.0f) {
		this->s = s;
		this->position = position;
		this->line_length = line_length;

		// format the text (add enters)
		lines = wrapText(s, basicFont, characterSize, this->line_length);
		
		generateText();
		generateRect();
	}

	~TextArea() {

	}

	void generateText() {
		texts.clear();

		float i = 0;
		for (auto& line : lines) {
			sf::Text t;
			t.setFont(basicFont);
			t.setFillColor(textColor);
			t.setCharacterSize(characterSize);
			t.setString(line);

			sf::Vector2f textPos;
			textPos.x = position.x + characterSize * 0.2f;
			textPos.y = position.y + getLineHeight() * float(i);
			t.setPosition(textPos.x + cam->position.x, textPos.y + cam->position.y);
			texts.push_back(t);
			i += 1.0f;
		}
	}

	float getLineHeight() {
		return characterSize * 1.3f;
	}

	void generateRect() {
		sf::Vector2f size;
		if (texts.size() > 0 && line_length > 0.0f) {
			size.x = line_length;
			size.y = getLineHeight();
		}
		else if(!texts.empty()){
			size.x = float(texts.front().getLocalBounds().getSize().x) + characterSize * 0.5f;
			size.y = getLineHeight();
		}
		else {
			size.x = 0;
			size.y = 0;
		}
			
		rect.setSize(size);
		rect.setPosition(position.x+cam->position.x, position.y+cam->position.y);
		rect.setFillColor(panelColor);
	}

	void setRectSize(sf::Vector2f size) {
		rect.setSize(size);
	}

	void setWstring(wstring s) {

		this->s = s;
		lines = wrapText(this->s, basicFont, characterSize, this->line_length);
		
		generateText();
	}

	void setPosition(sf::Vector2f position) {
		this->position = position;

		rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
		generateText();

	}

	void setCharacterSize(short val) {
		
		characterSize = val;

		generateText();
		generateRect();
	}

	void setRectColor(sf::Color color) {
		rect.setFillColor(color);
	}

	void setTextColor(sf::Color color) {
		for (auto& text : texts)
			text.setFillColor(color);
		
	}

	sf::Vector2f getSize() {
		return rect.getSize();
	}

	void update() {
		
	}

	void draw() {
		window->draw(rect);
		for (auto& t : texts)
			window->draw(t);
	}
};

#endif