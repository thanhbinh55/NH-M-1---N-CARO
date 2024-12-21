#include "Game.h"
#include "Draw.h"
#include <cstdio>
void SaveData(string filename);
void LoadData(string filename);
//vector<string> LoadFiles();
void Load();
bool CheckFileExistence(string filename);
void SaveGame();
void LoadGame(string filename);
void getFileGameNameList( string fileName);
void ChooseLoadFunction( );
void changeGameNameFunction( );
void drawLoad();
void drawSave();
void handleFullSaveNewGame();