#include "Help.h"

void Help(int x, int y, int w, int h)
{
	ShowCur(false);
	SetColor(0, 15);
	DrawBound();
	Draw_Guide(65, 35, text.goBackText);
	Box(x , y, w, h);
	
	GotoXY(x+2, y + 2);
	cout << text.menuGuideText << endl;
	GotoXY(x+2, y + 3);
	cout << text.menuInstructions1;
	GotoXY(x+2, y + 4);
	cout << text.menuInstructions2;
	GotoXY(x+2, y + 5);
	cout << text.menuInstructions3;
	GotoXY(x+2, y + 8);
	cout << text.gameGuideText << endl;
	GotoXY(x+2, y + 9);
	cout << text.gameInstructions1;
	GotoXY(x+2, y + 10);
	cout << text.gameInstructions2;
	GotoXY(x+2, y + 11);
	cout << text.gameInstructions3;

	while (1) {
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'B') { // 27 là mã của phím ESC
			system("cls");
			return;
		}
	
	}
	system("pause");
}
