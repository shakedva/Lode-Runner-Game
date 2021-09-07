//----------------------------------include section---------------------------------
#include "WallFloor.h"

//-------------------------------functions implementation------------------------------

//when there is a collision with a game object, we double dispach
void WallFloor::handleCollision(GameObjects& gameObject)
{
    gameObject.handleCollision(*this);
}

void WallFloor::handleCollision(Player& gameObject)
{	//if the player collides with wall/floor, it means he's not in the air
    gameObject.setPlayerInAir(false);
    gameObject.handleCollision(*this);
}

void WallFloor::handleCollision(Enemy& gameObject)
{
    gameObject.handleCollision(*this);
}