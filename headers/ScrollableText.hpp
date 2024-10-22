#ifndef ScrollableText_hpp
#define ScrollableText_hpp

class ScrollableText : public Dialog {
public:

	sf::Vector2f position;
	sf::RectangleShape rect;
	float width = 600;
	float height = 400;
	float margin = 8;
	TextArea* textarea;
	Scrollbar* scrollbar;
	sf::RenderTexture text_texture;
	sf::Sprite text_sprite;

	ScrollableText(wstring text) : Dialog(DialogType::ScrollableText) {

		textarea = new TextArea(text, cam->position, width - 2 * margin);
		textarea->setPosition(sf::Vector2f(- width/2.0f + margin, - height/2.0f + margin));

		rect = sf::RectangleShape(sf::Vector2f(width, height));
		rect.setFillColor(panelColor);
		rect.setPosition(cam->position.x - width / 2.0f, cam->position.y - height / 2.0f);

		sf::Vector2f scrollbar_size = sf::Vector2f(16, height);
		sf::Vector2f scrollbar_position = sf::Vector2f(width/2.0f, -height/2.0f);
		float scroll_max = textarea->getSize().y - height + textarea->getLineHeight();
		float scroll_len = height/scroll_max;
		scrollbar = new Scrollbar(scrollbar_size, scrollbar_position, 0, scroll_max, 0, scroll_len);
		
		text_texture.create(width-2*margin, height-2*margin);
		sf::View v = sf::View(sf::FloatRect(sf::Vector2f(cam->position.x-(width-2*margin)/2.0f, cam->position.y-(height-2*margin)/2.0f), sf::Vector2f(width-2*margin, height-2*margin)));
		text_texture.setView(v);
		text_texture.setSmooth(true);
		text_texture.clear(sf::Color::Transparent);
		text_texture.draw(textarea->rect);
		for (auto& text : textarea->texts)
			text_texture.draw(text);
		text_texture.display();
		text_sprite = sf::Sprite(text_texture.getTexture());
		text_sprite.setPosition(cam->position.x + position.x-width / 2.0f + margin, cam->position.y + position.y -height / 2.0f + margin);

	}

	~ScrollableText() {
		delete textarea;
		delete scrollbar;
	}

	virtual void update(sf::Event& event) {

		scrollbar->update(event);

		sf::Vector2f position;
		position.x = textarea->position.x;
		position.y = margin -scrollbar->scrollValue - height / 2.0f;
		textarea->setPosition(position);

		sf::View v = sf::View(sf::FloatRect(sf::Vector2f(cam->position.x-(width-2*margin)/2.0f,cam->position.y -(height-2*margin)/2.0f), sf::Vector2f(width-2*margin, height-2*margin)));
		text_texture.setView(v);
		text_texture.clear(sf::Color::Transparent);
		text_texture.draw(textarea->rect);
		for (auto& text : textarea->texts)
			text_texture.draw(text);
		text_texture.display();

	}

	virtual void draw() {
		window->draw(rect);
		scrollbar->draw();
		window->draw(text_sprite);
	}
};

#endif