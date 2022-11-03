#include "CursorFunctions.h"
#include "ResizeConsole.h"
#include "BackGround.h"
#include "StartMenu.h"
#include "CharacterSelectionMenu.h"
#include "Player.h"
#include "Enemy.h"
#include "UIandInfo.h"
int main() {
	ResizeConsole();
	RemoveCursor();
	InitUniBoard();
	StartMenu();
	ShowCharacterSelectionMenu();
	ShowBackGround();
	InitializeLifeGauge();
	while (1) { InvalidateUI(); InvalidateEnemy(); InvalidatePlayer(); Sleep(20); }
	return 0;
}