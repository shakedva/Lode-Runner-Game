//----------------------------------include section---------------------------------
#pragma once
#include "Character.h"
#include "Player.h"
//----------------------------------const section---------------------------------
const auto enemy_speed = (float)80;
//---------------------------------class implementation-----------------------------
class Enemy : public Character
{
public:
	using Character::Character;
	sf::Vector2f getDirection() const;
	void turnTheOtherDirection();
	void takeOutOfPit();
	bool isInPit() const;

	virtual void move(const sf::Time& deltaTime) = 0;
	//virtual functions
	virtual void handleCollision(GameObjects&)override;
	virtual void handleCollision(Player&)override;
	virtual void handleCollision(WallFloor&)override;
	virtual void handleCollision(Pit&)override;
	//empty virtual functions
	virtual void handleCollision(Money&)override {};
	virtual void handleCollision(Enemy&)override {};
	virtual void handleCollision(BadGift&)override {};
	virtual void handleCollision(MoneyGift&)override {};
	virtual void handleCollision(TimeGift&)override {};
	virtual void handleCollision(LivesGift&)override {};
	virtual void handleCollision(Pole&)override {};
	virtual void handleCollision(Ladder&)override {};
protected:
	bool m_inPit = false; // represent if the enemy is inside a pit
};