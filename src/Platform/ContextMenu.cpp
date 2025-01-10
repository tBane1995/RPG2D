#include "ContextMenu.h"
#include "Mouse.h"
#include "GameObjects.h"
#include "Camera.h"
#include "Character.h"
#include "Textures.h"
#include "CharacterInfoPanel.h"
#include "GameObjectsManager.h"
#include "Map.h"
#include "BuildingsManager.h"

ContextMenu::ContextMenu(GameObject* object) {

	_state = ContextMenuState::Idle;

	_position.x = worldMousePosition.x;
	_position.y = worldMousePosition.y;

	if (object == nullptr) {
		loadDefaultMenu();
	}
	else if (object->type == GameObjectType::Character) {
		loadCharacterMenu(object);
	}
	else if (object->type == GameObjectType::Building) {
		loadBuildingMenu(object);
	}
	else {
		loadObjectMenu(object);

	}

	// calculate max width of buttons
	short btn_width = 0;
	for (auto& btn : _buttons) {
		if (btn->rect.getSize().x > btn_width)
			btn_width = btn->rect.getSize().x;
	}

	// set the width for buttons
	sf::Vector2f btn_size(btn_width + 20, 30);
	for (auto& btn : _buttons) {
		btn->setRectSize(btn_size);
	}

	// positioning
	sf::Vector2f pos;
	pos.x = _position.x - cam->position.x;
	pos.y = _position.y - cam->position.y;

	for (short i = 0; i < _buttons.size(); i += 1) {
		_buttons[i]->setPosition(sf::Vector2f(pos.x, pos.y + i * 30));
	}
}

ContextMenu::~ContextMenu() {

	for (auto& btn : _buttons)
		delete btn;
}

void ContextMenu::loadDefaultMenu() {
	ButtonWithTextAndIcon* btn_undo = new ButtonWithTextAndIcon(L"undo", getSingleTexture("GUI/context_menu/btn_default"));
	ButtonWithTextAndIcon* btn_paste = new ButtonWithTextAndIcon(L"paste", getSingleTexture("GUI/context_menu/btn_default"));

	_buttons.push_back(btn_undo);
	_buttons.push_back(btn_paste);
}

void ContextMenu::loadCharacterMenu(GameObject* object) {
	Character* character = dynamic_cast <Character*>(object);

	ButtonWithTextAndIcon* btn_edit = new ButtonWithTextAndIcon(L"edit", getSingleTexture("GUI/context_menu/btn_edit"));
	btn_edit->onclick_func = [this, character]() {
		dialogs.push_back(new CharacterInfoPanel(character));
		};

	ButtonWithTextAndIcon* btn_copy = new ButtonWithTextAndIcon(L"copy", getSingleTexture("GUI/context_menu/btn_default"));
	ButtonWithTextAndIcon* btn_cut = new ButtonWithTextAndIcon(L"cut", getSingleTexture("GUI/context_menu/btn_default"));

	ButtonWithTextAndIcon* btn_remove = new ButtonWithTextAndIcon(L"remove", getSingleTexture("GUI/context_menu/btn_remove"));
	btn_remove->onclick_func = [this, character]() {
		deleteGameObjectFromMainLists(character);
		Chunk* chunk = nullptr;
		chunk = mapa->getChunk(character->position);
		if (chunk != nullptr)
			chunk->deleteGameObject(character);
		delete character;
		};

	ButtonWithTextAndIcon* btn_cancel = new ButtonWithTextAndIcon(L"cancel", getSingleTexture("GUI/context_menu/btn_cancel"));

	_buttons.push_back(btn_edit);
	_buttons.push_back(btn_copy);
	_buttons.push_back(btn_cut);
	_buttons.push_back(btn_remove);
	_buttons.push_back(btn_cancel);
}

void ContextMenu::loadBuildingMenu(GameObject* object) {
	Building* building = dynamic_cast <Building*>(object);

	// TO-DO
	ButtonWithTextAndIcon* btn_edit = new ButtonWithTextAndIcon(L"edit", getSingleTexture("GUI/context_menu/btn_edit"));
	ButtonWithTextAndIcon* btn_copy = new ButtonWithTextAndIcon(L"copy", getSingleTexture("GUI/context_menu/btn_default"));
	ButtonWithTextAndIcon* btn_cut = new ButtonWithTextAndIcon(L"cut", getSingleTexture("GUI/context_menu/btn_default"));
	ButtonWithTextAndIcon* btn_remove = new ButtonWithTextAndIcon(L"remove", getSingleTexture("GUI/context_menu/btn_remove"));
	ButtonWithTextAndIcon* btn_cancel = new ButtonWithTextAndIcon(L"cancel", getSingleTexture("GUI/context_menu/btn_cancel"));

	_buttons.push_back(btn_edit);
	_buttons.push_back(btn_copy);
	_buttons.push_back(btn_cut);
	_buttons.push_back(btn_remove);
	_buttons.push_back(btn_cancel);
}

void ContextMenu::loadObjectMenu(GameObject* object) {
	ButtonWithTextAndIcon* btn_copy = new ButtonWithTextAndIcon(L"copy", getSingleTexture("GUI/context_menu/btn_default"));
	ButtonWithTextAndIcon* btn_cut = new ButtonWithTextAndIcon(L"cut", getSingleTexture("GUI/context_menu/btn_default"));

	ButtonWithTextAndIcon* btn_remove = new ButtonWithTextAndIcon(L"remove", getSingleTexture("GUI/context_menu/btn_remove"));
	btn_remove->onclick_func = [this, object]() {
		deleteGameObjectFromMainLists(object);
		Chunk* chunk = nullptr;
		chunk = mapa->getChunk(object->position);
		if (chunk != nullptr)
			chunk->deleteGameObject(object);
		delete object;
		};

	ButtonWithTextAndIcon* btn_cancel = new ButtonWithTextAndIcon(L"cancel", getSingleTexture("GUI/context_menu/btn_cancel"));

	_buttons.push_back(btn_copy);
	_buttons.push_back(btn_cut);
	_buttons.push_back(btn_remove);
	_buttons.push_back(btn_cancel);

}

void ContextMenu::handleEvent(sf::Event& event) {

	for (auto& btn : _buttons) {
		btn->handleEvent(event);
	}

	if (event.type == sf::Event::MouseButtonReleased) {
		_state = ContextMenuState::Close;
		unselectGameObjects();
	}
}

void ContextMenu::update() {

	sf::Vector2f pos;
	pos.x = _position.x - cam->position.x;
	pos.y = _position.y - cam->position.y;

	for (short i = 0; i < _buttons.size(); i += 1) {
		_buttons[i]->setPosition(sf::Vector2f(pos.x, pos.y + i * 30));
		_buttons[i]->update();
	}


}

void ContextMenu::draw() {

	for (auto& btn : _buttons) {
		btn->draw();
	}
}

ContextMenu* context_menu = nullptr;