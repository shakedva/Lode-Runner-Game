
//----------------------------------include section---------------------------------
#include "Controller.h"
#include "Unmovable.h"
#include "Character.h"
#include <SFML/Graphics.hpp>

//----------------------------------functions section---------------------------------
Controller::Controller() : m_gameBoard(), m_time(sf::seconds(m_gameBoard.getTime()))
{}

// the main game loop
void Controller::run()
{
	if (openMenu()) // if the user pressed on "new game"
	{
		sf::RenderWindow window(sf::VideoMode(m_gameBoard.getWidth() * TILE_SIZE + INFO_SIZE, m_gameBoard.getHeight() * TILE_SIZE),
			"Lode Runner", sf::Style::Titlebar | sf::Style::Close);
		// the background texture of the game
		sf::Sprite background;
		background = sf::Sprite(Media::instance().getTexture(BACKGROUND));
		background.setPosition(0.f, 0.f);
		background.setScale(
			((float)(m_gameBoard.getWidth() * TILE_SIZE)+ INFO_SIZE) / background.getLocalBounds().width,
			((float)( m_gameBoard.getHeight() * TILE_SIZE)) / background.getLocalBounds().height);
        
		sf::Clock clock;
		m_time = sf::seconds(m_gameBoard.getTime());
		while (window.isOpen())
		{
			// Handle events
			sf::Event event;
			while (window.pollEvent(event))
			{
				// Window closed or escape key pressed: exit
				if ((event.type == sf::Event::Closed) ||
					((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
				{
					window.close();
					break;
				}
				if (event.type == sf::Event::KeyPressed)
				{	
					// set player direction
					m_gameBoard.setPlayerDirection(event.key.code);
				}
				else
				{ 
					// no key was pressed, don't move player 
					m_gameBoard.setPlayerDirection(sf::Keyboard::Key::Space);
				}
			}
			
			sf::Time deltaTime = clock.restart(); // restart the clock

			window.clear();
			window.draw(background);
			m_gameBoard.makeMove(deltaTime);
			m_gameBoard.printBoard(window, m_time);
			// if the player collided with time gift add 10 seconds to the time limitation
			if (m_gameBoard.getIsPlayerCollidedWithTime())
			{
				addTime();
				m_gameBoard.setTimeGiftCollision();
			}
			// if the player moved to the next level, receive new time limitation and resize the window
			// to its current dimentions
			if (m_gameBoard.getNextLevel())
			{
				m_gameBoard.setNextLevel(); // tells the board we received the new information
				m_time = sf::seconds(m_gameBoard.getTime());
				window.create(sf::VideoMode(m_gameBoard.getWidth() * TILE_SIZE + INFO_SIZE, m_gameBoard.getHeight() * TILE_SIZE),
					"Lode Runner", sf::Style::Titlebar | sf::Style::Close);
				background.setScale(
					((float)( m_gameBoard.getWidth() * TILE_SIZE) + INFO_SIZE) / background.getLocalBounds().width,
					((float)( m_gameBoard.getHeight() * TILE_SIZE)) / background.getLocalBounds().height);
			}
			// if there is time limitation
			if (m_time != sf::seconds(NO_TIME_LIMIT))
			{
				// if times up restart the level and change m_playedClock back to false
				if (m_time <= sf::seconds(TIMES_UP))
				{
					m_gameBoard.restartLevel();
					m_playedClock = false;
					m_time = sf::seconds(m_gameBoard.getTime());
				}
				// if there are 3 seconds left play clock ticking sound
				else if (m_time.asSeconds() <= THREE_SEC && !m_playedClock)
				{
					Media::instance().playSound(S_CLOCK);
					m_playedClock = true;
					m_time -= deltaTime;
				}
				else
					m_time -= deltaTime;
			}
			window.display();
		}
	}
}

bool Controller::openMenu() const
{
	sf::RenderWindow menuWindow(sf::VideoMode(MENU_SIZE, MENU_SIZE), "Lode Runner Menu", sf::Style::Titlebar | sf::Style::Close);

	sf::Sprite menuBackground;
	Media& tex = Media::instance();
	menuBackground = sf::Sprite(tex.getTexture(MENU));
	menuBackground.setPosition(0.f, 0.f);
	menuBackground.setScale(
		800.f / menuBackground.getLocalBounds().width,
		800.f / menuBackground.getLocalBounds().height);

	sf::Text newGame, exitGame;
	newGame.setFont(Media::instance().getFont());
	newGame.setCharacterSize(TILE_SIZE);
	newGame.setPosition(300.f, 300.f);
	newGame.setFillColor(sf::Color::White);
	newGame.setString("New Game");

	exitGame.setFont(Media::instance().getFont());
	exitGame.setCharacterSize(TILE_SIZE);
	exitGame.setPosition(300.f, 400.f);
	exitGame.setFillColor(sf::Color::White);
	exitGame.setString("Exit Game");

	while (menuWindow.isOpen())
	{
		// draw the menus background and its buttons
		menuWindow.draw(menuBackground);
		menuWindow.draw(newGame);
		menuWindow.draw(exitGame);
		
		sf::Event event;
		while (menuWindow.pollEvent(event))
		{
			// Window closed or escape key pressed: exit
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				menuWindow.close();
				return false;
			}
			// pressed on the window
			if (event.type == sf::Event::MouseButtonReleased)
			{
				// save the click location
				auto clickLocation = menuWindow.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				// pressed on "new game" return true
				if (newGame.getGlobalBounds().contains(clickLocation))
				{
					Media::instance().playSound(S_MENU);
					return true;
				}
				// pressed on "exit game" return false
				if (exitGame.getGlobalBounds().contains(clickLocation))
				{
					menuWindow.close();
					return false;
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
				// get the current mouse position in the window
				sf::Vector2i pixelPos = sf::Mouse::getPosition(menuWindow);

				// convert it to world coordinates
				sf::Vector2f worldPos = menuWindow.mapPixelToCoords(pixelPos);

				// if the cursor is on "new game" then change its outline to be thick and colorful
				if (newGame.getGlobalBounds().contains(worldPos))
				{
					newGame.setOutlineColor(sf::Color(205,86,106));
					newGame.setOutlineThickness(5);
				}
				else
				{
					newGame.setOutlineColor(sf::Color::Black);
					newGame.setOutlineThickness(5);
				}
				// if the cursor is on "exit game" then change its outline to be thick and colorful
				if (exitGame.getGlobalBounds().contains(worldPos))
				{
					exitGame.setOutlineColor(sf::Color(205, 86, 106));
					exitGame.setOutlineThickness(5);
				}
				else
				{
					exitGame.setOutlineColor(sf::Color::Black);
					exitGame.setOutlineThickness(5);
				}
			}
		}
		menuWindow.display();
	}
}
// adds 10 seconds to the time limitation
void Controller::addTime()
{
	m_time += sf::seconds(m_gameBoard.getLevel() * BONUS);
}