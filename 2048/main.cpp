#include  "GameManage.h"

int main() {
	GameManage GM;
	GM.Init();
	while (TRUE) {
		GM.Logic();
		GM.Refresh();
	}
	return 0;
}