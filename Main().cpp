#include "Game.h"
#include "SoundManager.h"
#include "SaveLoad.h"
#include "Draw.h"
#include "LanguageText.h"
#include "Setting.h"


int main()
{
	selectLanguage();
	playBackgroundMusic(true,a1);
	DrawScreen();
	MainMenu();
	system("color f0");
	system("pause");
	return 0;
} 