#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <time.h>
#include <Windows.h>
using std::vector;


class Grid
{
public:
	Grid();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void showGrid();
	void dataGenerate();
	bool canMove();
	int Score();
	void zero();
	~Grid();
private:
	vector<vector<int>> grid;
	int score = 0;
	bool haveZero();
	void removeZero(int& a, int& b, int& c, int& d);
	void dataTranslation(int& a, int& b, int& c, int& d);
	bool meetStandard(int a, int b, int c, int d);
};

