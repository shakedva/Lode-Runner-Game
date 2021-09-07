//----------------------------------include section---------------------------------
#pragma once
#include "Unmovable.h"
//-------------------------------class implementation------------------------------
class Pit : public Unmovable
{
public:
	Pit(int, int, int);
	~Pit();

	sf::Time getTimer() const;
	void decreaseTimer(sf::Time);
	void setEnemyInPit(Enemy*);
	bool isPitEmpty() const;

	//virtual functions
	virtual void handleCollision(GameObjects&)override;
	virtual void handleCollision(Enemy&)override;
	//empty virtual functions
	virtual void handleCollision(Player&)override {};
	virtual void handleCollision(WallFloor&)override {};
	virtual void handleCollision(Money&)override {};
	virtual void handleCollision(Pole&)override {};
	virtual void handleCollision(Ladder&)override {};
	virtual void handleCollision(Pit&)override {};
	virtual void handleCollision(BadGift&)override {};
	virtual void handleCollision(MoneyGift&)override {};
	virtual void handleCollision(TimeGift&)override {};
	virtual void handleCollision(LivesGift&)override {};
private:
	sf::Time m_timer; //set a timer each time a pit is created
	Enemy* m_enemy = nullptr; //hold an enemy that is in the pit
};