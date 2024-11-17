#include "Menu.h"
#include "Draw.h"
#include "Help.h"
int menu(const string items[], int itemCount, int startX, int startY) {
    int x = startX;
    int y = startY;
    ShowCur(false);

    int w = 17;  // Menu box width
    int h = 2;   // Menu box height
    int b_color = 240;      // Background color
    int b_color_sang = 252; // Highlight color

    // Display menu items
    for (int i = 0; i < itemCount; i++) {
        Box_Menu(x, y + i * (h + 1), w, h, items[i]);
    }

    int xp = x;  // Current selection
    int yp = y;
    int xcu = xp; // Previous position
    int ycu = yp;
    bool kt = true;

    while (true) {
        if (kt == true) {
            GotoXY(xcu, ycu);
            TextHighlight(xcu, ycu, w, h, b_color, items[(ycu - y) / (h + 1)]);
            xcu = xp;
            ycu = yp;
            TextHighlight(xp, yp, w, h, b_color_sang, items[(yp - y) / (h + 1)]);
            kt = false;
        }

        if (_kbhit()) {
            char _COMMAND = toupper(_getch());
            kt = true;

            if (_COMMAND == 'W') { // Move up
                playMoveSound();
                if (yp != y)
                    yp -= (h + 1);
                else
                    yp = y + (h + 1) * (itemCount - 1);
            }
            else if (_COMMAND == 'S') { // Move down
                playMoveSound();
                if (yp != y + (h + 1) * (itemCount - 1))
                    yp += (h + 1);
                else
                    yp = y;
            }
            else if (_COMMAND == 'B') { // Return to previous screen
                ShowCur(true);
                return -1;
            }
            else if (_COMMAND == 13) { // Enter key
                playSelectSound();
                int index = (yp - y) / (h + 1);
                ShowCur(true);
                return index;
            }
        }
    }
    ShowCur(true);
}

void ChooseGamePlay()
{
 
    DrawBackground();
    SetColor(0, 15);
    GotoXY(66, 10);
    cout << text.choseGamePlay;
    const string GamePlay[] = { "PvP", "PvC"};
  
    DrawBound();
    Draw_Guide(43, 35, text.moveUpText + ", " + text.moveDownText + ", " + text.selectText + ", " + text.goBackText);
    ShowCur(true);

    while (true) {
        SetColor(0, 15);
        int choice = menu(GamePlay, 2, 63, 15);

        if (choice == -1) { // Go back to game
            system("cls");
            MainMenu();
            return;
        }

        switch (choice) {
        case 0:
            system("cls");
            InputPvP(42, 15, 60, 6);
            ResetData();
            StartGame();
            GamePlayPvP();
           
            break;

        case 1:
            system("cls");
            InputPvC(42, 15, 60, 6);
            ResetData();
            StartGame();
            GamePlayPvC();
            break;
        default:
            break;
        }
    }
}

void MainMenu() {
    DrawScreen();
    const string mainMenuItems[] = { text.newGameText, text.loadGameText,text.settingText, text.helpText, text.aboutText,text.exit };
    while (true) {
        int choice = menu(mainMenuItems, 6, 63, 15);

        switch (choice) {
        case 0:
            system("cls");
            ChooseGamePlay();
            break;
        case 1:
            system("cls");
            Savegame_opt();
            break;
        case 2:
            system("cls");
            Setting();
            DrawScreen();
            MainMenu(); // goi vay de sau khi thoat ra tu setting no se chinh sang tieng anh cho menu
            break;
        case 3:
            system("cls");
            Help(30, 10, 80, 20);
            DrawScreen();
            break;
        case 4:
            system("cls");
            About(30, 10, 80, 20);
            DrawScreen();
            break;
        case 5:
            exit(0);
            system("pause");
            return;
        default:
            break;
        }
    }
}

// In-game Sub Menu function
void SubMenu() {
    const string subMenuItems[] = { text.newGameText, text.save, text.settingText, text.helpText ," Menu" };
    SetColor(0, 15);
    DrawBound();
    Draw_Guide(52, 35, text.moveUpText + ", " + text.moveDownText + ", " + text.selectText + ", " + text.goBackText);
    ShowCur(true);

    while (true) {
        SetColor(0, 15);
        int choice = menu(subMenuItems, 5, 70, 15);
     
        if (choice == -1) { // Go back to game
            system("cls");
            return;
        }

        switch (choice) {
        case 0:
            if (AskSaveGame() == 'Y') {
                SaveGame();
                system("cls");
                ChooseGamePlay();
                break;
            }
            else {
                system("cls");
                ChooseGamePlay();
                break;
              //  DrawLoaded(_A);
               // SubMenu();
               // DrawLoaded(_A);
            }
          
        case 1:
            system("cls");
            SaveGame();

            break;
        case 2:
            system("cls");
            Setting();
            Draw_Guide(52, 35, text.moveUpText + ", " + text.moveDownText + ", " + text.selectText + ", " + text.goBackText);
           // SubMenu();
            DrawLoaded(_A);
            
            break;
        case 3:
            system("cls");
            Help(5, 10, 80, 20);
            Draw_Guide(52, 35, text.moveUpText + ", " + text.moveDownText + ", " + text.selectText + ", " + text.goBackText);
            DrawLoaded(_A);
            break;
        case 4:
            if (AskSaveGame() == 'Y') {
                SaveGame();
                MainMenu();
                break;
            }
            else {
                system("cls");
                MainMenu();
                break;
            }

        default:
            break;
        }
    }
}


