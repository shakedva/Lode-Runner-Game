//----------------------------------include section---------------------------------
#pragma once
#include "Board.h"

//---------------------------------class implementation-----------------------------
class Controller
{
public:
	Controller();
	void run();
private:
	bool openMenu() const; // start menu
	void addTime();

	// --------------members--------------
	sf::Time m_time;
	Board m_gameBoard;
	bool m_playedClock = false; // if there are 3 seconds left to the game it will change to 'true'
};