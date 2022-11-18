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

//스토리 모드
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

//무한 모드
void InfiniteMode() {		//UI 수정필요
	while (1) {
		InvalidateStageNumber();
		ShowCurrentNSubSkill();
		ShowTime();
		ShowStageNumber();
		TimeCheckerStart();
		while (1) { InvalidateTime(); InvalidateItem();  InvalidateBullet(); InvalidateEnemy(); InvalidatePlayer(); if (GameOver()) return; }
	}
}

//게임 실행 함수
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
