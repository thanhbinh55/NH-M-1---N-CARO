#pragma once
//#include "Game.h"
#include "SoundManager.h"

// Cờ kiểm tra trạng thái nhạc nền và âm thanh hiệu ứng
bool isBackgroundMusicOpen = true;
bool isSoundEffectEnabled = true;
bool firstTime = true;

void InitializeAudioSettings() {
    if (firstTime) {
        isBackgroundMusicOpen = true;
        isSoundEffectEnabled = true;
        firstTime = false;  // Đặt lại để tránh khởi tạo lại ở lần sau
    }
}


//void playBackgroundMusic(bool play) {
//    if (play && !isBackgroundMusicOpen) { // Mở nhạc nền nếu chưa mở
//        const wchar_t* filePath = L"C:\\Users\\Admin\\VISUAL STUDIO SOURCE CODE\\repos\\[KHTN] BT TRÊN TRƯỜNG\\TEST FUNCTION CARO\\8bit-music-for-game-68698.mp3";
//
//        wchar_t errorBuffer[128];
//
//        // Thực hiện phát nhạc nền và lặp lại
//        if (mciSendString((L"open \"" + std::wstring(filePath) + L"\" type mpegvideo alias bgm").c_str(), errorBuffer, 128, NULL) != 0) {
//            std::wcerr << L"Error opening file: " << errorBuffer << std::endl;
//            return;
//        }
//        if (mciSendString(L"play bgm repeat", errorBuffer, 128, NULL) != 0) {
//            std::wcerr << L"Error playing file: " << errorBuffer << std::endl;
//            return;
//        }
//        isBackgroundMusicOpen = true;
//    }
//    else if (!play && isBackgroundMusicOpen) { // Dừng và đóng nhạc nền
//        wchar_t errorBuffer[128];
//
//        if (mciSendString(L"stop bgm", errorBuffer, 128, NULL) != 0) {
//            std::wcerr << L"Error stopping file: " << errorBuffer << std::endl;
//        }
//        if (mciSendString(L"close bgm", errorBuffer, 128, NULL) != 0) {
//            std::wcerr << L"Error closing file: " << errorBuffer << std::endl;
//        }
//        isBackgroundMusicOpen = false;
//    }
//}// Hàm để phát nhạc nền bằng mciSendString
//void playBackgroundMusic(bool play) {
//    if (play && !isBackgroundMusicOpen) { // Mở nhạc nền nếu chưa mở
//        const wchar_t* filePath = L"C:\\Users\\Admin\\VISUAL STUDIO SOURCE CODE\\repos\\[KHTN] BT TRÊN TRƯỜNG\\TEST FUNCTION CARO\\8bit-music-for-game-68698.mp3";
//
//        // Thực hiện phát nhạc nền và lặp lại
//        mciSendString((L"open \"" + std::wstring(filePath) + L"\" type mpegvideo alias bgm").c_str(), NULL, 0, NULL);
//        mciSendString(L"play bgm repeat", NULL, 0, NULL);
//        isBackgroundMusicOpen = true;
//    }
//    else if (!play && isBackgroundMusicOpen) { // Dừng và đóng nhạc nền
//        mciSendString(L"stop bgm", NULL, 0, NULL);
//        mciSendString(L"close bgm", NULL, 0, NULL);
//        isBackgroundMusicOpen = false;
//    }
//}
void playBackgroundMusic(bool play) {
    if (play) {
        const wchar_t* filePath = L"C:\\Users\\Admin\\VISUAL STUDIO SOURCE CODE\\repos\\[KHTN] BT TRÊN TRƯỜNG\\TEST FUNCTION CARO\\GameBGM.mp3"; //truy cap duong den duong dan cua file nhac

        // Thực hiện phát nhạc
        mciSendString((L"open \"" + std::wstring(filePath) + L"\" type mpegvideo alias bgm").c_str(), NULL, 0, NULL);
        mciSendString(L"play bgm repeat", NULL, 0, NULL);
    }
    else {
        mciSendString(L"stop bgm", NULL, 0, NULL);
        mciSendString(L"close bgm", NULL, 0, NULL);
    }
}
void playGameMusic(bool play) {
    if (play) {
        const wchar_t* filePath = L"C:\\Users\\Admin\\VISUAL STUDIO SOURCE CODE\\repos\\[KHTN] BT TRÊN TRƯỜNG\\TEST FUNCTION CARO\\8bit-music-for-game-68698.mp3"; //truy cap duong den duong dan cua file nhac

        // Thực hiện phát nhạc
        mciSendString((L"open \"" + std::wstring(filePath) + L"\" type mpegvideo alias bgm").c_str(), NULL, 0, NULL);
        mciSendString(L"play bgm repeat", NULL, 0, NULL);
    }
    else {
        mciSendString(L"stop bgm", NULL, 0, NULL);
        mciSendString(L"close bgm", NULL, 0, NULL);
    }
}
// Hàm để phát âm thanh hiệu ứng ngắn bằng PlaySound
void playMoveSound() {
    if (isSoundEffectEnabled) {
        const wchar_t* moveSoundPath = L"C:\\Users\\Admin\\VISUAL STUDIO SOURCE CODE\\repos\\[KHTN] BT TRÊN TRƯỜNG\\TEST FUNCTION CARO\\MenuMove.wav";
        PlaySound(moveSoundPath, NULL, SND_FILENAME | SND_ASYNC);
    }
}

void playSelectSound() {
    if (isSoundEffectEnabled) {
        const wchar_t* selectSoundPath = L"C:\\Users\\Admin\\VISUAL STUDIO SOURCE CODE\\repos\\[KHTN] BT TRÊN TRƯỜNG\\TEST FUNCTION CARO\\8-bit-game-2-186976.wav";
        PlaySound(selectSoundPath, NULL, SND_FILENAME | SND_ASYNC);
    }
}