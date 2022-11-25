#pragma once
#include "CursorFunctions.h"
#include "ResizeConsole.h"
#include "BackGround.h"
#include "StartMenu.h"
#include "CharacterSelectionMenu.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Item.h"
#include "UI.h"
#include "Timer.h"
#include "StageMenu.h"
#include "GameOverMenu.h"
#include "SoundPlay.h"
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
		while (1) { InvalidateMap(); InvalidateBullet(); InvalidateP_Bullet(); InvalidateItem(); InvalidateEnemy(); InvalidatePlayer(); if (GameOver()) return; if (StageOver()) break; }
	}
}

//���� ���
void InfiniteMode() {		//UI �����ʿ�
	while (1) {
		ShowCurrentNSubSkill();
		ShowTime();
		TimeCheckerStart();
		while (1) { InvalidateTime(); InvalidateBullet(); InvalidateItem(); InvalidateEnemy(); InvalidatePlayer(); if (GameOver()) return; }
	}
}

//���� ���� �Լ� ----������ ������ �� initialize �ؾ��� �͵鸸 �ֱ�
void RunGame() {
	ResizeConsole(); ResizeConsoleBuffer(); RemoveCursor(); InitUniBoard(); InitializePrisonInfo();
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
			if (GameOverMenu()) return;
		}
		else return;
	}
}
#endif // !GAMEFILE_H
