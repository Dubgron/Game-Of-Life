#pragma once
#ifndef  MAP_H
#define MAP_H

#include "SFML/Graphics.hpp"

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <vector>

struct MapData {

	void set(int, int, bool);
	void draw(sf::RenderWindow &window);
	void loadMap();
	void save();
	void loadList();
	void showList();
	void loadError();

	std::fstream file;
	std::vector<std::string> list;
	std::string sPath;
	int iPath;

	int squaresAmount;
	int cellSize;
	bool isInfinite;	

	sf::RectangleShape** squares;
	bool** isAlive;
	bool** willBeAlive;
};

#endif // ! MAP_H
