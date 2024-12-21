#include "Game.h"
#include "Menu.h"
#include "Help.h"
#include "About.h"
#include "Setting.h"
#include "SaveLoad.h"
#include "LanguageText.h"
#include "Draw.h"
#include "Bot.h"
#include "Timer.h"
#include <atomic>
#include <stack>
_POINT _A[BOARD_SIZE][BOARD_SIZE];
bool _TURN;
int _COMMAND;
int _X, _Y;
Player Player_1, Player_2;
Language currentLanguage;
int positions[5][2];
atomic<bool> keep;

// Cấu trúc lưu nước đi
struct Move {
	int x, y;    // Tọa độ
	int player;  // Người chơi (-1: Player 1, 1: Player 2)
};
stack<Move> moveHistoryP; // Stack lưu lịch sử nước đi
//// Hàm nhóm View
void ShowCur(bool CursorVisibility) {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = CursorVisibility; // Ẩn hoặc hiện con trỏ
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void SetTextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}//--> rieng cho menu

void SetColor(int textColor, int bgColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor + bgColor * 16);
}

void TextHighlight(int x, int y, int w, int h, int b_color_sang, string nd) {
	SetTextColor(b_color_sang); // Màu đậm hơn cho mục được chọn
	for (int iy = y + 1; iy <= y + h - 1; iy++) {
		for (int ix = x + 1; ix <= x + w - 1; ix++) {
			GotoXY(ix, iy);
			cout << " "; // Tô đầy
		}
	}
	GotoXY(x + (w - nd.length()) / 2, y + h / 2); // Căn giữa nội dung
	cout << nd;
}
void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Box(int x, int y, int w, int h) {
	if (h <= 1 || w <= 1) return;
	for (int ix = x; ix <= x + w; ix++) {
		GotoXY(ix, y);
		cout << char(205);
		GotoXY(ix, y + h);
		cout << char(205);
	}
	for (int iy = y; iy <= y + h; iy++) {
		GotoXY(x, iy);
		cout << char(186);
		GotoXY(x + w, iy);
		cout << char(186);
	}
	GotoXY(x, y);
	cout << char(201);
	GotoXY(x + w, y);
	cout << char(187);
	GotoXY(x, h + y);
	cout << char(200);
	GotoXY(x + w, y + h);
	cout << char(188);
}

void Box_Menu(int x, int y, int w, int h, string nd) {

	GotoXY(x + (w - nd.length()) / 2, y + h / 2); // Căn giữa nội dung
	cout << nd;

	if (h <= 1 || w <= 1) return;

	for (int ix = x; ix <= x + w; ix++) {
		GotoXY(ix, y);
		cout << char(205);
		GotoXY(ix, y + h);
		cout << char(205);
	}
	for (int iy = y; iy <= y + h; iy++) {
		GotoXY(x, iy);
		cout << char(186);
		GotoXY(x + w, iy);
		cout << char(186);
	}
	//for (int ix = x+1; ix < x + w; ix++) {
	//	for (int iy = y+1; iy < y + h; iy++) {
	//		SetColor(0, 15);
	//		cout << " ";
	//	}
	//}
	
	GotoXY(x, y); cout << char(201);
	GotoXY(x + w, y); cout << char(187);
	GotoXY(x, y + h); cout << char(200);
	GotoXY(x + w, y + h); cout << char(188);
}

//// Hàm nhóm Model (Xử lý dữ liệu)
void ResetGame()
 {
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_A[i][j].x = 4 * j + LEFT + 2; //Trùng với hoành độ màn hình bàn cờ
			_A[i][j].y = 2 * i + TOP + 1; //Trùng với tung độ màn hình bàn cờ
			_A[i][j].c = 0; //0: chưa đánh dấu, -1: true đánh, 1: fasle đánh
		}
	}
	_TURN = true; _COMMAND = -1; //Gán lượt và phím mặt định
	_X = _A[0][0].x; _Y = _A[0][0].y; //Thiết lập lại tọa đồ hiện hành ban đầu
}
//Doi luot danh dau tien, vi du X thang thi van tiep theo doi cho O danh dau tien
void ResetGameInOneGame()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_A[i][j].x = 4 * j + LEFT + 2; //Trùng với hoành độ màn hình bàn cờ
			_A[i][j].y = 2 * i + TOP + 1; //Trùng với tung độ màn hình bàn cờ
			_A[i][j].c = 0; //0: chưa đánh dấu, -1: true đánh, 1: fasle đánh
		}
	}
	_TURN = !_TURN;
	 _COMMAND = -1; //Gán lượt và phím mặt định
	_X = _A[0][0].x; _Y = _A[0][0].y; //Thiết lập lại tọa đồ hiện hành ban đầu
}

void ResetData() {
	ResetGame();
//	Player_1.Name = "";
	Player_1.Moves = 0;
	Player_1.Wins = 0;
//	Player_2.Name = "";
	Player_2.Moves = 0;
	Player_2.Wins = 0;
}
void ExitGame() {
	system("cls");
}
//hàm đánh dấu vào ma trận bàn cờ khi người chơi nhấn phím ‘enter
//--> kiểm tra vị trí đánh _X, _y là của 1 hay 0
int CheckBoard(int pX, int pY) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0) {
				if (_TURN == true) _A[i][j].c = -1; // Nếu lượt hiện hành là true thì c = -1
				else _A[i][j].c = 1; // Nếu lượt hiện hành là false thì c = 1
				return _A[i][j].c;
			}
		}
	}
	return 0;
}

int TestBoard() {
	// Kiểm tra điều kiện hòa
	if (isDraw()) {
		return 0;  // Hòa
	}

	// Kiểm tra điều kiện thắng
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].c != 0 && checkWin(i, j)) {
				if (_TURN == true) {
					Player_1.Wins++;
					return -1;
				}
				else {
					Player_2.Wins++;
					return 1;
				}
				//return (_TURN == true ? -1 : 1);  // -1 là lượt người chơi 1 thắng, 1 là người chơi 2 thắng
			}
		}
	}
	return 2;  // 2 nghĩa là chưa ai thắng, trò chơi tiếp tục
}
bool checkWin(int x, int y) {
	int player = _A[x][y].c;  // Giá trị người chơi ở ô (x, y)
	if (player == 0) return false; // Không có người chơi ở vị trí này

	int count = 0; // Biến đếm số quân cờ liên tiếp


	// Kiểm tra hàng ngang (trái - phải)
	count = 1;
	positions[0][0] = x; positions[0][1] = y; // Lưu vị trí quân cờ hiện tại
	for (int j = y - 1; j >= 0 && _A[x][j].c == player; j--) {
		positions[count][0] = x; positions[count][1] = j; // Lưu vị trí
		count++;
	}
	for (int j = y + 1; j < BOARD_SIZE && _A[x][j].c == player; j++) {
		positions[count][0] = x; positions[count][1] = j; // Lưu vị trí
		count++;
	}
	if (count >= 5) {
		// Xử lý lưu trữ hoặc hiển thị các vị trí
		return true;
	}

	// Kiểm tra hàng dọc (trên - dưới)
	count = 1;
	positions[0][0] = x; positions[0][1] = y; // Lưu vị trí quân cờ hiện tại
	for (int i = x - 1; i >= 0 && _A[i][y].c == player; i--) {
		positions[count][0] = i; positions[count][1] = y; // Lưu vị trí
		count++;
	}
	for (int i = x + 1; i < BOARD_SIZE && _A[i][y].c == player; i++) {
		positions[count][0] = i; positions[count][1] = y; // Lưu vị trí
		count++;
	}
	if (count >= 5) {
		// Xử lý lưu trữ hoặc hiển thị các vị trí
		return true;
	}

	// Kiểm tra đường chéo chính (\)
	count = 1;
	positions[0][0] = x; positions[0][1] = y; // Lưu vị trí quân cờ hiện tại
	for (int k = 1; x - k >= 0 && y - k >= 0 && _A[x - k][y - k].c == player; k++) {
		positions[count][0] = x - k; positions[count][1] = y - k; // Lưu vị trí
		count++;
	}
	for (int k = 1; x + k < BOARD_SIZE && y + k < BOARD_SIZE && _A[x + k][y + k].c == player; k++) {
		positions[count][0] = x + k; positions[count][1] = y + k; // Lưu vị trí
		count++;
	}
	if (count >= 5) {
		// Xử lý lưu trữ hoặc hiển thị các vị trí
		return true;
	}

	// Kiểm tra đường chéo phụ (/)
	count = 1;
	positions[0][0] = x; positions[0][1] = y; // Lưu vị trí quân cờ hiện tại
	for (int k = 1; x - k >= 0 && y + k < BOARD_SIZE && _A[x - k][y + k].c == player; k++) {
		positions[count][0] = x - k; positions[count][1] = y + k; // Lưu vị trí
		count++;
	}
	for (int k = 1; x + k < BOARD_SIZE && y - k >= 0 && _A[x + k][y - k].c == player; k++) {
		positions[count][0] = x + k; positions[count][1] = y - k; // Lưu vị trí
		count++;
	}
	if (count >= 5) {
		// Xử lý lưu trữ hoặc hiển thị các vị trí
		return true;
	}

	return false; // Không có ai thắng
}

bool isDraw() {
	// Kiểm tra nếu tất cả các ô trên bàn cờ đều đã được điền
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].c == 0)  // Ô trống
				return false; //--> chua full
		}
	}
	return true;  // Hòa khi tất cả các ô đều đầy
}

void InputPvP(int x, int y, int w, int h) {
	Box(x, y, w, h+3);
	system("Color F0");
	Draw_Guide(50, 35, text.inputText + ", " + text.selectText);
	DrawBound();
	DrawLogoCaro(45, 5);

	SetColor(4, 15);
	GotoXY(x + 1, y + 1);
	cout << text.nameText1 << endl;
	char c;
	Player_1.Name = "";
	GotoXY(x + 1, y + 2);
	// Nhập tên cho Player 1
	SetColor(4, 14);
	while (true) {
		c = _getch();

		// Nếu nhấn Enter
		if (c == 13) { // 13 là mã ASCII của Enter
			playSelectSound();
			break;
		}
		// Nếu nhấn Backspace
		else if (c == 8 && !Player_1.Name.empty()) { // 8 là mã ASCII của Backspace
			Player_1.Name.pop_back();
			GotoXY(x + 1, y + 2);
			cout << Player_1.Name << " "; // In lại chuỗi và xóa ký tự dư thừa
			GotoXY(x + 1 , y + 2);
		}
		// Nếu nhập ký tự hợp lệ
		else if ((isalpha(c) || c == ' ') && Player_1.Name.length() < 10) {
			c = toupper(c); // Chuyển sang chữ hoa
			Player_1.Name += c;
			cout << c;
		}
	}

	Player_2.Name = "";
	while (true) {
		GotoXY(x + 1, y + 5);
		SetColor(1, 15);
		cout << text.nameText2 << endl;
		GotoXY(x + 1, y + 6);
		SetColor(1, 14);
		while (true) {
			c = _getch();
			if (c == 13) {
				playSelectSound();
				break; // Press Enter to finish entering the name
			}
			if (c == 8 && !Player_2.Name.empty()) { // Check for empty string with Backspace
				Player_2.Name.pop_back();
				GotoXY(x + 1, y + 6);
				cout << Player_2.Name << " ";
				GotoXY(x + 1, y + 6);
			}
			else if ((isalpha(c) || c == ' ') && Player_2.Name.length() <= 10) { // Only accept letters or spaces and limit to 10 characters
				c = toupper(c);
				cout << c;
				Player_2.Name += c;
			}
		}

		// Check if Player 2's name is the same as Player 1's name
		if (Player_2.Name == Player_1.Name) {
			GotoXY(x + 1, y + 7); // Display error message
			SetColor(12, 15); // Red text color for error
			//cout << "Error: Name must be different from Player 1, again!";
			cout << text.ErrorGetName;
			// Clear the previous duplicate name
			Player_2.Name = ""; // Reset Player 2's name
			GotoXY(x + 1, y + 6);
			cout << "          "; // Overwrite old name with spaces
			GotoXY(x + 1, y + 6); // Move cursor back to the starting position for Player 2's name
		}
		else {
			break; // Exit loop if names are different
		}
	}
	SetColor(15, 0);
	ChooseAvatar();
}
void InputPvC(int x, int y, int w, int h) {
	Box(x, y, w, h);
	system("Color F0");
	Draw_Guide(50, 35, text.inputText + ", " + text.selectText);
	DrawBound();
	DrawLogoCaro(45, 5);

	SetColor(4, 15);
	GotoXY(x + 1, y + 1);
	cout << text.nameText1;
	char c;
	Player_1.Name = "";
	GotoXY(x + 1, y + 2);
	// Nhập tên cho Player 1
	SetColor(4, 14);
	while (true) {
		c = _getch();

		// Nếu nhấn Enter
		if (c == 13) { // 13 là mã ASCII của Enter
			playSelectSound();
			break;
		}
		// Nếu nhấn Backspace
		else if (c == 8 && !Player_1.Name.empty()) { // 8 là mã ASCII của Backspace
			Player_1.Name.pop_back();
			GotoXY(x + 1, y + 2);
			cout << Player_1.Name << " "; // In lại chuỗi và xóa ký tự dư thừa
			GotoXY(x + 1, y + 2);
		}
		// Nếu nhập ký tự hợp lệ
		else if ((isalpha(c) || c == ' ') && Player_1.Name.length() < 10) {
			c = toupper(c); // Chuyển sang chữ hoa
			Player_1.Name += c;
			cout << c;
		}
	}
	Player_2.Name = "Bot"; // Đặt tên cho Player 2 là Bot

	// In tên cho Player 2
	GotoXY(x + 1, y + 5);
	SetColor(1, 15);
	cout << "Player 2 (O): " << Player_2.Name << " (Bot)";
	SetColor(15, 0);
	ChooseAvatar();
}

void GamePlayTimerPvP() {
	 // Bắt đầu đếm thời gian: 5 phút ván đấu, 30 giây mỗi lượt

	StartTimer(MAXTIMEGAME, MAXTIMETURN); // tai lai van dau voi thoi gian tai len tu file 
	bool validEnter = true;

	while (true) {

		if (isTurnSkipped) {
			{
				timerMutex.lock();
				_TURN = !_TURN; // Chuyển lượt
				isTurnSkipped = false; // Reset trạng thái
				timerMutex.unlock();
			}
			HighlightPlayer(70, 6, 28, 12);
		}
		// Kiểm tra hết thời gian game
		if (gameTimer <= 0) {
			GotoXY(75 + 10, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2);		
			screenMutex.lock();
			std::cout << "Game over: Total time expired!";
			screenMutex.unlock();
			StopTimer();
	
				switch (ProcessFinish(0)) {
				case -1:  // Người chơi thắng
				case 1:   // Hòa
				case 0:   // Tiếp tục
					if (AskContinue() != 'Y') {
						if (AskSaveGame() == 'Y') {
							SaveGame();
							MainMenu();
							return;
						}
						else {
							system("cls");
							MainMenu();
						}
					}
					else {
						StartTimer(MAXTIMEGAME, MAXTIMETURN);
						StartGameInOneGame();    // Bắt đầu trò chơi mới trong 1 game dang choi
						break;
					}
				}
		}
		_COMMAND = toupper(_getch());

		if (_COMMAND == 27) {  // Phím ESC để mở menu phụ
			playSelectSound();
			StopTimer();
			SubMenu();
			StartTimer(gameTimer, turnTimer);
			system("cls");
			SetColor(0, 15);
			DrawLoaded(_A);
			continue;
		}
		else if (_COMMAND == 'A') {
			screenMutex.lock();
			playMoveSound();
			MoveLeft();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'W') {
			screenMutex.lock();
			playMoveSound();
			MoveUp();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'S') {
			screenMutex.lock();
			playMoveSound();
			MoveDown();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'D') {
			screenMutex.lock();
			playMoveSound();
			MoveRight();
			screenMutex.unlock();
		}
		else if (_COMMAND == 13) {  // Phím Enter để đánh dấu nước đi
			playSelectSound();
			
			switch (CheckBoard(_X, _Y)) {
			case -1:  // Người chơi 1 đánh
			{
				turnTimer = MAXTIMETURN;
				screenMutex.lock();
				SetColor(4, 15);
				printf("X");
				Player_1.Moves++;
				Draw_infor(70, 6, 28, 12);
				screenMutex.unlock();
				break;
			}
			
			case 1:   // Người chơi 2 đánh
			{
				turnTimer = MAXTIMETURN;
				screenMutex.lock();				
				SetColor(1, 15);
				printf("O");
				Player_2.Moves++;
				Draw_infor(70, 6, 28, 12);
				screenMutex.unlock();
				break;
			}
				
			case 0:   // Ô đã được đánh dấu
				validEnter = false;
				break;
			}

			// Kiểm tra kết quả ván đấu nếu lượt hợp lệ
			if (validEnter) {
				
					if (validEnter) {
						switch (ProcessFinish(TestBoard())) {
						case -1:  // Người chơi thắng
						case 1:   // Hòa
						case 0:   // Tiếp tục
							if (AskContinue() != 'Y') {
								if (AskSaveGame() == 'Y') {
									SaveGame();
									MainMenu();
									return;
								}
								else {
									system("cls");
									MainMenu();
								}
							}
							else {
								StartTimer(MAXTIMEGAME, MAXTIMETURN);
								StartGameInOneGame();    // Bắt đầu trò chơi mới trong 1 game dang choi
								break;
							}
						}
					}
				
			}
			validEnter = true;  // Reset trạng thái cho lượt tiếp theo
			/*turnTimer = 5; */    // Reset thời gian lượt tiếp theo
		}
		else if (_COMMAND == 'L') {  // Lưu trò chơi và quay lại Menu chính
			StopTimer();
			if (AskSaveGame() == 'Y') {
				SaveGame();
				MainMenu();
				return;
			}
			else {
				system("cls");
				DrawLoaded(_A);
				SubMenu();
				StartTimer(gameTimer, turnTimer);
				DrawLoaded(_A);
			}
		}
	}
}
void GamePlayTimerLoadPvP() {
	// Bắt đầu đếm thời gian: 5 phút ván đấu, 30 giây mỗi lượt

	StartTimer(gameTimer, turnTimer); // tai lai van dau voi thoi gian tai len tu file 
	bool validEnter = true;

	while (true) {

		if (isTurnSkipped) {
			{
				//std::lock_guard<std::mutex> lock(timerMutex); // Đảm bảo đồng bộ
				timerMutex.lock();
				_TURN = !_TURN; // Chuyển lượt
				isTurnSkipped = false; // Reset trạng thái
				timerMutex.unlock();
			}

			HighlightPlayer(70, 6, 28, 12);
		}

		// Kiểm tra hết thời gian game
		if (gameTimer <= 0) {
			GotoXY(75 + 10, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2);
			//std::lock_guard<std::mutex> lock(screenMutex);
			screenMutex.lock();
			std::cout << "Game over: Total time expired!";
			screenMutex.unlock();
			StopTimer();
			//system("cls");

			switch (ProcessFinish(0)) {
			case -1:  // Người chơi thắng
			case 1:   // Hòa
			case 0:   // Tiếp tục
				if (AskContinue() != 'Y') {
					if (AskSaveGame() == 'Y') {
						SaveGame();
						MainMenu();
						return;
					}
					else {
						system("cls");
						MainMenu();
					}
				}
				else {
					StartTimer(MAXTIMEGAME, MAXTIMETURN);
					StartGameInOneGame();    // Bắt đầu trò chơi mới trong 1 game dang choi
					break;
				}
			}
			
		}
		_COMMAND = toupper(_getch());

		if (_COMMAND == 27) {  // Phím ESC để mở menu phụ
			playSelectSound();
			StopTimer();
			SubMenu();
			StartTimer(gameTimer, turnTimer);
			system("cls");
			SetColor(0, 15);
			DrawLoaded(_A);
			continue;
		}
		else if (_COMMAND == 'A') {
			screenMutex.lock();
			playMoveSound();
			MoveLeft();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'W') {
			screenMutex.lock();
			playMoveSound();
			MoveUp();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'S') {
			screenMutex.lock();
			playMoveSound();
			MoveDown();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'D') {
			screenMutex.lock();
			playMoveSound();
			MoveRight();
			screenMutex.unlock();
		}
		else if (_COMMAND == 13) {  // Phím Enter để đánh dấu nước đi
			playSelectSound();

			switch (CheckBoard(_X, _Y)) {
			case -1:  // Người chơi 1 đánh
			{
				turnTimer = 5;
				screenMutex.lock();
				SetColor(4, 15);
				printf("X");
				Player_1.Moves++;
				Draw_infor(70, 6, 28, 12);
				screenMutex.unlock();
				break;
			}

			case 1:   // Người chơi 2 đánh
			{
				turnTimer = 5;
				screenMutex.lock();
				SetColor(1, 15);
				printf("O");
				Player_2.Moves++;
				Draw_infor(70, 6, 28, 12);
				screenMutex.unlock();
				break;
			}

			case 0:   // Ô đã được đánh dấu
				validEnter = false;
				break;
			}

			// Kiểm tra kết quả ván đấu nếu lượt hợp lệ
			if (validEnter) {

				if (validEnter) {
					switch (ProcessFinish(TestBoard())) {
					case -1:  // Người chơi thắng
					case 1:   // Hòa
					case 0:   // Tiếp tục
						if (AskContinue() != 'Y') {
							if (AskSaveGame() == 'Y') {
								SaveGame();
								MainMenu();
								return;
							}
							else {
								system("cls");
								MainMenu();
							}
						}
						else {
							StartTimer(MAXTIMEGAME, MAXTIMETURN);
							StartGameInOneGame();    // Bắt đầu trò chơi mới trong 1 game dang choi
							break;
						}
					}
				}

			}
			validEnter = true;  // Reset trạng thái cho lượt tiếp theo
			/*turnTimer = 5; */    // Reset thời gian lượt tiếp theo
		}
		else if (_COMMAND == 'L') {  // Lưu trò chơi và quay lại Menu chính
			StopTimer();
			if (AskSaveGame() == 'Y') {
				SaveGame();
				MainMenu();
				return;
			}
			else {
				system("cls");
				DrawLoaded(_A);
				SubMenu();
				StartTimer(gameTimer, turnTimer);
				DrawLoaded(_A);
			}
		}
	}
}

void GamePlayPvP() {
	bool validEnter = true;

	while (true) {
		_COMMAND = toupper(_getch());

		if (_COMMAND == 27) {  // Phím ESC để mở menu phụ
			playSelectSound();
			SubMenu();           // Gọi menu phụ
			system("cls");       // Xóa màn hình
			SetColor(0, 15);
			DrawLoaded(_A);      // Vẽ lại bàn cờ khi quay lại
			continue;            // Tiếp tục vòng lặp
		}
		else if (_COMMAND == 'A') {
			screenMutex.lock();
			playMoveSound();
			MoveLeft();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'W') {
			screenMutex.lock();
			playMoveSound();
			MoveUp();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'S') {
			screenMutex.lock();
			playMoveSound();
			MoveDown();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'D') {
			screenMutex.lock();
			playMoveSound();
			MoveRight();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'Z') {  // Phím Z để hủy nước đi trước đó
			if (!moveHistoryP.empty()) {
				Move lastMove = moveHistoryP.top(); // Lấy nước đi cuối cùng
				moveHistoryP.pop();  // Xóa khỏi lịch sử
				GotoXY(lastMove.x, lastMove.y);
				for (int i = 0; i < BOARD_SIZE; i++) {
					for (int j = 0; j < BOARD_SIZE; j++) {
						if (_A[i][j].x == lastMove.x && _A[i][j].y == lastMove.y) {
							_A[i][j].c = 0;
						}
					}
				}
				_TURN = !_TURN;
				printf(" ");  // Xóa ký tự trên màn hình
				// Giảm lượt đi của người chơi tương ứng
				if (lastMove.player == -1) {
					Player_1.Moves--;
				}
				else if (lastMove.player == 1) {
					Player_2.Moves--;
				}
				Draw_infor1(70, 6, 28, 12); // Cập nhật thông tin trên giao diện
				GotoXY(lastMove.x, lastMove.y);
			}
		}
		else if (_COMMAND == 13) {  // Phím Enter để đánh dấu nước đi
			playSelectSound();        
			// Kiểm tra ô có hợp lệ hay không
			switch (CheckBoard(_X, _Y)) {
			case -1:  // Người chơi 1 đánh
				SetColor(4, 15);
				printf("X");
				Player_1.Moves++;
				Draw_infor(70, 6, 28, 12);
				moveHistoryP.push({ _X, _Y, -1 });  // Lưu nước đi vào lịch sử
				break;
			case 1:   // Người chơi 2 đánh
				SetColor(1, 15);
				printf("O");
				Player_2.Moves++;
				Draw_infor(70, 6, 28, 12);
				moveHistoryP.push({ _X, _Y, 1 });  // Lưu nước đi vào lịch sử
				break;
			case 0:   // Ô đã được đánh dấu
				validEnter = false;
				break;
			}
			// Nếu ô hợp lệ, kiểm tra kết quả game
			if (validEnter) {
				switch (ProcessFinish(TestBoard())) {
				case -1:
				// Người chơi 1 thắng
				case 1: 
				 // Người chơi 2 thắng
				case 0:   // Hòa
					if (AskContinue() != 'Y') {
						if (AskSaveGame() == 'Y') {
							SaveGame();
							MainMenu();
							return;
						}
						else {
							system("cls");
							MainMenu();							
						}
					}
					else {
						StartGameInOneGame();    // Bắt đầu trò chơi mới
						break;
					}
				}
			}
			validEnter = true;  // Mở khóa cho lượt tiếp theo
		}
		else if (_COMMAND == 'L') {  // Lưu trò chơi và quay lại Menu chính
			if (AskSaveGame() == 'Y') {
				SaveGame();
				MainMenu();
				return;
			}
			else {
				system("cls");
				DrawLoaded(_A);
				SubMenu();
				DrawLoaded(_A);
			}
		}
	}
}
void EasyGamePlayPvC() {
	//int count = -1;
	bool validEnter = true;

	while (true) {
		_COMMAND = toupper(_getch());

		if (_COMMAND == 27) {  // ESC để mở menu phụ
			playSelectSound();
			SubMenu();
			system("cls");
			SetColor(0, 15);
			DrawLoaded(_A);
			continue;
		}
		else if (_COMMAND == 'A') {
			screenMutex.lock();
			playMoveSound();
			MoveLeft();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'W') {
			screenMutex.lock();
			playMoveSound();
			MoveUp();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'S') {
			screenMutex.lock();
			playMoveSound();
			MoveDown();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'D') {
			screenMutex.lock();
			playMoveSound();
			MoveRight();
			screenMutex.unlock();
		}
		else if (_COMMAND == 13) {  // Phím Enter
			playSelectSound();
			switch (CheckBoard(_X, _Y)) {
			case -1:
				SetColor(4, 15);
				printf("X");
				Player_1.Moves++;
				Draw_infor(70, 6, 28, 12);
				moveHistoryP.push({ _X,_Y,-1 });
				break;
			case 0:
				validEnter = false;
				break;
			}

			if (validEnter) {
				switch (ProcessFinish(TestBoard())) {
				case -1:  // Người chơi thắng
				case 1:   // Hòa
				case 0:   // Tiếp tục
					if (AskContinue() != 'Y') {
						if (AskSaveGame() == 'Y') {
							SaveGame();
							MainMenu();
							return;
						}
						else {
							system("cls");
							MainMenu();
						}
					}
					else {
						StartGameInOneGame();    // Bắt đầu trò chơi mới
						break;
					}
				}

				// Lượt của máy
				int pX, pY;
				MediumBot(_X, _Y, pX, pY);
				SetColor(1, 15);
				GotoXY(_A[pX][pY].x, _A[pX][pY].y);
				printf("O");
				Player_2.Moves++;
				Draw_infor(70, 6, 28, 12);
				moveHistoryP.push({ _A[pX][pY].x, _A[pX][pY].y, 1 });
				Sleep(300);

				switch (ProcessFinish(TestBoard())) {
				case -1:
				case 1:
				case 0:
					if (AskContinue() != 'Y') {
						if (AskSaveGame() == 'Y') {
							SaveGame();
							MainMenu();
							return;
						}
						else {
							system("cls");
							MainMenu();
						}
					}
					else {
						StartGameInOneGame();    // Bắt đầu trò chơi mới
						break;
					}
				}
			}
			validEnter = true;
		}
		else if (_COMMAND == 'Z') {  // Phím Z để hủy 2 nước đi trước đó
			if (moveHistoryP.size() >= 2) {  // Kiểm tra xem có đủ 2 nước đi để hủy không
				for (int i = 0; i < 2; ++i) {
					Move lastMove = moveHistoryP.top(); // Lấy nước đi cuối cùng
					moveHistoryP.pop();  // Xóa khỏi lịch sử
					for (int i = 0; i < BOARD_SIZE; i++) {
						for (int j = 0; j < BOARD_SIZE; j++) {
							if (_A[i][j].x == lastMove.x && _A[i][j].y == lastMove.y) {
								_A[i][j].c = 0;  // Xóa ký tự trong bảng
							}
						}
					}
					GotoXY(lastMove.x, lastMove.y);
					printf(" ");  // Xóa ký tự trên màn hình
					// Giảm lượt đi của người chơi tương ứng
					if (lastMove.player == -1) {
						Player_1.Moves--;
					}
					else if (lastMove.player == 1) {
						Player_2.Moves--;
					}
					Draw_infor1(70, 6, 28, 12); // Cập nhật thông tin trên giao diện
					GotoXY(lastMove.x, lastMove.y);
				}

			}
		}
		else if (_COMMAND == 'L') {  // Lưu trò chơi và quay lại Menu chính
			if (AskSaveGame() == 'Y') {
				SaveGame();
				MainMenu();
				return;
			}
			else {
				system("cls");
				DrawLoaded(_A);
				SubMenu();
				DrawLoaded(_A);
			}

		}
	}
}
void EasyGamePlayTimerPvC() {
	StartTimer(MAXTIMEGAME, MAXTIMETURN);
	//StartTimer(gameTimer, turnTimer);
	bool validEnter = true;

	while (true) {
		if (isTurnSkipped) {
			{
				//std::lock_guard<std::mutex> lock(timerMutex); // Đảm bảo đồng bộ
				timerMutex.lock();
				_TURN = !_TURN; // Chuyển lượt
				isTurnSkipped = false; // Reset trạng thái
				timerMutex.unlock();
			}
			HighlightPlayer(70, 6, 28, 12);
		}

		// Kiểm tra hết thời gian game
		if (gameTimer <= 0) {
			GotoXY(75 + 10, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2);
			//std::lock_guard<std::mutex> lock(screenMutex);
			screenMutex.lock();
			std::cout << "Game over: Total time expired!";
			screenMutex.unlock();
			StopTimer();
			//system("cls");

			switch (ProcessFinish(0)) {
			case -1:  // Người chơi thắng
			case 1:   // Hòa
			case 0:   // Tiếp tục
				if (AskContinue() != 'Y') {
					if (AskSaveGame() == 'Y') {
						SaveGame();
						MainMenu();
						return;
					}
					else {
						system("cls");
						MainMenu();
					}
				}
				else {
					StartTimer(MAXTIMEGAME, MAXTIMETURN);
					StartGameInOneGame();    // Bắt đầu trò chơi mới trong 1 game dang choi
					break;
				}
			}

		}
		_COMMAND = toupper(_getch());

		if (_COMMAND == 27) {  // ESC để mở menu phụ
			playSelectSound();
			StopTimer();
			SubMenu();
			StartTimer(gameTimer, turnTimer);
			system("cls");
			SetColor(0, 15);
			DrawLoaded(_A);
			continue;
		}
		else if (_COMMAND == 'A') {
			screenMutex.lock();
			playMoveSound();
			MoveLeft();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'W') {
			screenMutex.lock();
			playMoveSound();
			MoveUp();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'S') {
			screenMutex.lock();
			playMoveSound();
			MoveDown();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'D') {
			screenMutex.lock();
			playMoveSound();
			MoveRight();
			screenMutex.unlock();
		}
		else if (_COMMAND == 13) {  // Phím Enter
			playSelectSound();
			//std::lock_guard<std::mutex> lock(screenMutex);
			switch (CheckBoard(_X, _Y)) {
			case -1:
			{
				turnTimer = 5;
				screenMutex.lock();
				SetColor(4, 15);
				printf("X");
				Player_1.Moves++;
				Draw_infor(70, 6, 28, 12);
				screenMutex.unlock();
				break;
			}
			case 0:
				validEnter = false;
				break;
			}

			if (validEnter) {
				switch (ProcessFinish(TestBoard())) {
				case -1:  // Người chơi thắng
				case 1:   // Hòa
				case 0:   // Tiếp tục
					if (AskContinue() != 'Y') {
						if (AskSaveGame() == 'Y') {
							SaveGame();
							MainMenu();
							return;
						}
						else {
							system("cls");
							MainMenu();
						}
					}
					else {
						StartTimer(MAXTIMEGAME, MAXTIMETURN);
						StartGameInOneGame();    // Bắt đầu trò chơi mới
						break;
					}
				}

				// Lượt của máy
				int pX, pY;
				MediumBot(_X, _Y, pX, pY);
				turnTimer = 5;
				screenMutex.lock();
				SetColor(1, 15);
				GotoXY(_A[pX][pY].x, _A[pX][pY].y);
				printf("O");
				Player_2.Moves++;
				Draw_infor(70, 6, 28, 12);
				screenMutex.unlock();


				//Sleep(600);

				switch (ProcessFinish(TestBoard())) {
				case -1:
				case 1:
				case 0:
					if (AskContinue() != 'Y') {
						if (AskSaveGame() == 'Y') {
							SaveGame();
							MainMenu();
							return;
						}
						else {
							system("cls");
							MainMenu();
						}
					}
					else {
						StartTimer(MAXTIMEGAME, MAXTIMETURN);
						StartGameInOneGame();    // Bắt đầu trò chơi mới
						break;
					}
				}
			}
			validEnter = true;

		}
		else if (_COMMAND == 'L') {  // Lưu trò chơi và quay lại Menu chính
			StopTimer();
			if (AskSaveGame() == 'Y') {
				SaveGame();
				MainMenu();
				return;
			}
			else {
				system("cls");
				DrawLoaded(_A);
				SubMenu();
				StartTimer(gameTimer, turnTimer);
				DrawLoaded(_A);
			}


		}
	}
}
void EasyGamePlayTimerLoadPvC() {
	//StartTimer(30, 5);
	StartTimer(gameTimer, turnTimer);
	bool validEnter = true;

	while (true) {
		if (isTurnSkipped) {
			{
				//std::lock_guard<std::mutex> lock(timerMutex); // Đảm bảo đồng bộ
				timerMutex.lock();
				_TURN = !_TURN; // Chuyển lượt
				isTurnSkipped = false; // Reset trạng thái
				timerMutex.unlock();
			}
			HighlightPlayer(70, 6, 28, 12);
		}

		// Kiểm tra hết thời gian game
		if (gameTimer <= 0) {
			GotoXY(75 + 10, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2);
			//std::lock_guard<std::mutex> lock(screenMutex);
			screenMutex.lock();
			std::cout << "Game over: Total time expired!";
			screenMutex.unlock();
			StopTimer();
			//system("cls");

			switch (ProcessFinish(0)) {
			case -1:  // Người chơi thắng
			case 1:   // Hòa
			case 0:   // Tiếp tục
				if (AskContinue() != 'Y') {
					if (AskSaveGame() == 'Y') {
						SaveGame();
						MainMenu();
						return;
					}
					else {
						system("cls");
						MainMenu();
					}
				}
				else {
					StartTimer(MAXTIMEGAME, MAXTIMETURN);
					StartGameInOneGame();    // Bắt đầu trò chơi mới trong 1 game dang choi
					break;
				}
			}

		}
		_COMMAND = toupper(_getch());

		if (_COMMAND == 27) {  // ESC để mở menu phụ
			playSelectSound();
			StopTimer();
			SubMenu();
			StartTimer(gameTimer, turnTimer);
			system("cls");
			SetColor(0, 15);
			DrawLoaded(_A);
			continue;
		}
		else if (_COMMAND == 'A') {
			screenMutex.lock();
			playMoveSound();
			MoveLeft();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'W') {
			screenMutex.lock();
			playMoveSound();
			MoveUp();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'S') {
			screenMutex.lock();
			playMoveSound();
			MoveDown();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'D') {
			screenMutex.lock();
			playMoveSound();
			MoveRight();
			screenMutex.unlock();
		}
		else if (_COMMAND == 13) {  // Phím Enter
			playSelectSound();
			//std::lock_guard<std::mutex> lock(screenMutex);
			switch (CheckBoard(_X, _Y)) {
			case -1:
			{
				turnTimer = 5;
				screenMutex.lock();
				SetColor(4, 15);
				printf("X");
				Player_1.Moves++;
				Draw_infor(70, 6, 28, 12);
				screenMutex.unlock();
				break;
			}
			case 0:
				validEnter = false;
				break;
			}

			if (validEnter) {
				switch (ProcessFinish(TestBoard())) {
				case -1:  // Người chơi thắng
				case 1:   // Hòa
				case 0:   // Tiếp tục
					if (AskContinue() != 'Y') {
						if (AskSaveGame() == 'Y') {
							SaveGame();
							MainMenu();
							return;
						}
						else {
							system("cls");
							MainMenu();
						}
					}
					else {
						StartTimer(MAXTIMEGAME, MAXTIMETURN);
						StartGameInOneGame();    // Bắt đầu trò chơi mới
						break;
					}
				}

				// Lượt của máy
				int pX, pY;
				MediumBot(_X, _Y, pX, pY);
				turnTimer = 5;
				screenMutex.lock();
				SetColor(1, 15);
				GotoXY(_A[pX][pY].x, _A[pX][pY].y);
				printf("O");
				Player_2.Moves++;
				Draw_infor(70, 6, 28, 12);
				screenMutex.unlock();


				//Sleep(600);

				switch (ProcessFinish(TestBoard())) {
				case -1:
				case 1:
				case 0:
					if (AskContinue() != 'Y') {
						if (AskSaveGame() == 'Y') {
							SaveGame();
							MainMenu();
							return;
						}
						else {
							system("cls");
							MainMenu();
						}
					}
					else {
						StartTimer(MAXTIMEGAME, MAXTIMETURN);
						StartGameInOneGame();    // Bắt đầu trò chơi mới
						break;
					}
				}
			}
			validEnter = true;

		}
		else if (_COMMAND == 'L') {  // Lưu trò chơi và quay lại Menu chính
			StopTimer();
			if (AskSaveGame() == 'Y') {
				SaveGame();
				MainMenu();
				return;
			}
			else {
				system("cls");
				DrawLoaded(_A);
				SubMenu();
				StartTimer(gameTimer, turnTimer);
				DrawLoaded(_A);
			}


		}
	}
}
void HardGamePlayPvC() {
	//int count = -1;
	bool validEnter = true;

	while (true) {
		_COMMAND = toupper(_getch());

		if (_COMMAND == 27) {  // ESC để mở menu phụ
			playSelectSound();
			SubMenu();
			system("cls");
			SetColor(0, 15);
			DrawLoaded(_A);
			continue;
		}
		else if (_COMMAND == 'A') {
			screenMutex.lock();
			playMoveSound();
			MoveLeft();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'W') {
			screenMutex.lock();
			playMoveSound();
			MoveUp();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'S') {
			screenMutex.lock();
			playMoveSound();
			MoveDown();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'D') {
			screenMutex.lock();
			playMoveSound();
			MoveRight();
			screenMutex.unlock();
		}
		else if (_COMMAND == 13) {  // Phím Enter
			playSelectSound();
			switch (CheckBoard(_X, _Y)) {
			case -1:
				SetColor(4, 15);
				printf("X");
				Player_1.Moves++;
				Draw_infor(70, 6, 28, 12);
				moveHistoryP.push({ _X,_Y,-1 });
				break;
			case 0:
				validEnter = false;
				break;
			}

			if (validEnter) {
				switch (ProcessFinish(TestBoard())) {
				case -1:  // Người chơi thắng
				case 1:   // Hòa
				case 0:   // Tiếp tục
					if (AskContinue() != 'Y') {
						if (AskSaveGame() == 'Y') {
							SaveGame();
							MainMenu();
							return;
						}
						else {
							system("cls");
							MainMenu();
						}
					}
					else {
						StartGameInOneGame();    // Bắt đầu trò chơi mới
						break;
					}
				}

				// Lượt của máy
				int pX, pY;
				improvedBot(_X, _Y, pX, pY);
				SetColor(1, 15);
				GotoXY(_A[pX][pY].x, _A[pX][pY].y);
				printf("O");
				Player_2.Moves++;
				Draw_infor(70, 6, 28, 12);
				moveHistoryP.push({ _A[pX][pY].x, _A[pX][pY].y, 1 });
				Sleep(300);

				switch (ProcessFinish(TestBoard())) {
				case -1:
				case 1:
				case 0:
					if (AskContinue() != 'Y') {
						if (AskSaveGame() == 'Y') {
							SaveGame();
							MainMenu();
							return;
						}
						else {
							system("cls");
							MainMenu();
						}
					}
					else {						
						StartGameInOneGame();    // Bắt đầu trò chơi mới
						break;
					}
				}
			}
			validEnter = true;
		}
		else if (_COMMAND == 'Z') {  // Phím Z để hủy 2 nước đi trước đó
			if (moveHistoryP.size() >= 2) {  // Kiểm tra xem có đủ 2 nước đi để hủy không
				for (int i = 0; i < 2; ++i) {
					Move lastMove = moveHistoryP.top(); // Lấy nước đi cuối cùng
					moveHistoryP.pop();  // Xóa khỏi lịch sử
					for (int i = 0; i < BOARD_SIZE; i++) {
						for (int j = 0; j < BOARD_SIZE; j++) {
							if (_A[i][j].x == lastMove.x && _A[i][j].y == lastMove.y) {
								_A[i][j].c = 0;  // Xóa ký tự trong bảng
							}
						}
					}
					GotoXY(lastMove.x, lastMove.y);
					printf(" ");  // Xóa ký tự trên màn hình
					// Giảm lượt đi của người chơi tương ứng
					if (lastMove.player == -1) {
						Player_1.Moves--;
					}
					else if (lastMove.player == 1) {
						Player_2.Moves--;
					}
					Draw_infor1(70, 6, 28, 12); // Cập nhật thông tin trên giao diện
					GotoXY(lastMove.x, lastMove.y);
				}
			
			}
			}
		else if (_COMMAND == 'L') {  // Lưu trò chơi và quay lại Menu chính
			if (AskSaveGame() == 'Y') {
				SaveGame();
				MainMenu();
				return;
			}
			else {
				system("cls");
				DrawLoaded(_A);
				SubMenu();
				DrawLoaded(_A);
			}

		}
	}
}
void HardGamePlayTimerPvC() {
	StartTimer(MAXTIMEGAME, MAXTIMETURN);
	//StartTimer(gameTimer, turnTimer);
	bool validEnter = true;

	while (true) {
		if (isTurnSkipped) {
			{
				//std::lock_guard<std::mutex> lock(timerMutex); // Đảm bảo đồng bộ
				timerMutex.lock();
				_TURN = !_TURN; // Chuyển lượt
				isTurnSkipped = false; // Reset trạng thái
				timerMutex.unlock();
			}
			HighlightPlayer(70, 6, 28, 12);
		}

		// Kiểm tra hết thời gian game
		if (gameTimer <= 0) {
			GotoXY(75 + 10, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2);
			//std::lock_guard<std::mutex> lock(screenMutex);
			screenMutex.lock();
			std::cout << "Game over: Total time expired!";
			screenMutex.unlock();
			StopTimer();
			//system("cls");

			switch (ProcessFinish(0)) {
			case -1:  // Người chơi thắng
			case 1:   // Hòa
			case 0:   // Tiếp tục
				if (AskContinue() != 'Y') {
					if (AskSaveGame() == 'Y') {
						SaveGame();
						MainMenu();
						return;
					}
					else {
						system("cls");
						MainMenu();
					}
				}
				else {
					StartTimer(MAXTIMEGAME, MAXTIMETURN);
					StartGameInOneGame();    // Bắt đầu trò chơi mới trong 1 game dang choi
					break;
				}
			}
			
		}
		_COMMAND = toupper(_getch());

		if (_COMMAND == 27) {  // ESC để mở menu phụ
			playSelectSound();
			StopTimer();
			SubMenu();
			StartTimer(gameTimer, turnTimer);
			system("cls");
			SetColor(0, 15);
			DrawLoaded(_A);
			continue;
		}
		else if (_COMMAND == 'A') {
			screenMutex.lock();
			playMoveSound();
			MoveLeft();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'W') {
			screenMutex.lock();
			playMoveSound();
			MoveUp();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'S') {
			screenMutex.lock();
			playMoveSound();
			MoveDown();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'D') {
			screenMutex.lock();
			playMoveSound();
			MoveRight();
			screenMutex.unlock();
		}
		else if (_COMMAND == 13) {  // Phím Enter
			playSelectSound();
			//std::lock_guard<std::mutex> lock(screenMutex);
			switch (CheckBoard(_X, _Y)) {
			case -1:
			{
				turnTimer = 5;
				screenMutex.lock();
				SetColor(4, 15);
				printf("X");
				Player_1.Moves++;
				Draw_infor(70, 6, 28, 12);
				screenMutex.unlock();
				break;
			}
			case 0:
				validEnter = false;
				break;
			}

			if (validEnter) {
				switch (ProcessFinish(TestBoard())) {
				case -1:  // Người chơi thắng
				case 1:   // Hòa
				case 0:   // Tiếp tục
					if (AskContinue() != 'Y') {
						if (AskSaveGame() == 'Y') {
							SaveGame();
							MainMenu();
							return;
						}
						else {
							system("cls");
							MainMenu();
						}
					}
					else {
						StartTimer(MAXTIMEGAME, MAXTIMETURN);
						StartGameInOneGame();    // Bắt đầu trò chơi mới
						break;
					}
				}

				// Lượt của máy
				int pX, pY;
				improvedBot(_X, _Y, pX, pY);
				turnTimer = 5;
				screenMutex.lock();
				SetColor(1, 15);
				GotoXY(_A[pX][pY].x, _A[pX][pY].y);
				printf("O");
				Player_2.Moves++;
				Draw_infor(70, 6, 28, 12);	
				screenMutex.unlock();


				//Sleep(600);

				switch (ProcessFinish(TestBoard())) {
				case -1:
				case 1:
				case 0:
					if (AskContinue() != 'Y') {
						if (AskSaveGame() == 'Y') {
							SaveGame();
							MainMenu();
							return;
						}
						else {
							system("cls");
							MainMenu();
						}
					}
					else {
						StartTimer(MAXTIMEGAME, MAXTIMETURN);
						StartGameInOneGame();    // Bắt đầu trò chơi mới
						break;
					}
				}
			}
			validEnter = true;
			
		}
		else if (_COMMAND == 'L') {  // Lưu trò chơi và quay lại Menu chính
			StopTimer();
			if (AskSaveGame() == 'Y') {
				SaveGame();
				MainMenu();
				return;
			}
			else {
				system("cls");
				DrawLoaded(_A);
				SubMenu();
				StartTimer(gameTimer, turnTimer);
				DrawLoaded(_A);
			}
			

		}
	}
}
void HardGamePlayTimerLoadPvC() {
	//StartTimer(30, 5);
	StartTimer(gameTimer, turnTimer);
	bool validEnter = true;

	while (true) {
		if (isTurnSkipped) {
			{
				//std::lock_guard<std::mutex> lock(timerMutex); // Đảm bảo đồng bộ
				timerMutex.lock();
				_TURN = !_TURN; // Chuyển lượt
				isTurnSkipped = false; // Reset trạng thái
				timerMutex.unlock();
			}
			HighlightPlayer(70, 6, 28, 12);
		}

		// Kiểm tra hết thời gian game
		if (gameTimer <= 0) {
			GotoXY(75 + 10, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2);
			//std::lock_guard<std::mutex> lock(screenMutex);
			screenMutex.lock();
			std::cout << "Game over: Total time expired!";
			screenMutex.unlock();
			StopTimer();
			//system("cls");

			switch (ProcessFinish(0)) {
			case -1:  // Người chơi thắng
			case 1:   // Hòa
			case 0:   // Tiếp tục
				if (AskContinue() != 'Y') {
					if (AskSaveGame() == 'Y') {
						SaveGame();
						MainMenu();
						return;
					}
					else {
						system("cls");
						MainMenu();
					}
				}
				else {
					StartTimer(MAXTIMEGAME, MAXTIMETURN);
					StartGameInOneGame();    // Bắt đầu trò chơi mới trong 1 game dang choi
					break;
				}
			}
			
		}
		_COMMAND = toupper(_getch());

		if (_COMMAND == 27) {  // ESC để mở menu phụ
			playSelectSound();
			StopTimer();
			SubMenu();
			StartTimer(gameTimer, turnTimer);
			system("cls");
			SetColor(0, 15);
			DrawLoaded(_A);
			continue;
		}
		else if (_COMMAND == 'A') {
			screenMutex.lock();
			playMoveSound();
			MoveLeft();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'W') {
			screenMutex.lock();
			playMoveSound();
			MoveUp();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'S') {
			screenMutex.lock();
			playMoveSound();
			MoveDown();
			screenMutex.unlock();
		}
		else if (_COMMAND == 'D') {
			screenMutex.lock();
			playMoveSound();
			MoveRight();
			screenMutex.unlock();
		}
		else if (_COMMAND == 13) {  // Phím Enter
			playSelectSound();
			//std::lock_guard<std::mutex> lock(screenMutex);
			switch (CheckBoard(_X, _Y)) {
			case -1:
			{
				turnTimer = 5;
				screenMutex.lock();
				SetColor(4, 15);
				printf("X");
				Player_1.Moves++;
				Draw_infor(70, 6, 28, 12);
				screenMutex.unlock();
				break;
			}
			case 0:
				validEnter = false;
				break;
			}

			if (validEnter) {
				switch (ProcessFinish(TestBoard())) {
				case -1:  // Người chơi thắng
				case 1:   // Hòa
				case 0:   // Tiếp tục
					if (AskContinue() != 'Y') {
						if (AskSaveGame() == 'Y') {
							SaveGame();
							MainMenu();
							return;
						}
						else {
							system("cls");
							MainMenu();
						}
					}
					else {
						StartTimer(MAXTIMEGAME, MAXTIMETURN);
						StartGameInOneGame();    // Bắt đầu trò chơi mới
						break;
					}
				}

				// Lượt của máy
				int pX, pY;
				improvedBot(_X, _Y, pX, pY);
				turnTimer = 5;
				screenMutex.lock();
				SetColor(1, 15);
				GotoXY(_A[pX][pY].x, _A[pX][pY].y);
				printf("O");
				Player_2.Moves++;
				Draw_infor(70, 6, 28, 12);
				screenMutex.unlock();


				//Sleep(600);

				switch (ProcessFinish(TestBoard())) {
				case -1:
				case 1:
				case 0:
					if (AskContinue() != 'Y') {
						if (AskSaveGame() == 'Y') {
							SaveGame();
							MainMenu();
							return;
						}
						else {
							system("cls");
							MainMenu();
						}
					}
					else {
						StartTimer(MAXTIMEGAME, MAXTIMETURN);
						StartGameInOneGame();    // Bắt đầu trò chơi mới
						break;
					}
				}
			}
			validEnter = true;

		}
		else if (_COMMAND == 'L') {  // Lưu trò chơi và quay lại Menu chính
			StopTimer();
			if (AskSaveGame() == 'Y') {
				SaveGame();
				MainMenu();
				return;
			}
			else {
				system("cls");
				DrawLoaded(_A);
				SubMenu();
				StartTimer(gameTimer, turnTimer);
				DrawLoaded(_A);
			}


		}
	}
}

// Hàm nhóm Control (Điều khiển trò chơi)
void StartGame() {
	system("Color F0");
	system("cls");
	DrawBound();
	ResetGame(); // Khoi tao lai ban co, toa do, khong xoa win, move
	ShowCur(true);
	keep = false;
	DrawBoard(BOARD_SIZE); // Vẽ màn hình game
	DrawGuideGame(3, 35);
	Draw_infor1(70, 6, 28, 12);
	DrawGameMode(70, 3, choicestyle, choicegame);
	GotoXY(_X, _Y);
}
//Dam bao rang se doi luot sau moi tran thang, vi du x thang thi doi luot sang o
void StartGameInOneGame() {
	system("Color F0");
	system("cls");
	DrawBound();
	ResetGameInOneGame(); // Khoi tao lai ban co, toa do, khong xoa win, move
	ShowCur(true);
	keep = false;
	DrawBoard(BOARD_SIZE); // Vẽ màn hình game
	DrawGuideGame(3, 35);
	Draw_infor1(70, 6, 28, 12);
	DrawGameMode(70, 3, choicestyle, choicegame);
	GotoXY(_X, _Y);
	
}
void MoveRight() {
	if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x)
	{
		int _x = _X;
		_X += 4;
		GotoXY(_X, _Y);
	}
}
void MoveLeft() {
	if (_X > _A[0][0].x) {
		int _x = _X;
		_X -= 4;
		GotoXY(_X, _Y);
	}
}
void MoveDown() {
	if (_Y < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y)
	{
		_Y += 2;
		GotoXY(_X, _Y);
	}
}
void MoveUp() {
	if (_Y > _A[0][0].y) {
		_Y -= 2;
		GotoXY(_X, _Y);
	}
}
// Hàm hỏi người chơi có tiếp tục hay không
int AskContinue() {
	char choice;
	do {
		GotoXY(60, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 4); // Nhảy đến vị trí để hỏi người chơi
		SetColor(2, 15);
		cout << text.askContinueText;
		choice = toupper(_getch()); // Đọc ký tự và chuyển sang chữ hoa
		if (choice != 'Y' && choice != 'N') {
			GotoXY(60, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 5); // Hiện cảnh báo phía dưới
			SetColor(4, 15);
			cout << text.errorYN;
			SetColor(0, 15);
		}
	} while (choice != 'Y' && choice != 'N'); // Lặp lại nếu nhập sai
	return choice;
}

int AskSaveGame() {
	char choice;
	do {
		GotoXY(60, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 4); // Nhảy đến vị trí để hỏi người chơi
		SetColor(2, 15);
		cout << text.askSaveGameText;
		choice = toupper(_getch()); // Đọc ký tự và chuyển sang chữ hoa
		if (choice != 'Y' && choice != 'N') {
			GotoXY(60, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 5); // Hiện cảnh báo phía dưới
			SetColor(4, 15);
			cout << text.errorYN;
			SetColor(0, 15);
		}
	} while (choice != 'Y' && choice != 'N'); // Lặp lại nếu nhập sai
	return choice;
}
void BlinkConsoleCharacters() {
	CHAR_INFO charInfo;
	COORD bufferSize = { 1, 1 };
	COORD bufferCoord = { 0, 0 };
	SMALL_RECT readRegion;	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// Kiểm tra nếu không thể lấy handle console
	if (hConsole == INVALID_HANDLE_VALUE) {
		std::cerr << "Failed to get console handle.\n";
		return;
	}
	static bool isGreen = true;  // Khai báo biến tĩnh isGreen
	while (keep) { // Lặp vô hạn để nhấp nháy
		for (int i = 0; i < 5; i++) {
			// Lấy tọa độ x và y từ positions
			int x = _A[positions[i][0]][positions[i][1]].x;
			int y = _A[positions[i][0]][positions[i][1]].y;
			// Xác định vùng đọc chỉ với một ô tại tọa độ (x, y)
			readRegion = { SHORT(x), SHORT(y), SHORT(x), SHORT(y) };
			// Đọc ký tự và thuộc tính gốc tại vị trí
			if (!ReadConsoleOutput(hConsole, &charInfo, bufferSize, bufferCoord, &readRegion)) {
				std::cerr << "Failed to read console output.\n";
				return;
			}
			// Thay đổi màu sắc nhấp nháy
			if (isGreen) {
				// Đổi màu chữ thành xanh lá cây
				charInfo.Attributes = (charInfo.Attributes & 0xF0) | FOREGROUND_GREEN;
			}
			else {
				// Đổi màu chữ thành màu mặc định 
				charInfo.Attributes = (charInfo.Attributes & 0xF0) |
					(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			// Ghi lại ký tự với màu mới
			if (!WriteConsoleOutput(hConsole, &charInfo, bufferSize, bufferCoord, &readRegion)) {
				std::cerr << "Failed to write console output.\n";
				return;
			}
		}
		// Đổi trạng thái màu cho lần nhấp nháy tiếp theo
		isGreen = !isGreen;
		// Dừng một khoảng thời gian trước khi lặp lại
		Sleep(200); // Dừng 200ms
	}
}
int ProcessFinish(int pWhoWin) {
	GotoXY(85 + 2, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 8); // Nhảy tới vị trí thích hợp để in chuỗi thắng/thua/hòa

	switch (pWhoWin) {

	case -1:
	{
		StopTimer();
		keep = true;
		thread nhapnhay(BlinkConsoleCharacters);
		nhapnhay.detach();
	}
		playWINGameMusic();
		SetColor(0, 15);
		Box(70, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 9, 63, 10);
		nhapnhayX(75, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 6);
		keep = false;
		GotoXY(60, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 5);
		SetColor(2, 15);
		system("pause");
		SetColor(0, 15);
		drawBangthongbao(32, 10, 80, 20, -1, choicegame, choicestyle);
		break;
	case 1:
	{
		StopTimer();
		keep = true;
		thread nhapnhay(BlinkConsoleCharacters);
		nhapnhay.detach();
	}
		playWINGameMusic();
		SetColor(0, 15);
		Box(70, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 9, 63, 10);
		nhapnhayO(75, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 6);
		keep = false;
		GotoXY(60, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 5); 
		SetColor(2, 15); 
		system("pause");
		SetColor(0, 15);
		drawBangthongbao(32, 10, 80, 20, 1, choicegame, choicestyle);
		break;
	case 0:
		StopTimer();
		playDRAWGameMusic();
		Box(70, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 9, 63, 10);
		nhapnhayDRAW(75, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 7);
		GotoXY(60, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 5);
		SetColor(2, 15); 
		system("pause");
		SetColor(0, 15);
		drawBangthongbao(32, 10, 80, 20, 0, choicegame, choicestyle);
		
		break;
	case 2:
		_TURN = !_TURN; // Đổi lượt nếu không có gì xảy ra
	}
	GotoXY(_X, _Y); // Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
	return pWhoWin;
}