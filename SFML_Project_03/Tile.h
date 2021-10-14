#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

struct Tile {
	bool revealed;
	bool mine;
	bool flag;
	vector<Tile*> adjacent;
	int number;
	bool center;
	Tile() {
		mine = false;
		flag = false;
		revealed = false;
		number = 0;
		center = false;
	}

};
