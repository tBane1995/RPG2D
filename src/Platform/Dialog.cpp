#include "Dialog.h"
#include "GUI.h"

std::vector < Dialog* > dialogs;

Dialog::Dialog(DialogType type) {
	this->type = type;
}

Dialog::~Dialog() { 

}

void Dialog::handleEvent(sf::Event& event) {

}

void Dialog::update() {
	GUIwasOpen = true;
}

void Dialog::draw() {

}