#ifndef NatureObjects_hpp
#define NatureObjects_hpp

class Nature : public GameObject {
public:
	sf::Sprite sprite;

	Nature(string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, true, ColliderType::Elipse) {
		type = GameObjectType::Nature;
		this->texture = getSingleTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(position);

	}

	Nature(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = GameObjectType::Nature;

		this->texture = getSingleTexture(name);

		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(position);

	}

	virtual ~Nature() {
	
	}

	virtual void setPosition(sf::Vector2f position) {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) { 

	}

	virtual void draw() {

		if (mouseIsHover)
			GameObject::draw();

		//window->draw(shadow);
		Shader* s = getShader("shaders/shadow");
		s->shader->setUniform("texture", texture->texture);
		s->shader->setUniform("camPosition", cam->position);
		s->shader->setUniform("resolution", sf::Vector2f(screenWidth, screenHeight));
		window->draw(sprite, s->shader);
		window->draw(sprite);

		
	}
};

std::vector < Nature* > natures;

#endif