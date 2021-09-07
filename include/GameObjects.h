//----------------------------------include section---------------------------------
#pragma once
#include <SFML/Graphics.hpp>
#include "Media.h"
#include "macros.h"

class Player;
class Enemy;
class WallFloor;
class Money;
class Pole;
class Ladder;
class BadGift;
class GoodGift;
class MoneyGift;
class TimeGift;
class LivesGift;
class Pit;
//---------------------------------class implementation-----------------------------
class GameObjects
{
public:
	GameObjects(int, int, int);
	virtual ~GameObjects() = default;
	void draw(sf::RenderWindow& window) const;
	bool checkCollision(const sf::FloatRect& ) const;
	sf::FloatRect getGlobalBounds() const; // returns the global bounds of m_objSprite
	bool isDisposed() const; // if the game object was collected then it is disposed
	sf::Vector2f getPosition(); //returns the position of m_objSprite 
	
	// abstruct functions
	virtual void handleCollision(GameObjects&) = 0;
	virtual void handleCollision(Player&) = 0;
	virtual void handleCollision(Enemy&) = 0;
	virtual void handleCollision(WallFloor&) = 0;
	virtual void handleCollision(Money&) = 0;
	virtual void handleCollision(Pole&) = 0;
	virtual void handleCollision(Ladder&) = 0;
	virtual void handleCollision(Pit&) = 0;
	virtual void handleCollision(BadGift&) = 0;
	virtual void handleCollision(MoneyGift&) = 0;
	virtual void handleCollision(TimeGift&) = 0;
	virtual void handleCollision(LivesGift&) = 0;

protected:
	sf::Sprite m_objSprite;
	bool m_isDisposed = false;
};