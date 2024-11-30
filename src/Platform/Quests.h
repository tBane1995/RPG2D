#pragma once

#include <string>
#include <vector>

enum class questCondition { currentHP, showDialogue, haveArmor, haveHelmet, havePants, position, is_dressed };
enum class questState { unstarted, actual, ended };

class Step {
public:
	questCondition condition;
	std::string value;
	std::wstring text;

	Step(questCondition condition, std::string value, std::wstring text) {
		this->condition = condition;
		this->value = value;
		this->text = text;
	}

	bool check();

};


class Quest {
public:
	short id;
	std::wstring name;
	questState state;
	std::vector < Step* > steps;
	short currentStep;

	Quest(short id, std::wstring name) {
		
		this->id = id;
		this->name = name;
		steps.clear();
		state = questState::unstarted;
		currentStep = 0;

	}
	
	void addStep(questCondition condition, std::string value, std::wstring text) {
		Step* step = new Step(condition, value, text);
		steps.push_back(step);
	}

	void check() {

		if (currentStep >= steps.size() - 1)
			state = questState::ended;

		if (steps[currentStep]->check())
			currentStep++;
		
	}


};

extern std::vector < Quest* > quests;
void loadQuests();
void checkQuests();