#pragma once
#pragma warning(disable:4996)
#include "CursorFunctions.h"
#include "VariableSets.h"
#ifndef ENEMY_H
#define ENEMY_H

//적 NPC 버퍼 시간 계산 함수
int CalculateEnemyTimeBuffer() {
	if (TimeCheckerEnd() - EnemyInputTime - PausingTime > ENEMYTIMEBUFFER) { EnemyInputTime += ENEMYTIMEBUFFER; return 0; }
	else return 1;
}

//적 위치 초기화 함수
void ClearEnemyPosition() {
	ENEMY_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
	ENEMY_POS_Y = GAMEBOARD_ORIGIN_Y + 1;
	direction = 0;
}

//적 삭제 함수
void HideEnemy() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			SetCurrentCursorPos(ENEMY_POS_X + j, ENEMY_POS_Y + i);
			if (EnemyModel[i][j] != ' ') printf(" ");
		}
	}
	SetCurrentCursorPos(ENEMY_POS_X, ENEMY_POS_Y);
}

//적 출력 함수
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

//Enemy Location change
void setEnemyLeft() {
	HideEnemy();
	ENEMY_POS_X = GAMEBOARD_ORIGIN_X + 15;
	ShowEnemy();
}

void setEnemyLeftMiddle() {
	HideEnemy();
	ENEMY_POS_X = GAMEBOARD_ORIGIN_X + 30;
	ShowEnemy();
}

void setEnemyMiddle() {
	HideEnemy();
	ENEMY_POS_X = GAMEBOARD_ORIGIN_X + 45;
	ShowEnemy();
}

void setEnemyRightMiddle() {
	HideEnemy();
	ENEMY_POS_X = GAMEBOARD_ORIGIN_X + 60;
	ShowEnemy();
}

void setEnemyRight() {
	HideEnemy();
	ENEMY_POS_X = GAMEBOARD_ORIGIN_X + 75;
	ShowEnemy();
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
		if (PatternNumber == 1) {
			if (TimeCheckerForInt() % 5 == 0) { setEnemyLeft(); }
			else if (TimeCheckerForInt() % 5 == 1) { setEnemyRight(); }
			else if (TimeCheckerForInt() % 5 == 2) { setEnemyLeftMiddle(); }
			else if (TimeCheckerForInt() % 5 == 3) { setEnemyRightMiddle(); }
			else { setEnemyMiddle(); }
		}
		else if (PatternNumber == 2) {
			if (rand() % 2 == 0) { shiftEnemyLeft(); }
			else { shiftEnemyRight(); }
		}
		//else if(PatternNumber == 3) 이거는 낼 모임에서 같이 토의할 생각
	}
}
#endif // !ENEMY_H