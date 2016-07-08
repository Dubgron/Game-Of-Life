#ifndef OPTIONS_H
#define OPTIONS_H

#define THEMES_AMOUNT 2

#include "SFML/Graphics.hpp"

struct Options {
	
	Options();
	void set(sf::Color, sf::Color);

	sf::Time frameRate;
	sf::Color* theme;
};

#endif // !OPTIONS_H
