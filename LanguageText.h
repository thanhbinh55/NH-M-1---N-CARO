#pragma once
#include <string>
using namespace std;

enum Language { ENGLISH, VIETNAMESE };
struct LanguageText {
	string newGameText;
	string loadGameText;
	string settingText;
	string helpText;
	string aboutText;
	string exit;
	string save;
	string exitText;
	string saveText;
	string inputText;
	string nameText1;
	string nameText2;
	string movesText;
	string winsText;
	string onText;
	string offText;
	string backgroundSoundText;
	string soundEffectText;
	string languageText;
	string askContinueText;
	string askSaveGameText;
	string errorYN;
	string moveLeftText;
	string moveRightText;
	string moveUpText;
	string moveDownText;
	string selectText;
	string goBackText;
	string undoText;

	// Help
	string menuGuideText;
	string menuInstructions1;
	string menuInstructions2;
	string menuInstructions3;
	string menuInstructions4;

	string menuInstructions5;
	string menuInstructions6;
	string menuInstructions7;
	string menuInstructions8;
	string menuInstructions9;

	string gameGuideText;
	string gameInstructions1;
	string gameInstructions2;
	string gameInstructions3;
	string gameInstructions4;

	// Choose Game
	string choseGamePlay;
	string choseGameStyle;
	string gamemode;
	string gamestyle;
	string gametime;
	string turntime;
	string basicStyle;
	string speedUpStyle;
	string ErrorGetName;

	//bang thong bao
	string name;
	string score;
	string move;
	string player;
	string announce;
	string announce1;

	//
	string choosecharacter;

	//saveload
	string ErrorFile;
	string entername;
	string Errorname;
	string nameexist;

	string savemode;
	string gameExiting;
	string gameList;
	string List;
	string Loadmode;
	string LoadExist;
	string Exist;

	//Delete
	string Deletename;
	string Deletefile;
	string DeleteExist;

	//Rename
	string Rename;
	string Newgame;
	string Changed;
	string Changedmode;
	string Error;
	string ErrorRead;

	string ErrorLoad;
	string ErrorData;
	string maxsave;
	string maxsave1;

	string L;
	string D;
	string R;
	string S;

	string volume;
};


extern LanguageText text;
extern Language currentLanguage;


void InitializeText(); // Cai dat ngon ngu
void ToggleLanguage(); // Chuyen doi ngon ngu