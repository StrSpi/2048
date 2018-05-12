#pragma once
#include "Grid.h"
#include <stdexcept>
#include <windows.h>  

class GameManage
{
public:
	void Init();
	void Logic();
	void Refresh();
	void GameOver();
};