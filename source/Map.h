#ifndef  MAP_H
#define MAP_H

#include "SFML/Graphics.hpp"

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <vector>

class Map {

public:
	void set(int, int, bool);
	void draw(sf::RenderWindow &window);
	void loadMap();
	void save();
	void loadList();
	void showList();
	void loadError();

	bool** isAlive;
	bool** willBeAlive;
	sf::VertexArray squares;

	void statusChange(bool &, int, int);
	void statusChange(sf::Vertex*, sf::Color);

	int squaresAmount;
	int cellSize;
	bool isInfinite;

private:
	std::fstream file;
	std::vector<std::string> list;

};

#endif // !MAP_H
