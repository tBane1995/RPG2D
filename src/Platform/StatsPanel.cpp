#include "StatsPanel.h"
#include "Theme.h"
#include "Textures.h"
#include "Window.h"
#include "Fonts.h"
#include "Player.h"
#include "Camera.h"

StatsPanel::StatsPanel() {
	panel = sf::Sprite();
	SingleTexture::SetTextureForSprite(&panel, getSingleTexture("GUI/bigPanel"));
	panel.setOrigin(300, 200);

	LEVEL = sf::Text();
	LEVEL.setFont(basicFont);
	LEVEL.setCharacterSize(18);
	LEVEL.setFillColor(dialoguesColor);
	LEVEL.setString("poziom: " + std::to_string(player->LEVEL));

	EXPERIENCE = sf::Text();
	EXPERIENCE.setFont(basicFont);
	EXPERIENCE.setCharacterSize(18);
	EXPERIENCE.setFillColor(dialoguesColor);
	EXPERIENCE.setString(L"doświadczenie: " + std::to_wstring(player->EXPERIENCE) + L" / " + std::to_wstring(player->EXPERIENCE_TO_NEXT_LEVEL));

	SKILLPOINTS = sf::Text();
	SKILLPOINTS.setFont(basicFont);
	SKILLPOINTS.setCharacterSize(18);
	SKILLPOINTS.setFillColor(dialoguesColor);
	SKILLPOINTS.setString(L"punkty nauki: " + std::to_wstring(player->SKILL_POINTS));

	//////////////////////////////////////////////////////////////////////////////////////////

	HP = sf::Text();
	HP.setFont(basicFont);
	HP.setCharacterSize(18);
	HP.setFillColor(dialoguesColor);
	HP.setString(L"punkty trafień: " + std::to_wstring(player->HP) + L" / " + std::to_wstring(player->HP_FULL));

	MP = sf::Text();
	MP.setFont(basicFont);
	MP.setCharacterSize(18);
	MP.setFillColor(dialoguesColor);
	MP.setString(L"punkty many: " + std::to_wstring(player->MP) + L" / " + std::to_wstring(player->MP_FULL));

	STRENGTH = sf::Text();
	STRENGTH.setFont(basicFont);
	STRENGTH.setCharacterSize(18);
	STRENGTH.setFillColor(dialoguesColor);
	STRENGTH.setString(L"siła: " + std::to_wstring(player->STRENGTH));

	DEXTERITY = sf::Text();
	DEXTERITY.setFont(basicFont);
	DEXTERITY.setCharacterSize(18);
	DEXTERITY.setFillColor(dialoguesColor);
	DEXTERITY.setString(L"zręczność: " + std::to_wstring(player->DEXTERITY));

	INTELLIGENCE = sf::Text();
	INTELLIGENCE.setFont(basicFont);
	INTELLIGENCE.setCharacterSize(18);
	INTELLIGENCE.setFillColor(dialoguesColor);
	INTELLIGENCE.setString(L"inteligencja: " + std::to_wstring(player->INTELLIGENCE));

}

void StatsPanel::update() {
	panel.setPosition(cam->position);

	LEVEL.setPosition(cam->position.x - 280, cam->position.y - 180);
	EXPERIENCE.setPosition(cam->position.x - 280, cam->position.y - 160);
	SKILLPOINTS.setPosition(cam->position.x - 280, cam->position.y - 140);

	HP.setPosition(cam->position.x - 280, cam->position.y - 100);
	MP.setPosition(cam->position.x - 280, cam->position.y - 80);

	STRENGTH.setPosition(cam->position.x - 280, cam->position.y - 40);
	DEXTERITY.setPosition(cam->position.x - 280, cam->position.y - 20);
	INTELLIGENCE.setPosition(cam->position.x - 280, cam->position.y);

}

void StatsPanel::draw() {
	window->draw(panel);

	window->draw(LEVEL);
	window->draw(EXPERIENCE);
	window->draw(SKILLPOINTS);

	window->draw(HP);
	window->draw(MP);
	window->draw(STRENGTH);
	window->draw(DEXTERITY);
	window->draw(INTELLIGENCE);
}

StatsPanel* stats = nullptr;
