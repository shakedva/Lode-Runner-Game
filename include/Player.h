//----------------------------------include section---------------------------------
#pragma once
#include "Character.h"

//---------------------------------class implementation-----------------------------
class Player : public Character
{
public:
	Player(int, int, int);
	//reduce player's lives if he lost to an enemy
	void reducePlayerLives();
	//add momey to the score when player collects stars or moved to next level
	void addMoney(int);

	// get functions
	sf::Vector2f getLocation() const;
	int getScore() const;
	int getLives() const;
	bool getDefault() const;
	char whereToDig() const;
	bool isPlayerInTheAIr() const;
	//set functions
	void setSpritePos(int, int);
	void setDefault();
	void setPlayerInAir(bool);
	void doneDigging(); // after the player digged a pit it changes m_digAhole to ' '
	void setDirection(const sf::Keyboard::Key&);

	void centerThePlayer();

	//virtual functions
	virtual void move(const sf::Time&)override;
	virtual void handleCollision(GameObjects&) override;
	virtual void handleCollision(Enemy&)override;
	virtual void handleCollision(WallFloor&)override;
	virtual void handleCollision(Pole&)override;
	virtual void handleCollision(Ladder&)override;
	virtual void handleCollision(BadGift&)override;
	virtual void handleCollision(MoneyGift&)override;
	virtual void handleCollision(TimeGift&)override;
	virtual void handleCollision(LivesGift&)override;
	//empty virtual functions
	virtual void handleCollision(Money&) override {};
	virtual void handleCollision(Player&) override {};
	virtual void handleCollision(Pit&) override {};


private:
	void incLives(); // if player collected lives gift

	int m_lives, m_score;
	//m_lost- if the player lost a life m_default will turn to true
	//m_isInAir- if the player is falling m_isInAir will turn to true
	bool m_lost = false, 
		 m_isInAir = false; 

	// if the player wants to dig a pit it will represent if it is 'Z' or 'X',
	// ' ' means the player does not want to dig a pit
	char m_digAhole = NO_DIGGING;

};