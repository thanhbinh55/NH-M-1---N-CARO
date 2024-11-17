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

void playWINGameMusic() {
    if (isSoundEffectEnabled) {
        const wchar_t* moveSoundPath = L"Win.wav";
        PlaySound(moveSoundPath, NULL, SND_FILENAME | SND_ASYNC);
    }
}
void playDRAWGameMusic() {
    if (isSoundEffectEnabled) {
        const wchar_t* moveSoundPath = L"Draw.wav";
        PlaySound(moveSoundPath, NULL, SND_FILENAME | SND_ASYNC);
    }
}
void playBackgroundMusic(bool play) {
    if (play) {
        const wchar_t* filePath = L"GameBGM.mp3"; //truy cap duong den duong dan cua file nhac

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
        const wchar_t* filePath = L"8bit-music-for-game-68698.mp3"; //truy cap duong den duong dan cua file nhac

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
        const wchar_t* moveSoundPath = L"MenuMove.wav";
        PlaySound(moveSoundPath, NULL, SND_FILENAME | SND_ASYNC);
    }
}

void playSelectSound() {
    if (isSoundEffectEnabled) {
        const wchar_t* selectSoundPath = L"8-bit-game-2-186976.wav";
        PlaySound(selectSoundPath, NULL, SND_FILENAME | SND_ASYNC);
    }
}