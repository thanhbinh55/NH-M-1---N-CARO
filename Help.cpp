#include "Help.h"

void Help(int x, int y, int w, int h)
{
	ShowCur(false);
	vechuHELP(53, 2);
	SetColor(0, 15);
	DrawBound();
	Draw_Guide(65, 35, text.goBackText);
	Box(x, y, w, h);



	GotoXY(x + 2, y + 2);
	cout << text.menuGuideText << endl;
	GotoXY(x + 2, y + 3);
	cout << text.menuInstructions1;
	GotoXY(x + 2, y + 4);
	cout << text.menuInstructions2;
	GotoXY(x + 2, y + 5);
	cout << text.menuInstructions3;
	GotoXY(x + 2, y + 6);
	cout << text.menuInstructions4;
	GotoXY(x + 2, y + 8);
	cout << text.menuInstructions5;
	GotoXY(x + 2, y + 9);
	cout << text.menuInstructions6;
	GotoXY(x + 2, y + 10);
	cout << text.menuInstructions7;
	GotoXY(x + 2, y + 11);
	cout << text.menuInstructions8;
	GotoXY(x + 2, y + 12);
	cout << text.menuInstructions9;
	GotoXY(x + 2, y + 14);
	cout << text.gameGuideText << endl;
	GotoXY(x + 2, y + 15);
	cout << text.gameInstructions1;
	GotoXY(x + 2, y + 16);
	cout << text.gameInstructions2;
	GotoXY(x + 2, y + 17);
	cout << text.gameInstructions3;
	GotoXY(x + 2, y + 18);
	cout << text.gameInstructions4;

	while (1) {
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'B') { // 27 là mã của phím ESC
			system("cls");
			return;
		}

	}
	system("pause");
}