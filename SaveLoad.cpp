#include "SaveLoad.h"
#include "Draw.h"


void SaveData(string filename) {
	ofstream savefile;
	savefile.open(filename, ios::out);
	if (!savefile.is_open()) {
		cout << "Không thể mở file Gamelist.txt!" << endl;
		return ;
	}

	savefile << Player_1.Name << endl;
	savefile << Player_1.Moves << endl;
	savefile << Player_1.Wins << endl;
	savefile << Player_1.Character << endl;
	savefile << Player_2.Name << endl;
	savefile << Player_2.Moves << endl;
	savefile << Player_2.Wins << endl;
	savefile << Player_2.Character << endl;
	savefile << _TURN << endl;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			savefile << _A[i][j].c << " ";
		}
		savefile << endl;
	}
	savefile.close();
}

void Savegame_opt() {
	system("cls");
	system("color F0");
	DrawBound();
	ShowCur(true);
	string filename;
	vector<string> files = LoadFiles();

	int j = 12;
	GotoXY(50, 10);
	cout << "Danh sach file game da luu: ";
	for (int i = 0; i < files.size(); i++) {
		GotoXY(50, j);
		cout << files[i];
		j++;
	}

	GotoXY(50, j);
	
	
	//cout << "";
	cout << "Nhap ten file ban muon tai: ";
	//cin.ignore();
	getline(cin, filename);
	if (filename.substr(filename.length() - 4) != ".txt") {
		filename += ".txt";
	}

	if (!CheckFileExistence(filename)) {
		cout << "File khong ton tai!" << endl;
		system("pause");
		system("cls");
		MainMenu();
		return; // Thoát nếu file không tồn tại
	}

	LoadGame(filename);
	DrawLoaded(_A);
	GotoXY(_X, _Y);
	GamePlayPvP();
}
void SaveGame() {
	string filename;
	int i = 2;
	system("cls");
	system("color F0");
	DrawBound();
	GotoXY(50, 35);
	SetColor(0, 15);

	
	cout << "Enter game's name: ";
	//cin.ignore();
	do {
		
		getline(cin, filename);
		filename += ".txt";
		if (!CheckFileExistence(filename)) {
			Draw_Guide(56, 35, "Save succesfully.            ");
			cout << endl;
			break;
		}
		else {
			GotoXY(50, 15 + i);
			cout << "Enter another name: ";
			i += 2;
		}
	} while (1);

	SaveData(filename);

	ofstream savedfile;

	savedfile.open("Gamelist.txt", ios::app);
	savedfile << filename << endl;
	savedfile.close();
	system("pause");
	system("cls");
	MainMenu();
}
bool CheckFileExistence(string filename) {
	string name;
	ifstream savedfile("Gamelist.txt");

	// Kiểm tra xem file có mở thành công không
	if (!savedfile.is_open()) {
		cout << "Khong the mo file Gamelist.txt!" << endl;
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
void LoadData(string filename) {
	ifstream loadfile;
	loadfile.open(filename, ios::in);

	// Kiểm tra xem file có mở thành công không
	if (!loadfile.is_open()) {
		cout << "Khong the mo file: " << filename << endl;
		return; // Thoát khỏi hàm nếu không mở được file
	}

	int turn;
	Player P[2];

	for (int i = 0; i < 2; i++) {
		string name = "";
		int moves = 0;
		int wins = 0;
		string character = "";

		if (i == 1) {
			loadfile.ignore(); // Bỏ qua dòng trước đó nếu cần
		}
		getline(loadfile, name);
		loadfile >> moves >> wins;
		getline(loadfile, character);
		P[i].Name = name;
		P[i].Moves = moves;
		P[i].Wins = wins;
		P[i].Character = character;
	}

	loadfile >> turn;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			int x = 0;
			if (!(loadfile >> x)) {
				cout << "Loi khi doc du lieu tu file22!" << endl;
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

	loadfile.close();
	_COMMAND = -1;
	_X = _A[0][0].x;
	_Y = _A[0][0].y;
}

vector<string> LoadFiles() {
	vector<string> files;
	string filename;

	ifstream savedFile("Gamelist.txt");
	// Kiểm tra xem file có mở thành công không
	if (!savedFile.is_open()) {
		cout << "Khong the mo fiele file Gamelist.txt!" << endl;
		return files; // Trả về danh sách rỗng
	}

	while (getline(savedFile, filename)) {
		files.push_back(filename);
	}
	savedFile.close();

	return files;
}
void LoadGame(string filename) {
	system("cls");
	system("color F0");
	SetColor(0, 15);
	ShowCur(true);
	// Kiểm tra xem file có tồn tại không
	if (!CheckFileExistence(filename)) {
		cout << "File khong ton tai!" << endl;
		return; // Thoát nếu file không tồn tại
	}

	LoadData(filename);

	// Kiểm tra lại _A có được cập nhật không
	if (_A[0][0].c == -1 && _A[0][0].x == 0 && _A[0][0].y == 0) {
		cout << "Khong co du lieu de tai!" << endl;
		return; // Thoát nếu không có dữ liệu
	}

	GotoXY(_X, _Y);
}