
//----------------------------------include section---------------------------------
#include "Board.h"
#include <experimental/vector>
#include <stdio.h>
#include <string>
#include "macros.h"
#include <time.h>
#include "GoodGift.h"
#include "LivesGift.h"
#include "MoneyGift.h"
#include "PermEnemy.h"
#include "RandEnemy.h"
#include "SmartEnemy.h"
#include "Ladder.h"
#include "Pole.h"
#include "WallFloor.h"
#include "Media.h"
#include "Money.h"
#include "BadGift.h"
#include "TimeGift.h"
//----------------------------------const section---------------------------------
const int ALL_COLLECTED = 0, LIFE_OVER = 0, LEVEL_BOUNS = 50, MAX_LEN = 10, BASE = 10;

const char C_EMPTY = ' ', C_PLAYER = '@', C_ENEMY = '%', C_MONEY = '*', C_LADDER = 'H', C_POLE = '-',
		   C_FLOORWALL = '#', C_GIFT = '+';

//----------------------------------functions section---------------------------------
// constructor for Board
Board::Board() : m_level(0), m_player(0,0, PLAYER) 
{
	// opening the file of all the levels
	std::string path = "Board.txt";
	m_mapFile.open(path, std::ios::in);
	// if the file did not open - exit the game
	if (!m_mapFile.is_open())
	{
		exit(EXIT_FAILURE);
	}
	readLevel(); // read the first level
}

void Board::readLevel()
{
	// if reached to the end of the file - player won
	if (m_mapFile.eof()) 
	{
		Media::instance().printEndOfGame(YOU_WON);
		m_mapFile.close(); // closing the file 
		exit(EXIT_SUCCESS);
	}
	// every level add ( 50 * level ) points to the player
	m_player.addMoney(LEVEL_BOUNS * m_level);
	m_level++;

	// read from file height & width & time
	std::string s_height, s_width, s_time;
	m_mapFile >> s_height >> s_width >> s_time;
	// convert from string to int
	m_height = std::stoi(s_height);
	m_width = std::stoi(s_width);
	m_time = std::stoi(s_time);

	// clear all vectors
	m_gameMap.clear();
	m_enemies.clear();
	m_unmovables.clear();

	// represent to the controller that we read a new level and received new time
	m_nextLevel = true;

	// read this level's game map
	std::string line;
	std::getline(m_mapFile, line); // eat \n at the end of the string
	// read the new level and push it to the vector
	for (int i = 0; i < m_height; i++)
	{
		std::getline(m_mapFile, line);
		m_gameMap.push_back(line);
	}
	initBoard();
}

// converting chars from the level's map file to game objects
void Board::initBoard()
{
	char curr;
	// iterate through the level's game map
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			curr = m_gameMap[i][j]; // current char
			switch (curr)
			{
			case C_PLAYER: m_player.setSpritePos(i, j);
				break;
			case C_ENEMY: if(!m_restart) randomizeEnemy(i, j); // dont allow randomizing new enemy if we restart the game
				break;
			case C_MONEY: m_unmovables.push_back(std::make_unique<Money>(i, j, MONEY, *this)); 
				break;
			case C_LADDER: m_unmovables.push_back(std::make_unique<Ladder>(i, j, LADDER)); 
				break;
			case C_POLE: m_unmovables.push_back(std::make_unique<Pole>(i, j, POLE)); 
				break;
			case C_FLOORWALL:m_unmovables.push_back(std::make_unique<WallFloor>(i, j, FLOORWALL)); 
				break;
			case C_GIFT: randomizeGift(i, j);
				break;
			}
		}
	}
	m_restart = false;
}

// this function randomizes gifts, there are 4 types of gifts: bad gift, money gift, lives gift and times gift
void Board::randomizeGift(int row, int col)
{

	 /*allow time gift only when there is time limitation*/
	int typeOfGift = (m_time != NO_TIME_LIMIT) ? rand() % 4 + 1 : rand() % 3 + 1;
	
	switch (typeOfGift)
	{
	case 1: m_unmovables.push_back(std::make_unique<BadGift>(row, col, GIFT, *this));
		break;
	case 2: m_unmovables.push_back(std::make_unique<MoneyGift>(row, col, GIFT));
		break;
	case 3:m_unmovables.push_back(std::make_unique<LivesGift>(row, col, GIFT));
		break;
	case 4: m_unmovables.push_back(std::make_unique<TimeGift>(row, col, GIFT, *this));
		break;
	}
}

// this function randomizes enemies, there are 3 types of enemies: random, smart and permenemt enemies
void Board::randomizeEnemy(int row, int col)
{
	int typeOfEnemy = rand() % 3 + 1;;
	
	switch (typeOfEnemy)
	{
	case 1: m_enemies.push_back(std::make_unique<PermEnemy>(row, col, ENEMY));
		break;
	case 2: m_enemies.push_back(std::make_unique<SmartEnemy>(row, col, ENEMY, m_player));
		break;
	case 3: m_enemies.push_back(std::make_unique<RandEnemy>(row, col, ENEMY));
		break;
	}
}

// this function prints all the game objects and the side menu with all the information required
void Board::printBoard(sf::RenderWindow& window, sf::Time time) const
{
	// print the side menu
	sf::Text info;
	info.setFont(Media::instance().getFont());
	info.setCharacterSize(FONT_SIZE);
	info.setPosition((float)TILE_SIZE * m_width, 0.f);
	info.setFillColor(sf::Color(255, 182, 56));

	char level[MAX_LEN * DEVIATION] = " Level:  ",
		 score[MAX_LEN + DEVIATION] = "\n Score:  ",
		 lives[MAX_LEN + DEVIATION] = "\n Lives:  ";

	char levelString[MAX_LEN], scoreString[MAX_LEN], livesString[MAX_LEN];

	itoa(m_level, levelString, BASE);
	strcat(level, levelString);

	int i_score = m_player.getScore(),
		i_lives = m_player.getLives();

	itoa(i_score, scoreString, BASE);
	strcat(score, scoreString);
	
	itoa(i_lives, livesString, BASE);
	strcat(lives, livesString);
	// unite all the strings with strcat 
	strcat(level, score);
	strcat(level, lives);

	// print the time info only when there is time limitation
	if (time.asSeconds() != NO_TIME_LIMIT)
	{
		char TimeLeft[MAX_LEN + DEVIATION] = "\n Time:  ";
		char TimeLeftString[MAX_LEN + DEVIATION];
		itoa(time.asSeconds(), TimeLeftString, BASE);
		strcat(TimeLeft, TimeLeftString);
		strcat(level, TimeLeft);
	}
	// set into info the united strings
	info.setString(level);
	window.draw(info);
	// prints the level's board
	printGameObjects(window);

}
// prints the player, the enemies, the unmovable objects and the pit if exist
void Board::printGameObjects(sf::RenderWindow& window) const
{
	m_player.draw(window);

	for (int i = 0; i < m_unmovables.size(); i++)
		m_unmovables[i]->draw(window);

	if (m_pit)
		m_pit->draw(window);

	for (int i = 0; i < m_enemies.size(); i++)
		m_enemies[i]->draw(window);
}
// calls the moveables game objects to make a move on the board 
void Board::makeMove(const sf::Time& deltaTime)
{
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->move(deltaTime);
		handleCollisions(*m_enemies[i]);
	}
	m_player.move(deltaTime);
	handleCollisions(m_player);

	// check if the player pressed 'Z' or 'X' for digging a pit
	checkDigAhole();
	// if pit exist, decrese its timer. 
	if(m_pit)
	{
		m_pit->decreaseTimer(deltaTime);
		// it the pit's times up - delete the pit
		if (m_pit->getTimer() <= sf::seconds(TIMES_UP))
		{
			Pit* p = m_pit;
			m_pit = nullptr;
			delete p;
		}
	}
}
//calls every game object to handle its collisions
void Board::handleCollisions(GameObjects& gameObject)
{
	for (auto& unmovable : m_unmovables)
		if (gameObject.checkCollision(unmovable->getGlobalBounds()))
			gameObject.handleCollision(*unmovable);

	// if the game object was collected then remove it from the vector
	std::experimental::erase_if(m_unmovables, [](const auto& item) { return item->isDisposed(); });
	
	// if all money was collected, read the next level
	if (Money::getMoneyConter() == ALL_COLLECTED)
	{
		Media::instance().playSound(S_NEXTLEVEL);
		readLevel();
	}

	if(m_pit)
		if (gameObject.checkCollision(m_pit->getGlobalBounds()))
			gameObject.handleCollision(*m_pit);

	for (auto& enemy : m_enemies)
		if (gameObject.checkCollision(enemy->getGlobalBounds()))
			gameObject.handleCollision(*enemy);

	if (gameObject.checkCollision(m_player.getGlobalBounds()))
		gameObject.handleCollision(m_player);
	
	checkIsPlayerInAir(); 
	checkIsEnemyInAir();
	
	// getDefualt returns if the player lost a life and if so restart level
	// and set default back to 'false'
	if (m_player.getDefault())
	{
		restartLevel();
		m_player.setDefault();
	}

	// if the player lost - game over
	if (m_player.getLives() == LIFE_OVER)
	{
		Media::instance().printEndOfGame(GAME_OVER);
		exit(EXIT_FAILURE);
	}
}

// the function checks if the player is in the air, if he is during a fall
void Board::checkIsPlayerInAir()
{
	// gloBuPlayer is the rectangle underneath the player
	sf::FloatRect gloBuPlayer(m_player.getGlobalBounds().left, m_player.getGlobalBounds().top + DEVIATION,
		m_player.getGlobalBounds().width, m_player.getGlobalBounds().height);

	// iterate through all the unmovable objects ans check if it collides with the rectangle underneath the player
	// if so - the player is not in the air
	for (int j = 0; j < m_unmovables.size(); j++)
	{
		if (m_unmovables[j]->checkCollision(gloBuPlayer))
		{
			m_player.setPlayerInAir(false);
			return;
		}
	}
	// the player is in the air
	m_player.setPlayerInAir(true);
}
// check if the enemy reach the end of the floor and if so- stop him
void Board::checkIsEnemyInAir()
{
	for (int i = 0; i < m_enemies.size(); i++)
	{
		bool notInAir = false;

		// gloBuEnemy is the rectangle from the down left or down right of the enemy
		// if the enemy's is going left, the gloBuEnemy is the rectangle from the down left side of the enemy
		// if the enemy's is going right, the gloBuEnemy is the rectangle from the down right side of the enemy
		sf::FloatRect gloBuEnemy(m_enemies[i]->getGlobalBounds().left+35*m_enemies[i]->getDirection().x,
			m_enemies[i]->getGlobalBounds().top + DEVIATION, m_enemies[i]->getGlobalBounds().width, m_enemies[i]->getGlobalBounds().height);

		for (int j = 0; j < m_unmovables.size(); j++)
		{
			// if the gloBuEnemy collides with floor it means the enemy is not about to fall
			if (m_unmovables[j]->checkCollision(gloBuEnemy))
			{
				notInAir = true;
				break;
			}
		}
		// if he is not about to fall check the next enemy in the vector
		if (notInAir)
			continue;
		// he is about to fall then turn to the other direction
		m_enemies[i]->turnTheOtherDirection();
		
	}
}
// check if the player pressed 'Z' or 'X' to dig a pit
void Board::checkDigAhole()
{
	if (m_player.whereToDig() != NO_DIGGING) // the player tries to dig 
	{
		//check if pit does not exist and that the player is not in the air
		if (!m_pit && !m_player.isPlayerInTheAIr())
		{
			m_player.centerThePlayer(); // center the player directly on the floor
			if (m_player.whereToDig() == LEFT_PIT)
				m_pit = new Pit(((int)(m_player.getPosition().y + TILE_SIZE) / TILE_SIZE), (int)((m_player.getPosition().x - TILE_SIZE) / TILE_SIZE), PIT);
			else
				m_pit = new Pit((int)((m_player.getPosition().y + TILE_SIZE) / TILE_SIZE),(int) ((m_player.getPosition().x + TILE_SIZE) / TILE_SIZE), PIT);
		}
		m_player.doneDigging(); // set the player's digging to default
	}
}
// return the enemies to their default locations & read again the level
void Board::restartLevel()
{
	m_restart = true; 
	m_player.reducePlayerLives();
	for (auto& enemy : m_enemies)
		enemy->moveToDefaultLocation();
	m_unmovables.clear();

	initBoard(); 
}

//----------------------------------------------set functions------------------------------------------ 
void Board::setPlayerDirection(const sf::Keyboard::Key& key)
{
	m_player.setDirection(key);
}

void Board::setTimeGiftCollision()
{
	m_addTime = !m_addTime;
}

void Board::setNextLevel()
{
	m_nextLevel = false;
}
//----------------------------------------------get functions------------------------------------------ 
int Board::getLevel() const
{
	return m_level;
}

// if the player collided with time gift we change the value of m_addTime to true
// so the controller will know to add 10 seconds to the timer of the game
bool Board::getIsPlayerCollidedWithTime() const
{
	return m_addTime;
}

// m_nextLevel tells the controller if we read a new level so it could receive the new time limitation
// on the current level
bool Board::getNextLevel() const
{
	return m_nextLevel;
}

int Board::getHeight() const
{
	return m_height;
}
int Board::getWidth() const
{
	return m_width;
}
int Board::getTime() const
{
	return m_time;
}