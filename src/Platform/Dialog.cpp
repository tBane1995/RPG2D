#include "Dialog.h"

std::vector < Dialog* > dialogs;

Dialog::Dialog(DialogType type) {
	this->type = type;
}

Dialog::~Dialog() { 

}

void Dialog::update() {

}

void Dialog::update(sf::Event& event) {

}

void Dialog::draw() {

}