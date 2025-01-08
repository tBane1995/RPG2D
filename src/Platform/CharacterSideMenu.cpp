#include "CharacterSideMenu.h"
#include "GameObjectsManager.h"
#include "Map.h"
#include "CharacterInfoPanel.h"
#include "BuildingsManager.h"
#include "GameObjectsManager.h"
#include "GUI.h"

GameObjectSideMenu::GameObjectSideMenu(GameObject* object) {

	_object = object;

	_state = GameObjectSideMenuState::Idle;

	if (object->type == GameObjectType::Character) {
		loadCharacterSideMenu(_object);
		// edit
		// remove
		// cancel
	}
	else if (object->type == GameObjectType::Building) {
		loadBuildingSideMenu(_object);
		// edit
		// remove
		// cancel
	}

	if (_buttons.empty()) {
		_state = GameObjectSideMenuState::Close;
	}
}

GameObjectSideMenu::~GameObjectSideMenu() {

	for (auto& btn : _buttons)
		delete btn;
}

void GameObjectSideMenu::loadCharacterSideMenu(GameObject* object) {
	Character* character = dynamic_cast <Character*>(object);

	ButtonWithImage* btn_edit = new ButtonWithImage(getSingleTexture("GUI/character_menu/btn_info"));
	btn_edit->onclick_func = [this, character]() {
		dialogs.push_back(new CharacterInfoPanel(character));
		_state = GameObjectSideMenuState::Close;
		};

	ButtonWithImage* btn_remove = new ButtonWithImage(getSingleTexture("GUI/character_menu/btn_remove"));
	btn_remove->onclick_func = [this, character]() {
		deleteGameObjectFromMainLists(character);
		Chunk* chunk = nullptr;
		chunk = mapa->getChunk(character->position);
		if (chunk != nullptr)
			chunk->deleteGameObject(character);
		delete character;
		_state = GameObjectSideMenuState::Close;
		};

	ButtonWithImage* btn_cancel = new ButtonWithImage(getSingleTexture("GUI/character_menu/btn_cancel"));
	btn_cancel->onclick_func = [this]() {
		_state = GameObjectSideMenuState::Close;
		};

	_buttons.push_back(btn_edit);
	_buttons.push_back(btn_remove);
	_buttons.push_back(btn_cancel);
}

void GameObjectSideMenu::loadBuildingSideMenu(GameObject* object) {
	Building* building = dynamic_cast <Building*>(object);

	// TO-DO
	ButtonWithImage* btn_edit = new ButtonWithImage(getSingleTexture("GUI/character_menu/btn_info"));
	ButtonWithImage* btn_remove = new ButtonWithImage(getSingleTexture("GUI/character_menu/btn_info"));
	ButtonWithImage* btn_cancel = new ButtonWithImage(getSingleTexture("GUI/character_menu/btn_info"));

	_buttons.push_back(btn_edit);
	_buttons.push_back(btn_remove);
	_buttons.push_back(btn_cancel);
}

void GameObjectSideMenu::handleEvent(sf::Event& event) {

	for (auto& btn : _buttons) {
		btn->handleEvent(event);
	}

	if (event.type == sf::Event::MouseButtonReleased) {
		_state = GameObjectSideMenuState::Close;
		unselectGameObjects();
	}
}

void GameObjectSideMenu::update() {

	GUIwasOpen = true;

	float menu_hgh = 3 * 32 + 2 * 8;

	sf::Vector2f pos;
	pos.x = _object->position.x + _object->colliders[0]->width / 2.0f + 16.0f - cam->position.x + 32.0f;
	pos.y = _object->position.y - _object->height - cam->position.y - menu_hgh / 2.0f;

	if (_object->type == GameObjectType::Building) {
		pos.y -= dynamic_cast<Building*>(_object)->size.y * 16;
	}

	for (short i = 0; i < _buttons.size(); i += 1) {
		_buttons[i]->setPosition(sf::Vector2f(pos.x, pos.y + i * 32 + i * 8));
		_buttons[i]->update();
	}


}

void GameObjectSideMenu::draw() {

	for (auto& btn : _buttons) {
		btn->draw();
	}
}

GameObjectSideMenu* gameobject_side_menu = nullptr;
