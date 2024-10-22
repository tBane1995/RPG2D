#ifndef FlatObjects_hpp
#define FlatObjects_hpp

class FlatObject : public GameObject {
public:

	sf::Sprite sprite;
	
	FlatObject(string name, float width, float length, float height ) : GameObject(name, 0, 0, width, length, height, false, ColliderType::Elipse) {
		type = GameObjectType::FlatObject;
		this->texture = getSingleTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
	}

	FlatObject(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = GameObjectType::FlatObject;
		this->texture = getSingleTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*getSingleTexture(name)->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(position);
		
	}

	virtual ~FlatObject() {
	
	}

	virtual void setPosition(sf::Vector2f position) {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) {

	}

	virtual void draw() {
		
		if(mouseIsHover)
			GameObject::draw();
	
		window->draw(sprite);
	}
};

std::vector < FlatObject* > flatObjects;

bool isPathOnPosition( float x, float y) {
	// TO-DO
	for (auto& path : flatObjects) {
		if (pointInEllipse(x, y, path->position.x, path->position.y, path->collider->width/2.0f, path->collider->length / 2.0f))
			return true;
	}

	return false;
}

#endif