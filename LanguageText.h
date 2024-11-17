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
	string saveText;          // Corrected to match cpp
	string inputText;          // Corrected to match cpp
	string nameText1;
	string nameText2;
	string movesText;
	string winsText;
	string onText;
	string offText;            // Corrected to match cpp
	string backgroundSoundText;
	string soundEffectText;
	string languageText;
	string askContinueText;    // Corrected to match cpp
	string askSaveGameText;    // Corrected to match cpp
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

// Declare these as extern to avoid multiple definitions
extern LanguageText text;            // Global variable to store the current language text
extern Language currentLanguage;     // Language setting (ENGLISH or VIETNAMESE)

// Function to initialize text based on the current language
void InitializeText();
void ToggleLanguage();