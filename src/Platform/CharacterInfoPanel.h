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
#include "Items.h"
#include "Scrollbar.h"
#include <iostream>

class CharacterInfoPanel : public Panel {
public:
	Character* _character;

	class CharacterInfoPage {
	public:
		CharacterInfoPanel* parent;

		CharacterInfoPage(CharacterInfoPanel* parent);
		virtual void handleEvent(sf::Event& event);
		virtual void update();
		virtual void draw();
	};

	class Statistics : public CharacterInfoPage {
	public:
		std::vector < TextArea* > stats_names;
		std::vector < TextArea* > stats_values;

		Statistics(CharacterInfoPanel* parent);
		~Statistics();
		void handleEvent(sf::Event& event);
		void update();
		void draw();
	};

	class Layout : public CharacterInfoPage {
	public:

		class DirectionButton : public ButtonWithImage {
		public:
			sf::Sprite slot;

			DirectionButton(SingleTexture* texture, sf::Vector2f position, CharacterInfoPanel* parent, short direction);
			void handleEvent(sf::Event& event);
			void update();
			void draw();
		};

		class LayoutButton : public ButtonWithImage {
		public:
			sf::Sprite slot;
			std::string body_name;

			LayoutButton(SingleTexture* texture, sf::Vector2f position, std::string body_name = "sets/body/hero");
			void handleEvent(sf::Event& event);
			void update();
			void draw();
		};

		std::vector < ButtonWithImage* > buttons;
		sf::Sprite preview;

		Layout(CharacterInfoPanel* parent);
		void handleEvent(sf::Event& event);
		void update();
		void draw();
	};

	class Equipment : public CharacterInfoPage {
	public:

		class Slot : public ButtonWithImage {
		public:
			Item* _item;
			sf::Sprite sprite;

			Slot(SingleTexture* texture, sf::Vector2f position);
			~Slot();
			void setItem(Item* item);
			void draw();
		};

		sf::Sprite preview;
		sf::Vector2i slots_count = sf::Vector2i(6, 6);
		std::vector < Slot* > slots;
		std::vector < Item* > items_list;
		Scrollbar* scrollbar;

		Equipment(CharacterInfoPanel* parent);
		void setItemsToSlots();
		void handleEvent(sf::Event& event);
		void update();
		void draw();
	};

	class Inventory : public CharacterInfoPage {
	public:
		Inventory(CharacterInfoPanel* parent);
		void handleEvent(sf::Event& event);
		void update();
		void draw();
	};

	class Dialogues : public CharacterInfoPage {
	public:
		Dialogues(CharacterInfoPanel* parent);
		void handleEvent(sf::Event& event);
		void update();
		void draw();
	};

	class Quests : public CharacterInfoPage {
	public:
		Quests(CharacterInfoPanel* parent);
		void handleEvent(sf::Event& event);
		void update();
		void draw();
	};

	sf::Vector2f border_part_size = sf::Vector2f(6, 6);
	sf::Vector2f corner_part_size = sf::Vector2f(8, 8);

	std::vector < ButtonWithImage* > menu;
	std::vector < CharacterInfoPage* > pages;
	CharacterInfoPage* active_page;

	sf::Sprite left_border;
	sf::Sprite right_border;
	sf::Sprite top_border;
	sf::Sprite bottom_border;
	sf::Sprite top_left_corner;
	sf::Sprite top_right_corner;
	sf::Sprite bottom_left_corner;
	sf::Sprite bottom_right_corner;

	CharacterInfoPanel(Character* character);
	~CharacterInfoPanel();
	void handleEvent(sf::Event& event);
	void update();
	void draw();
};