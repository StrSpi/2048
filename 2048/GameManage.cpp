#include "GameManage.h"

Grid g;

void GameManage::Init()
{
	g.dataGenerate();
	g.dataGenerate();
	g.dataGenerate();
	g.showGrid();
}

void GameManage::Logic()
{
	int i = 0;
	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);      //��ñ�׼�����豸���  
	INPUT_RECORD keyrec;        //���������¼��ṹ��  
	DWORD res;      //���巵�ؼ�¼  
	while (TRUE) {
		ReadConsoleInput(handle_in, &keyrec, 1, &res);
		if (keyrec.EventType == KEY_EVENT)      //�����ǰ�¼��Ǽ����¼�  
		{
			if (keyrec.Event.KeyEvent.wVirtualKeyCode == VK_UP
				&& keyrec.Event.KeyEvent.bKeyDown == true) {
				g.moveUp();
				break;
			}
			if (keyrec.Event.KeyEvent.wVirtualKeyCode == VK_DOWN
				&& keyrec.Event.KeyEvent.bKeyDown == true) {
				g.moveDown();
				break;
			}
			if (keyrec.Event.KeyEvent.wVirtualKeyCode == VK_LEFT
				&& keyrec.Event.KeyEvent.bKeyDown == true) {
				g.moveLeft();
				break;
			}
			if (keyrec.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT
				&& keyrec.Event.KeyEvent.bKeyDown == true) {
				g.moveRight();
				break;
			}
		}
	}
}

void GameManage::Refresh()
{
	system("cls");
	if (!g.canMove()) {
		GameOver();
		return;
	}
	g.showGrid();
}

void GameManage::GameOver()
{
	printf("Game Over\n");
	printf("Score: %d\n", g.Score());
	printf("Press Enter to replay");
	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);      //��ñ�׼�����豸���  
	INPUT_RECORD keyrec;        //���������¼��ṹ��  
	DWORD res;      //���巵�ؼ�¼  
	while (true) {
		ReadConsoleInput(handle_in, &keyrec, 1, &res);
		if (keyrec.Event.KeyEvent.wVirtualKeyCode == VK_RETURN
			&& keyrec.Event.KeyEvent.bKeyDown == true) {
			g.zero();
			Init();
			break;
		}
		if (keyrec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE
			&& keyrec.Event.KeyEvent.bKeyDown == true)
			exit(0);
	}
}
