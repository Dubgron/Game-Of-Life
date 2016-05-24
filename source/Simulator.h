#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Map.h"
#include <thread>
#include <chrono>

class Simulator{

public:

	static void setOptions(Map &);
	static void simulation(sf::RenderWindow &, sf::Event &, Map &, int, std::string);
	static void displayMap(sf::RenderWindow &, Map &);
	static void displayTurnCounter(int);
	static void countDownToTheStart();
	static int fCounter(Map &, int, int);
	static int fDecrease(Map &, int);
	static int fIncrease(Map &, int);

private:
	static bool isStopped;
	static int turn;
};

#endif // !SIMULATOR_H
