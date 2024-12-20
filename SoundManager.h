﻿#ifndef AUDIO_SETTINGS_H
#define AUDIO_SETTINGS_H

#include "Windows.h"
#include <mmsystem.h>
#include <string>
#include <iostream>
#pragma comment(lib, "winmm.lib") 
extern bool isBackgroundMusicOpen;
extern bool isSoundEffectEnabled;
extern bool firstTime;
extern int a1;//bien am luong
void playBackgroundMusic(bool play, int volume);
void playGameMusic(bool play);
void playDRAWGameMusic();
void playWINGameMusic();
void playMoveSound();
void playSelectSound();

// Hàm khởi tạo âm thanh lần đầu
void InitializeAudioSettings();

#endif 