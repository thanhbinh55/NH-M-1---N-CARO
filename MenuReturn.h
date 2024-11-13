#pragma once
#include "Game.h"
#include "SoundManager.h"
#include "SaveLoad.h"
#include"DrawDragon.h"

//
//void MenuReturn() {
//	//LogoCaro(52, 5);
//	system("cls");
//	DrawBound(1, 1, 38, 150);
//	Draw_Guide(56, 35, "'W': Move up, 'S': Move down, 'Enter': Select, 'B': Go Back");
//	DrawDragonWomen(107, 15);
//	DrawDragonMen(15, 15);
//	int choice = menu();
//	ShowCur(true);
//	switch (choice)
//	{
//	case 0:
//		system("cls");
//		InputPvP(45, 15, 60, 6);
//		ResetData();
//		StartGame();
//		GamePlayPvP();
//		break;
//	case 1: //Load game
//		system("cls");
//		Savegame_opt();
//		break;
//	case 2:
//		system("cls");
//		Setting();
//		break;
//	case 3:
//		system("cls");
//		Help(10, 10, 80, 20);
//	case 4:
//		exit(0);
//		system("pause");
//		return;
//	}
//
//	system("pause");
//}


void MenuReturn() {
    // Draw decorative elements like borders and guidelines
    system("cls");
    DrawBound();
    Draw_Guide(56, 35, "'W': Move up, 'S': Move down, 'Enter': Select, 'B': Go Back");
    DrawDragonWomen(107, 15);
    DrawDragonMen(15, 15);

    // Define menu items for MenuReturn
    const string returnMenuItems[] = { " New Game", " Load Game", " Setting", " Help", " Exit" };

    // Call menu function and get user choice
    int choice = menu(returnMenuItems, 5);

    ShowCur(true); // Show cursor if needed for further inputs

    switch (choice) {
    case 0:  // New Game
        system("cls");
        InputPvP(45, 15, 60, 6);
        ResetData();
        StartGame();
        GamePlayPvP();
        break;
    case 1:  // Load game
        system("cls");
        Savegame_opt();
        break;
    case 2:  // Setting
        system("cls");
        Setting();
        break;
    case 3:  // Help
        system("cls");
        Help(10, 10, 80, 20);
        break;
    case 4:  // Exit
        exit(0);
    }

    system("pause");
}
