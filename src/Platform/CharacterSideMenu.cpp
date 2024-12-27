#include "CharacterSideMenu.h"
#include "GameObjectsManager.h"
#include "Map.h"
#include "CharacterInfoPanel.h"

CharacterSideMenu::CharacterSideMenu(Character* character) {
	_character = character;

	state = CharacterSideMenuState::Idle;


	float menu_hgh = 3 * 32 + 2 * 8;

	sf::Vector2f pos;
	pos.x = character->position.x + character->colliders[0]->width / 2.0f + 16.0f - cam->position.x + 32.0f;
	pos.y = character->position.y - character->height - cam->position.y - menu_hgh / 2.0f;

	btn_info = new ButtonWithImage(getSingleTexture("GUI/character_menu/btn_info"), sf::Vector2f(pos.x, pos.y + 0));
	btn_info->onclick_func = [this]() {
		dialogs.push_back(new CharacterInfoPanel(_character));
		state = CharacterSideMenuState::Close;
		};

	btn_remove = new ButtonWithImage(getSingleTexture("GUI/character_menu/btn_remove"), sf::Vector2f(pos.x, pos.y + 32 + 8));
	btn_remove->onclick_func = [this]() {
		deleteGameObjectFromMainLists(_character);
		Chunk* chunk = nullptr;
		chunk = mapa->getChunk(_character->position);
		if (chunk != nullptr)
			chunk->deleteGameObject(_character);
		delete _character;
		state = CharacterSideMenuState::Close;
		};

	btn_cancel = new ButtonWithImage(getSingleTexture("GUI/character_menu/btn_cancel"), sf::Vector2f(pos.x, pos.y + 64 + 16));
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

	float menu_hgh = 3 * 32 + 2 * 8;

	sf::Vector2f pos;
	pos.x = _character->position.x + _character->colliders[0]->width / 2.0f + 16.0f - cam->position.x + 32.0f;
	pos.y = _character->position.y - _character->height - cam->position.y - menu_hgh / 2.0f;

	btn_info->setPosition(sf::Vector2f(pos.x, pos.y + 0));
	btn_remove->setPosition(sf::Vector2f(pos.x, pos.y + 32 + 8));
	btn_cancel->setPosition(sf::Vector2f(pos.x, pos.y + 64 + 16));

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
