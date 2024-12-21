#include"Setting.h"
#include "Draw.h"


void boxSetting(int x, int y, int w, int h, int currentOption, bool& backgroundSound, bool& soundEffect) {
    SetColor(0, 15);
    Box(x + 35, y, w, h);
    GotoXY(x + 35 + 2, y + 11);
    // Hiển thị trạng thái âm thanh nền
    GotoXY(x + 35 + 2, y + 2);
    std::cout << text.backgroundSoundText << ": "; // Sử dụng biến từ LanguageText
    if (currentOption == 0) {
        SetColor(15, 0);
        std::cout << (a1 == 0 ? text.offText : text.onText);
        SetColor(0, 15);
    }
    else {
        std::cout << (a1 == 0 ? text.offText : text.onText);
    }

    // Hiển thị trạng thái hiệu ứng âm thanh
    GotoXY(x + 35 + 2, y + 3);
    std::cout << text.soundEffectText << ": "; // Sử dụng biến từ LanguageText
    if (currentOption == 1) {
        SetColor(15, 0);
        std::cout << (isSoundEffectEnabled ? text.onText : text.offText);
        SetColor(0, 15);
    }
    else {
        std::cout << (isSoundEffectEnabled ? text.onText : text.offText);
    }

    // Hiển thị lựa chọn ngôn ngữ
    GotoXY(x + 35 + 2, y + 4);
    std::cout << text.languageText << ": ";
    if (currentOption == 2)
    {
        SetColor(15, 0);
        std::cout << ((currentLanguage == ENGLISH) ? "English    " : "Vietnamese ");
        SetColor(0, 15);
    }
    else
    {
        SetColor(0, 15);
        std::cout << ((currentLanguage == ENGLISH) ? "English    " : "Vietnamese ");
    }

}

void selectLanguage() {
    FixConsoleWindow();
    DrawBackground();
    SetColor(0, 15);
    DrawBound();
    char choice;
    GotoXY(42, 15);
    std::cout << "Select Language / Chon Ngon Ngu: (E) English / (V) Tieng Viet: ";
    std::cin >> choice;

    if (choice == 'E' || choice == 'e') {
        currentLanguage = VIETNAMESE;
    }
    else if (choice == 'V' || choice == 'v') {
        currentLanguage = ENGLISH;
    }
    else {
        std::cout << "Invalid choice. Defaulting to English.\n";
        currentLanguage = VIETNAMESE;
    }
    ToggleLanguage();
    system("cls");
}

void Setting() {
    ShowCur(false);
    vechuSETTING(46, 2);
    SetColor(0, 15);
    Draw_Guide(50, 35, text.moveUpText + ", " + text.selectText + ", " + text.goBackText + ", " + char(30)+char(31) + ": Volume");
    DrawBound();
    InitializeAudioSettings();
    int currentOption = 0;

    playBackgroundMusic(isBackgroundMusicOpen, a1);

    while (true) {
        boxSetting(16, 18, 40, 7, currentOption, isBackgroundMusicOpen, isSoundEffectEnabled);
        char _COMMAND = toupper(_getch());
        if (_COMMAND == 'W' || _COMMAND == 'S') {
            currentOption = (currentOption + 1) % 3; // Chuyển đổi giữa 0, 1 và 2
            playMoveSound(); // Phát âm thanh di chuyển khi thay đổi tùy chọn

        }
        else if (_COMMAND == 13) { // Nhấn Enter để chọn
            if (currentOption == 0) {
                volumesetting(16 + 35 + 13, 29, a1 / 50, 0);
                //if (a1 == 0) {
                //    //isBackgroundMusicOpen = !isBackgroundMusicOpen;
                //}
                //else
                //{
                //    isBackgroundMusicOpen = !isBackgroundMusicOpen;
                //}
                //playBackgroundMusic(isBackgroundMusicOpen, a1);
            }
            else if (currentOption == 1) {
                isSoundEffectEnabled = !isSoundEffectEnabled;
                if (isSoundEffectEnabled) {
                    playSelectSound();
                }


            }
            else if (currentOption == 2) { // Chuyển ngôn ngữ
                ToggleLanguage();
            }
        }
        else if (_COMMAND == 'B') { // ESC để thoát
            system("cls");
            return;
        }
    }
}
void volumesetting(int x, int y, int z, int currentchoice) {
    string b0 = u8R"()";
    string b1 = u8R"(██)";
    string b2 = u8R"(████)";
    string b3 = u8R"(██████)";
    string b4 = u8R"(████████)";
    string b5 = u8R"(██████████)";
    string b6 = u8R"(████████████)";
    string b7 = u8R"(██████████████)";
    string b8 = u8R"(████████████████)";
    string b9 = u8R"(██████████████████)";
    string b10 = u8R"(████████████████████)";
    string b[11] = { b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10 };
    if (currentchoice == 0) {
        Box(x - 13, y - 1, 40, 7 - 5);
        GotoXY(x - 13 + 2, y);
        std::cout << text.volume;
        SetConsoleOutputCP(CP_UTF8);
        GotoXY(x, y); SetColor(0, 15);
        cout << b[a1 / 100];
        SetConsoleOutputCP(437);
        while (true) {
            char _COMMAND = toupper(_getch());

            if (_COMMAND == 72) {
                if (a1 < 1000) {
                    SetConsoleOutputCP(CP_UTF8);
                    GotoXY(x + z, y); SetColor(0, 15);
                    cout << u8R"(██)";
                    z += 2;
                    SetConsoleOutputCP(437);
                    a1 += 100;
                    playBackgroundMusic(isBackgroundMusicOpen, a1);
                }
                else if (a1 == 1000) {
                    playBackgroundMusic(isBackgroundMusicOpen, a1);
                }
            }
            if (_COMMAND == 80) {  // Mã phím mũi tên xuống
                if (a1 > 0) {
                    a1 -= 100;
                    SetConsoleOutputCP(CP_UTF8);
                    z -= 2;
                    GotoXY(z + x, y); SetColor(15, 15);
                    cout << u8R"(██)";
                    SetConsoleOutputCP(437);
                    playBackgroundMusic(isBackgroundMusicOpen, a1);
                }
                else if (a1 == 0) {
                    playBackgroundMusic(isBackgroundMusicOpen, a1);
                }

            }
            if (_COMMAND == 'S' || _COMMAND == 'W') {
                SetColor(15, 15);
                Box(x - 13, y - 1, 40, 7 - 5);
                SetConsoleOutputCP(CP_UTF8);
                GotoXY(x - 13 + 2, y); SetColor(15, 15);
                cout << u8R"(███████████████████████████████████████)";
                SetConsoleOutputCP(437);
                break;
            }
        }
    }
}
