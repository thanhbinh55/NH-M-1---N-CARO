#include "Game.h"
#include "Menu.h"
#include "Help.h"
#include "Setting.h"
#include "SaveLoad.h"
#include "LanguageText.h"
#include "Draw.h"
#include "Bot.h"
_POINT _A[BOARD_SIZE][BOARD_SIZE];
bool _TURN;
int _COMMAND;
int _X, _Y;
Player Player_1, Player_2;
//bool isSoundEffectEnabled = true;
Language currentLanguage;
int positions[5][2];

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
	// SetTextColor(252); // Màu chữ trắng --> bỏ dòng này thì chữ sẽ trở về màu cũ sau khi hết chọn 
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
	//GabageCollect();
	//Có thể lưu game trước khi exit
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
	//SetColor(0, 15);
	Box(x, y, w, h);
	system("Color F0");
	Draw_Guide(50, 35, "Nhap ky tu tu ban phim,   Enter: Get Name");
	DrawBound();
	DrawLogoCaro(45, 5);

	SetColor(4, 15);
	GotoXY(x + 1, y + 1);
	cout << text.nameText1;
	char c;
	Player_1.Name = "";
	// Nhập tên cho Player 1
	while (true) {
		c = _getch();
		if (c == 13)
		{
			playSelectSound();
			break; // Nhấn Enter để kết thúc nhập tên
		}
		if (c == 8 && !Player_1.Name.empty()) { // Kiểm tra chuỗi trống khi dùng Backspace
			Player_1.Name.pop_back();
			GotoXY(x + 19, y + 1);
			cout << Player_1.Name << " "; // In lại chuỗi và xóa ký tự dư thừa
			GotoXY(x + 19 + Player_1.Name.length(), y + 1);
		}
		else if ((isalpha(c) || c == ' ') && Player_1.Name.length() <= 10) { // Chỉ nhận chữ cái hoặc dấu cách và giới hạn 10 ký tự
			c = toupper(c); // Chuyển ký tự sang chữ hoa
			cout << c;
			Player_1.Name += c;
		}
	}
	Player_2.Name = "";

	// Nhập tên cho Player 2
	GotoXY(x + 1, y + 4);
	SetColor(1, 15);
	cout << text.nameText2;
	while (true) {
		c = _getch();
		if (c == 13) {
			playSelectSound();
			break; // Nhấn Enter để kết thúc nhập tên
		}
		if (c == 8 && !Player_2.Name.empty()) { // Kiểm tra chuỗi trống khi dùng Backspace
			Player_2.Name.pop_back();
			GotoXY(x + 19, y + 4);
			cout << Player_2.Name << " ";
			GotoXY(x + 19 + Player_2.Name.length(), y + 4);
		}
		else if ((isalpha(c) || c == ' ') && Player_2.Name.length() <= 10) { // Chỉ nhận chữ cái hoặc dấu cách và giới hạn 10 ký tự
			c = toupper(c);
			cout << c;
			Player_2.Name += c;
		}
	}
	SetColor(15, 0);
}
void InputPvC(int x, int y, int w, int h) {
	//SetColor(0, 15);
	Box(x, y, w, h);
	system("Color F0");
	Draw_Guide(56, 35, "Nhap ky tu tu ban phim,   Enter: Get Name");
	DrawBound();
	LogoCaro(52, 5);

	SetColor(4, 15);
	GotoXY(x + 1, y + 1);
	cout << text.nameText1;
	char c;
	Player_1.Name = "";
	// Nhập tên cho Player 1
	while (true) {
		c = _getch();
		if (c == 13)
		{
			playSelectSound();
			break; // Nhấn Enter để kết thúc nhập tên
		}
		if (c == 8 && !Player_1.Name.empty()) { // Kiểm tra chuỗi trống khi dùng Backspace
			Player_1.Name.pop_back();
			GotoXY(x + 19, y + 1);
			cout << Player_1.Name << " "; // In lại chuỗi và xóa ký tự dư thừa
			GotoXY(x + 19 + Player_1.Name.length(), y + 1);
		}
		else if ((isalpha(c) || c == ' ') && Player_1.Name.length() <= 10) { // Chỉ nhận chữ cái hoặc dấu cách và giới hạn 10 ký tự
			c = toupper(c); // Chuyển ký tự sang chữ hoa
			cout << c;
			Player_1.Name += c;
		}
	}

	Player_2.Name = "Bot"; // Đặt tên cho Player 2 là Bot

	// In tên cho Player 2
	GotoXY(x + 1, y + 4);
	SetColor(1, 15);
	cout << "Player 2 (O): " << Player_2.Name << " (Bot)";

	SetColor(15, 0);
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
			playMoveSound();
			MoveLeft();
		}
		else if (_COMMAND == 'W') {
			playMoveSound();
			MoveUp();
		}
		else if (_COMMAND == 'S') {
			playMoveSound();
			MoveDown();
		}
		else if (_COMMAND == 'D') {
			playMoveSound();
			MoveRight();
		}
		else if (_COMMAND == 13) {  // Phím Enter để đánh dấu nước đi
			playSelectSound();

			// Kiểm tra ô có hợp lệ hay không
			switch (CheckBoard(_X, _Y)) {
			case -1:  // Người chơi 1 đánh
				SetColor(4, 15);
				printf("X");
				Player_1.Moves++;
				Draw_infor2(105, 3, 28, 10, Player_2);
				Draw_infor(70, 3, 28, 10, Player_1);
				break;
			case 1:   // Người chơi 2 đánh
				SetColor(1, 15);
				printf("O");
				Player_2.Moves++;
				Draw_infor2(70, 3, 28, 10, Player_1);
				Draw_infor(105, 3, 28, 10, Player_2);
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
						system("cls");  // Xóa màn hình
						MainMenu();
						//MenuReturn();   // Quay lại menu chính
						return;
					}
					else {
						StartGame();    // Bắt đầu trò chơi mới
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
				break;
			}
			
		}
	}
}
void GamePlayPvC() {
	int count = -1;
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
			playMoveSound();
			MoveLeft();
		}
		else if (_COMMAND == 'W') {
			playMoveSound();
			MoveUp();
		}
		else if (_COMMAND == 'S') {
			playMoveSound();
			MoveDown();
		}
		else if (_COMMAND == 'D') {
			playMoveSound();
			MoveRight();
		}
		else if (_COMMAND == 13) {  // Phím Enter
			playSelectSound();
			switch (CheckBoard(_X, _Y)) {
			case -1:
				SetColor(4, 15);
				printf("X");
				Player_1.Moves++;
				Draw_infor(70, 3, 28, 10, Player_1);
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
						system("cls");
						MainMenu();
					}
					else {
						StartGame();
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
				Draw_infor(105, 3, 28, 10, Player_2);

				Sleep(600);

				switch (ProcessFinish(TestBoard())) {
				case -1:
				case 1:
				case 0:
					if (AskContinue() != 'Y') {
						system("cls");
						MainMenu();
						//MenuReturn();
					}
					else {
						StartGame();
						break;
					}
				}
			}
			validEnter = true;
		}
		else if (_COMMAND == 'L') {  // Lưu và quay lại MenuReturn
			SaveGame();
			MainMenu();
			//MenuReturn();
		}
	}
}

void SetConsoleBackgroundColor() {
	CHAR_INFO charInfo;
	COORD bufferSize = { 1, 1 };
	COORD bufferCoord = { 0, 0 };
	SMALL_RECT readRegion;

	// Duyệt qua các vị trí
	for (int i = 0; i < 5; i++) {
		// Lấy tọa độ x và y từ positions
		int x = _A[positions[i][0]][positions[i][1]].x;
		int y = _A[positions[i][0]][positions[i][1]].y;

		// Xác định vùng đọc chỉ với một ô tại tọa độ (x, y)
		readRegion = { SHORT(x), SHORT(y), SHORT(x), SHORT(y) };

		// Đọc ký tự và thuộc tính màu sắc gốc tại vị trí
		if (!ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &charInfo, bufferSize, bufferCoord, &readRegion)) {
			std::cerr << "Failed to read console output.\n";
			return;
		}

		// Chỉ thay đổi màu chữ thành xanh lá (FOREGROUND_GREEN), giữ nguyên nền
		WORD newAttributes = (charInfo.Attributes & 0xF0) | FOREGROUND_GREEN;

		// Cập nhật thuộc tính của ký tự tại vị trí, giữ nguyên ký tự gốc và chỉ thay đổi màu chữ
		charInfo.Attributes = newAttributes;

		// Viết lại ký tự với màu xanh lá mà không làm thay đổi nền
		if (!WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &charInfo, bufferSize, bufferCoord, &readRegion)) {
			std::cerr << "Failed to write console output.\n";
			return;
		}
	}

	// Đặt lại màu sắc về mặc định (màu trắng)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// Hàm nhóm Control (Điều khiển trò chơi)
void StartGame() {
	system("Color F0");
	system("cls");
	DrawBound();
	ResetGame(); // Khoi tao lai ban co, toa do, khong xoa win, move
	//ResetData(); // Khởi tạo dữ liệu gốc win, move =0;
	ShowCur(true);
	DrawBoard(BOARD_SIZE); // Vẽ màn hình game
	DrawGuideGame(3, 35);
	Draw_infor(70, 3, 28, 10, Player_1);
	Draw_infor(105, 3, 28, 10, Player_2);
	GotoXY(_X, _Y);
}
void MoveRight() {
	if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x)
	{
		_X += 4;
		GotoXY(_X, _Y);
	}
}
void MoveLeft() {
	if (_X > _A[0][0].x) {
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
	Box(70, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 15, 63, 4);
	GotoXY(75 + 10, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 13); // Nhảy đến vị trí để hỏi người chơi
	cout<<text.askContinueText;
	return toupper(_getch()); // Đọc ký tự và trả về dạng chữ hoa

}
int AskSaveGame()
{
	Box(70, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 15, 63, 4);
	GotoXY(75 + 10, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 13); // Nhảy đến vị trí để hỏi người chơi
	cout<<text.askSaveGameText;
	return toupper(_getch());
	//char _COMMAND = toupper(_getch()); // Đọc ký tự và trả về dạng chữ hoa
	//if (_COMMAND == 'Y')
	//{
	//	SaveGame();
	//	return;
	//}
	//else
	//{
	//	return;
	//}

}
int ProcessFinish(int pWhoWin) {
	GotoXY(85 + 2, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 8); // Nhảy tới vị trí thích hợp để in chuỗi thắng/thua/hòa

	switch (pWhoWin) {

	case -1:
		SetConsoleBackgroundColor();
		DrawWIN(80, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 8);
	//	DrawDRAW(76, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 8);
		SetColor(0, 15);
		Box(70, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 10, 63, 10);
		GotoXY(85 + 10, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 5);
		//cout << "Player_1: " << Player_1.Name << " THANG" << " Player_2: " << Player_2.Name << endl;
		break;
	case 1:
		SetConsoleBackgroundColor();
		SetColor(0, 15);
		Box(70, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 10, 63, 10);
		GotoXY(85 + 10, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 5);
		cout << "Player_2: " << Player_2.Name << " THANG" << " Player_1: " << Player_1.Name << endl;
		break;
	case 0:
		DrawDRAW(76, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 8);
		Box(70, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 10, 63, 10);
		GotoXY(85 + 10, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y - 5);
		//cout << "Player_1: " << Player_1.Name << " HOA" << " Player_2: " << Player_2.Name << endl;
		break;
	case 2:
		_TURN = !_TURN; // Đổi lượt nếu không có gì xảy ra
	}
	GotoXY(_X, _Y); // Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
	return pWhoWin;
}
