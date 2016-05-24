#include "Options.h"

Options::Options() {

	theme = new sf::Color[THEMES_AMOUNT];
	theme[0] = sf::Color::Black;
	theme[1] = sf::Color::White;
}

void Options::set(sf::Color aliveColor, sf::Color deadColor) {

	theme[0] = aliveColor;
	theme[1] = deadColor;
}
