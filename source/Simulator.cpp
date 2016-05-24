#include "Simulator.h"

bool Simulator::isStopped = false;
int Simulator::turn = 0;

sf::Clock Simulator::clock;
sf::Time Simulator::frameCounter = sf::Time::Zero;
sf::Time Simulator::framesPerSecond = sf::Time::Zero;

int Simulator::fIncrease(Map &map, int n) {

	return n < map.squaresAmount - 1 ? n + 1 : 0;
}

int Simulator::fDecrease(Map &map, int n) {

	return n > 0 ? n - 1 : map.squaresAmount - 1;
}

int Simulator::fCounter(Map &map, int x, int y) {

	int counter = 0;

	int dX = fDecrease(map, x);
	int iX = fIncrease(map, x);
	int dY = fDecrease(map, y);
	int iY = fIncrease(map, y);

	if (map.isAlive[dX][dY]) counter++;
	if (map.isAlive[x][dY]) counter++;
	if (map.isAlive[iX][dY]) counter++;
	if (map.isAlive[iX][y]) counter++;
	if (map.isAlive[iX][iY]) counter++;
	if (map.isAlive[x][iY]) counter++;
	if (map.isAlive[dX][iY]) counter++;
	if (map.isAlive[dX][y]) counter++;

	return counter;
}

void Simulator::countDownToTheStart(sf::RenderWindow &window) {

	for (int i = 3; i > 0; i--) {

		system("cls");
		std::cout << "-= The Game of Life =-\n\n";
		std::cout << "Simulation starts in " << i << (i == 1 ? " second." : " seconds.");
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	system("cls");

	std::cout << "-= The Game of Life =-\n\n";
	std::cout << "Simulation started.";

	window.setActive();
}

void Simulator::simulation(sf::RenderWindow &window, sf::Event &event, Map &map, int windowSize, std::string title) {

	window.create(sf::VideoMode(windowSize, windowSize), title, sf::Style::Close);

	displayMap(window, map);
	countDownToTheStart(window);

	framesPerSecond = map.settings.frameRate;
	clock.restart();

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			switch (event.type) {

				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						window.close();
					break;
			}
		}

		update(window, map);
	}
}

void Simulator::update(sf::RenderWindow &window, Map &map) {

	int counter;

	while (frameCounter > framesPerSecond) {
		frameCounter -= framesPerSecond;

		window.clear();

		for (int y = 0; y < map.squaresAmount; y++) {
			for (int x = 0; x < map.squaresAmount; x++) {

				counter = fCounter(map, x, y);

				map.statusChange(map.isAlive[x][y], x, y);

				if (map.isAlive[x][y] && (counter < 2 || counter > 3))
					map.willBeAlive[x][y] = false;
				else if (counter == 3)
					map.willBeAlive[x][y] = true;
			}
		}
		for (int y = 0; y < map.squaresAmount; y++)
			for (int x = 0; x < map.squaresAmount; x++)
				map.isAlive[x][y] = map.willBeAlive[x][y];

		window.draw(map.squares);
		window.display();

		turn++;
	}
	frameCounter += clock.restart();
}

void Simulator::displayMap(sf::RenderWindow &window, Map &map) {

	window.clear(sf::Color::White);

	for (int y = 0; y < map.squaresAmount; y++) {
		for (int x = 0; x < map.squaresAmount; x++) {

			map.willBeAlive[x][y] = map.isAlive[x][y];
			map.statusChange(map.isAlive[x][y], x, y);
		}
	}

	window.draw(map.squares);
	window.display();
}

void Simulator::displayTurnCounter(int turn) {

	system("cls");
	std::cout << "-= The Game of Life =-\n\n";
	std::cout << "Amount of turns: " << turn << std::endl;
	std::cout << "Press SPACE to continue simulation.";
}

void Simulator::setOptions(Map &map) {

	float framesPerSecond;
	short color;

	system("cls");
	std::cout << "-= The Game of Life =-\n\n";
	std::cout << "How many steps in one second: ";
	std::cin >> framesPerSecond;
	map.settings.frameRate = sf::seconds(1.f / framesPerSecond);

	do {
		system("cls");
		std::cout << "-= The Game of Life =-\n\n";
		std::cout << "1. Black / White\n";
		std::cout << "2. Green / Black\n";
		std::cout << "\nChoose color theme: ";
		std::cin >> color;
	} while (color > THEMES_AMOUNT && color < 0);
	
	if (color == 1) 
		map.settings.set(sf::Color::Black, sf::Color::White);
	else if (color == 2)
		map.settings.set(sf::Color::Green, sf::Color::Black);
}
