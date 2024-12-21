#pragma once
#include "Game.h"
#include "Setting.h"
#include "About.h"
#include "SaveLoad.h"
extern int choicestyle;
extern int choicegame;
int menu(const string items[], int itemCount, int startX, int startY);
void MainMenu();
void SubMenu();
void ChooseGame();
void ChoosePvPStyle();
void ChoosePvCStyle();
void EasyChoosePvCStyle();
void HardChoosePvPStyle();




