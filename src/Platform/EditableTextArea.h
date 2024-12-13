#pragma once


#include <SFML/Graphics.hpp>
#include <string>
#include "TextArea.h"
#include "Mouse.h"


class EditableTextArea : public TextArea {
public:
	bool isSelected;

	EditableTextArea(std::wstring text = L"");
	~EditableTextArea();
	void update(sf::Event& event);
	void draw();

};