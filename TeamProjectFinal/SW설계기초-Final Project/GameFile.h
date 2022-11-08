#pragma once
#include "CursorFunctions.h"
#include "ResizeConsole.h"
#include "BackGround.h"
#include "StartMenu.h"
#include "CharacterSelectionMenu.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"
#include "Timer.h"
#ifndef GAMEFILE_H
#define GAMEFILE_H

//���丮 ���
void StoryMode() { while (1) { InvalidateUI(); InvalidateEnemy(); InvalidatePlayer(); } }

//���� ���


//���� ���� �Լ�
void RunGame() {
	ResizeConsole(); RemoveCursor(); InitUniBoard();
	if (StartMenu()) {
		ShowCharacterSelectionMenu();
		ShowBackGround();
		InitializeLifeGauge();
		TimeCheckerStart();
		switch (GameMode) {
		case 0: StoryMode(); break;
		case 1: break;
		}
	}
	return;
}
#endif // !GAMEMODE_H
