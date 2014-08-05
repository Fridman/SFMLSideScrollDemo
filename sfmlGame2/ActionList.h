#pragma once

class ActionList
{
public:
	ActionList(void);
	void appendAction(char _action);
	bool checkAction(char _action);
	void clearActions();
	~ActionList(void);
private:
	char list[16];
};
