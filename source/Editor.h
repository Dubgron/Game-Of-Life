#pragma once
#ifndef EDITOR_H
#define EDITOR_H

#include "Map.h"

class Editor {

public:
	//Window, map, event, window size, title
	static void edit(sf::RenderWindow &, sf::Event &, Map &, int, std::string);
	static void info();
};

#endif // !EDITOR_H
