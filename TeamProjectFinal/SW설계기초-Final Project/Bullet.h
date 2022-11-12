#pragma once
#pragma warning(disable:4996)
#include "VariableSets.h"
#include "Enemy.h"
#include "CursorFunctions.h"
#include "Timer.h"
#ifndef BULLET_H
#define BULLET_H

//�Ѿ� ��ǲŸ�� ���۽ð�
double BulletInputTime = 0;

//�Ѿ� ���� ��ġ
int BULLET_POS_X[50];
int BULLET_POS_Y[50];

//�Ѿ� ���� ��ġ
int BULLET_BEFORE_POS_X[50];
int BULLET_BEFORE_POS_Y[50];

//�Ѿ��� ���� ���� ����
int BULLET_COUNT;

//�Ѿ� �߻� �ӵ��� ���� ����
double BulletTimeCheckerStart = 3.5;
double BulletTimeCheckerEnd = 9.5;

//�Ѿ��� ���� �� ���� ���� ����
int BULLET_ERASE_COUNT;

//�Ѿ� ��ǲŸ�� ���� �ð� ��� �Լ�
int CalculateBulletTimeBuffer() {
	if (TimeCheckerEnd() - BulletInputTime > BULLETTIMEBUFFER / BulletSpeed) { BulletInputTime += BULLETTIMEBUFFER / BulletSpeed; return 0; }
	else return 1;
}

//�Ѿ� ��ġ �ʱ�ȭ �Լ�
void ClearBulletPosition() {
	for (int i = 0; i < 50; i++) {
		BULLET_POS_X[i] = BULLET_BEFORE_POS_X[i] = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
		BULLET_POS_Y[i] = BULLET_BEFORE_POS_Y[i] = GAMEBOARD_ORIGIN_Y + 5;

	}
}

//�Ѿ� ��ġ ���� �Լ�
void BulletPostionRenewal() {
	for (int i = 0; i < 50; i++) {
		BULLET_POS_X[i] = ENEMY_POS_X;
		BULLET_POS_Y[i] = GAMEBOARD_ORIGIN_Y + 5;
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
	if (DetectCollision_BulletwithWall(BULLET_POS_X[i], BULLET_POS_Y[i] + 1))
		return;
	else if (DetectCollision_BulletwithWall(BULLET_POS_X[i], BULLET_POS_Y[i] + 2))
		return ;
	ShowBullet(i);
}

//�Ѿ� ���н� 1
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

//�Ѿ� ���� �ð�
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

//-------------------------------------�Ѿ� ���� �Լ�-------------------------------------------------------
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