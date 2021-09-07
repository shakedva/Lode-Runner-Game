//----------------------------------include section---------------------------------
#include "Pit.h"
//-------------------------------functions implementation------------------------------

Pit::Pit(int row, int col, int index) : Unmovable(row, col, index), m_timer(sf::seconds(THREE_SEC))
{
    Media::instance().playSound(S_PIT);
    //when a pit is created, we move it up a little, so an enemy can collide with it    
    m_objSprite.move(0, -DEVIATION);
}

//when a pit is removed, we take the enemy out of it and update the enemy member to nullptr
Pit::~Pit()
{
    if (m_enemy)
    {
        m_enemy->takeOutOfPit();
        m_enemy = nullptr;
    }
}

sf::Time Pit::getTimer() const
{
    return m_timer;
}

//update the time for the pit when each second passes
void Pit::decreaseTimer(sf::Time deltaTime)
{
    m_timer -= deltaTime;
}

void Pit::setEnemyInPit(Enemy* e)
{
    if (!m_enemy) //if there is an enemy in the pit, save it
        m_enemy = e;
}

bool Pit::isPitEmpty() const
{
    if (m_enemy) // there is an enemy in the pit
        return false;
    else // no enemy in the pit
        return true;
}

//when there is a collision with a game object, we double dispach
void Pit::handleCollision(GameObjects& gameObject)
{
    if (&gameObject == this)
        return;
    //double dispatch
    gameObject.handleCollision(*this);
}

void Pit::handleCollision(Enemy& gameObject)
{
    gameObject.handleCollision(*this);
}