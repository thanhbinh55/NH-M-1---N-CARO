#include "SaveLoad.h"
#include "Draw.h"
#include "Timer.h"
#include "LanguageText.h"
#include <cstdio> // Thư viện cho hàm remove
const int MAX_SAVE_FILES = 15;
vector<string> ListFileGameName;
vector<string> listdeleteGame; // chua cac file da xoa

void SaveData(string filename) {
	ofstream savegamefile(filename, ios::out); //ghi de noi dung len file game moi luu
	if (!savegamefile) {
		cout << "Không thể mở file voi ten game vua luut!" << endl;
		return;
	}
	savegamefile << Player_1.Name << endl;
	savegamefile << Player_1.Moves << endl;
	savegamefile << Player_1.Wins << endl;
	savegamefile << Player_1.Character << endl;
	savegamefile << Player_2.Name << endl;
	savegamefile << Player_2.Moves << endl;
	savegamefile << Player_2.Wins << endl;
	savegamefile << Player_2.Character << endl;
	savegamefile << _TURN << endl;
	savegamefile << turnTimer << endl;
	savegamefile << gameTimer << endl;
	savegamefile << choicegame << endl;
	savegamefile << choicestyle << endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			savegamefile << _A[i][j].c << " ";
		}
		//		savegamefile << endl;
	}
	savegamefile.close();
}
int CountSaveFiles() {
	int count = 0;
	string line;
	ifstream file("Gamelist.txt");
	if (file.is_open()) {
		while (getline(file, line)) {
			count++;
		}
		file.close();
	}
	return count;
}

void SaveGame() {

	system("cls");
	system("color F0");
	DrawBound();
	drawSave();

	Box(30, 32, 84, 4);
	// Kiểm tra số lượng file lưu
	if (CountSaveFiles() >= MAX_SAVE_FILES) {
		handleFullSaveNewGame();
		return;
	}

	string fileGameName;
	int i = 2;

	GotoXY(33, 33);
	SetColor(4, 15);
	cout << text.entername;
	if (cin.peek() == '\n') cin.get();
	SetColor(0, 15);
	//cin.ignore();
	bool check = true;
	while (check)
	{
		getline(cin, fileGameName);
		// Loại bỏ khoảng trắng thừa ở cuối
		while (!fileGameName.empty() && isspace(fileGameName.back()))
			fileGameName.pop_back();

		// Kiểm tra độ dài và chuỗi không rỗng
		if (fileGameName.empty() || fileGameName.length() > 10) {
			SetConsoleOutputCP(CP_UTF8);
			GotoXY(33, 33); SetColor(15, 15);
			cout << u8"█████████████████████████████████████████████████████████████████████████████";
			SetConsoleOutputCP(437);
			GotoXY(33, 34); SetColor(4, 15);
			cout << text.Errorname;
			continue;
		}
		fileGameName = fileGameName + ".txt";
		if (!CheckFileExistence(fileGameName)) {
			SetConsoleOutputCP(CP_UTF8);
			GotoXY(33, 34); SetColor(15, 15);
			cout << u8"██████████████████████████████████████████████████████████████████████████████";
			SetConsoleOutputCP(437);
			SetColor(4, 15);
			Draw_Guide(33, 34, text.savemode);
			GotoXY(54, 35);
			system("pause");
			SetColor(0, 15);
			check = false;
			cout << endl;
			system("cls");
			break;
		}
		else {
			SetColor(0, 15);
			GotoXY(33, 34); SetColor(4, 15);
			cout << text.nameexist;
			//SetColor(0, 15);
		}
	}

	SaveData(fileGameName);


	ofstream saveGameNametoList;

	saveGameNametoList.open("Gamelist.txt", ios::app);
	saveGameNametoList << fileGameName << endl;
	saveGameNametoList.close();

	MainMenu();
}

bool CheckFileExistence(string filename) {
	string name;
	ifstream savedfile("Gamelist.txt");

	// Kiểm tra xem file có mở thành công không
	if (!savedfile.is_open()) {
		cout << text.gameList << endl;
		return false; // Trả về false nếu không mở được file
	}

	while (getline(savedfile, name)) {
		if (name == filename) {
			savedfile.close();
			return true;
		}
	}
	savedfile.close();
	return false;
}
void drawLoad()
{
	system("cls");
	vechuLOAD(0, 1);
	SetColor(0, 15);
	DrawBound();
	Draw_Guide(43, 37, text.moveUpText + ", " + text.moveDownText + ", " + text.selectText + ", " + text.goBackText);
	Box(30, 12, 60, 19);
	Box(95, 12, 19, 19);
	ShowCur(true);
	ListFileGameName.clear();
	getFileGameNameList("Gamelist.txt"); //Lay duoc danh sash tu Gamelist
	int j = 16;
	GotoXY(40, 14);
	SetColor(15, 0);
	cout << text.List;
	SetColor(0, 15);
	for (int i = 0; i < ListFileGameName.size(); i++) {
		GotoXY(40, j);
		if (i < 9) cout << i + 1 << ".  " << ListFileGameName[i];
		else cout << i + 1 << ". " << ListFileGameName[i];
		j++;
	}
}
void drawSave()
{
	system("cls");
	vechuSAVE(10, 2);
	SetColor(0, 15);
	DrawBound();
	Draw_Guide(43, 37, text.moveUpText + ", " + text.moveDownText + ", " + text.selectText + ", " + text.goBackText);
	Box(30, 12, 60, 19);
	Box(95, 12, 19, 19);
	ShowCur(true);
	ListFileGameName.clear();
	getFileGameNameList("Gamelist.txt"); //Lay duoc danh sash tu Gamelist
	int j = 16;
	GotoXY(40, 14);
	SetColor(15, 0);
	cout << text.List;
	SetColor(0, 15);
	for (int i = 0; i < ListFileGameName.size(); i++) {
		GotoXY(40, j);
		if (i < 9) cout << i + 1 << ".  " << ListFileGameName[i];
		else cout << i + 1 << ". " << ListFileGameName[i];
		j++;
	}
}
void Load() {

	drawLoad();
	DrawBound();
	ChooseLoadFunction();

}
//Người dùng sẽ nhấn Enter để chọn hoặc  Y trong phim tắt L, thì phải xử lý thừa ký tự ở đây

void loadGameFunction() {
	string fileGameName;
	SetColor(0, 15);
	Box(30, 32, 84, 4);
	SetColor(4, 15);
	GotoXY(40, 33);
	cout << text.Loadmode;
	if (cin.peek() == '\n') cin.get();
	//cin.ignore();
	getline(cin, fileGameName);

	if (fileGameName.length() < 4 || fileGameName.substr(fileGameName.length() - 4) != ".txt") {
		fileGameName += ".txt";
	}


	if (!CheckFileExistence(fileGameName)) {
		GotoXY(40, 34);
		cout << text.LoadExist << endl;
		GotoXY(40, 35);
		system("pause");
		drawLoad();
		return; // Thoát nếu file không tồn tại
	}

	LoadGame(fileGameName);
	//LoadData(fileGameName);
	DrawLoaded(_A);
	GotoXY(_X, _Y);
	if (choicegame == 0) {//PvP
		if (choicestyle == 0)//basic
		{
			GamePlayPvP();
		}
		else
		{
			GamePlayTimerLoadPvP();
		}
	}
	else {
		{//PvC
			if (choicestyle == 0)
			{
				HardGamePlayPvC();
			}
			else
			{
				HardGamePlayTimerLoadPvC();
			}
		}
	}
}



void deleteGameFunction() {
	SetColor(0, 15);
	Box(30, 32, 84, 4);
	SetColor(4, 15);
	ListFileGameName.clear();
	getFileGameNameList("Gamelist.txt");
	string fileGameName;
	GotoXY(40, 33); SetColor(4, 15);
	cout << text.Deletename;
	if (cin.peek() == '\n') cin.get();
	getline(cin, fileGameName);

	if (fileGameName.length() < 4 || fileGameName.substr(fileGameName.length() - 4) != ".txt") {
		fileGameName += ".txt";
	}

	if (!CheckFileExistence(fileGameName)) {
		GotoXY(40, 34); SetColor(4, 15);
		cout << text.LoadExist << endl;
		GotoXY(40, 35);
		system("pause");
		drawLoad();
		return;
	}


	bool found = false;
	for (int i = 0; i < ListFileGameName.size(); i++) {
		if (ListFileGameName[i] == fileGameName) {
			found = true;


			listdeleteGame.push_back(ListFileGameName[i]);

			if (remove(fileGameName.c_str()) == 0) {
				GotoXY(40, 34);
				cout << text.Deletefile << fileGameName << "               " << endl;
			}
			else {
				GotoXY(40, 34);
				cout << text.DeleteExist << endl;
			}


			ListFileGameName.erase(ListFileGameName.begin() + i);
			break;
		}
	}

	if (!found) {
		GotoXY(40, 34);
		cout << text.DeleteExist << endl;
	}

	// Cập nhật lại nội dung của file Gamelist.txt
	ofstream outFile("Gamelist.txt", ios::out);
	for (const auto& gameName : ListFileGameName) {
		outFile << gameName << endl;
	}
	outFile.close();

	drawLoad();
	GotoXY(40, 36);
}

void changeGameNameFunction() {
	SetColor(0, 15);
	Box(30, 32, 84, 4);
	SetColor(4, 15);
	// Làm mới danh sách file
	ListFileGameName.clear();
	getFileGameNameList("Gamelist.txt");

	string fileGameName;
	GotoXY(40, 33); SetColor(4, 15);
	cout << text.Rename;
	if (cin.peek() == '\n') cin.get();
	getline(cin, fileGameName);

	// Đảm bảo file có đuôi ".txt"
	if (fileGameName.length() < 4 || fileGameName.substr(fileGameName.length() - 4) != ".txt") {
		fileGameName += ".txt";
	}

	// Kiểm tra sự tồn tại của file
	if (!CheckFileExistence(fileGameName)) {
		GotoXY(40, 34); SetColor(4, 15);
		cout << text.LoadExist << endl;
		GotoXY(40, 35);
		system("pause");
		SetColor(0, 15);
		drawLoad();
		return; // Thoát nếu file không tồn tại
	}

	string fileGameNameChange;
	SetConsoleOutputCP(CP_UTF8);
	GotoXY(33, 33); SetColor(15, 15);
	cout << u8"██████████████████████████████████████████████████████████████";
	SetConsoleOutputCP(437);
	GotoXY(40, 34); SetColor(4, 15);
	cout << text.Newgame;
	//SetColor(0, 15);
	if (cin.peek() == '\n') cin.get();
	getline(cin, fileGameNameChange);

	// Đảm bảo file mới có đuôi ".txt"
	if (fileGameNameChange.length() < 4 || fileGameNameChange.substr(fileGameNameChange.length() - 4) != ".txt") {
		fileGameNameChange += ".txt";
	}

	// Thực hiện đổi tên file
	if (std::rename(fileGameName.c_str(), fileGameNameChange.c_str()) == 0) {
		// Tìm và cập nhật trong danh sách
		for (auto& gameName : ListFileGameName) {
			if (gameName == fileGameName) {
				gameName = fileGameNameChange;
				break;
			}
		}

		GotoXY(40, 34);
		cout << text.Changed << fileGameNameChange << "               " << endl;

		// Cập nhật lại file Gamelist.txt
		ofstream outFile("Gamelist.txt", ios::out);
		for (const auto& gameName : ListFileGameName) {
			outFile << gameName << endl;
		}
		outFile.close();
	}
	else {
		GotoXY(40, 35);
		perror("Error renaming file");
	}

	drawLoad();
	GotoXY(40, 36);
}

void LoadData(string filename) {
	ifstream loadfileGameName;
	loadfileGameName.open(filename, ios::in);

	// Kiểm tra xem file có mở thành công không
	if (!loadfileGameName.is_open()) {
		cout << text.Changedmode << filename << endl;
		return; // Thoát khỏi hàm nếu không mở được file
	}

	int turn;
	int turntimer;  // Thời gian cho mỗi lượt chơi
	int gametimer;
	int choicegamee;
	int choicestylee;
	Player P[2];

	for (int i = 0; i < 2; i++) {
		string name = "";
		int moves = 0;
		int wins = 0;
		string character = "";

		if (i == 1) {
			loadfileGameName.ignore(); // Bỏ qua dòng trước đó nếu cần
		}
		getline(loadfileGameName, name);
		loadfileGameName >> moves >> wins;
		loadfileGameName.ignore();
		getline(loadfileGameName, character);
		P[i].Name = name;
		P[i].Moves = moves;
		P[i].Wins = wins;
		P[i].Character = character;
	}

	loadfileGameName >> turn >> turntimer >> gametimer >> choicegamee >> choicestylee;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			int x = 0;
			if (!(loadfileGameName >> x)) {
				cout << text.Error << endl;
				return; // Thoát nếu không đọc được dữ liệu
			}
			_A[i][j].x = 4 * j + LEFT + 2; // Trung với hoành độ bàn cờ
			_A[i][j].y = 2 * i + TOP + 1; // Trung với tung độ bàn cờ
			_A[i][j].c = x;
		}
	}

	Player_1 = P[0];
	Player_2 = P[1];
	_TURN = turn;
	turnTimer = turntimer;
	gameTimer = gametimer;
	choicegame = choicegamee;
	choicestyle = choicestylee;

	loadfileGameName.close();
	_COMMAND = -1;
	_X = _A[0][0].x;
	_Y = _A[0][0].y;
}

void getFileGameNameList(string fileName) //day danh sach game vao vector
{
	string fileGameName; //ten cua cac game da luu trong danh sach

	ifstream saveGameNametoList;
	saveGameNametoList.open(fileName);

	if (!saveGameNametoList.is_open()) {
		cout << text.ErrorRead << endl;
	}

	while (getline(saveGameNametoList, fileGameName)) {
		ListFileGameName.push_back(fileGameName);
	}
	saveGameNametoList.close();

}

void LoadGame(string filename) {
	system("cls");
	system("color F0");
	SetColor(0, 15);
	ShowCur(true);
	// Kiểm tra xem file có tồn tại không
	if (!CheckFileExistence(filename)) {
		cout << text.ErrorLoad << endl;
		return; // Thoát nếu file không tồn tại
	}

	LoadData(filename);

	// Kiểm tra lại _A có được cập nhật không
	if (_A[0][0].c == -1 && _A[0][0].x == 0 && _A[0][0].y == 0) {
		cout << text.ErrorData << endl;
		return; // Thoát nếu không có dữ liệu
	}

	GotoXY(_X, _Y);
}

void ChooseLoadFunction()
{

	SetColor(0, 15);
	const string LoadFunction[3] = { text.L, text.D, text.R };


	ShowCur(true);

	while (true) {
		SetColor(0, 15);
		int choiceload = menu(LoadFunction, 3, 97, 17);
		if (choiceload == -1) { // Go back to game
			system("cls");
			MainMenu();
			return;
		}

		switch (choiceload) {
		case 0:
		{
			loadGameFunction();
			break;
		}
		case 1:
			deleteGameFunction();
			break;
		case 2:
			changeGameNameFunction();
			break;
		default:
			break;
		}
	}
}

void handleFullSaveNewGame()
{

	drawSave();
	vechuSAVE(10, 2);
	Box(30, 32, 84, 4);
	GotoXY(40, 33);
	SetColor(4, 15);
	cout << text.maxsave << MAX_SAVE_FILES << text.maxsave1 << endl;
	SetColor(0, 15);
	const string LoadFunction[2] = { text.D, text.S };

	ShowCur(true);

	while (true) {
		SetColor(0, 15);
		int choiceload = menu(LoadFunction, 2, 97, 18);

		if (choiceload == -1) { // Go back to game
			system("cls");
			DrawLoaded(_A);
			GotoXY(_X, _Y);
			if (choicegame == 0) {//PvP
				if (choicestyle == 0)//basic
				{
					GamePlayPvP();
				}
				else
				{
					GamePlayTimerLoadPvP();
				}
			}
			else {
				{//PvC
					if (choicestyle == 0)//basic
					{
						HardGamePlayPvC();
					}
					else
					{
						HardGamePlayTimerLoadPvC();
					}
				}
			}

		}
		switch (choiceload) {
		case 0:
			SetConsoleOutputCP(CP_UTF8);
			GotoXY(33, 33); SetColor(15, 15);
			cout << u8"██████████████████████████████████████████████████████████████████████████████";
			SetConsoleOutputCP(437);
			SetColor(0, 15);
			deleteGameFunction();
			SaveGame();
			break;
		case 1:
			system("cls");
			MainMenu();
			break;
		default:
			break;
		}
	}
}