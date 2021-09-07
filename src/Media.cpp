//----------------------------------include section---------------------------------
#include "Media.h"
#include <Windows.h>
#include "macros.h"
//----------------------------------const section---------------------------------
const int MILI_SEC = 1000;
//----------------------------------functions section---------------------------------
// constructor that opens all the files needed for the game
Media::Media()
{
	m_font.loadFromFile("resources/Bubblegum.ttf");
	loadTextures(); 
	loadAudio();
}
// load all the textures for the game and push it into m_textures
void Media::loadTextures()
{
	sf::Texture player, enemy, money, ladder, pole, floorWall, gift, menuBackground, hole, Background;
	player.loadFromFile("1.png");
	enemy.loadFromFile("6.png");
	money.loadFromFile("2.png");
	ladder.loadFromFile("888.png");
	pole.loadFromFile("5.png");
	floorWall.loadFromFile("3-1.png");
	gift.loadFromFile("7.png");
	menuBackground.loadFromFile("poster1.png");
	hole.loadFromFile("99.png");
	Background.loadFromFile("background.jpg");

	// push into Texture vector 
	m_textures.push_back(player);
	m_textures.push_back(enemy);
	m_textures.push_back(money);
	m_textures.push_back(ladder);
	m_textures.push_back(pole);
	m_textures.push_back(floorWall);
	m_textures.push_back(gift);
	m_textures.push_back(hole);
	m_textures.push_back(menuBackground);
	m_textures.push_back(Background);
}
// load all the audio for the game and saves it the the class's members
void Media::loadAudio()
{
	if (m_backgroundMusic.openFromFile("resources/funny-adventure.wav"))
	{
		m_backgroundMusic.setVolume(VOLUME);
		m_backgroundMusic.setLoop(true);
		m_backgroundMusic.play();
	}

	sf::SoundBuffer moneySoundBuffer, enemySoundBuffer, clockSoundBuffer, pitSoundBuffer, badGiftSoundBuffer,
		nextLevelSoundBuffer, clickSoundBuffer, livesGiftSoundBuffer, timesGiftSonundBuffer;
	moneySoundBuffer.loadFromFile("resources/take_money.wav");
	enemySoundBuffer.loadFromFile("resources/lost_lives.wav");
	clockSoundBuffer.loadFromFile("resources/clock-ticking.wav");
	pitSoundBuffer.loadFromFile("resources/digging.wav");
	badGiftSoundBuffer.loadFromFile("resources/badgift.wav");
	nextLevelSoundBuffer.loadFromFile("resources/nextlevel.wav");
	clickSoundBuffer.loadFromFile("resources/click.wav");
	livesGiftSoundBuffer.loadFromFile("resources/livesgift.wav");
	timesGiftSonundBuffer.loadFromFile("resources/timegift.wav");

	m_soundBuffer.push_back(moneySoundBuffer);
	m_soundBuffer.push_back(enemySoundBuffer);
	m_soundBuffer.push_back(clockSoundBuffer);
	m_soundBuffer.push_back(pitSoundBuffer);
	m_soundBuffer.push_back(badGiftSoundBuffer);
	m_soundBuffer.push_back(nextLevelSoundBuffer);
	m_soundBuffer.push_back(clickSoundBuffer);
	m_soundBuffer.push_back(livesGiftSoundBuffer);
	m_soundBuffer.push_back(timesGiftSonundBuffer);


	for (int i = 0; i < m_soundBuffer.size(); i++)
	{
		m_sounds.push_back(sf::Sound(m_soundBuffer[i]));
	}
}

Media& Media::instance()
{
	// the object inst is created once and can be reached everywhere in the game
	static Media inst;
	return inst;
}
// returns the wanted texture
sf::Texture& Media::getTexture(int index) 
{
	return m_textures[index];
}

sf::Font& Media::getFont() 
{
	return m_font;
}
// playes the wanted sound effect 
void Media::playSound(int index)
{
	m_sounds[index].play();
}
// opens a new small window and it shows if the player lost or won the game accordinig to the action received
void Media::printEndOfGame(int action) const
{
	sf::RenderWindow window(sf::VideoMode(MENU_SIZE, MENU_SIZE), "Lode Runner", sf::Style::Titlebar | sf::Style::Close);
	// setes the text
	sf::Text endText;
	endText.setFont(m_font);
	endText.setCharacterSize(INFO_SIZE);
	endText.setPosition(150.f, 200.f);
	endText.setFillColor(sf::Color(205, 86, 106));
	switch (action)
	{
	case GAME_OVER: endText.setString("Game\nOver"); break;
	case YOU_WON: endText.setString("You\nWon!"); break;
	}
	// print the background and the text
	sf::Sprite background = sf::Sprite(m_textures[BACKGROUND]);
	window.draw(background);
	window.draw(endText);
	window.display();
	Sleep(THREE_SEC * MILI_SEC); // shows the message for 3 seconds
}
