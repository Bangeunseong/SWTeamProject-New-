﻿#pragma once
#include "CursorFunctions.h"
#include "ResizeConsole.h"
#include "BackGround.h"
#include "StartMenu.h"
#include "CharacterSelectionMenu.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Item.h"
#include "ExpItem.h"
#include "UI.h"
#include "Timer.h"
#include "StageMenu.h"
#include "GameOverMenu.h"
#include "SoundPlay.h"
#ifndef GAMEFILE_H
#define GAMEFILE_H

//스토리 모드
void StoryMode() { 
	while (StageNumber < 4) {
		InitStageEnemyHealth();
		ShowCurrentNSubSkill();
		ShowEnemyHealthBar();
		ShowStoryModeTime();
		ShowStageNumber();
		TimeCheckerStart();
		while (1) { InvalidatePlayerLevel(); InvalidateStoryModeTime(); InvalidateEnemyHealthBar(); InvalidateItem(); InvalidateExp(); InvalidateBullet(); InvalidateP_Bullet(); InvalidateEnemy(); InvalidatePlayer(); if (GameOver()) return; if (StageOver()) break; }
	}
}

//무한 모드
void InfiniteMode() {		//UI 수정필요
	while (1) {
		InitInfiniteModeEnemyHealth();
		ShowCurrentNSubSkill();
		ShowEnemyHealthBar();
		ShowInfiniteModeTime();
		TimeCheckerStart();
		while (1) { InvalidateInfiniteModeTime(); InvalidateItem(); InvalidateExp(); InvalidateBullet(); InvalidateP_Bullet(); InvalidateEnemy(); InvalidatePlayer(); if (GameOver()) return; }
	}
}

//게임 실행 함수 ----게임을 실행할 때 initialize 해야할 것들만 넣기
void RunGame() {
	ResizeConsole(); ResizeConsoleBuffer(); RemoveCursor(); InitUniBoard(); InitializePrisonInfo(); //PlayBGMSound();
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
