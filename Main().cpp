#include "Game.h"
#include "SoundManager.h"
#include "SaveLoad.h"
#include "Draw.h"
#include "LanguageText.h"
#include "Setting.h"


int main()
{
	selectLanguage();
	playBackgroundMusic(true);
	DrawScreen();
	MainMenu();
	system("pause");
	return 0;
} 