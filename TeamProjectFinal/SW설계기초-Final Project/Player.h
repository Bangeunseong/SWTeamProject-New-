#pragma once
#pragma warning(disable:4996)
#include <conio.h>
#include <WinUser.h>
#include <string.h>
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Item.h"
#include "Timer.h"
#include "UI.h"
#include "SoundPlay.h"
#ifndef PLAYER_H
#define PLAYER_H

//�÷��̾� ��ǲŸ�� ���� �ð� ��� �Լ�
int CalculatePlayerTimeBuffer() {
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime - PlayerInputTime > PLAYERTIMEBUFFER / CurSpeed) { PlayerInputTime = CheckedTime; return 0; }
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
	PLAYER_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - PlayerLevel;
	PLAYER_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN - 10;
}

//�÷��̾� ��� �Լ�
void ShowPlayer() {
	if (Invinsible) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERINVINSIBLEINDICATECOLOR);
	else if (UsingSkill > 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERUSINGSKILLCOLOR);
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERCOLOR);
	for (int i = 0; i < PlayerLevel * 2; i++) { SetCurrentCursorPos(PLAYER_POS_X + i, PLAYER_POS_Y); printf("%c", PlayerModel[PlayerModelIndex][PlayerLevel - 1][i]); }
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	SetCurrentCursorPos(PLAYER_POS_X, PLAYER_POS_Y);
}
//�÷��̾� ���� �Լ�
void HidePlayer() {
	for (int i = 0; i < PlayerLevel * 2; i++) { SetCurrentCursorPos(PLAYER_POS_X + i, PLAYER_POS_Y); printf(" "); }
	SetCurrentCursorPos(PLAYER_POS_X, PLAYER_POS_Y);
}

//---------------------������ �� ������ ������ ���� ó�� �Լ�--------------------------

//�÷��̾� ���� ���� �΋H���� �� ����ϴ� �Լ�
int DetectCollision_PlayerwithWall(int x, int y) {
	for (int i = 0; i < PlayerLevel * 2; i++) {
		if (EnemySkillPrisonActivation) {
			if (y <= P.LU_Y || y >= P.RD_Y) return 1;
			if ((x + i < P.LU_X + 2) || (x + i >= P.RD_X)) return 1;
		}
		else { if (UniBoard[y - GAMEBOARD_ORIGIN_Y][x - GAMEBOARD_ORIGIN_X + i] == WALL) return 1; }
	}
	return 0;
}
//�÷��̾� ���� ���� �΋H���� �� ����ϴ� �Լ�
int DetectCollision_PlayerwithEnemy(int x, int y) {
	for (int i = 0; i < PlayerLevel * 2; i++) {
		for (int j = 0; j < ENEMYSIZE_H; j++) {
			for (int k = 0; k < ENEMYSIZE_W; k++) {
				if (EnemyModel[j][k] != ' ')
					if (ENEMY_POS_Y + j == PLAYER_POS_Y && ENEMY_POS_X + k == PLAYER_POS_X + i) return 1;
			}
		}
	}
	return 0;
}

int DetectCollision_PlayerwithBullet(int x, int y) {
	for (int i = 0; i < PlayerLevel * 2; i++) {
		if (UniBoard[y - GAMEBOARD_ORIGIN_Y][x - GAMEBOARD_ORIGIN_X + i] == BULLET) return 1;
	}
	return 0;
}

//�÷��̾� ���� �����۰� �ε����� �� �˻��ϴ� �Լ�
int DetectCollision_PlayerwithItem(int x, int y) {
	if (itemFLAG) {
		for (int i = 0; i < PlayerLevel * 2; i++) {
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
		if (PlayerLevel < 2) {		//�÷��̾� ���� 2 ������ ��� ������ 1�� ����
			ReduceLifeGauge(BULLETDAMAGE);
			InvalidateLifeGauge();												//������ ������ ������ �������� ���� ���� ����
		}
		else PlayerLevel--;
		Invinsible = 1; CollisionTime = TimeCheckerEnd() - PausingTime;		//�������·� ����� �浹�� �ð� ����
		return;
	}
	if (DetectCollision_PlayerwithEnemy(PLAYER_POS_X, PLAYER_POS_Y) && Invinsible == 0) { 
		if (PlayerLevel == 3)	//�÷��̾� ���� 3�� ��� 2�ܰ� ����
			PlayerLevel -= 2;	
		else if (PlayerLevel == 2) {	//�÷��̾� ���� 2�� ��� 1�ܰ� ���� �� ������ 1 ����
			ReduceLifeGauge(BULLETDAMAGE);
			InvalidateLifeGauge();												//������ ������ ������ �������� ���� ���� ����
			PlayerLevel--;
		}
		else {	//�÷��̾� ���� 1�� ��� ������ 2 ����
			ReduceLifeGauge(ENEMYDAMAGE);
			InvalidateLifeGauge();												//������ ������ ������ �������� ���� ���� ����
		}
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

//-------------------------------------�÷��̾� �Ѿ� ���� �Լ�------------------------------------------

int CalculateP_BulletTimeBuffer() {
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	if (CheckedTime - P_BulletInputTime > P_BULLETTIMEBUFFER / P_BulletSpeed) { P_BulletInputTime += P_BULLETTIMEBUFFER / P_BulletSpeed; return 0; }
	else return 1;
}

void HideP_Bullet(int P_bulletnumber) {
	SetCurrentCursorPos(PB[P_bulletnumber].P_BULLET_POS_X, PB[P_bulletnumber].P_BULLET_POS_Y);
	printf(" ");
}

void ShowP_Bullet(int P_bulletnumber) {
	if (!PB[P_bulletnumber].BulletActivation) PB[P_bulletnumber].BulletActivation = 1;
	SetCurrentCursorPos(PB[P_bulletnumber].P_BULLET_POS_X, PB[P_bulletnumber].P_BULLET_POS_Y);
	printf("%c", PLAYERBULLETMODEL);
}

void ClearAll_PBulletPosition() {
	for (int i = 0; i < BULLETCOUNTLIMIT; i++) {
		HideP_Bullet(i);
		PB[i].BulletActivation = PB[i].CollisionEnemy = PB[i].CollisionWall = PB[i].inProgress = 0;
	}
	P_BULLETCOUNTSTART = 0;
	P_BULLETCOUNTEND = -1;
	P_BulletInputTime = 0;
}

void ClearSingle_PBulletPosition(int P_bulletnumber) {
	PB[P_bulletnumber].BulletActivation = PB[P_bulletnumber].CollisionEnemy = PB[P_bulletnumber].CollisionWall = PB[P_bulletnumber].inProgress = 0;
}

void P_BulletPositionRenewal(int P_bulletnumber) {
	if (PlayerLevel == 1) {
		if (P_bulletnumber % 2 == 0) { PB[P_bulletnumber].P_BULLET_POS_X = PLAYER_POS_X; PB[P_bulletnumber].P_BULLET_POS_Y = PLAYER_POS_Y; }
		else { PB[P_bulletnumber].P_BULLET_POS_X = PLAYER_POS_X + 1; PB[P_bulletnumber].P_BULLET_POS_Y = PLAYER_POS_Y; }
	}
	else if (PlayerLevel == 2) {
		if (P_bulletnumber % 2 == 0) { PB[P_bulletnumber].P_BULLET_POS_X = PLAYER_POS_X; PB[P_bulletnumber].P_BULLET_POS_Y = PLAYER_POS_Y; }
		else { PB[P_bulletnumber].P_BULLET_POS_X = PLAYER_POS_X + PlayerLevel * 2 - 1; PB[P_bulletnumber].P_BULLET_POS_Y = PLAYER_POS_Y; }
	}
	else {
		if (P_bulletnumber % 2 == 0) { PB[P_bulletnumber].P_BULLET_POS_X = PLAYER_POS_X; PB[P_bulletnumber].P_BULLET_POS_Y = PLAYER_POS_Y; }
		else if(P_bulletnumber % 2 == 1){ PB[P_bulletnumber].P_BULLET_POS_X = PLAYER_POS_X + PlayerLevel - 1; PB[P_bulletnumber].P_BULLET_POS_Y = PLAYER_POS_Y; }
		else if(P_bulletnumber % 2 == 2){ PB[P_bulletnumber].P_BULLET_POS_X = PLAYER_POS_X + PlayerLevel; PB[P_bulletnumber].P_BULLET_POS_Y = PLAYER_POS_Y; }
		else { PB[P_bulletnumber].P_BULLET_POS_X = PLAYER_POS_X + PlayerLevel *2 - 1; PB[P_bulletnumber].P_BULLET_POS_Y = PLAYER_POS_Y; }
	}
}

int DetectCollision_P_BulletwithWall(int x, int y) {
	if (UniBoard[y - GAMEBOARD_ORIGIN_Y][x - GAMEBOARD_ORIGIN_X] == WALL)
		return 1;
	return 0;
}

int DetectCollision_P_BulletwithEnemy(int x, int y) {
	for (int i = 0; i < ENEMYSIZE_H; i++) {
		for (int j = 0; j < ENEMYSIZE_W; j++) {
			if (EnemyModel[i][j] != ' ') {
				if (ENEMY_POS_X + j == x && ENEMY_POS_Y + i == y) return 1;
			}
		}
	}
	return 0;
}

int MoveP_Bullet_N(int P_bulletnumber) {
	if (!PB[P_bulletnumber].BulletActivation) return 0;

	HideP_Bullet(P_bulletnumber);
	if(DetectCollision_P_BulletwithEnemy(PB[P_bulletnumber].P_BULLET_POS_X, PB[P_bulletnumber].P_BULLET_POS_Y)){ PB[P_bulletnumber].BulletActivation = 0; PB[P_bulletnumber].CollisionEnemy = 1; return 0; }
	if (!DetectCollision_P_BulletwithWall(PB[P_bulletnumber].P_BULLET_POS_X, PB[P_bulletnumber].P_BULLET_POS_Y - 1)) PB[P_bulletnumber].P_BULLET_POS_Y--;
	else { PB[P_bulletnumber].BulletActivation = 0; PB[P_bulletnumber].CollisionWall = 1; return 0; }
	ShowP_Bullet(P_bulletnumber); return 1;
}

void P_BulletLaunch() {
	if (PlayerLevel <= 2) P_BULLETCOUNTEND += 2;
	else P_BULLETCOUNTEND += 4;
}

void InvalidateP_Bullet() {
	if (!CalculateP_BulletTimeBuffer()) {
		for (int i = P_BULLETCOUNTSTART; i <= P_BULLETCOUNTEND; i++) {
			if (!PB[i % BULLETCOUNTLIMIT].BulletActivation && !PB[i % BULLETCOUNTLIMIT].inProgress) {
				P_BulletPositionRenewal(i % BULLETCOUNTLIMIT); PB[i % BULLETCOUNTLIMIT].BulletActivation = PB[i % BULLETCOUNTLIMIT].inProgress = 1;
				ShowP_Bullet(i % BULLETCOUNTLIMIT);
			}
			if (!MoveP_Bullet_N(i % BULLETCOUNTLIMIT) && i == P_BULLETCOUNTSTART) { ClearSingle_PBulletPosition(i % BULLETCOUNTLIMIT); P_BULLETCOUNTSTART++; }
		}
	}
	else {
		for (int i = P_BULLETCOUNTSTART; i <= P_BULLETCOUNTEND; i++) {
			if (DetectCollision_P_BulletwithEnemy(PB[i % BULLETCOUNTLIMIT].P_BULLET_POS_X, PB[i % BULLETCOUNTLIMIT].P_BULLET_POS_Y)) {
				HideP_Bullet(i % BULLETCOUNTLIMIT);
				if (i == P_BULLETCOUNTSTART) { ClearSingle_PBulletPosition(i % BULLETCOUNTLIMIT); P_BULLETCOUNTSTART++; }
				else PB[i % BULLETCOUNTLIMIT].BulletActivation = 0; PB[i % BULLETCOUNTLIMIT].CollisionEnemy = 1; 
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------------

//-------------------------------------�÷��̾� ���� �Լ�-------------------------------------------------------
void InvalidatePlayer() {
	ShowPlayer();
	if (DetectCollision_PlayerwithItem(ITEM_POS_X, ITEM_POS_Y)) ItemCollisionDetected = 1;
	if (!CalculatePlayerTimeBuffer()) {
		if (kbhit()) {
			if (GetAsyncKeyState(LEFT) & 0x8000) shiftLeft();
			if (GetAsyncKeyState(RIGHT) & 0x8000) shiftRight();
			if (GetAsyncKeyState(UP) & 0x8000) shiftUp();
			if (GetAsyncKeyState(DOWN) & 0x8000) shiftDown();
			if (GetAsyncKeyState(BULLETLAUNCH) & 0x0001) P_BulletLaunch();
			if (GetAsyncKeyState(SKILLACTIVE) & 0x0001) ActivateSkillItem();
			if (GetAsyncKeyState(SWAP) & 0x0001) SwapItem();
			if (GetAsyncKeyState(QUIT) & 0x0001) GamePause();
		}
	}
	SkillTimeCheck();
	GetDamagedFromEnemy();
}
//--------------------------------------------------------------------------------------------------------------------
#endif // !PLAYER_H