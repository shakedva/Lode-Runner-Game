#pragma once

//---------------enum section-----------------
enum E_GameObjects
{
	EMPTY = -1, PLAYER, ENEMY, MONEY, LADDER, POLE, FLOORWALL, GIFT, PIT, MENU, BACKGROUND, GAME_OVER, YOU_WON
};
enum E_MediaSound
{
	S_MONEY, S_ENEMY, S_CLOCK, S_PIT, S_BADGIFT, S_NEXTLEVEL, S_MENU, S_LIVESGIFT, S_TIMESGIFT
};


const char NO_DIGGING = ' ', LEFT_PIT = 'Z', RIGHT_PIT = 'X';

const int NO_TIME_LIMIT = -1, TIMES_UP = 0, INIT = 0, TILE_SIZE = 40, DEVIATION = 5, FONT_SIZE = 30,
		  THREE_SEC = 3, MENU_SIZE = 800, BONUS = 10, VOLUME = 30, INFO_SIZE = 200;
