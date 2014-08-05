#include "ActionList.h"

// Functions for ActionList helper object go here.
ActionList::ActionList()
{
	for (int i = 0; i < 16; i++)
		list[i] = '`';
}

void ActionList::appendAction(char _action)
{
	for (int i = 0; i < 16; i++)
		if (list[i] == '`') {
			list[i] = _action;
			break;
		}
}

bool ActionList::checkAction(char _action)
{
	for (int i = 0; i < 16; i++)
		if (list[i] == _action)
			return true;
	return false;
}

void ActionList::clearActions()
{
	for (int i = 0; i < 16; i++)
		if (list[i] != '`')
			list[i] = '`';
}

ActionList::~ActionList()
{
}
