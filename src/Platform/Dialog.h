#pragma once

#include <vector>

enum class DialogType { Message, ScrollableText, OpenFile };

class Dialog {
public:
	DialogType type;

	Dialog(DialogType type) {
		this->type = type;
	}
	
	virtual ~Dialog() { }
	
	virtual void update(sf::Event& event) {

	}

	virtual void draw() {

	}
};

extern std::vector < Dialog* > dialogs;
