#include "Dialog.h"

std::vector < Dialog* > dialogs;

Dialog::Dialog(DialogType type) {
	this->type = type;
}

Dialog::~Dialog() { 

}

void Dialog::handleEvent(sf::Event& event) {

}

void Dialog::update() {

}

void Dialog::draw() {

}