#pragma once
#include "Game.h"

int searchAddressOfBoard(int pX, int pY, int& row, int& col);
int MediumBot(int _X, int _Y, int& pX, int& pY);
int EasyBot(int _X, int _Y, int& pX, int& pY);
int countInLine(int x, int y, int dx, int dy, int player);
int evaluate(int x, int y, int player);
int minimax(int depth, int alpha, int beta, bool isMaximizingPlayer);
void improvedBot(int _X, int _Y, int& pX, int& pY);
bool canWin(int x, int y, int player);
bool blockOpponent(int& pX, int& pY);

bool extendThreeInLine(int& pX, int& pY);