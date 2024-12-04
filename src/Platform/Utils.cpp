#include "Utils.h"

void Explode(char ExplodeChar, std::string String, std::vector<std::string>& Items)
{
	char ch;
	std::string CurrentString = "";
	Items.clear();
	for (size_t i = 0; i < String.length(); i++)
	{
		ch = String[i];
		if (ch == ExplodeChar)
		{
			Items.push_back(CurrentString);
			CurrentString = "";
		}
		else
		{
			CurrentString += ch;
		}
	}
	if (CurrentString.length() > 0)
	{
		Items.push_back(CurrentString);
	}
}
