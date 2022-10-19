#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Board {
	int width;
	int height;
	int tiles;
	int mines;
public:
	
	Board() {
		width = 0;
		height = 0;
		tiles = 0;
		mines = 0;
	}
	void SetWidth(int collumns) {
		width = collumns * 32;
	}
	void SetHeight(int rows) {
		height = rows * 32 + 88;
	}
	void SetTiles(int collumns, int rows) {
		tiles = collumns * rows;
	}
	void SetMines(int _mines) {
		mines = _mines;
	}
	int GetWidth() const {
		return width;
	}
	int GetHeight() const {
		return height;
	}
	int GetTiles() const {
		return tiles;
	}
	int GetMines() const {
		return mines;
	}
};
