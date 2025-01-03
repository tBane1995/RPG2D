#include "CharacterInfoPanel.h"

CharacterInfoPanel::CharacterInfoPage::CharacterInfoPage(CharacterInfoPanel* parent) {
	this->parent = parent;
}

void CharacterInfoPanel::CharacterInfoPage::handleEvent(sf::Event& event) {

}

void CharacterInfoPanel::CharacterInfoPage::update() {

}

void CharacterInfoPanel::CharacterInfoPage::draw() {

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CharacterInfoPanel::Statistics::Statistics::Statistics(CharacterInfoPanel* parent) : CharacterInfoPage(parent) {
	stats_names.push_back(new TextArea(L"NAME"));
	stats_values.push_back(new TextArea(ConvertUtf8ToWide(parent->_character->name)));

	stats_names.push_back(new TextArea(L"ID"));
	stats_values.push_back(new TextArea(L"0"));

	//
	stats_names.push_back(new TextArea(L""));
	stats_values.push_back(new TextArea(L""));
	//

	stats_names.push_back(new TextArea(L"LEVEL"));
	stats_values.push_back(new TextArea(std::to_wstring(parent->_character->LEVEL)));

	stats_names.push_back(new TextArea(L"EXPERIENCE"));
	stats_values.push_back(new TextArea(std::to_wstring(parent->_character->EXPERIENCE)));

	stats_names.push_back(new TextArea(L"SKILL POINTS"));
	stats_values.push_back(new TextArea(std::to_wstring(parent->_character->SKILL_POINTS)));

	//
	stats_names.push_back(new TextArea(L""));
	stats_values.push_back(new TextArea(L""));
	//

	stats_names.push_back(new TextArea(L"CURRENT HP"));
	stats_values.push_back(new TextArea(std::to_wstring(parent->_character->HP)));

	stats_names.push_back(new TextArea(L"MAX HP"));
	stats_values.push_back(new TextArea(std::to_wstring(parent->_character->HP_FULL)));

	stats_names.push_back(new TextArea(L"CURRENT MANA"));
	stats_values.push_back(new TextArea(std::to_wstring(parent->_character->MP)));

	stats_names.push_back(new TextArea(L"MAX MANA"));
	stats_values.push_back(new TextArea(std::to_wstring(parent->_character->MP_FULL)));

	stats_names.push_back(new TextArea(L"STRENGTH"));
	stats_values.push_back(new TextArea(std::to_wstring(parent->_character->STRENGTH)));

	stats_names.push_back(new TextArea(L"DEXTERITY"));
	stats_values.push_back(new TextArea(std::to_wstring(parent->_character->DEXTERITY)));

	stats_names.push_back(new TextArea(L"INTELLIGENCE"));
	stats_values.push_back(new TextArea(std::to_wstring(parent->_character->INTELLIGENCE)));

	//
	stats_names.push_back(new TextArea(L""));
	stats_values.push_back(new TextArea(L""));
	//

	stats_names.push_back(new TextArea(L"ACTION RANGE"));
	stats_values.push_back(new TextArea(std::to_wstring(parent->_character->ACTION_RANGE)));

	stats_names.push_back(new TextArea(L"VIEW RANGE"));
	stats_values.push_back(new TextArea(std::to_wstring(parent->_character->VIEW_RANGE)));

	//
	stats_names.push_back(new TextArea(L""));
	stats_values.push_back(new TextArea(L""));
	//

	stats_names.push_back(new TextArea(L"ATTACK"));
	stats_values.push_back(new TextArea(L"0"));

	stats_names.push_back(new TextArea(L"DEFEND"));
	stats_values.push_back(new TextArea(L"0"));

	sf::Vector2f pos;

	float panel_height = parent->rect.getSize().y;
	float corner_size = parent->corner_part_size.y;
	float menu_height = parent->menu[0]->texture->getSize().y;

	for (int i = 0; i < stats_names.size(); i++) {

		pos.y = parent->position.y - panel_height / 2.0f + margin + corner_size + menu_height + i * stats_names[0]->getLineHeight();
		stats_names[i]->setBackgroundColor(panelColor_normal);
		pos.x = parent->position.x - parent->rect.getSize().x / 2.0f + margin;
		stats_names[i]->setPosition(sf::Vector2f(pos.x, pos.y));

		stats_values[i]->setBackgroundColor(panelColor_normal);
		pos.x = parent->position.x + parent->rect.getSize().x / 2.0f - margin - stats_values[i]->getSize().x;
		stats_values[i]->setPosition(sf::Vector2f(pos.x, pos.y));
	}
}

CharacterInfoPanel::Statistics::Statistics::~Statistics() {
	for (auto& sn : stats_names)
		delete sn;

	for (auto& sv : stats_names)
		delete sv;
}

void CharacterInfoPanel::Statistics::Statistics::handleEvent(sf::Event& event) {

}

void CharacterInfoPanel::Statistics::Statistics::update() {

}

void CharacterInfoPanel::Statistics::Statistics::draw() {
	for (auto& sn : stats_names)
		sn->draw();

	for (auto& sv : stats_values)
		sv->draw();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CharacterInfoPanel::Layout::DirectionButton::DirectionButton(SingleTexture* texture, sf::Vector2f position, CharacterInfoPanel* parent, short direction) : ButtonWithImage(texture, position) {

	SingleTexture* tex_slot = getSingleTexture("GUI/character_menu/layout_slot");
	slot = sf::Sprite();
	SingleTexture::SetTextureForSprite(&slot, tex_slot);
	slot.setOrigin(tex_slot->cx, tex_slot->cy);
	slot.setPosition(position.x + cam->position.x, position.y + cam->position.y);

	onclick_func = [this, parent, direction]() {
		parent->_character->direction = direction;
		};
}

void CharacterInfoPanel::Layout::DirectionButton::handleEvent(sf::Event& event) {

	ButtonWithImage::handleEvent(event);
}

void CharacterInfoPanel::Layout::DirectionButton::update() {
	slot.setPosition(cam->position.x + position.x, cam->position.y + position.y);
	ButtonWithImage::update();
}

void CharacterInfoPanel::Layout::DirectionButton::draw() {
	window->draw(slot);
	window->draw(sprite);
}

CharacterInfoPanel::Layout::LayoutButton::LayoutButton(SingleTexture* texture, sf::Vector2f position, std::string body_name) : ButtonWithImage(texture, position) {

	this->body_name = body_name;

	SingleTexture* tex_slot = getSingleTexture("GUI/character_menu/layout_slot");
	slot = sf::Sprite();
	SingleTexture::SetTextureForSprite(&slot, tex_slot);
	slot.setOrigin(tex_slot->cx, tex_slot->cy);
	slot.setPosition(position.x + cam->position.x, position.y + cam->position.y);
}

void CharacterInfoPanel::Layout::LayoutButton::handleEvent(sf::Event& event) {
	ButtonWithImage::handleEvent(event);
}

void CharacterInfoPanel::Layout::LayoutButton::update() {
	slot.setPosition(cam->position.x + position.x, cam->position.y + position.y);
	ButtonWithImage::update();
}

void CharacterInfoPanel::Layout::LayoutButton::draw() {
	window->draw(slot);
	window->draw(sprite);
}

CharacterInfoPanel::Layout::Layout(CharacterInfoPanel* parent) : CharacterInfoPage(parent) {

	// load the Bodies
	std::vector < std::filesystem::directory_entry > sets;
	for (auto& entry : std::filesystem::directory_iterator("assets\\sets\\body"))
		sets.push_back(entry);

	std::sort(sets.begin(), sets.end(), [](const auto& a, const auto& b) { return a.path().filename().string() < b.path().filename().string(); });

	// some parameters
	float panel_height = parent->rect.getSize().y;
	float corner_size = parent->corner_part_size.y;
	float menu_height = parent->menu[0]->texture->getSize().y;

	sf::Vector2f preview_size(parent->_character->texture->getSize().x * 2.0f, parent->_character->texture->getSize().y * 2.0f);
	float preview_margin = margin;
	sf::Vector2f btn_size(80, 80);
	float btn_margin = 0;

	// create Preview
	sf::Vector2f preview_pos;
	preview_pos.x = parent->position.x;
	preview_pos.y = parent->position.y - panel_height / 2.0f + preview_margin + menu_height + preview_margin + preview_size.y / 2.0f;
	preview.setTexture(*parent->_character->sprite.getTexture());
	preview.setTextureRect(parent->_character->sprite.getTextureRect());
	preview.setOrigin(32, 32);
	preview.setScale(2.0f, 2.0f);
	preview.setPosition(preview_pos.x + cam->position.x, preview_pos.y + cam->position.y);

	// create Buttons
	sf::Vector2f start_pos;
	start_pos.x = parent->position.x - float(btn_size.x * 4 + btn_margin * 3) / 2.0f + btn_size.x / 2.0f;
	start_pos.y = parent->position.y - panel_height / 2.0f + corner_size + menu_height + preview_margin + preview_size.y + preview_margin + btn_size.y / 2.0f;

	// direction buttons
	sf::Vector2f btn_pos;
	btn_pos.y = start_pos.y;

	btn_pos.x = start_pos.x + (0) * (btn_size.x + btn_margin);
	DirectionButton* left = new DirectionButton(getSingleTexture("GUI/character_menu/direction_left"), btn_pos, parent, 3);
	buttons.push_back(left);

	btn_pos.x = start_pos.x + (1) * (btn_size.x + btn_margin);
	DirectionButton* bottom = new DirectionButton(getSingleTexture("GUI/character_menu/direction_bottom"), btn_pos, parent, 2);
	buttons.push_back(bottom);

	btn_pos.x = start_pos.x + (2) * (btn_size.x + btn_margin);
	DirectionButton* top = new DirectionButton(getSingleTexture("GUI/character_menu/direction_top"), btn_pos, parent, 0);
	buttons.push_back(top);

	btn_pos.x = start_pos.x + (3) * (btn_size.x + btn_margin);
	DirectionButton* right = new DirectionButton(getSingleTexture("GUI/character_menu/direction_right"), btn_pos, parent, 1);
	buttons.push_back(right);

	// layout buttons
	for (short i = 0; i < sets.size(); i++) {

		btn_pos.x = start_pos.x + (i % 4) * (btn_size.x + btn_margin);
		btn_pos.y = start_pos.y + (i / 4) * (btn_size.y + btn_margin) + (btn_size.y);
		std::string body_name = "sets/body/" + sets[i].path().filename().string();
		SingleTexture* tex = getSingleTexture(body_name + "/attackBottom0");
		LayoutButton* btn = new LayoutButton(tex, btn_pos, body_name);

		btn->onclick_func = [this, btn]() {
			this->parent->_character->bodySet = btn->body_name;
			this->parent->_character->loadBody();
			};
		buttons.push_back(btn);
	}
}

void CharacterInfoPanel::Layout::handleEvent(sf::Event& event) {
	for (auto& btn : buttons)
		btn->handleEvent(event);
}

void CharacterInfoPanel::Layout::update() {
	for (auto& btn : buttons)
		btn->update();

	preview.setTexture(*parent->_character->sprite.getTexture());
	preview.setTextureRect(parent->_character->sprite.getTextureRect());
}

void CharacterInfoPanel::Layout::draw() {
	window->draw(preview);

	for (auto& btn : buttons)
		btn->draw();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CharacterInfoPanel::Equipment::Slot::Slot(SingleTexture* texture, sf::Vector2f position) : ButtonWithImage(texture, position) {
	_item = nullptr;

	sprite = sf::Sprite();
	sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);
}

CharacterInfoPanel::Equipment::Slot::~Slot() {

}

void CharacterInfoPanel::Equipment::Slot::setItem(Item* item) {
	_item = item;

	sprite = sf::Sprite();

	sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);

	if (_item != nullptr) {
		SingleTexture::SetTextureForSprite(&sprite, _item->texture);
		sf::IntRect rect = sprite.getTextureRect();
		rect.left += 8;
		rect.top += 8;
		rect.width -= 16;
		rect.height -= 16;
		sprite.setTextureRect(rect);
		sprite.setOrigin(24, 24);
	}
}

void CharacterInfoPanel::Equipment::Slot::draw() {
	ButtonWithImage::draw();
	window->draw(sprite);
}

CharacterInfoPanel::Equipment::Equipment(CharacterInfoPanel* parent) : CharacterInfoPage(parent) {
	slots.clear();

	// some parameters
	float panel_height = parent->rect.getSize().y;
	float corner_size = parent->corner_part_size.y;
	float menu_height = parent->menu[0]->texture->getSize().y;

	SingleTexture* slot_texture = getSingleTexture("GUI/character_menu/item_slot");
	sf::Vector2f preview_size(parent->_character->texture->getSize().x * 2.0f, parent->_character->texture->getSize().y * 2.0f);
	float preview_margin = margin;
	sf::Vector2f slot_size(slot_texture->getSize());
	float border_width = 6;

	// create Preview
	sf::Vector2f preview_pos;
	preview_pos.x = parent->position.x;
	preview_pos.y = parent->position.y - panel_height / 2.0f + preview_margin + menu_height + preview_margin + preview_size.y / 2.0f;
	preview.setTexture(*parent->_character->sprite.getTexture());
	preview.setTextureRect(parent->_character->sprite.getTextureRect());
	preview.setOrigin(32, 32);
	preview.setScale(2.0f, 2.0f);
	preview.setPosition(preview_pos.x + cam->position.x, preview_pos.y + cam->position.y);

	// create Slots
	for (short y = 0; y < slots_count.y; y += 1) {
		for (short x = 0; x < slots_count.x; x += 1) {
			sf::Vector2f pos;
			pos.x = parent->position.x - parent->rect.getSize().x / 2.0f + slot_size.x / 2.0f + x * slot_size.x + border_width;
			pos.y = parent->position.y - panel_height / 2.0f + corner_size + menu_height + preview_margin + preview_size.y + preview_margin + slot_size.y / 2.0f + y * slot_size.y;
			Slot* slot = new Slot(slot_texture, pos);
			slot->onclick_func = [slot, parent]() {
				if (slot->_item != nullptr) {

					// TO-DO - it is under rewrite to parent->_character->useItem();
					if (slot->_item->type == ItemType::helmet) {
						(parent->_character->helmet != slot->_item) ? parent->_character->helmet = slot->_item : parent->_character->helmet = nullptr;
						parent->_character->loadHelmet();
					}

					if (slot->_item->type == ItemType::armor) {
						(parent->_character->armor != slot->_item) ? parent->_character->armor = slot->_item : parent->_character->armor = nullptr;
						parent->_character->loadArmor();
					}

					if (slot->_item->type == ItemType::pants) {
						(parent->_character->pants != slot->_item) ? parent->_character->pants = slot->_item : parent->_character->pants = nullptr;
						parent->_character->loadPants();
					}

					if (slot->_item->type == ItemType::weapon) {
						(parent->_character->rightHand != slot->_item) ? parent->_character->rightHand = slot->_item : parent->_character->rightHand = nullptr;
						parent->_character->loadRightHand();
					}

					if (slot->_item->type == ItemType::shield) {
						(parent->_character->leftHand != slot->_item) ? parent->_character->leftHand = slot->_item : parent->_character->leftHand = nullptr;
						parent->_character->loadLeftHand();
					}
					//////////////////
				}

				};
			slots.push_back(slot);
		}
	}

	setItemsToSlots();

	sf::Vector2f scrollbar_size(16, 6 * 64);
	sf::Vector2f scrollbar_position;
	scrollbar_position.x = parent->position.x + parent->rect.getSize().x / 2.0f - 16 - border_width;
	scrollbar_position.y = slots.front()->position.y - slots.front()->texture->getSize().y / 2.0f;
	scrollbar = new Scrollbar(scrollbar_size, scrollbar_position, 0, items_list.size(), 0, slots_count.x * slots_count.y);
}

void CharacterInfoPanel::Equipment::setItemsToSlots() {
	items_list.clear();
	for (Item* item : items) {
		if (item->type == ItemType::helmet || item->type == ItemType::armor || item->type == ItemType::pants || item->type == ItemType::weapon || item->type == ItemType::shield)
			items_list.push_back(item);
	}

	for (int i = 0; i < 36; i++) {
		if (i < items_list.size()) {
			slots[i]->setItem(items_list[i]);
		}
	}
}

void CharacterInfoPanel::Equipment::handleEvent(sf::Event& event) {
	scrollbar->handleEvent(event);
	setItemsToSlots();

	for (auto& slot : slots)
		slot->handleEvent(event);
}

void CharacterInfoPanel::Equipment::update() {
	scrollbar->update();
	preview.setTexture(*parent->_character->sprite.getTexture());

	for (auto& slot : slots)
		slot->update();
}

void CharacterInfoPanel::Equipment::draw() {
	for (auto& slot : slots) {
		slot->draw();
	}

	scrollbar->draw();
	window->draw(preview);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO-DO
CharacterInfoPanel::Inventory::Inventory(CharacterInfoPanel* parent) : CharacterInfoPage(parent) { }
void CharacterInfoPanel::Inventory::handleEvent(sf::Event& event) { }
void CharacterInfoPanel::Inventory::update() { }
void CharacterInfoPanel::Inventory::draw() { }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO-DO
CharacterInfoPanel::Dialogues::Dialogues(CharacterInfoPanel* parent) : CharacterInfoPage(parent) { }
void CharacterInfoPanel::Dialogues::handleEvent(sf::Event& event) { }
void CharacterInfoPanel::Dialogues::update() { }
void CharacterInfoPanel::Dialogues::draw() { }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO-DO
CharacterInfoPanel::Quests::Quests(CharacterInfoPanel* parent) : CharacterInfoPage(parent) { }
void CharacterInfoPanel::Quests::handleEvent(sf::Event& event) { }
void CharacterInfoPanel::Quests::update() { }
void CharacterInfoPanel::Quests::draw() { }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CharacterInfoPanel::CharacterInfoPanel(Character* character) : Panel(sf::Vector2f(412 + 16, 596)) {

	_character = character;

	SingleTexture* menu_button_texture = getSingleTexture("GUI/character_menu/menu_slot");

	float btn_wdt = menu_button_texture->getSize().x;
	float btn_hgh = menu_button_texture->getSize().y;

	sf::Vector2f pos;
	pos.x = position.x - size.x / 2.0f + btn_wdt / 2.0f + margin + corner_part_size.x;
	pos.y = position.y - size.y / 2.0f + btn_hgh / 2.0f + margin + corner_part_size.y;

	// create menu buttons
	ButtonWithImage* menu_statistics = new ButtonWithImage(getSingleTexture("GUI/character_menu/menu_statistics"), sf::Vector2f(pos.x, pos.y));
	menu_statistics->onclick_func = [this]() {
		active_page = pages[0];
		};

	ButtonWithImage* menu_layout = new ButtonWithImage(getSingleTexture("GUI/character_menu/menu_layout"), sf::Vector2f(pos.x + btn_wdt, pos.y));
	menu_layout->onclick_func = [this]() {
		active_page = pages[1];
		};

	ButtonWithImage* menu_equipment = new ButtonWithImage(getSingleTexture("GUI/character_menu/menu_equipment"), sf::Vector2f(pos.x + 2 * btn_wdt, pos.y));
	menu_equipment->onclick_func = [this]() {
		active_page = pages[2];
		};

	ButtonWithImage* menu_inventory = new ButtonWithImage(getSingleTexture("GUI/character_menu/menu_inventory"), sf::Vector2f(pos.x + 3 * btn_wdt, pos.y));
	menu_inventory->onclick_func = [this]() {
		active_page = pages[3];
		};

	ButtonWithImage* menu_dialogues = new ButtonWithImage(getSingleTexture("GUI/character_menu/menu_dialogues"), sf::Vector2f(pos.x + 4 * btn_wdt, pos.y));
	menu_dialogues->onclick_func = [this]() {
		active_page = pages[4];
		};

	ButtonWithImage* menu_quests = new ButtonWithImage(getSingleTexture("GUI/character_menu/menu_quests"), sf::Vector2f(pos.x + 5 * btn_wdt, pos.y));
	menu_quests->onclick_func = [this]() {
		active_page = pages[5];
		};


	menu.push_back(menu_statistics);
	menu.push_back(menu_layout);
	menu.push_back(menu_equipment);
	menu.push_back(menu_inventory);
	menu.push_back(menu_dialogues);
	menu.push_back(menu_quests);

	// create pages
	pages.push_back(new Statistics(this));
	pages.push_back(new Layout(this));
	pages.push_back(new Equipment(this));
	pages.push_back(new Inventory(this));
	pages.push_back(new Dialogues(this));
	pages.push_back(new Quests(this));

	active_page = pages[0];

	// generate border
	float border_wdt = size.x - 2 * margin - 2.0f * corner_part_size.x;
	float border_hgh = size.y - 2 * margin - corner_part_size.y;

	left_border = sf::Sprite();
	SingleTexture::SetTextureForSprite(&left_border, getSingleTexture("GUI/border_vertical"));
	pos.x = position.x + cam->position.x - size.x / 2.0f + margin;
	pos.y = position.y + cam->position.y - size.y / 2.0f + margin + corner_part_size.y;
	left_border.setScale(1.0f, border_hgh / border_part_size.y);
	left_border.setPosition(pos);

	right_border = sf::Sprite();
	SingleTexture::SetTextureForSprite(&right_border, getSingleTexture("GUI/border_vertical"));
	pos.x = position.x + cam->position.x + size.x / 2.0f - margin - border_part_size.x;
	pos.y = position.y + cam->position.y - size.y / 2.0f + margin + corner_part_size.y;
	right_border.setScale(1.0f, border_hgh / border_part_size.y);
	right_border.setPosition(pos);

	top_border = sf::Sprite();
	SingleTexture::SetTextureForSprite(&top_border, getSingleTexture("GUI/border_horizontal"));
	pos.x = position.x + cam->position.x - size.x / 2.0f + margin + corner_part_size.x;
	pos.y = position.y + cam->position.y - size.y / 2.0f + margin;
	top_border.setScale(border_wdt / border_part_size.x, 1.0f);
	top_border.setPosition(pos);

	bottom_border = sf::Sprite();
	SingleTexture::SetTextureForSprite(&bottom_border, getSingleTexture("GUI/border_horizontal"));
	pos.x = position.x + cam->position.x - size.x / 2.0f + margin + corner_part_size.x;
	pos.y = position.y + cam->position.y + size.y / 2.0f - margin - border_part_size.y;
	bottom_border.setScale(border_wdt / border_part_size.x, 1.0f);
	bottom_border.setPosition(pos);

	top_left_corner = sf::Sprite();
	SingleTexture::SetTextureForSprite(&top_left_corner, getSingleTexture("GUI/corner"));
	pos.x = position.x + cam->position.x - size.x / 2.0f + margin;
	pos.y = position.y + cam->position.y - size.y / 2.0f + margin;
	top_left_corner.setPosition(pos);

	top_right_corner = sf::Sprite();
	SingleTexture::SetTextureForSprite(&top_right_corner, getSingleTexture("GUI/corner"));
	pos.x = position.x + cam->position.x + size.x / 2.0f - margin - corner_part_size.x;
	pos.y = position.y + cam->position.y - size.y / 2.0f + margin;
	top_right_corner.setPosition(pos);

	bottom_left_corner = sf::Sprite();
	SingleTexture::SetTextureForSprite(&bottom_left_corner, getSingleTexture("GUI/corner"));
	pos.x = position.x + cam->position.x - size.x / 2.0f + margin;
	pos.y = position.y + cam->position.y + size.y / 2.0f - margin - corner_part_size.y;
	bottom_left_corner.setPosition(pos);

	bottom_right_corner = sf::Sprite();
	SingleTexture::SetTextureForSprite(&bottom_right_corner, getSingleTexture("GUI/corner"));
	pos.x = position.x + cam->position.x + size.x / 2.0f - margin - corner_part_size.x;
	pos.y = position.y + cam->position.y + size.y / 2.0f - margin - corner_part_size.y;
	bottom_right_corner.setPosition(pos);
}

CharacterInfoPanel::~CharacterInfoPanel() {

	for (auto& m : menu)
		delete m;

	for (auto& p : pages)
		delete p;
}

void CharacterInfoPanel::handleEvent(sf::Event& event) {

	for (auto& m : menu)
		m->handleEvent(event);

	active_page->handleEvent(event);
}

void CharacterInfoPanel::update() {
	for (auto& m : menu)
		m->update();

	active_page->update();
}

void CharacterInfoPanel::draw() {
	Panel::draw();

	for (auto& m : menu)
		m->draw();

	window->draw(left_border);
	window->draw(right_border);
	window->draw(top_border);
	window->draw(bottom_border);
	window->draw(top_left_corner);
	window->draw(top_right_corner);
	window->draw(bottom_left_corner);
	window->draw(bottom_right_corner);

	active_page->draw();


}
