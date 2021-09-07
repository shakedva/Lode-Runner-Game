//----------------------------------include section---------------------------------
#include "Player.h"
#include "macros.h"
#include <iostream>
#include "Pole.h"
#include "WallFloor.h"
#include "Ladder.h"

//----------------------------------const section---------------------------------
const auto fallingSpeed = (float)200,
		   player_speed = (float)140;
const int LIVES = 3;

//----------------------------------functions section---------------------------------


Player::Player(int row, int col, int index) : Character(row,col, index), m_lives(LIVES), m_score(0)
{
	m_defaultLocation = sf::Vector2f((float)col * TILE_SIZE, (float)row * TILE_SIZE);
}

//----------------------------------get functions---------------------------------

sf::Vector2f Player::getLocation() const
{
	return m_objSprite.getPosition();
}
int Player::getScore() const
{
	return m_score;
}
bool Player::getDefault() const
{
	return m_lost;
}
int Player::getLives() const
{
	return m_lives;
}
char Player::whereToDig() const
{
	return m_digAhole;
}
bool Player::isPlayerInTheAIr() const
{
	return m_isInAir;
}

//----------------------------------set functions---------------------------------
// sets the direction of the player according to the key received from the user
void Player::setDirection(const sf::Keyboard::Key& key)
{
	switch (key)
	{
	case sf::Keyboard::Key::Space:
		m_direction = sf::Vector2f(0, 0); break;
	case sf::Keyboard::Key::Left:
		m_direction = sf::Vector2f(-1, 0); break;
	case sf::Keyboard::Key::Right:
		m_direction = sf::Vector2f(1, 0); break;
	case sf::Keyboard::Key::Down:
		m_direction = sf::Vector2f(0, 1); break;
	case sf::Keyboard::Key::Up:
		m_direction = sf::Vector2f(0, -1); break;
	case sf::Keyboard::Key::Z: // dig a left hole
		m_digAhole = LEFT_PIT;
		break;
	case sf::Keyboard::Key::X: // dig a right hole
		m_digAhole = RIGHT_PIT;
		break;
	default: m_direction = sf::Vector2f(0, 0);
		break;
	}
}
// this function is accessed after restarting the level and it changes m_defualt to false
void Player::setDefault()
{
	m_lost = false;
}
// receive if the player is in the air or not
void Player::setPlayerInAir(bool b)
{
	m_isInAir = b;
}
// after digging this function changes m_digAhole to ' ' so the player won't try to dig again
void  Player::doneDigging()
{
	m_digAhole = NO_DIGGING;
}
void Player::setSpritePos(int row, int col)
{
	m_objSprite.setPosition((float)col * TILE_SIZE, (float)row * TILE_SIZE);
	m_defaultLocation = sf::Vector2f((float)col * TILE_SIZE, (float)row * TILE_SIZE);
}
//--------------------------other functions----------------------
//this function moves the player to its direction if he is not in the air
//otherwise he will keep falling
void Player::move(const sf::Time& deltaTime) 
{
	if (m_isInAir)
	{
		setDirection(sf::Keyboard::Key::Down);
		m_objSprite.move(m_direction * fallingSpeed * deltaTime.asSeconds());
	}
	else
		m_objSprite.move(m_direction * player_speed * deltaTime.asSeconds());
}

void Player::reducePlayerLives()
{
	m_lives--;
}

void Player::addMoney (int money)
{
	m_score += money;
}
void Player::incLives()
{
	m_lives++;
}

//center the player on the floor
void Player::centerThePlayer()
{
	// is ceils the y coordinate of the player so he could be directly on the floor
	m_objSprite.setPosition(m_objSprite.getPosition().x, (ceil(m_objSprite.getPosition().y / TILE_SIZE)) * TILE_SIZE);
}

//------------------------------------virtual functions----------------------------------

//when there is a collision with a game object, we double dispach
void Player::handleCollision(GameObjects& gameObject)
{
	if (&gameObject == this)
		return;
	//double dispatch
	gameObject.handleCollision(*this);
}

// player collides with enemy
void  Player::handleCollision(Enemy& ) 
{
	Media::instance().playSound(S_ENEMY);
	m_lost = true; // the player lost a life
}

void  Player::handleCollision(WallFloor& gameObject)
{
	m_direction = sf::Vector2f(0, 0);
	hitAwall(gameObject);

	if (gameObject.getPosition().y > m_objSprite.getPosition().y)  // this is a collision with floor
	{
		// center the player on the floor after falling on it
		m_objSprite.move(0, -1);
		m_objSprite.setPosition(m_objSprite.getPosition().x, floor(m_objSprite.getPosition().y) + 1);
	}
}

void Player::handleCollision(MoneyGift& ) 
{
	addMoney(BONUS); // add 10 points to the player's score
}

void Player::handleCollision(LivesGift& ) 
{
	Media::instance().playSound(S_LIVESGIFT);
	incLives();
}

void Player::handleCollision(Pole& gameObject)
{
	// the player is not allowed to climb up the pole  
	if (m_direction == sf::Vector2f(0, -1))
		setDirection(sf::Keyboard::Key::Space);

	// the player is allowed to move left and right on the pole  
	if (m_direction == sf::Vector2f(1, 0) || m_direction == sf::Vector2f(-1, 0))
		m_objSprite.setPosition({ m_objSprite.getPosition().x,gameObject.getPosition().y }); // center on the pole
}
void Player::handleCollision(Ladder& gameObject)
{
	// the player is allowed to move up and down the ladder
	if (m_direction == sf::Vector2f(0, 1) || m_direction == sf::Vector2f(0, -1))
		m_objSprite.setPosition({ gameObject.getPosition().x ,m_objSprite.getPosition().y }); // center on the ladder
}

void Player::handleCollision(BadGift& ) 
{
	Media::instance().playSound(S_BADGIFT);
}
void Player::handleCollision(TimeGift& ) 
{
	Media::instance().playSound(S_TIMESGIFT);
}