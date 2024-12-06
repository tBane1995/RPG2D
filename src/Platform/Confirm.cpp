#include "Confirm.h"
#include "Buttons.h"
#include "TextArea.h"
#include <iostream>
#include "Camera.h"
#include "Fonts.h"
#include "Theme.h"
#include "Mouse.h"
#include "Textures.h"
#include "Time.h"

Confirm::Confirm(std::wstring text) : Dialog(DialogType::Confirm) {

}

Confirm::~Confirm() {
	delete textarea;
	delete btn_yes;
	delete btn_no;
}

