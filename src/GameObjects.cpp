//----------------------------------include section---------------------------------
#include <iostream>
#include "GameObjects.h"

GameObjects::GameObjects(int row, int col, int index) 
{
	Media& tex = Media::instance();
	m_objSprite = sf::Sprite(tex.getTexture(index));
	m_objSprite.setPosition((float)col * TILE_SIZE, (float)row * TILE_SIZE);
}

// print m_objSprite on the window received
void GameObjects::draw(sf::RenderWindow& window) const
{
	window.draw(m_objSprite);
}
// return if the game object was collected
bool GameObjects::isDisposed() const
{
	return m_isDisposed;
}
//returns the position of m_objSprite
sf::Vector2f GameObjects::getPosition()
{
	return m_objSprite.getPosition();
}

// check if there is a collision of the game object with the global bounds received
bool GameObjects::checkCollision(const sf::FloatRect& gloBou) const
{
	return m_objSprite.getGlobalBounds().intersects(gloBou);
}

sf::FloatRect GameObjects::getGlobalBounds() const
{
	return m_objSprite.getGlobalBounds();
}

