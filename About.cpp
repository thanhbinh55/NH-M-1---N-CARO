#include "About.h"
#include "LanguageText.h"
void About(int x, int y, int w, int h)
{
	ShowCur(false);
	SetColor(0, 15);
	DrawBound();
	Draw_Guide(65, 35, text.goBackText);
	Box(x, y, w, h);

	GotoXY(x + 36, y + 2);
	cout << "Group: 1" << endl;
	GotoXY(x + 25, y + 4);
	cout << "24120269: Ngo Viet Thanh Binh";
	GotoXY(x + 25, y + 6);
	cout << "24120261: Dang Bui The Bao";
	GotoXY(x + 25, y + 8);
	cout << "24120293: Duong Nhut Duy";
	GotoXY(x + 25, y + 10);
	cout << "24120250: Ngo Man Nhi" << endl;
	GotoXY(x + 25, y + 13);
	cout << "Instructor: Truong Toan Thinh";
	GotoXY(x + 10, y + 16);
	cout << "Source code: https://github.com/thanhbinh55/NHOM1-CARO.git";

	while (1) {
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'B') { // 27 là mã của phím ESC
			system("cls");
			return;
		}

	}
	system("pause");
}
