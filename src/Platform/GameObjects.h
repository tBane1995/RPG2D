#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Collider;

enum class GameObjectType { 
	GameObject, 
	Nature, Object,
	Unit, Monster, Character, Player, 
	ItemOnMap, InventoryOnMap, 
	FlatObject, SmallObject, 
	Terrain, Floor, Water,
	Door, Furniture, Wall, Building
};

enum class ColliderType { Elipse, Rectangle };

class Collider
{
public:
	float width;
	float length;
	sf::Vector2f position;
	ColliderType type;
	sf::Shape* shape;
	

	Collider(float width, float length, sf::Vector2f position, ColliderType type);
	Collider(Collider* col);

	~Collider() {
		delete shape;	// sf::Shape* shape
	}

	void setPosition(sf::Vector2f position) {
		this->position = position;
		shape->setPosition(this->position);
	}

	void draw() {
		window->draw(*shape);
	}
};

class GameObject { 
public:
	std::string name;
	GameObjectType type;
	sf::Vector2f position;
	float height;
	SingleTexture* texture;
	
	std::vector < Collider* > colliders;
	sf::Text textname;

	bool collisioning;	// check the collision
	bool mouseIsHover;	// mouse is on GameObject
	bool isVisible;		
	bool isSelected;
	bool isInTheMainList;


	GameObject(std::string name, float x, float y, float width, float length, float height, bool collisioning, ColliderType col_type);
	GameObject(std::string name, float x, float y, float width, float length, float height, float width_left, float width_right);
	GameObject(GameObject* go, float x, float y);
	GameObject(std::string name);
	GameObject(std::string name, float x, float y);

	virtual ~GameObject();

	virtual void setPosition(sf::Vector2f position);
	void createTextname();
	virtual void mouseHovering();
	virtual void update(float dt) { 
		createTextname();
	}
	virtual void updateStatistic(float dt);
	virtual void draw()
	{
		window->draw(textname);
	}
	virtual void drawStatistics();
	virtual void drawAllStatistics();
};


extern std::vector < GameObject* > gameObjects;



bool collisionPrediction(GameObject* object, float dx, float dy);
bool collisionPrediction(GameObject* object, Point p, float dx, float dy);
