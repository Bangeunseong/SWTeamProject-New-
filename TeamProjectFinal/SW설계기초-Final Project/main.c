#include "CursorFunctions.h"
#include "ResizeConsole.h"
#include "BackGround.h"
#include "StartMenu.h"
#include "CharacterSelectionMenu.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"
#include "Timer.h"
int main() {
	ResizeConsole();
	RemoveCursor();
	InitUniBoard();
	StartMenu();
	ShowCharacterSelectionMenu();
	ShowBackGround();
	InitializeLifeGauge();
	TimeCheckerStart();
	while (1) { InvalidateUI(); InvalidateEnemy(); InvalidatePlayer(); RunGameAfterTimeBuffer(); }
	return 0;
}