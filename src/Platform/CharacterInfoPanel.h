#pragma once
#include "Theme.h"
#include "TextArea.h"
#include "Fonts.h"
#include <filesystem>
#include "Buttons.h"
#include "Camera.h"
#include "Character.h"
#include "Panel.h"
#include "Textures.h"

class CharacterInfoPanel : public Panel {
public:
	Character* _character;


	class CharacterInfoPage {
	public:
		CharacterInfoPanel* parent;;

		CharacterInfoPage(CharacterInfoPanel* parent) {
			this->parent = parent;
		}
		virtual void handleEvent(sf::Event& event) { }
		virtual void update() { }
		virtual void draw() { }
	};

	class Statistics : public CharacterInfoPage {
	public:
		std::vector < TextArea* > stats_names;
		std::vector < TextArea* > stats_values;

		Statistics(CharacterInfoPanel* parent) : CharacterInfoPage(parent) {
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

			stats_names.push_back(new TextArea(L"ATTACK"));
			stats_values.push_back(new TextArea(L"0"));

			stats_names.push_back(new TextArea(L"DEFEND"));
			stats_values.push_back(new TextArea(L"0"));


			//stats_names.push_back(new TextArea(L"ID"));

			sf::Vector2f pos;

			for (int i = 0; i < stats_names.size(); i++) {

				pos.y = parent->position.y - parent->rect.getSize().y / 2.0f + margin + parent->menu[0]->texture->getSize().y + i * stats_names[0]->getLineHeight();

				stats_names[i]->setBackgroundColor(panelColor_normal);
				pos.x = parent->position.x - parent->rect.getSize().x / 2.0f + margin;
				stats_names[i]->setPosition(sf::Vector2f(pos.x, pos.y));

				stats_values[i]->setBackgroundColor(panelColor_normal);
				pos.x = parent->position.x + parent->rect.getSize().x / 2.0f - margin - stats_values[i]->getSize().x;
				stats_values[i]->setPosition(sf::Vector2f(pos.x, pos.y));
			}
		}

		~Statistics() {
			for (auto& sn : stats_names)
				delete sn;

			for (auto& sv : stats_names)
				delete sv;
		}

		void handleEvent(sf::Event& event) { }
		void update() { }

		void draw() {
			for (auto& sn : stats_names)
				sn->draw();

			for (auto& sv : stats_values)
				sv->draw();
		}
	};

	class Layout : public CharacterInfoPage {
	public:

		class LayoutButton : public ButtonWithImage {
		public:
			sf::RectangleShape rect;
			std::string body_name;

			LayoutButton(SingleTexture* texture, sf::Vector2f position, std::string body_name = "sets/body/hero") : ButtonWithImage(texture, position) {

				this->body_name = body_name;

				rect = sf::RectangleShape(sf::Vector2f(texture->getSize()));
				rect.setFillColor(panelColor_medium);
				rect.setOrigin(texture->texture->getSize().x / 2.0f, texture->getSize().y / 2.0f);
				rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
			}

			void handleEvent(sf::Event& event) {
				ButtonWithImage::handleEvent(event);
			}

			void update() {
				rect.setPosition(cam->position.x + position.x, cam->position.y + position.y);
				ButtonWithImage::update();
			}

			void draw() {
				window->draw(rect);
				window->draw(sprite);
			}
		};

		std::vector < LayoutButton* > buttons;
		sf::Sprite preview;

		Layout(CharacterInfoPanel* parent) : CharacterInfoPage(parent) {

			// load the Bodies
			std::vector < std::filesystem::directory_entry > sets;
			for (auto& entry : std::filesystem::directory_iterator("assets\\sets\\body"))
				sets.push_back(entry);

			std::sort(sets.begin(), sets.end(), [](const auto& a, const auto& b) { return a.path().filename().string() < b.path().filename().string(); });

			// some parameters
			sf::Vector2f preview_size(128, 128);
			sf::Vector2f btn_size(64, 64);
			float btn_margin = 8;

			// create Preview
			sf::Vector2f preview_pos;
			preview_pos.x = parent->position.x;
			preview_pos.y = parent->position.y - parent->rect.getSize().y / 2.0f + margin + parent->menu[0]->texture->getSize().y + margin + preview_size.y / 2.0f;
			preview.setTexture(*parent->_character->sprite.getTexture());
			preview.setOrigin(32, 32);
			preview.setScale(2.0f, 2.0f);
			preview.setPosition(preview_pos.x + cam->position.x, preview_pos.y + cam->position.y);

			// create Buttons
			sf::Vector2f start_pos;
			start_pos.x = parent->position.x - float(btn_size.x * 4 + btn_margin * 3) / 2.0f + btn_size.x / 2.0f;
			start_pos.y = parent->position.y - parent->rect.getSize().y / 2.0f;
			start_pos.y += margin + parent->menu[0]->texture->texture->getSize().y;
			start_pos.y += margin + preview_size.y + margin + btn_size.y / 2.0f;

			for (short i = 0; i < sets.size(); i++) {
				sf::Vector2f btn_pos;
				btn_pos.x = start_pos.x + (i % 4) * (btn_size.x + btn_margin);
				btn_pos.y = start_pos.y + (i / 4) * (btn_size.y + btn_margin);
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

		void handleEvent(sf::Event& event) {
			for (auto& btn : buttons)
				btn->handleEvent(event);
		}

		void update() {
			for (auto& btn : buttons)
				btn->update();

			preview.setTexture(*parent->_character->sprite.getTexture());	// TO-DO
		}

		void draw() {

			window->draw(preview);

			for (auto& btn : buttons)
				btn->draw();
		}
	};

	class Equipment : public CharacterInfoPage {
	public:
		Equipment(CharacterInfoPanel* parent) : CharacterInfoPage(parent) { }
		void handleEvent(sf::Event& event) { }
		void update() { }
		void draw() { }
	};

	class Inventory : public CharacterInfoPage {
	public:
		Inventory(CharacterInfoPanel* parent) : CharacterInfoPage(parent) { }
		void handleEvent(sf::Event& event) { }
		void update() { }
		void draw() { }
	};

	class Dialogues : public CharacterInfoPage {
	public:
		Dialogues(CharacterInfoPanel* parent) : CharacterInfoPage(parent) { }
		void handleEvent(sf::Event& event) { }
		void update() { }
		void draw() { }
	};

	class Quests : public CharacterInfoPage {
	public:
		Quests(CharacterInfoPanel* parent) : CharacterInfoPage(parent) { }
		void handleEvent(sf::Event& event) { }
		void update() { }
		void draw() { }
	};



	std::vector < ButtonWithImage* > menu;
	std::vector < CharacterInfoPage* > pages;
	CharacterInfoPage* active_page;

	sf::Sprite left_border;
	sf::Sprite right_border;
	sf::Sprite bottom_border;
	sf::Sprite left_corner;
	sf::Sprite right_corner;

	CharacterInfoPanel(Character* character) : Panel(sf::Vector2f(352, 500)) {

		_character = character;

		SingleTexture* menu_button_texture = getSingleTexture("GUI/character_menu/menu_slot");

		float btn_wdt = menu_button_texture->getSize().x;
		float btn_hgh = menu_button_texture->getSize().y;

		sf::Vector2f pos;
		pos.x = position.x - size.x / 2.0f + btn_wdt / 2.0f + margin;
		pos.y = position.y - size.y / 2.0f + btn_hgh / 2.0f + margin;

		// create menu buttons
		ButtonWithImage* menu_statistics = new ButtonWithImage(menu_button_texture, sf::Vector2f(pos.x, pos.y));
		menu_statistics->onclick_func = [this]() {
			active_page = pages[0];
			};

		ButtonWithImage* menu_layout = new ButtonWithImage(menu_button_texture, sf::Vector2f(pos.x + btn_wdt, pos.y));
		menu_layout->onclick_func = [this]() {
			active_page = pages[1];
			};

		ButtonWithImage* menu_equipment = new ButtonWithImage(menu_button_texture, sf::Vector2f(pos.x + 2 * btn_wdt, pos.y));
		menu_equipment->onclick_func = [this]() {
			active_page = pages[2];
			};

		ButtonWithImage* menu_inventory = new ButtonWithImage(menu_button_texture, sf::Vector2f(pos.x + 3 * btn_wdt, pos.y));
		menu_inventory->onclick_func = [this]() {
			active_page = pages[3];
			};

		ButtonWithImage* menu_dialogues = new ButtonWithImage(menu_button_texture, sf::Vector2f(pos.x + 4 * btn_wdt, pos.y));
		menu_dialogues->onclick_func = [this]() {
			active_page = pages[4];
			};

		ButtonWithImage* menu_quests = new ButtonWithImage(menu_button_texture, sf::Vector2f(pos.x + 5 * btn_wdt, pos.y));
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
		sf::Vector2f border_part_size = sf::Vector2f(6, 6);
		sf::Vector2f corner_part_size = sf::Vector2f(8, 8);
		float border_wdt = size.x - 2 * margin - 2.0f * corner_part_size.x;
		float border_hgh = size.y - 2 * margin - btn_hgh - corner_part_size.y;

		SingleTexture::SetTextureForSprite(&left_border, getSingleTexture("GUI/border_vertical"));
		pos.x = position.x + cam->position.x - size.x / 2.0f + margin;
		pos.y = position.y + cam->position.y - size.y / 2.0f + margin + btn_hgh;
		left_border.setScale(1.0f, border_hgh / border_part_size.y);
		left_border.setPosition(pos);

		SingleTexture::SetTextureForSprite(&right_border, getSingleTexture("GUI/border_vertical"));
		pos.x = position.x + cam->position.x + size.x / 2.0f - margin - border_part_size.x;
		pos.y = position.y + cam->position.y - size.y / 2.0f + margin + btn_hgh;
		right_border.setScale(1.0f, border_hgh / border_part_size.y);
		right_border.setPosition(pos);

		SingleTexture::SetTextureForSprite(&bottom_border, getSingleTexture("GUI/border_horizontal"));
		pos.x = position.x + cam->position.x - size.x / 2.0f + margin + corner_part_size.x;
		pos.y = position.y + cam->position.y + size.y / 2.0f - margin - border_part_size.y;
		bottom_border.setScale(border_wdt / border_part_size.x, 1.0f);
		bottom_border.setPosition(pos);

		SingleTexture::SetTextureForSprite(&left_corner, getSingleTexture("GUI/corner"));
		pos.x = position.x + cam->position.x - size.x / 2.0f + margin;
		pos.y = position.y + cam->position.y + size.y / 2.0f - margin - corner_part_size.y;
		left_corner.setPosition(pos);

		SingleTexture::SetTextureForSprite(&right_corner, getSingleTexture("GUI/corner"));
		pos.x = position.x + cam->position.x + size.x / 2.0f - margin - corner_part_size.x;
		pos.y = position.y + cam->position.y + size.y / 2.0f - margin - corner_part_size.y;
		right_corner.setPosition(pos);
	}

	~CharacterInfoPanel() {

		for (auto& m : menu)
			delete m;

		for (auto& p : pages)
			delete p;
	}

	void handleEvent(sf::Event& event) {

		for (auto& m : menu)
			m->handleEvent(event);

		active_page->handleEvent(event);
	}

	void update() {
		for (auto& m : menu)
			m->update();

		active_page->update();
	}

	void draw() {
		Panel::draw();

		for (auto& m : menu)
			m->draw();

		active_page->draw();

		window->draw(left_border);
		window->draw(right_border);
		window->draw(bottom_border);
		window->draw(left_corner);
		window->draw(right_corner);
	}

};
