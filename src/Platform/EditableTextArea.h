#pragma once


#include <SFML/Graphics.hpp>
#include <string>
#include "TextArea.h"
#include "Mouse.h"

enum class CursorState { ShowCursor, HideCursor };

class EditableTextArea : public TextArea {
public:
	bool isSelected;
	sf::Time last_action_time;
	CursorState cursorState;

	EditableTextArea(std::wstring text = L"");
	~EditableTextArea();
	void update();
	void update(sf::Event& event);
	void draw();

};