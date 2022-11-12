#pragma once
#pragma warning(disable:4996)
#include "VariableSets.h"
#include "Enemy.h"
#include "CursorFunctions.h"
#include "Timer.h"
#ifndef BULLET_H
#define BULLET_H

//총알 인풋타임 시작시간
double BulletInputTime = 0;

//총알 시작 위치
int BULLET_POS_X[50];
int BULLET_POS_Y[50];

//총알 이전 위치
int BULLET_BEFORE_POS_X[50];
int BULLET_BEFORE_POS_Y[50];

//총알을 세기 위한 변수
int BULLET_COUNT;

//총알 발사 속도를 위한 변수
double BulletTimeCheckerStart = 3.5;
double BulletTimeCheckerEnd = 9.5;

//총알을 지울 때 세기 위한 변수
int BULLET_ERASE_COUNT;

//총알 인풋타임 버퍼 시간 계산 함수
int CalculateBulletTimeBuffer() {
	if (TimeCheckerEnd() - BulletInputTime > BULLETTIMEBUFFER / BulletSpeed) { BulletInputTime += BULLETTIMEBUFFER / BulletSpeed; return 0; }
	else return 1;
}

//총알 위치 초기화 함수
void ClearBulletPosition() {
	for (int i = 0; i < 50; i++) {
		BULLET_POS_X[i] = BULLET_BEFORE_POS_X[i] = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
		BULLET_POS_Y[i] = BULLET_BEFORE_POS_Y[i] = GAMEBOARD_ORIGIN_Y + 5;

	}
}

//총알 위치 갱신 함수
void BulletPostionRenewal() {
	for (int i = 0; i < 50; i++) {
		BULLET_POS_X[i] = ENEMY_POS_X;
		BULLET_POS_Y[i] = GAMEBOARD_ORIGIN_Y + 5;
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
	if (DetectCollision_BulletwithWall(BULLET_POS_X[i], BULLET_POS_Y[i] + 1))
		return;
	else if (DetectCollision_BulletwithWall(BULLET_POS_X[i], BULLET_POS_Y[i] + 2))
		return ;
	ShowBullet(i);
}

//총알 수학식 1
void BulletFormula1(int i) {
	int Before_count = 0;
	if (i > BULLET_MAX)
		Before_count = i - BULLET_MAX;
	for (int j = Before_count; j < i; j++) {
		SetCurrentCursorPos(BULLET_POS_X[j], BULLET_POS_Y[j]);
		BulletDown(j);
		if (j > BULLET_MAX / 2) {
			HideBullet(j);
		}
		(BULLET_POS_Y[j]) += 2;
	}
}

//총알 가동 시간
int BulletLaunchTime() {
	if (TimeCheckerEnd() > BulletTimeCheckerStart && TimeCheckerEnd() < BulletTimeCheckerEnd) {
		return 1;
	}
	else if (TimeCheckerEnd() > BulletTimeCheckerEnd) {
		BulletTimeCheckerStart += 10.0;
		BulletTimeCheckerEnd += 10.0;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------------------------

//-------------------------------------총알 갱신 함수-------------------------------------------------------
void InvalidateBullet() {

	if (!CalculateBulletTimeBuffer()) {
		if (BulletLaunchTime()) {
			BulletFormula1(BULLET_COUNT);
			if (BULLET_COUNT < (BULLET_MAX * 3) / 2) {
				BULLET_COUNT++;
			}
			else {
				BULLET_COUNT = 0;
				BulletPostionRenewal();
			}
		}
		else {
			BULLET_COUNT = 0;
			BulletPostionRenewal();
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------
#endif // !BULLET_H