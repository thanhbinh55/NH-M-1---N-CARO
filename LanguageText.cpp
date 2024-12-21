#include "LanguageText.h"

LanguageText text;
void InitializeText() {
    if (currentLanguage == ENGLISH) {
        text.newGameText = " NEW GAME";
        text.loadGameText = "  LOAD GAME";
        text.settingText = " SETTING";
        text.helpText = " HELP";
        text.aboutText = " ABOUT";
        text.exit = " EXIT";
        text.save = "SAVE GAME";
        text.exitText = "'ESC': Pause";
        text.saveText = "'L': Save Game";
        text.inputText = "Enter name from keyboard";
        text.nameText1 = "Enter Player 1 name (less than 10 characters): ";
        text.nameText2 = "Enter Player 2 name (less than 10 characters): ";
        text.movesText = "Moves: ";
        text.winsText = "Wins: ";
        text.onText = "On          ";
        text.offText = "Off         ";
        text.backgroundSoundText = "BACKGROUND SOUND: ";
        text.soundEffectText = "SOUND EFFECT: ";
        text.languageText = "LANGUAGE: ";
        text.aboutText = "ABOUT";
        text.askContinueText = "Do you want to continue? (Y/N)";
        text.askSaveGameText = "Do you want to save Game? (Y/N)";
        text.errorYN = "Enter 'Y' or 'N'.";
        text.moveLeftText = "'A': Move left";
        text.moveRightText = "'D': Move right";
        text.moveUpText = "'W': Move up";
        text.moveDownText = "'S': Move down";
        text.selectText = "'Enter': Select";
        text.goBackText = "'B': Go Back";
        text.undoText = "'Z': Undo";

        text.menuGuideText = "GAME GUIDE:";
        text.menuInstructions1 = "- PLAYER VS PLAYER MODE:\n";
        text.menuInstructions2 = "+ Two players take turns moving and placing pieces on the board.\n";
        text.menuInstructions3 = "+ Use the keys A, W, S, D to move and press ENTER to place a piece.\n";
        text.menuInstructions4 = "+ First align 5 pieces in a row (horizontally,vertically,diagonally) wins.";

        text.menuInstructions5 = "- PLAYER VS COMPUTER MODE:\n:";
        text.menuInstructions6 = "+ The player and the computer take turns moving and placing pieces.\n";
        text.menuInstructions7 = "+ The player uses keys A, W, S, D to move and presses ENTER to place a piece.\n";
        text.menuInstructions8 = "+ The computer will calculate and place its pieces after the player's turn.\n";
        text.menuInstructions9 = "+ First align 5 pieces in a row (horizontally,vertically,diagonally) wins.";

        text.gameGuideText = "- TIMED MODE:";
        text.gameInstructions1 = "+ The match has a total duration of 300 seconds.\n";
        text.gameInstructions2 = "+ Each player (computer) has a maximum of 15 seconds per turn to make a move.\n";
        text.gameInstructions3 = "+ If player not make a move within 15 seconds, the turn will pass to opponent.\n";
        text.gameInstructions4 = "+ If no winner is determined after 300 seconds, the match ends in a draw.";

        text.choseGamePlay = "CHOSE GAME";
        text.choseGameStyle = "CHOSE GAME STYLE";
        text.gamemode = "MODE: ";
        text.gamestyle = "STYLE: ";
        text.gametime = "GAME's TIME: ";
        text.turntime = "TURN's TIME: ";
        text.basicStyle = "BASIC";
        text.speedUpStyle = "SPEED";

        text.ErrorGetName = "Error: Name must be different from Player 1, again!";
        //bang thong bao
        text.name = "NAME";
        text.score = "SCORE";
        text.move = "MOVE";
        text.player = "PLAYER";
        text.announce = "WON THIS GAME";
        text.announce1 = " DRAW ";

        text.choosecharacter = "Choose successfully!";

        //saveload
        text.ErrorFile = "Cannot open file with the saved name!";
        text.entername = "ENTER GAME'S NAME (not enter '.txt'): ";
        text.Errorname = "GAME'S NAME IS NOT VALID! PLEASE ENTER AGAIN (maximum 10 characters): ";
        text.nameexist = "NAME IS EXISTED, PLEASE ENTER ANOTHER NAME (not enter '.txt': ";

        text.savemode = "Save successfully.";
        text.gameExiting = "Name game existed!!!, Enter another name: ";
        text.gameList = "Cannot open Gamelist.txt file!";
        text.List = "SAVED GAME LIST";
        text.Loadmode = "ENTER THE GAME YOU WANT TO LOAD: ";
        text.LoadExist = "NAME NOT EXISTED!!!           ";
        // text.LoadExist = "EXIST";

         //Delete
        text.Deletename = "ENTER THE GAME YOU WANT TO DELETE: ";
        text.Deletefile = "DELETE FILE SUCCESSFULLY FROM THE SYSTEM: ";
        text.DeleteExist = "CANNOT DELETE FILE FROM THE SYSTEM!!!           ";

        //Rename
        text.Rename = "ENTER THE GAME YOU WANT TO CHANGE: ";
        text.Newgame = "ENTER THE NEW NAME: ";
        text.Changed = "CHANGE NEW NAME SUCCESSFULLY: ";
        text.Changedmode = "Cannot open the game name file to load the data!!! ";
        text.Error = "Error when read the data from game name file!";
        text.ErrorRead = "Cannot open Gamelist.txt file to take the name game list!";

        text.ErrorLoad = "File not existed!";
        text.ErrorData = "No data to load!";
        text.maxsave = "Saved files reached limit (";
        text.maxsave1 = "). Please delete some saved files to continue.";

        text.L = "LOAD";
        text.D = "DELETE";
        text.R = "RENAME";
        text.S = "CANCEL SAVE";

        text.volume = "Volume: ";
    }
    else { // VIETNAMESE
        text.newGameText = " TRO CHOI MOI";
        text.loadGameText = " TAI TRO CHOI";
        text.settingText = "CAI DAT";
        text.helpText = " HUONG DAN";
        text.aboutText = "THONG TIN";
        text.exit = "THOAT";
        text.save = " LUU TRO CHOI";
        text.exitText = "'ESC': Tam dung";
        text.saveText = "'L': Luu Tro Choi";
        text.inputText = "Nhap ky tu tu ban phim:";
        text.nameText1 = "Nhap ten nguoi choi 1 (it hon 10 ky tu): ";
        text.nameText2 = "Nhap ten nguoi choi 2 (it hon 10 ky tu): ";
        text.movesText = "So Nuoc Di: ";
        text.winsText = "So Tran Thang: ";
        text.onText = "Bat           ";
        text.offText = "Tat           ";
        text.backgroundSoundText = "NHAC NEN: ";
        text.soundEffectText = "HIEU UNG AM THANH: ";
        text.languageText = "NGON NGU: ";
        text.askContinueText = "Ban co muon tiep tuc tro choi? (Y/N)";
        text.askSaveGameText = "Ban co muon luu tro choi? (Y/N)      ";
        text.errorYN = "Vui long nhap 'Y' hoac 'N'.";
        text.moveLeftText = "'A': Trai";
        text.moveRightText = "'D': Phai";
        text.moveUpText = "'W': Len tren";
        text.moveDownText = "'S': Xuong duoi";
        text.selectText = "'ENTER': Chon";
        text.goBackText = "'B': Quay Lai";
        text.undoText = "'Z': Hoan tac";

        //Help
        text.menuGuideText = "HUONG DAN CHOI GAME:";
        text.menuInstructions1 = "- CHE DO CHE DO CHOI PVP (NGUOI VOI NGUOI):\n";
        text.menuInstructions2 = "+ Hai nguoi choi lan luot di chuyen va dat quan tren ban co.\n";
        text.menuInstructions3 = "+ Su dung cac phim A, W, S, D de di chuyen va nhan ENTER de dat quan.\n";
        text.menuInstructions4 = "+ Ben nao dat duoc 5 quan lien tiep (ngang, doc, cheo) se gianh chien thang.";

        text.menuInstructions5 = "- CHE DO CHE DO CHOI PVC (NGUOI VOI MAY)\n:";
        text.menuInstructions6 = "+ Nguoi choi va may lan luot di chuyen va dat quan tren ban co.\n";
        text.menuInstructions7 = "+ Nguoi choi su dung cac phim A, W, S, D de di chuyen, nhan ENTER de dat quan.\n";
        text.menuInstructions8 = "+ May se tu dong tinh toan va dat quan sau moi luot cua nguoi choi.\n";
        text.menuInstructions9 = "+ Ben nao dat duoc 5 quan lien tiep(ngang, doc, cheo) se gianh chien thang.";

        text.gameGuideText = "- CHE DO THOI GIAN:";
        text.gameInstructions1 = "+ Tran dau co tong cong 300 giay de hoan thanh.\n";
        text.gameInstructions2 = "+ Moi nguoi choi (hoac may) co toi da 15 giay de thuc hien nuoc di cua minh.\n";
        text.gameInstructions3 = "+ Neu het 15 giay ma khong thuc hien nuoc di, se chuyen sang luot doi phuong.\n";
        text.gameInstructions4 = "+ Neu het 300 giay ma khong co nguoi chien thang, tran dau se hoa va ket thuc.";


        text.choseGamePlay = "CHON CHE DO CHOI";
        text.choseGameStyle = "CHON CHE DO CHOI";
        text.gamemode = "CHE DO: ";
        text.gamestyle = "THE LOAI: ";
        text.gametime = "THOI GIAN: ";
        text.turntime = "LUOT DANH: ";
        text.basicStyle = "CO BAN";
        text.speedUpStyle = "TOC DO";

        text.ErrorGetName = "Loi! Vui long nhap ten khac nguoi choi 1";

        //bang thong bao
        text.name = "TEN: ";
        text.score = "DIEM: ";
        text.move = "BUOC DI CHUYEN: ";
        text.player = "NGUOI CHOI";
        text.announce = "CHIEN THANG TRO CHOI";
        text.announce1 = " HOA ";

        text.choosecharacter = "Chon thanh cong!";

        //saveload
        text.ErrorFile = "Khong the mo file voi ten game vua luu!";
        text.Errorname = "TEN GAME KHONG HOP LE! VUI LONG NHAP LAI (toi da 10 ky tu): ";
        text.nameexist = "TEN DA TON TAI, VUI LONG NHAP TEN GAME KHAC (khong can nhap duoi '.txt'): ";

        text.entername = "NHAP TEN GAME (khong can nhap duoi '.txt'): ";
        text.savemode = "Luu thanh cong.";
        text.gameExiting = "Ten tro choi da ton tai!!!, Vui long nhap ten khac: ";
        text.gameList = "Khong the mo file Gamelist.txt!";
        text.List = "DANH SACH GAME DA LUU";
        text.Loadmode = "NHAP TEN GAME BAN MUON TAI: ";
        text.LoadExist = "TEN KHONG TON TAI!!!           ";
        text.Exist = "TON TAI";

        //Delete
        text.Deletename = "NHAP TEN GAME BAN MUON XOA: ";
        text.Deletefile = "FILE DA DUOC XOA KHOI HE THONG: ";
        text.DeleteExist = "KHONG THE XOA FILE KHOI HE THONG!!!               ";

        //Rename
        text.Rename = "NHAP TEN GAME BAN MUON THAY DOI: ";
        text.Newgame = "NHAP TEN GAME MOI: ";
        text.Changed = "DA THAY DOI TEN MOI: ";
        text.Changedmode = "Khong the mo file game name de tai du lieu cho van dau!!! ";
        text.Error = "Loi khi doc du lieu cua ban co tu file game name!";
        text.ErrorRead = "Khong the mo file Gamelist.txt de lay danh sach ten game!";

        text.ErrorLoad = "File khong ton tai!";
        text.ErrorData = "Khong co du lieu de tai!";
        text.maxsave = "Da dat gioi han file luu (";
        text.maxsave1 = "). Vui long xoa bot file luu de tiep tuc.";

        text.L = "TAI";
        text.D = "XOA";
        text.R = "DOI TEN";
        text.S = "HUY LUU";

        text.volume = "Am luong: ";
    }
}
void ToggleLanguage() {
    currentLanguage = (currentLanguage == ENGLISH) ? VIETNAMESE : ENGLISH;
    InitializeText();
}

