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
	static void countDownToTheStart(sf::RenderWindow &);
	static void update(sf::RenderWindow &, Map &);
	static int fCounter(Map &, int, int);
	static int fDecrease(Map &, int);
	static int fIncrease(Map &, int);

private:
	static bool isStopped;
	static int turn;

	static sf::Clock clock;
	static sf::Time frameCounter;
	static sf::Time framesPerSecond;
};

#endif // !SIMULATOR_H
