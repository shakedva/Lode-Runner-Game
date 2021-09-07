//----------------------------------include section--------------------------------
#pragma once
#include "Unmovable.h"
//----------------------------------class implementation---------------------------
class Pole : public Unmovable
{
public:
	using Unmovable::Unmovable;
	//virtual functions
	virtual void handleCollision(GameObjects&)override;
	virtual void handleCollision(Player&)override;
	//empty virtual functions
	virtual void handleCollision(Enemy&)override {};
	virtual void handleCollision(WallFloor&)override {};
	virtual void handleCollision(Money&)override {};
	virtual void handleCollision(Pole&)override {};
	virtual void handleCollision(Ladder&)override {};
	virtual void handleCollision(Pit&)override {};
	virtual void handleCollision(BadGift&)override {};
	virtual void handleCollision(MoneyGift&)override {};
	virtual void handleCollision(TimeGift&)override {};
	virtual void handleCollision(LivesGift&)override {};
};