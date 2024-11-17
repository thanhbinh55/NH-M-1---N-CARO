#include "LanguageText.h"

// Define global variables here (only in the .cpp file)
LanguageText text;
//Language currentLanguage = ENGLISH;

void InitializeText() {
    if (currentLanguage == ENGLISH) {
        text.newGameText = " New Game";
        text.loadGameText = " Load Game";
        text.settingText = " Setting";
        text.helpText = " Help";
        text.aboutText = " About";
        text.exit = " Exit";
        text.save = "Save Game";
        text.exitText = "'ESC': Pause";
        text.saveText = "'L': Save Game";
        text.inputText = "Enter name from keyboard";
        text.nameText1 = "Enter Player 1 name (less than 10 characters): ";
        text.nameText2 = "Enter Player 2 name (less than 10 characters): ";
        text.movesText = "Moves: ";
        text.winsText = "Wins: ";
        text.onText = "On          ";
        text.offText = "Off          ";
        text.backgroundSoundText = "BACKGROUND SOUND: ";
        text.soundEffectText = "SOUND EFFECT: ";
        text.languageText = "LANGUAGE: ";
        text.aboutText = "About";
        text.askContinueText = "Do you want to continue? (Y/N)";
        text.askSaveGameText = "Do you want to save the Game? (Y/N)";
        text.moveLeftText = "'A': Move left";
        text.moveRightText = "'D': Move right";
        text.moveUpText = "'W': Move up";
        text.moveDownText = "'S': Move down";
        text.selectText = "'Enter': Select";
        text.goBackText = "'B': Go Back";

        text.menuGuideText = "MENU GUIDE:";
        text.menuInstructions1 = "+ Use W or S to navigate through options.\n";
        text.menuInstructions2 = "+ Press Enter to select an option.\n";
        text.menuInstructions3 = "+ Press Esc to show the menu.";

        text.gameGuideText = "GAME GUIDE:";
        text.gameInstructions1 = "+ Use A, W, S, D to move the cursor.\n";
        text.gameInstructions2 = "+ Press ENTER to place a piece.\n";
        text.gameInstructions3 = "+ The first player to align 5 pieces in a row, column, or diagonal wins.";

        text.choseGamePlay= "CHOOSE GAME";

    }
    else { // VIETNAMESE
        text.newGameText = "Tro Choi Moi";
        text.loadGameText = "Tai Tro Choi";
        text.settingText = "Cai Dat";
        text.helpText = "Huong Dan";
        text.aboutText = "Thong tin";
        text.exit = "Thoat";
        text.save = "Luu Tro choi";
        text.exitText = "'ESC': Tam dung";
        text.saveText = "'L': Luu Tro Choi";
        text.inputText = "Nhap ky tu tu ban phim:";
        text.nameText1 = "Nhap ten nguoi choi 1 (it hon 10 ky tu): ";
        text.nameText2 = "Nhap ten nguoi choi 2 (it hon 10 ky tu): ";
        text.movesText = "So Nuoc Di: ";
        text.winsText = "So Tran Thang: ";
        text.onText = "Bat           ";
        text.offText = "Tat            ";
        text.backgroundSoundText = "NHAC NEN: ";
        text.soundEffectText = "HIEU UNG AM THANH: ";
        text.languageText = "NGON NGU: ";
        text.aboutText = "Gioi Thieu";
        text.askContinueText = "Ban co muon tiep tuc tro choi? (Y/N)";
        text.askSaveGameText = "Ban co muon luu tro choi? (Y/N)";
        text.moveLeftText = "'A': Trai";
        text.moveRightText = "'D': Phai";
        text.moveUpText = "'W': Len tren";
        text.moveDownText = "'S': Xuong duoi";
        text.selectText = "'ENTER': Chon";
        text.goBackText = "'B': Quay Lai";
        text.menuGuideText = "HUONG DAN THAO TAC VOI MENU:";
        text.menuInstructions1 = "+ Su dung phim W hoac S de lua chon chuc nang.\n";
        text.menuInstructions2 = "+ Nhan Enter de chon chuc nang.\n";
        text.menuInstructions3 = "+ Nhan Esc de hien thi menu.";

        text.gameGuideText = "HUONG DAN CHOI GAME:";
        text.gameInstructions1 = "+ Su dung cac phim A, W, S, D de di chuyen.\n";
        text.gameInstructions2 = "+ Nhan ENTER de dat quan.\n";
        text.gameInstructions3 = "+ Ben nao dat duoc 5 quan lien tiep se chien thang.";


        text.choseGamePlay = "CHON CHE DO CHOI";
    }
}
void ToggleLanguage() {
    // Switch between ENGLISH and VIETNAMESE
    currentLanguage = (currentLanguage == ENGLISH) ? VIETNAMESE : ENGLISH;
    InitializeText(); // Update text strings based on the selected language
}

