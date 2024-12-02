#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>


extern sf::Font basicFont;
extern sf::Font dialogBoxFont;


void loadFonts();
std::wstring ConvertUtf8ToWide(const std::string& utf8Str);
void replaceAll(std::string& str, const std::string& from, const std::string& to);
std::vector < std::wstring > wrapText(std::wstring text, const sf::Font& font, short characterSize, short maxWidth);
std::string getShortName(std::string fullname);
std::wstring getShortName(std::wstring fullname);
