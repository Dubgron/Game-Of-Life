#pragma once
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Map.h"
#include <Windows.h>

class Simulator{

public:

	static void simulation(sf::RenderWindow &, sf::Event &, MapData &, int, std::string);
	static void displayMap(sf::RenderWindow &, MapData &);
	static void displayTurnCounter(int);
	static void countDownToTheStart();
	static int fCounter(MapData &, int, int);
	static int fDecrease(MapData &, int);
	static int fIncrease(MapData &, int);

private:
	static bool isStopped;
	static int turn;
};

#endif // !SIMULATOR_H
