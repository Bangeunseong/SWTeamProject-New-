#pragma once
#pragma warning(disable:4996)
#include "VariableSets.h"
#include "Enemy.h"
#include "CursorFunctions.h"
#include "Timer.h"
#ifndef BULLET_H
#define BULLET_H

//총알 인풋타임 버퍼시간
double BULLETTIMEBUFFER = 0.2;

//총알 인풋타임 시작시간
double BulletInputTime = 0;

//총알 시작 위치
int BULLET_POS_X[50];
int BULLET_POS_Y[50];

//총알 이전 위치
int BULLET_BEFORE_POS_X[50];
int BULLET_BEFORE_POS_Y[50];

//총알 개수
int BULLET_COUNT;

//총알 발사 속도
double BULLETLAUNCHSPEED = 0.001;

//총알 인풋타임 버퍼 시간 계산 함수
int CalculateBulletTimeBuffer() {
	if (TimeCheckerEnd() - BulletInputTime > BULLETTIMEBUFFER / BulletSpeed) { BulletInputTime += BULLETTIMEBUFFER / BulletSpeed; return 0; }
	else return 1;
}

//총알 위치 초기화 함수
void ClearBulletPosition() {
	for (int i = 0; i < 50; i++) {
		BULLET_POS_X[i] = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
		BULLET_POS_Y[i] = GAMEBOARD_ORIGIN_Y + 5;
	}
}

//총알 위치 갱신 함수
void BulletPostionRenewal() {
	for (int i = 0; i < 20; i++) {
		BULLET_POS_X[i] = ENEMY_POS_X;
	}
}

//총알 출력 함수
void ShowBullet(int i) {
	BULLET_BEFORE_POS_X[i] = BULLET_POS_X[i];
	BULLET_BEFORE_POS_Y[i] = BULLET_POS_Y[i];
	SetCurrentCursorPos(BULLET_POS_X[i], BULLET_POS_Y[i]);
	printf("ο"); // ㅎ한자
}

//총알 숨김 함수
void HideBullet(int i) {
	SetCurrentCursorPos(BULLET_BEFORE_POS_X[i], BULLET_BEFORE_POS_Y[i]);
	printf("  ");
}

//총알 기준 벽과 부딫혔을 때 사용하는 함수
int DetectCollision_BulletwithWall(int x, int y) {
	if (UniBoard[y - GAMEBOARD_ORIGIN_Y][x - GAMEBOARD_ORIGIN_X] == 1) 
		return 1;
	return 0;
}

//총알 down
void BulletDown(int i) {
	HideBullet(i);
	if (DetectCollision_BulletwithWall(BULLET_POS_X[i], BULLET_POS_Y[i] + 1))
		return ;
	ShowBullet(i);
}

//총알 수학식
void BulletFormula(int i) {
	for (int j = 0; j < i; j++) {
		SetCurrentCursorPos(BULLET_POS_X[i], BULLET_POS_Y[i]);
		BulletDown(j);
		if (BULLET_POS_Y[j] < GAMEBOARD_COLUMN - 10);
			(BULLET_POS_Y[j])++;
	}
}

//총알 가동 시간
int BulletLaunchTime() {
	if (TimeCheckerEnd() > 3.0 && TimeCheckerEnd() < 10.0) {
		return 1;
	}
	else if (TimeCheckerEnd() > 13.0 && TimeCheckerEnd() < 20.0) {
		return 1;
	}
	else if (TimeCheckerEnd() > 23.0 && TimeCheckerEnd() < 30.0) {
		return 1;
	}
	else if (TimeCheckerEnd() > 33.0 && TimeCheckerEnd() < 40.0) {
		return 1;
	}
	else if (TimeCheckerEnd() > 43.0 && TimeCheckerEnd() < 50.0) {
		return 1;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------------------------

//-------------------------------------총알 갱신 함수-------------------------------------------------------
void InvalidateBullet() {
	BulletPostionRenewal();
	if (!CalculateBulletTimeBuffer()) {
		if (BulletLaunchTime()) {
			BulletPostionRenewal();
			BulletFormula(BULLET_COUNT);
			if (BULLET_COUNT < 20) {
				BULLET_COUNT++;
			}
		}
		else {
			for (int j = 0; j < 20; j++) {
				BULLET_POS_Y[j] = GAMEBOARD_ORIGIN_Y + 5;
			}
			BULLET_COUNT = 0;
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------
#endif // !BULLET_H