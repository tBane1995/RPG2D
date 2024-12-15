#pragma once


#include <SFML/Graphics.hpp>
#include <string>
#include "TextArea.h"
#include "Mouse.h"

enum class CursorState { ShowCursor, HideCursor };

class EditableTextArea : public TextArea {
public:
	std::wstring editable_text;
	short cursor_position;
	bool isSelected;
	sf::Time last_action_time;
	CursorState cursorState;

	EditableTextArea(std::wstring text = L"");
	~EditableTextArea();
	
	void update(sf::Event& event);
	void update();
	void draw();

};