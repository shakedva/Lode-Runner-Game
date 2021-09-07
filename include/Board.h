
//----------------------------------include section---------------------------------
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Player.h"
#include "Unmovable.h"
#include "Pit.h"
//---------------------------------class implementation-----------------------------
class Board
{
public:
	Board();
	void printBoard(sf::RenderWindow& ,sf::Time) const;
	void makeMove(const sf::Time&);
	void restartLevel();
	void randomizeEnemy(int, int);

	// get functions
	int getHeight() const;
	int getWidth() const;
	int getTime() const;
	int getLevel() const;
	bool getNextLevel() const;
	bool getIsPlayerCollidedWithTime() const;

	// set functions
	void setPlayerDirection(const sf::Keyboard::Key&);
	void setNextLevel();
	void setTimeGiftCollision();

private:
	void readLevel();
	void printGameObjects(sf::RenderWindow&) const;
	void initBoard();
	void randomizeGift(int ,int);
	void handleCollisions(GameObjects&);
	void checkIsPlayerInAir();
	void checkIsEnemyInAir();
	void checkDigAhole();

	int m_time, m_width, m_height, m_level;

	Player m_player;
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	std::vector<std::unique_ptr<Unmovable>> m_unmovables;
	Pit* m_pit = nullptr;

	std::vector<std::string> m_gameMap;
	std::ifstream m_mapFile;

	bool m_nextLevel = false, // represent if we read a new level
		m_addTime = false, // represent if more time need to be added after collecting time gift
		m_restart = false;  // represent if the player lost life and we restart the game

};