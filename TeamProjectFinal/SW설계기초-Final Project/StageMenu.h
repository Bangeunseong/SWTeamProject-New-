#pragma once
#include "VariableSets.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "UI.h"
#ifndef STAGEMENU_H
#define STAGEMENU_H

//스테이지별 출력되는 화면
void ShowStageNumber() {
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 4, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2);
	printf("Stage %d", StageNumber);
	TimeCheckerStart();
	while (TimeCheckerEnd() < STAGEDURATIONTIME);
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 4, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2);
	for (int i = 0; i < 7; i++) printf(" ");
}

//스테이지 종료 조건
int StageOver() {
	if (PlayerPos == MAPLENGTH * 2) {
		HidePlayer();
		HideEnemy();
		ClearPlayerPosition();
		ClearEnemyPosition();
		ClearBulletPosition(); // ---- ClearBulletPosition 삽입
		PlayerInputTime = 0; PlayerPos = 0; Invinsible = 0; 
		EnemyInputTime = 0; 
		ItemInputTime = 0;
		ItemCreationLoop = 1;
		CurrentTime = 1; StageNumber++;
		return 1; 
	}
	return 0;
}

//게임 종료 조건
int GameOver() {
	if (CurrentLife <= 0) return 1;
	return 0;
}
#endif // !STAGEMENU_H
