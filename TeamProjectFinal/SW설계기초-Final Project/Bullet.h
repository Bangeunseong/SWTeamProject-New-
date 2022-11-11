#pragma once
#pragma warning(disable:4996)
#include "VariableSets.h"
#include "Enemy.h"
#include "CursorFunctions.h"
#include "Timer.h"
#ifndef BULLET_H
#define BULLET_H

//�Ѿ� ��ǲŸ�� ���۽ð�
double BULLETTIMEBUFFER = 0.2;

//�Ѿ� ��ǲŸ�� ���۽ð�
double BulletInputTime = 0;

//�Ѿ� ���� ��ġ
int BULLET_POS_X[50];
int BULLET_POS_Y[50];

//�Ѿ� ���� ��ġ
int BULLET_BEFORE_POS_X[50];
int BULLET_BEFORE_POS_Y[50];

//�Ѿ� ����
int BULLET_COUNT;

//�Ѿ� �߻� �ӵ�
double BULLETLAUNCHSPEED = 0.001;

//�Ѿ� ��ǲŸ�� ���� �ð� ��� �Լ�
int CalculateBulletTimeBuffer() {
	if (TimeCheckerEnd() - BulletInputTime > BULLETTIMEBUFFER / BulletSpeed) { BulletInputTime += BULLETTIMEBUFFER / BulletSpeed; return 0; }
	else return 1;
}

//�Ѿ� ��ġ �ʱ�ȭ �Լ�
void ClearBulletPosition() {
	for (int i = 0; i < 50; i++) {
		BULLET_POS_X[i] = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
		BULLET_POS_Y[i] = GAMEBOARD_ORIGIN_Y + 5;
	}
}

//�Ѿ� ��ġ ���� �Լ�
void BulletPostionRenewal() {
	for (int i = 0; i < 20; i++) {
		BULLET_POS_X[i] = ENEMY_POS_X;
	}
}

//�Ѿ� ��� �Լ�
void ShowBullet(int i) {
	BULLET_BEFORE_POS_X[i] = BULLET_POS_X[i];
	BULLET_BEFORE_POS_Y[i] = BULLET_POS_Y[i];
	SetCurrentCursorPos(BULLET_POS_X[i], BULLET_POS_Y[i]);
	printf("��"); // ������
}

//�Ѿ� ���� �Լ�
void HideBullet(int i) {
	SetCurrentCursorPos(BULLET_BEFORE_POS_X[i], BULLET_BEFORE_POS_Y[i]);
	printf("  ");
}

//�Ѿ� ���� ���� �΋H���� �� ����ϴ� �Լ�
int DetectCollision_BulletwithWall(int x, int y) {
	if (UniBoard[y - GAMEBOARD_ORIGIN_Y][x - GAMEBOARD_ORIGIN_X] == 1) 
		return 1;
	return 0;
}

//�Ѿ� down
void BulletDown(int i) {
	HideBullet(i);
	if (DetectCollision_BulletwithWall(BULLET_POS_X[i], BULLET_POS_Y[i] + 1))
		return ;
	ShowBullet(i);
}

//�Ѿ� ���н�
void BulletFormula(int i) {
	for (int j = 0; j < i; j++) {
		SetCurrentCursorPos(BULLET_POS_X[i], BULLET_POS_Y[i]);
		BulletDown(j);
		if (BULLET_POS_Y[j] < GAMEBOARD_COLUMN - 10);
			(BULLET_POS_Y[j])++;
	}
}

//�Ѿ� ���� �ð�
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

//-------------------------------------�Ѿ� ���� �Լ�-------------------------------------------------------
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