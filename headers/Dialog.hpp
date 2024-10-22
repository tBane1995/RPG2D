#ifndef Dialog_hpp
#define Dialog_hpp

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

std::vector < Dialog* > dialogs;

#endif