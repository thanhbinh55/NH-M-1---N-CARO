#pragma once
#ifndef CARO_GAME_H
#define CARO_GAME_H

#include <iostream>
#include <vector>
#include "fstream"
#include <string>
#include <cstdlib>
#include <conio.h> 
#include <windows.h> 
#include <thread> // Thư viện để sử dụng std::this_thread::sleep_for
#include <chrono> // Thư viện cho thời gian
#include <mutex>
#include <algorithm>
#include <cmath>
//#include "playgame.h"
using namespace std;

#define BOARD_SIZE 15 // Kích thước ma trận bàn cờ
#define LEFT 3        // Tọa độ trái màn hình bàn cờ
#define TOP 3         // Tọa độ trên màn hình bàn cờ
#define MAX_DEPTH 2 // Độ sâu tìm kiếm
#define MAXTIMEGAME 300
#define MAXTIMETURN 15
// Khai báo kiểu dữ liệu
struct _POINT {
    int x, y, c; // x: tọa độ dòng, y: tọa độ cột, c: đánh dấu (-1, 1 hoặc 0)
    char value;
};

// Khai báo biến toàn cục
extern _POINT _A[BOARD_SIZE][BOARD_SIZE]; // Ma trận bàn cờ
extern bool _TURN; // Lượt người chơi: true là người thứ nhất, false là người thứ hai
extern int _COMMAND; // Biến nhận giá trị phím người dùng nhập
extern int _X, _Y;   // Tọa độ hiện hành trên màn hình bàn cờ
// Khai báo kiểu dữ liệu người chơi
struct Player {
    string Name;
    int Moves; // Số bước di chuyển
    int Wins ;  // Số lượt thắng
    string Character;
};
// Biến người chơi toàn cục
extern Player Player_1, Player_2;
extern int choicestyle;

extern int choicegame;
void Thong_so_Players(int n); // Nhập thông tin người chơi
void In_thong_so_Player(int n); // In thông tin người chơi
void So_buoc_di_chuyen(); // In số bước di chuyển
void So_lan_thang(); // In số lần thắng

// Hàm nhóm View (Hiển thị)
void ShowCur(bool CursorVisibility);// Hàm ẩn hoặc hiện con trỏ
void SetTextColor(int color);
void SetColor(int textColor, int bgColor);
void TextHighlight(int x, int y, int w, int h, int b_color_sang, string nd);
void FixConsoleWindow();
void GotoXY(int x, int y);
//ve
void Draw_Guide(int x, int y, string nd);
void DrawGuideGame(int x, int y);
void DrawBoard(int pSize);
void DrawBound();
void Box(int x, int y, int w, int h);
void Box_Menu(int x, int y, int w, int h, string nd);
void Draw_infor(int x, int y, int w, int h, const Player& player);
void Draw_infor2(int x, int y, int w, int h, const Player& player);
void drawBlock(int x, int y, int color);
void LogoCaro(int startX, int startY);
void printLogo(int x);
void DrawLOSE(int x, int y);
//void DrawWIN(int startX, int startY);
void MainMenu();
//int menu();
int menu(const string items[], int itemCount, int startX = 68, int startY = 15);
void SubMenu();
void Help(int x, int y, int w, int h);
void Setting();
void DrawScreen();
// Hàm nhóm Model (Xử lý dữ liệu)
void ResetData();
int CheckBoard(int pX, int pY); // Đánh dấu vào bàn cờ
int TestBoard(); // Kiểm tra kết quả bàn cờ
bool checkWin(int x, int y); // Kiểm tra điều kiện thắng
bool isDraw(); // Kiểm tra điều kiện hòa
void MenuReturn();
void ResetGame();
void ResetGameInOneGame();
void ExitGame();
// Hàm nhóm Control (Điều khiển trò chơi)
void StartGame();
void StartGameInOneGame();
void MoveRight();
void MoveLeft();
void MoveDown();
void MoveUp();
int AskContinue(); // Hỏi người chơi có tiếp tục hay không
int AskSaveGame();
int ProcessFinish(int pWhoWin); // Xử lý kết quả sau khi kết thúc ván
void InputPvC(int x, int y, int w, int h);
void InputPvP(int x, int y, int w, int h);
void EasyGamePlayPvC();
void HardGamePlayPvC();
void GamePlayPvP();
void GamePlayTimerPvP();
void HardGamePlayTimerPvC();
void EasyGamePlayTimerPvC();
void GamePlayTimerLoadPvP();
void EasyGamePlayTimerLoadPvC();//dung de xu ly van de thoi gian khi choi che do tai lai game
void HardGamePlayTimerLoadPvC();

#endif
