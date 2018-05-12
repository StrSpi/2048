#include "Grid.h"

const int SZ = 4;

Grid::Grid() :grid(SZ, vector<int>(SZ, 0))
{
	score = 0;
}

//移动控制,首先判断是否可动，不可动直接返回，可动则动，动后判断是否gameover
void Grid::moveLeft()
{
	int i;
	for (i = 0; i != SZ; ++i) 
		if (meetStandard(grid[i][0], grid[i][1], grid[i][2], grid[i][3]))
			break;
	if (i == SZ)
		return;
	for (i = 0; i != SZ; ++i)
		removeZero(grid[i][0], grid[i][1], grid[i][2], grid[i][3]);
	for (i = 0; i != SZ; ++i)
		dataTranslation(grid[i][0], grid[i][1], grid[i][2], grid[i][3]);
	for (i = 0; i != SZ; ++i)
		removeZero(grid[i][0], grid[i][1], grid[i][2], grid[i][3]);
	dataGenerate();
}

void Grid::moveRight()
{
	int i;
	for (i = 0; i != SZ; ++i)
		if (meetStandard(grid[i][3], grid[i][2], grid[i][1], grid[i][0]))
			break;
	if (i == SZ)
		return;
	for (i = 0; i != SZ; ++i)
		removeZero(grid[i][3], grid[i][2], grid[i][1], grid[i][0]);
	for (i = 0; i != SZ; ++i)
		dataTranslation(grid[i][3], grid[i][2], grid[i][1], grid[i][0]);
	for (i = 0; i != SZ; ++i)
		removeZero(grid[i][3], grid[i][2], grid[i][1], grid[i][0]);
	dataGenerate();
}

void Grid::moveUp()
{
	int i;
	for (i = 0; i != SZ; ++i)
		if (meetStandard(grid[0][i], grid[1][i], grid[2][i], grid[3][i]))
			break;
	if (i == SZ)
		return;
	for (i = 0; i != SZ; ++i)
		removeZero(grid[0][i], grid[1][i], grid[2][i], grid[3][i]);
	for (i = 0; i != SZ; ++i)
		dataTranslation(grid[0][i], grid[1][i], grid[2][i], grid[3][i]);
	for (i = 0; i != SZ; ++i)
		removeZero(grid[0][i], grid[1][i], grid[2][i], grid[3][i]);
	dataGenerate();
}

void Grid::moveDown()
{
	int i;
	for (i = 0; i != SZ; ++i)
		if (meetStandard(grid[3][i], grid[2][i], grid[1][i], grid[0][i]))
			break;
	if (i == SZ)
		return;
	for (i = 0; i != SZ; ++i)
		removeZero(grid[3][i], grid[2][i], grid[1][i], grid[0][i]);
	for (i = 0; i != SZ; ++i)
		dataTranslation(grid[3][i], grid[2][i], grid[1][i], grid[0][i]);
	for (i = 0; i != SZ; ++i)
		removeZero(grid[3][i], grid[2][i], grid[1][i], grid[0][i]);
	dataGenerate();
}

//显示控制
void Grid::showGrid()
{
	printf("          2048\n");
	printf("    score:   ");
	printf("%7d\n", score);
	for (int i = 0; i != SZ; ++i) {
		for (int j = 0; j != SZ; ++j) {
			printf("%5d", grid[i][j]);
		}
		printf("\n\n");
	}
}

//是否gameover
bool Grid::canMove()
{
	if (haveZero())
		return true;
	for (int i = 0; i != SZ-1; ++i)
		for (int j = 0; j != SZ - 1; ++j)
			if (grid[i][j] == grid[i + 1][j] || grid[i][j] == grid[i][j + 1])
				return true;
	for (int i = 0; i != SZ - 1; ++i) {
		if (grid[SZ - 1][i] == grid[SZ - 1][i + 1])
			return true;
		if (grid[i][SZ - 1] == grid[i + 1][SZ - 1])
			return true;
	}
	return false;
}

int Grid::Score()
{
	return score;
}

void Grid::zero()
{
	for (int i = 0; i != SZ; ++i)
		for (int j = 0; j != SZ; ++j)
			grid[i][j] = 0;
	score = 0;
}

//是否存在0
bool Grid::haveZero()
{
	for (int i = 0; i != SZ; ++i)
		for (int j = 0; j != SZ; ++j)
			if (grid[i][j] == 0)
				return true;
	return false;
}

//消除位移方向开头的0
void Grid::removeZero(int& a, int& b, int& c, int& d) {
	int vec[SZ] = { a,b,c,d };
	for (int i = 0; i != SZ - 1; ++i) {
		if (vec[i] == 0) {
			for (int j = i + 1; j != SZ; ++j) {
				if (vec[j] != 0) {
					vec[i] = vec[j];
					vec[j] = 0;
					break;
				}
			}
		}
	}
	a = vec[0]; b = vec[1]; c = vec[2]; d = vec[3];
}

//数据平移，累加，加分
void Grid::dataTranslation(int& a, int& b, int& c, int& d) {
	int vec[4] = { a,b,c,d };
	for (int i = 0; i != SZ - 1; ++i) {
		if (vec[i] == vec[i + 1]) {
			vec[i] += vec[i + 1];
			vec[i + 1] = 0;
			score += vec[i];
		}
	}
	a = vec[0]; b = vec[1]; c = vec[2]; d = vec[3];
}

//生成随机数
void Grid::dataGenerate()
{
	static std::default_random_engine e(time(0));
	static std::uniform_int_distribution<int> u1(0, 15);
	static std::uniform_int_distribution<int> u2(1, 2);
	int n = 0;
	while (++n) {
		if (n > 20) {
			for (int x = 0; x != 16; ++x) {
				if (grid[x / SZ][x % SZ] == 0) {
					grid[x / SZ][x % SZ] = u2(e) * 2;;
					break;
				}
			}
			break;
		}
		int i = u1(e);
		if (grid[i / SZ][i % SZ] == 0) {
			grid[i / SZ][i % SZ] = u2(e) * 2;
			break;
		}
	}
}

//是否符合可以移动的标准
bool Grid::meetStandard(int a, int b, int c, int d)
{
	int vec[SZ] = { a,b,c,d };
	for (int i = 0; i != SZ - 1; ++i) {
		if (vec[i] == 0 && vec[i + 1] != 0)
			return true;
		if (vec[i] != 0 && vec[i] == vec[i + 1])
			return true;
	}
	return false;
}

Grid::~Grid()
{
}