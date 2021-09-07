//----------------------------------include section---------------------------------
#pragma once
#include <iostream>
#include "GameObjects.h"
#include "Player.h"
#include "Enemy.h"

//-------------------------------class implementation------------------------------
class Unmovable : public GameObjects
{
public:
	using GameObjects::GameObjects;
};