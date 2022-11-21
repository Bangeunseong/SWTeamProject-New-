#pragma once
#pragma warning(disable:4996)
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Player.h"
#include "Timer.h"
#ifndef ENEMY_H
#define ENEMY_H
//---------------------------------------------------------
//---------------�ʱ�ȭ �� �ð���� �Լ�----------------

//�� NPC ���� �ð� ��� �Լ�
int CalculateEnemyTimeBuffer() {
	if (TimeCheckerEnd() - EnemyInputTime - PausingTime > ENEMYTIMEBUFFER / EnemySpeed) { EnemyInputTime += ENEMYTIMEBUFFER / EnemySpeed; return 0; }
	else return 1;
}

//�� ��ġ �ʱ�ȭ �Լ�
void ClearEnemyPosition() {
	ENEMY_POS_X = ENEMY_ORIGIN_POS_X;
	ENEMY_POS_Y = ENEMY_ORIGIN_POS_Y;
	direction = EnemyIsMoving = 0;
}

//----------------------------------------------------------
//-----------------�� �̹��� ����Լ�--------------------

//�� ���� �Լ�
void HideEnemy() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			SetCurrentCursorPos(ENEMY_POS_X + j, ENEMY_POS_Y + i);
			if (EnemyModel[i][j] != ' ') printf(" ");
		}
	}
	SetCurrentCursorPos(ENEMY_POS_X, ENEMY_POS_Y);
}

//�� ��� �Լ�
void ShowEnemy() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			SetCurrentCursorPos(ENEMY_POS_X + j, ENEMY_POS_Y + i);
			if (EnemyModel[i][j] != ' ') printf("%c", EnemyModel[i][j]);
		}
	}
	SetCurrentCursorPos(ENEMY_POS_X, ENEMY_POS_Y);
}

//----------------------------------------------------------
//-------------------�浹�˻� �Լ�------------------------

//���� ���� �浹�Ͽ����� ���� Ȯ�� �Լ�
int DetectCollision_Enemy(int x, int y) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (EnemyUniModel[i][j] == ENEMY) {
				if (UniBoard[y - GAMEBOARD_ORIGIN_Y + i][x - GAMEBOARD_ORIGIN_X + j] == WALL) return 1;
			}
		}
	}
	return 0;
}

//-------------------------------------------------------------
//-----------------EnemyMotion �����Լ�-------------------

void shiftEnemyLeft() {
	HideEnemy();
	if (!DetectCollision_Enemy(ENEMY_POS_X - 1, ENEMY_POS_Y)) { direction = DIRECTION_LEFT; ENEMY_POS_X--; }
	else direction = DIRECTION_RIGHT;
	ShowEnemy();
}
void shiftEnemyRight() {
	HideEnemy();
	if (!DetectCollision_Enemy(ENEMY_POS_X + 1, ENEMY_POS_Y)) { direction = DIRECTION_RIGHT; ENEMY_POS_X++; }
	else direction = DIRECTION_LEFT;
	ShowEnemy();
}
void shiftEnemyUp() {
	HideEnemy();
	if (!DetectCollision_Enemy(ENEMY_POS_X, ENEMY_POS_Y - 1)) { direction = DIRECTION_UP; ENEMY_POS_Y--; }
	else direction = DIRECTION_DOWN;
	ShowEnemy();
}
void shiftEnemyDown() {
	HideEnemy();
	if (!DetectCollision_Enemy(ENEMY_POS_X, ENEMY_POS_Y + 1)) { direction = DIRECTION_DOWN; ENEMY_POS_Y++; }
	else direction = DIRECTION_UP;
	ShowEnemy();
}
void shiftEnemyLeftUp() {
	int CombinedDirection = 0;
	shiftEnemyLeft(); CombinedDirection += direction;
	shiftEnemyUp(); CombinedDirection += direction * 2;
	direction = CombinedDirection;
}
void shiftEnemyLeftDown() {
	int CombinedDirection = 0;
	shiftEnemyLeft(); CombinedDirection += direction;
	shiftEnemyDown(); CombinedDirection += direction * 2;
	direction = CombinedDirection;
}
void shiftEnemyRightUp() {
	int CombinedDirection = 0;
	shiftEnemyRight(); CombinedDirection += direction;
	shiftEnemyUp(); CombinedDirection += direction * 2;
	direction = CombinedDirection;
}
void shiftEnemyRightDown() {
	int CombinedDirection = 0;
	shiftEnemyRight(); CombinedDirection += direction;
	shiftEnemyDown(); CombinedDirection += direction * 2;
	direction = CombinedDirection;
}

//---------------------------------------------------------------
//------------------EnemyMovement �Լ�---------------------
//���� ��ǥ�� ���ư���
int EnemyMotion_MoveToOriginPos() {
	int flag = 0;
	if (ENEMY_POS_X < ENEMY_ORIGIN_POS_X) shiftEnemyRight();
	else if (ENEMY_POS_X > ENEMY_ORIGIN_POS_X) shiftEnemyLeft();
	else flag++;

	if (ENEMY_POS_Y < ENEMY_ORIGIN_POS_Y) shiftEnemyDown();
	else if (ENEMY_POS_Y > ENEMY_ORIGIN_POS_Y) shiftEnemyUp();
	else flag++;

	if (flag > 1) { EnemyIsMoving = 0; direction = 0; return 1; } return 0;		//ó�� �ڸ��� �ǵ��� ������ 1 ��ȯ, �� �� 0 ��ȯ
}

//�¿�� ����ϰ� �����δ�
void EnemyMotion_MovingLeftRight() {
	if (direction == DIRECTION_RIGHT) shiftEnemyRight();
	else if(direction == DIRECTION_LEFT) shiftEnemyLeft();
}

//���� ���������� �����ϸ� �����δ�
void EnemyMotion_FlashToRandomPos() {
	if (TimeCheckerEnd() - PausingTime - EnemyMovementTiming > ENEMYMOVEMENTDURATION) { 
		HideEnemy();
		ENEMY_POS_X = rand() % (GAMEBOARD_ROW - 6) + GAMEBOARD_ORIGIN_X + 2;
		ShowEnemy();
		EnemyMovementTiming += ENEMYMOVEMENTDURATION;
	}
}

//�߽����� �̵��ϰ� �����
void EnemyMotion_MoveToCenter() {
	if (ENEMY_POS_X < ENEMY_ORIGIN_POS_X) shiftEnemyRight();
	else if (ENEMY_POS_X > ENEMY_ORIGIN_POS_X) shiftEnemyLeft();

	if (ENEMY_POS_Y < GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 2 - 1) shiftEnemyDown();
	else if (ENEMY_POS_Y > GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN / 2 - 1) shiftEnemyUp();
}

//���� ƨ��鼭 �̵�
void EnemyMotion_BouncingAroundWall() {
	switch (direction) {
	case 1: shiftEnemyUp(); break;
	case 2: shiftEnemyDown(); break;
	case 3: shiftEnemyLeft(); break;
	case 4: shiftEnemyRight(); break;
	case 5: shiftEnemyLeftUp(); break;
	case 6: shiftEnemyRightUp(); break;
	case 7: shiftEnemyLeftDown(); break;
	case 8: shiftEnemyRightDown(); break;
	}
}

//--------------------------------------------------------------
//--------------------EnemySkill �Լ�------------------------- 

void InitializePrisonInfo() {
	P.Prison_H = 7; P.Prison_W = 24;
	P.LU_X = P.LU_Y = P.RD_X = P.RD_Y = 0;
}

//----------------EnemySkillPrison ��� �Լ�---------------

//���� ���� ����
void InvalidatePrisonInfo() {
	P.LU_X = PLAYER_POS_X - (P.Prison_W - 6) / 2 - 2;
	P.LU_Y = PLAYER_POS_Y - (P.Prison_H - 1) / 2 - 1;
	P.RD_X = P.LU_X + P.Prison_W + 2;
	P.RD_Y = P.LU_Y + P.Prison_H + 1;
}

//���� ��� �Լ�
void DrawEnemySkillPrison() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	for (int i = 0; i <= P.Prison_H; i++) {
		SetCurrentCursorPos(P.LU_X, P.LU_Y + i);
		if (i == 0) printf("��");
		else if (i == P.Prison_H) printf("��");
		else printf("��");
		SetCurrentCursorPos(P.RD_X, P.LU_Y + i);
		if (i == 0) printf("��");
		else if (i == P.Prison_H) printf("��");
		else printf("��");
	}

	for (int i = 2; i < P.Prison_W; i += 2) {
		SetCurrentCursorPos(P.LU_X + i, P.LU_Y);
		printf("��");
		SetCurrentCursorPos(P.LU_X + i, P.RD_Y);
		printf("��");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

//���� ���� �Լ�
void EraseEnemySkillPrison() {
	for (int x = P.LU_X; x <= P.RD_X; x++) {
		SetCurrentCursorPos(x, P.LU_Y);
		if (x == P.LU_X) printf("  ");
		else if (x == P.RD_X) printf("  ");
		else printf("  ");
		SetCurrentCursorPos(x, P.RD_Y);
		if (x == P.LU_X) printf("  ");
		else if (x == P.RD_X) printf("  ");
		else printf("  ");
	}
	for (int y = P.LU_Y + 1; y < P.RD_Y; y++) {
		SetCurrentCursorPos(P.LU_X, y);
		printf("  ");
		SetCurrentCursorPos(P.RD_X, y);
		printf("  ");
	}
}

//------------��ų �ߵ� �Լ�---------------

void ActivateEnemySkill_Prison() {
	DrawEnemySkillPrison();
	EnemySkillPrisonActivation = 1;
}
void DeactivateEnemySkill_Prison() {
	EraseEnemySkillPrison();
	EnemySkillPrisonActivation = 0;
}

//--------------------------------------------------------------
//-------------------Invalidation �Լ�-------------------------

//�� ���� �Լ�
void InvalidateEnemy() {
	ShowEnemy();
	if (!CalculateEnemyTimeBuffer()) {
		if (PatternNumber == 1) { 
			if (PatternTimeEnded) { if (EnemyMotion_MoveToOriginPos()) return; }	//���� ���ӽð��� ������ ��� �ٽ� ���ڸ��� �̵��ϴµ� �� �̵������� Enemy�̵� �ε������� 0���� ����
			else {
				if (!direction) direction = DIRECTION_LEFT;	//������ ���������� ���� �� ���� ����
				EnemyMotion_MovingLeftRight();
			}
		}
		else if (PatternNumber == 2 || PatternNumber == 4 || PatternNumber == 9) {
			if (PatternTimeEnded) {
				if (EnemyMotion_MoveToOriginPos()) {	//���� ���ӽð��� ������ ��� �ٽ� ���ڸ��� �̵��ϴµ� �� �̵������� Enemy�̵� �ε������� 0���� ����
					EnemyIsMoving = 0;
					if (PatternNumber == 2) DeactivateEnemySkill_Prison();	//���� �ѹ��� 2���̸� ������ ����
					return;
				}
			}
			else { if (PatternNumber == 2) { if (!EnemySkillPrisonActivation) { HidePlayer(); ClearPlayerPosition(); InvalidatePrisonInfo(); } ActivateEnemySkill_Prison(); } EnemyMotion_FlashToRandomPos(); }
		}
		else if (PatternNumber == 3 || PatternNumber == 5) {
			if (PatternTimeEnded) { EnemySpeed = 1.0; if (EnemyMotion_MoveToOriginPos()) EnemyIsMoving = 0; return; }	//���� ���ӽð��� ������ ��� �ٽ� ���ڸ��� �̵��ϴµ� �� �̵������� Enemy�̵� �ε������� 0���� ����
			else {
				EnemySpeed = 0.5;
				if (!direction) direction = rand() % 2 + 7;
				EnemyMotion_BouncingAroundWall();
			}
		}
		else if (PatternNumber == 6 || PatternNumber == 10) {
			if (PatternTimeEnded) { if (EnemyMotion_MoveToOriginPos()) EnemyIsMoving = 0; return; }	//���� ���ӽð��� ������ ��� �ٽ� ���ڸ��� �̵��ϴµ� �� �̵������� Enemy�̵� �ε������� 0���� ����
			else EnemyMotion_MoveToCenter();
		}
		else if (PatternNumber == 7) {
			if (PatternTimeEnded) { if (EnemyMotion_MoveToOriginPos()) EnemyIsMoving = 0; return; }	//���� ���ӽð��� ������ ��� �ٽ� ���ڸ��� �̵��ϴµ� �� �̵������� Enemy�̵� �ε������� 0���� ����
			else EnemyMotion_FlashToRandomPos();
		}
		else if (PatternNumber == 8) {
			if (PatternTimeEnded) { if (EnemyMotion_MoveToOriginPos()) EnemyIsMoving = 0; return; }	//���� ���ӽð��� ������ ��� �ٽ� ���ڸ��� �̵��ϴµ� �� �̵������� Enemy�̵� �ε������� 0���� ����
			else if (ENEMY_POS_X < GAMEBOARD_ROW - 5) shiftEnemyRight();
			else {
				HideEnemy();
				ENEMY_POS_X = GAMEBOARD_ORIGIN_X + 4;
			}
		}
	}
}
#endif // !ENEMY_H