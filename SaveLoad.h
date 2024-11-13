#include "Game.h"


void DrawLoaded(_POINT _A[][BOARD_SIZE]);
void SaveData(string filename);
void LoadData(string filename);
vector<string> LoadFiles();
void Savegame_opt();
bool CheckFileExistence(string filename);
void SaveGame();
void LoadGame(string filename);