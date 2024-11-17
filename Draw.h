#pragma once
#include "Game.h"
#include "LanguageText.h"

void DrawScreen();
void SSetColor(int mauBg, int mauchu);
void DrawRedDragon(int x, int y);
void DrawPikachu(int x, int y);
void DrawBlueBoom(int x, int y);
void DrawBlackBoom(int x, int y);
void DrawRedBoom(int x, int y);
void DrawYellowBoom(int x, int y);
void DrawGreenBoom(int x, int y);
void DrawPig(int x, int y);
void DrawDragonWomen(int x, int y);
void DrawDragonMen(int x, int y);
void DrawLogoCaro(int x, int y);
void DrawDRAW(int x, int y);
void DrawWIN(int x, int y);
void drawSelectionBox(int x, int y, int color);
void clearSelectionBox(int x, int y);
void ChooseAvatar();
void DrawChooseAvatar(const Player& Player, int x, int y);
void vechuW(int x, int y);
void vechuI(int x, int y);
void vechuN(int x, int y);
void vechuX(int x, int y);
void vechuO(int x, int y);
void Owin(int x, int y);
void Xwin(int x, int y);
void vechuwin(int x, int y);
void nhapnhayO(int x, int y);
void nhapnhayX(int x, int y);
void nhapnhayDRAW(int x, int y);
void bangtrang(int x, int y);
void DrawBackground();
void DrawLoaded(_POINT _A[][BOARD_SIZE]);
void Draw_infor(int x, int y, int w, int h);
void Draw_infor1(int x, int y, int w, int h);
void HiglightTurn(int x, int y);