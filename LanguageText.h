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
	string moveLeftText;
	string moveRightText;
	string moveUpText;
	string moveDownText;
	string selectText;
	string goBackText;

	string menuGuideText;
	string menuInstructions1;
	string menuInstructions2;
	string menuInstructions3;
	string gameGuideText;
	string gameInstructions1;
	string gameInstructions2;
	string gameInstructions3;

	string choseGamePlay;

};


extern LanguageText text;          
extern Language currentLanguage;    


void InitializeText();
void ToggleLanguage();