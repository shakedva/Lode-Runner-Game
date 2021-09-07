//----------------------------------include section---------------------------------
#pragma once
#include "ObjectsToCollect.h"
#include "Board.h"

//---------------------------------class implementation--------------------------------
class Money : public ObjectsToCollect
{
public:
	Money(int, int, int, Board&);
	~Money();
	static int getMoneyConter(); //static get function
	//virtual functions
	virtual void handleCollision(GameObjects&)override;
	virtual void handleCollision(Player&)override;
	//empty virtual functions
	virtual void handleCollision(Enemy&)override {};
	virtual void handleCollision(WallFloor&) override {};
	virtual void handleCollision(Money&)override {};
	virtual void handleCollision(Pit&)override {};
	virtual void handleCollision(Pole&) override {};
	virtual void handleCollision(Ladder&)override {};
	virtual void handleCollision(BadGift&) override {};
	virtual void handleCollision(MoneyGift&)override {};
	virtual void handleCollision(TimeGift&)override {};
	virtual void handleCollision(LivesGift&) override {};

private:
	Board& m_b; //receives the board to change it
	static int m_MoneyConter; //how many money objects there are
};