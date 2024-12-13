#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum class DialogType { Message, Panel, ScrollableText, OpenFile, SaveFile, Confirm };

class Dialog {
public:
	DialogType type;

	Dialog(DialogType type);
	virtual ~Dialog();
	virtual void update();
	virtual void update(sf::Event& event);
	virtual void draw();
};

extern std::vector < Dialog* > dialogs;
