#include"Setting.h"
#include "Draw.h"


void boxSetting(int x, int y, int w, int h, int currentOption, bool& backgroundSound, bool& soundEffect) {
    SetColor(0, 15);
    Box(x + 35, y, w, h);

    // Hiển thị trạng thái âm thanh nền
    GotoXY(x + 35 + 2, y + 2);
    std::cout << text.backgroundSoundText << ": "; // Sử dụng biến từ LanguageText
    if (currentOption == 0) {
        SetColor(15, 0);
        std::cout << (isBackgroundMusicOpen ? text.onText : text.offText);
        SetColor(0, 15);
    }
    else {
        std::cout << (isBackgroundMusicOpen ? text.onText : text.offText);
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
        std::cout << (isSoundEffectEnabled ? text.onText: text.offText);
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
   // system("Color F0");
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
    DrawLogoCaro(45, 5);
    SetColor(0, 15);
    Draw_Guide(43, 35, text.moveUpText + ", " + text.moveDownText + ", " + text.selectText + ", " + text.goBackText);
    DrawBound();
    InitializeAudioSettings();
    int currentOption = 0;

    playBackgroundMusic(isBackgroundMusicOpen);

    while (true) {
        boxSetting(16, 15, 40, 7, currentOption, isBackgroundMusicOpen, isSoundEffectEnabled);

        char _COMMAND = toupper(_getch());
        if (_COMMAND == 'W' || _COMMAND == 'S') {
            currentOption = (currentOption + 1) % 3; // Chuyển đổi giữa 0, 1 và 2
            playMoveSound(); // Phát âm thanh di chuyển khi thay đổi tùy chọn
        }
        else if (_COMMAND == 13) { // Nhấn Enter để chọn
            if (currentOption == 0) {
                isBackgroundMusicOpen = !isBackgroundMusicOpen;
                playBackgroundMusic(isBackgroundMusicOpen);
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
