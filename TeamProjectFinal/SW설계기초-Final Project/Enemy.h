#pragma once
#pragma warning(disable:4996)
#include "CursorFunctions.h"
#include "BackGround.h"
#include "EnemyInfo.h"
#ifndef ENEMY_H
#define ENEMY_H

//적 NPC 인풋타임 버퍼 시간
double ENEMYTIMEBUFFER = 0.02;

//적 NPC 인풋타임 시작시간
double EnemyInputTime = 0;

//적 NPC 버퍼 시간 계산 함수
int CalculateEnemyTimeBuffer() {
	if (TimeCheckerEnd() - EnemyInputTime > ENEMYTIMEBUFFER) { EnemyInputTime += ENEMYTIMEBUFFER; return 0; }
	else return 1;
}

//적 출력 및 삭제 함수
void HideEnemy() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			SetCurrentCursorPos(ENEMY_POS_X + j, ENEMY_POS_Y + i);
			if (EnemyModel[i][j] != ' ') printf(" ");
		}
	}
	SetCurrentCursorPos(ENEMY_POS_X, ENEMY_POS_Y);
}
void ShowEnemy() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			SetCurrentCursorPos(ENEMY_POS_X + j, ENEMY_POS_Y + i);
			if (EnemyModel[i][j] != ' ') printf("%c", EnemyModel[i][j]);
		}
	}
	SetCurrentCursorPos(ENEMY_POS_X, ENEMY_POS_Y);
}

int DetectCollision_Enemy(int x, int y) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (EnemyUniModel[i][j] == ENEMY) {
				if (UniBoard[y - GAMEBOARD_ORIGIN_Y + i][x - GAMEBOARD_ORIGIN_X + j] == 1) return 1;
			}
		}
	}
	return 0;
}

//적 위치 변환 함수
void shiftEnemyLeft() {
	HideEnemy();
	if (!DetectCollision_Enemy(ENEMY_POS_X - 1, ENEMY_POS_Y)) { ENEMY_POS_X--; direction = 0; }
	else direction = 1;
	ShowEnemy();
}
void shiftEnemyRight() {
	HideEnemy();
	if (!DetectCollision_Enemy(ENEMY_POS_X + 1, ENEMY_POS_Y)) { ENEMY_POS_X++; direction = 1; }
	else direction = 0;
	ShowEnemy();
}

//적 갱신 함수
void InvalidateEnemy() {
	ShowEnemy();
	if (!CalculateEnemyTimeBuffer()) {
		if (direction) shiftEnemyRight();
		else shiftEnemyLeft();
	}
}
#endif // !ENEMY_H