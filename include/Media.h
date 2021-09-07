//----------------------------------include section---------------------------------
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
//---------------------------------class implementation-----------------------------
//Media is a Singelton pattern
class Media
{
public:
	static Media& instance();
	sf::Texture& getTexture(int); 
	sf::Font& getFont() ;
	void printEndOfGame(int) const;
	void playSound(int);
private:
	Media(); // private constructor
	void loadTextures();
	void loadAudio();

	std::vector <sf::Texture> m_textures;
	sf::Font m_font;
	sf::Music m_backgroundMusic;
	std::vector <sf::Sound> m_sounds;
	std::vector <sf::SoundBuffer> m_soundBuffer;
};