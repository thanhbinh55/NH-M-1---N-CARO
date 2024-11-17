#pragma once
#include "Game.h"
#include "Setting.h"
#include "About.h"
#include "SaveLoad.h"

int menu(const string items[], int itemCount, int startX, int startY);
void MainMenu();
void SubMenu();
void ChooseGamePlay();