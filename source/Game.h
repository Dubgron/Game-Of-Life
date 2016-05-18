#pragma once
#ifndef GAME_H
#define GAME_H

#include "Editor.h"
#include "Simulator.h"

class Game {

public:
	Game(int, std::string);

	void start();
	void menu();
	MapData map;

private:
	sf::RenderWindow window;
	sf::Event event;
	int windowSize;
	std::string title;
};

#endif // !GAME_H
