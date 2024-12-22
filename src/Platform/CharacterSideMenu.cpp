#include "CharacterSideMenu.h"

CharacterSideMenu::CharacterSideMenu(Character* character) {
	this->character = character;

	state = CharacterSideMenuState::Idle;

	sf::Vector2f position;
	position.x = character->position.x + character->colliders[0]->width / 2.0f + 16.0f - cam->position.x;
	position.y = character->position.y - character->height - 32.0f - cam->position.y;

	btn_info = new ButtonWithImage(getSingleTexture("GUI/character_menu/btn_info"), sf::Vector2f(position.x, position.y + 0));
	btn_info->onclick_func = [this]() {
		dialogs.push_back(new Panel());
		state = CharacterSideMenuState::Close;
		};

	btn_remove = new ButtonWithImage(getSingleTexture("GUI/character_menu/btn_remove"), sf::Vector2f(position.x, position.y + 32 + 8));
	btn_remove->onclick_func = [this]() {
		dialogs.push_back(new Panel());
		state = CharacterSideMenuState::Close;
		};

	btn_cancel = new ButtonWithImage(getSingleTexture("GUI/character_menu/btn_cancel"), sf::Vector2f(position.x, position.y + 64 + 16));
	btn_cancel->onclick_func = [this]() {
		state = CharacterSideMenuState::Close;
		};
}

CharacterSideMenu::~CharacterSideMenu() {
	delete btn_info;
	delete btn_remove;
	delete btn_cancel;
}

void CharacterSideMenu::update() {

	sf::Vector2f position;
	position.x = character->position.x + character->colliders[0]->width / 2.0f + 16.0f - cam->position.x;
	position.y = character->position.y - character->height - 32.0f - cam->position.y;

	btn_info->setPosition(sf::Vector2f(position.x, position.y + 0));
	btn_remove->setPosition(sf::Vector2f(position.x, position.y + 32 + 8));
	btn_cancel->setPosition(sf::Vector2f(position.x, position.y + 64 + 16));

	btn_info->update();
	btn_remove->update();
	btn_cancel->update();

}

void CharacterSideMenu::handleEvent(sf::Event& event) {
	btn_info->handleEvent(event);
	btn_remove->handleEvent(event);
	btn_cancel->handleEvent(event);

	if (event.type == sf::Event::KeyPressed) {
		state = CharacterSideMenuState::Close;
	}
	else if (!(btn_info->state == ButtonState::Pressed || btn_remove->state == ButtonState::Pressed || btn_cancel->state == ButtonState::Pressed)) {
		state = CharacterSideMenuState::Close;
	}
}

void CharacterSideMenu::draw() {
	btn_info->draw();
	btn_remove->draw();
	btn_cancel->draw();
}

CharacterSideMenu* character_side_menu = nullptr;