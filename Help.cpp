#include "Help.h"

void Help(int x, int y, int w, int h)
{
	DrawBound();
	Draw_Guide(56, 35, text.goBackText);
	SetColor(0, 15);
	Box(x + 35, y, w, h);
	//Box(x + 35, y, w, h);
	GotoXY(x + 35 + 2, y + 2);
	cout << "HUONG DAN THAO TAC VOI MENU:" << endl;
	GotoXY(x + 35 + 2, y + 3);
	cout << "+su dung phim W hoac S de lua chuc nang." << endl;
	GotoXY(x + 35 + 2, y + 4);
	cout << "+su dung phim enter de chon chuc nang.";
	GotoXY(x + 35 + 2, y + 5);
	cout << "+su dung phim Esc de hien menu.";
	GotoXY(x + 35 + 2, y + 8);
	cout << "HUONG DAN CHOI GAME:" << endl;
	GotoXY(x + 35 + 2, y + 9);
	cout << "+su dung cac phin A, W, S, D de lua vi tri dat quan." << endl;
	GotoXY(x + 35 + 2, y + 10);
	cout << "+su dung phim ENTER de dat quan." << endl;
	GotoXY(x + 35 + 2, y + 11);
	cout << "+ben nao cos duoc 5 quan lien tiep theo cac hang ngang, doc, cheo thi " << endl;
	GotoXY(x + 35 + 2, y + 12);
	cout << " se la nguoi chien thang." << endl;

	while (1) {
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'B') { // 27 là mã của phím ESC
			system("cls");
			return;

		}
	
	}
	system("pause");
}
