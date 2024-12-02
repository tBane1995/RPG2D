#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class DialogueOption {
public:
	std::wstring text;
	short nextDialogueID;

	DialogueOption(int nextDialogueID, std::wstring text) {
		this->nextDialogueID = nextDialogueID;
		this->text = text;
	}
};

class Dialogue {
public:
	short id;
	std::wstring text;
	std::vector < DialogueOption > options;

	Dialogue(short id, std::wstring text) {
		this->id = id;
		this->text = text;
	}
};

// TO-DO //////////////////////////////

extern std::vector < Dialogue* > dialogues;

Dialogue* getDialogue(short id);

enum class DialogueState { Showing, Choosing, Answering, End};

class DialogueBox {
public:
	DialogueState state;
	Dialogue* currentDialogue;
	short page;
	short lastPage;
	short chooseScroll;
	short chooseCursor;

	sf::Sprite background;
	sf::Text texts[5];

	std::vector < std::wstring > lines;
	std::vector < std::wstring > answers;

	short animationingLine;	// animation
	short animationingChar; // animation
	sf::Time animStart;

	DialogueBox(Dialogue* dialogue);

	void loadPage();
	void loadDialogueAndAnswers();
	void update(sf::Event& event);
	void draw();
};

extern DialogueBox* dialogueBox;


void loadDialogue(int dialogID);
void loadDialogues();
