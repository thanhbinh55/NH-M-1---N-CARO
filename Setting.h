#pragma once
#include "Game.h"
#include "SoundManager.h"
#include "LanguageText.h"
#include "Draw.h"

void volumesetting(int x, int y, int z, int currentchoice);
void boxSetting(int x, int y, int w, int h, int currentOption, bool& backgroundSound, bool& soundEffect);
void Setting();
void selectLanguage();