#pragma once
#include "CursorFunctions.h"
#include "ResizeConsole.h"
#include "BackGround.h"
#include "StartMenu.h"
#include "CharacterSelectionMenu.h"
#include "StageMenu.h"
#include "GameOverMenu.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "UI.h"
#include "Timer.h"
#ifndef GAMEFILE_H
#define GAMEFILE_H

//���丮 ���
void StoryMode() { 
	while (StageNumber < 4) {
		InvalidateStageNumber();
		ShowCurrentNSubSkill();
		ShowMap();
		ShowStageNumber();
		TimeCheckerStart();
		while (1) { InvalidateMap(); InvalidateItem();  InvalidateBullet(); InvalidateEnemy(); InvalidatePlayer(); if (GameOver()) return; if (StageOver()) break; }
	}
}

//���� ���
void InfiniteMode() {		//UI �����ʿ�
	while (1) {
		InvalidateStageNumber();
		ShowCurrentNSubSkill();
		ShowTime();
		ShowStageNumber();
		TimeCheckerStart();
		while (1) { InvalidateTime(); InvalidateItem();  InvalidateBullet(); InvalidateEnemy(); InvalidatePlayer(); if (GameOver()) return; }
	}
}

//���� ���� �Լ�
void RunGame() {
	ResizeConsole(); RemoveCursor(); InitUniBoard();
	
	while (1) {
		srand((unsigned)time(NULL));
		if (StartMenu()) {
			ShowCharacterSelectionMenu();
			ShowBackGround();
			InitializeLifeGauge();
			switch (GameMode) {
			case 0: StoryMode(); break;
			case 1: InfiniteMode(); break;
			}
		}
		if (GameOverMenu()) break;
	}
	return;
}
#endif // !GAMEFILE_H
