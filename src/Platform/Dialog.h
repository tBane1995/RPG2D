#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum class DialogType { Message, Panel, ScrollableText, OpenFile, SaveFile, Confirm };

class Dialog {
public:
	DialogType type;

	Dialog(DialogType type);
	virtual ~Dialog();
	virtual void handleEvent(sf::Event& event);
	virtual void update();
	virtual void draw();
};

extern std::vector < Dialog* > dialogs;
