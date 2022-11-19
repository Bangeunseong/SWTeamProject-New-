#pragma once
#pragma warning(disable:4996)
#include <conio.h>
#include <WinUser.h>
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Item.h"
#include "Timer.h"
#include "UI.h"
#ifndef PLAYER_H
#define PLAYER_H

//�÷��̾� ��ǲŸ�� ���� �ð� ��� �Լ�
int CalculatePlayerTimeBuffer() {
	if (TimeCheckerEnd() - PlayerInputTime - PausingTime > PLAYERTIMEBUFFER / CurSpeed) { PlayerInputTime += PLAYERTIMEBUFFER / CurSpeed; return 0; }
	else return 1;
}

//���� �����Լ�
void GamePause() {
	GamePaused = 1;
 	PausedTime = TimeCheckerEnd();
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 2, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2);
	printf("Pause");
	while (1) { if (GetAsyncKeyState(QUIT) & 0x0001) { PausingTime += TimeCheckerEnd() - PausedTime; GamePaused = 0; break; } }
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 2, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2);
	for (int i = 0; i < 5; i++) printf(" ");
}

//�÷��̾� ��ġ �ʱ�ȭ �Լ�
void ClearPlayerPosition() {
	PLAYER_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
	PLAYER_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN - 8;
}

//�÷��̾� ��� �Լ�
void ShowPlayer() {
	if (Invinsible) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERINVINSIBLEINDICATECOLOR);
	else if (UsingSkill > 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERUSINGSKILLCOLOR);
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERCOLOR);
	for (int i = 0; i < 6; i++) { SetCurrentCursorPos(PLAYER_POS_X + i, PLAYER_POS_Y); printf("%c", PlayerModel[i]); }
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	SetCurrentCursorPos(PLAYER_POS_X, PLAYER_POS_Y);
}
//�÷��̾� ���� �Լ�
void HidePlayer() {
	for (int i = 0; i < 6; i++) { SetCurrentCursorPos(PLAYER_POS_X + i, PLAYER_POS_Y); printf(" "); }
	SetCurrentCursorPos(PLAYER_POS_X, PLAYER_POS_Y);
}

//---------------------������ �� ������ ������ ���� ó�� �Լ�--------------------------

//�÷��̾� ���� ���� �΋H���� �� ����ϴ� �Լ�
int DetectCollision_PlayerwithWall(int x, int y) {
	for (int i = 0; i < 6; i++) {
		if (UniBoard[y - GAMEBOARD_ORIGIN_Y][x - GAMEBOARD_ORIGIN_X + i] == WALL) return 1;
	}
	return 0;
}
//�÷��̾� ���� ���� �΋H���� �� ����ϴ� �Լ�
int DetectCollision_PlayerwithEnemy(int x, int y) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 5; k++) {
				if (ENEMY_POS_Y + j == PLAYER_POS_Y && ENEMY_POS_X + k == PLAYER_POS_X + i) return 1;
			}
		}
	}
	return 0;
}

int DetectCollision_PlayerwithBullet(int x, int y) {
	for (int i = 0; i < 6; i++) {
		if (UniBoard[y - GAMEBOARD_ORIGIN_Y][x - GAMEBOARD_ORIGIN_X + i] == BULLET) return 1;
	}
	return 0;
}

//�÷��̾� ���� �����۰� �ε����� �� �˻��ϴ� �Լ�
int DetectCollision_PlayerwithItem(int x, int y) {
	if (itemFLAG) {
		for (int i = 0; i < 6; i++) {
			if (x == PLAYER_POS_X + i && y == PLAYER_POS_Y) return 1;
		}
	}
	return 0;
}

//������ ������ ����
void ReduceLifeGauge(int damage) {
	CurrentLife -= damage;
	for (int i = 0; i < SelectedLife; i++) { if (i >= CurrentLife) LifeGauge[i] = 0; }
}

//������ ó���Լ�
void GetDamagedFromEnemy() {
	if (UsingSkill == 3) return;
	if (Invinsible == 1) { if (TimeCheckerEnd() - CollisionTime - PausingTime > InvinsibleTime) Invinsible = 0; }		//������ ���¿��� ���ӽð��� ������ �����ϴ� �Լ�
	if (DetectCollision_PlayerwithBullet(PLAYER_POS_X, PLAYER_POS_Y) && Invinsible == 0) {
		ReduceLifeGauge(BULLETDAMAGE);
		InvalidateLifeGauge();												//������ ������ ������ �������� ���� ���� ����
		Invinsible = 1; CollisionTime = TimeCheckerEnd() - PausingTime;		//�������·� ����� �浹�� �ð� ����
		return;
	}
	if (DetectCollision_PlayerwithEnemy(PLAYER_POS_X, PLAYER_POS_Y) && Invinsible == 0) { 
		ReduceLifeGauge(ENEMYDAMAGE);
		InvalidateLifeGauge();												//������ ������ ������ �������� ���� ���� ����
		Invinsible = 1; CollisionTime = TimeCheckerEnd() - PausingTime;		//�������·� ����� �浹�� �ð� ����
		return;
	}
}


//-----------------------------------------------------------------------------------------------

//--------------------------����� �Է� Ű�� ���� ��ġ ��ȯ �� ��ų ��� �Լ�------------------------------
//����� �Է� Ű�� ���� ��ġ ��ȯ �Լ�

void shiftUp() {
	HidePlayer();
	if (!DetectCollision_PlayerwithWall(PLAYER_POS_X, PLAYER_POS_Y - 1)) PLAYER_POS_Y--;
	ShowPlayer();
}
void shiftDown() {
	HidePlayer();
	if (!DetectCollision_PlayerwithWall(PLAYER_POS_X, PLAYER_POS_Y + 1)) PLAYER_POS_Y++;
	ShowPlayer();
}
void shiftLeft() {
	HidePlayer();
	if (!DetectCollision_PlayerwithWall(PLAYER_POS_X - 1, PLAYER_POS_Y)) PLAYER_POS_X--;
	ShowPlayer();
}
void shiftRight() {
	HidePlayer();
	if (!DetectCollision_PlayerwithWall(PLAYER_POS_X + 1, PLAYER_POS_Y)) PLAYER_POS_X++;
	ShowPlayer();
}

//------------------------------------------------------------------------------------------------------------------

//-------------------------------------�÷��̾� ���� �Լ�-------------------------------------------------------
void InvalidatePlayer() {
	ShowPlayer();
	if (DetectCollision_PlayerwithItem(ITEM_POS_X, ITEM_POS_Y)) ItemCollisionDetected = 1;
	if (!CalculatePlayerTimeBuffer()) {
		if (kbhit()) {
			if (GetAsyncKeyState(SPACE) & 0x0001) ActivateSkillItem();
			if (GetAsyncKeyState(VK_LSHIFT) & 0x0001) SwapItem();
			if (GetAsyncKeyState(QUIT) & 0x0001) GamePause();
			if (GetAsyncKeyState(LEFT) & 0x8000) shiftLeft();
			if (GetAsyncKeyState(RIGHT) & 0x8000) shiftRight();
			if (GetAsyncKeyState(UP) & 0x8000) shiftUp();
			if (GetAsyncKeyState(DOWN) & 0x8000) shiftDown();
		}
	}
	SkillTimeCheck();
	GetDamagedFromEnemy();
}
//--------------------------------------------------------------------------------------------------------------------
#endif // !PLAYER_H