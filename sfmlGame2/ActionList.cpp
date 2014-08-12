#include "ActionList.h"

// Functions for ActionList helper object go here.
ActionList::ActionList()
{
	for (int i = 0; i < 16; i++)
		list[i] = '`';
}

void ActionList::appendAction(char _action)
	// Adds actions to the list for the game entities to do.
{
	for (int i = 0; i < 16; i++)
		if (list[i] == '`') {
			list[i] = _action;
			break;
		}
}

bool ActionList::checkAction(char _action)
	// Checks whether the action exists within the list or not.
{
	for (int i = 0; i < 16; i++)
		if (list[i] == _action)
			return true;
	return false;
}

void ActionList::clearActions()
	// Clears the list of all actions.
{
	for (int i = 0; i < 16; i++)
		if (list[i] != '`')
			list[i] = '`';
}

ActionList::~ActionList()
{
}
