#ifndef AUDIO_SETTINGS_H
#define AUDIO_SETTINGS_H

#include "Windows.h"
#include <mmsystem.h>
#include <string>
#include <iostream>
#pragma comment(lib, "winmm.lib") // Liên kết thư viện winmm.lib

extern bool isBackgroundMusicOpen;
extern bool isSoundEffectEnabled;
extern bool firstTime;

void playBackgroundMusic(bool play);
void playGameMusic(bool play);
void playDRAWGameMusic();
void playWINGameMusic();
void playMoveSound();
void playSelectSound();

// Hàm khởi tạo âm thanh lần đầu
void InitializeAudioSettings();

#endif // AUDIO_SETTINGS_H