#pragma once
#pragma warning(disable:4996)
#include <conio.h>
#include <WinUser.h>
#include "CursorFunctions.h"
#include "BackGround.h"
#include "Enemy.h"
#include "UIandInfo.h"
#ifndef PLAYER_H
#define PLAYER_H

//����� �Է� Ű �ƽ�Ű �ڵ�
#define LEFT VK_LEFT
#define RIGHT VK_RIGHT
#define UP VK_UP
#define DOWN VK_DOWN
#define PLAYER 4

//�÷��̾� ���� ��ġ
int PLAYER_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
int PLAYER_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN - 8;

//�÷��̾� ���ּ�
char PlayerModel[6];
char PlayerUniModel[6] = { 4,4,4,4,4,4 };

//�÷��̾� ���Ϻ��� ��ġ ���� �Լ�
void ErasePlayer() {
	for (int i = 0; i < 6; i++) {
		UniBoard[PLAYER_POS_Y - GAMEBOARD_ORIGIN_Y][PLAYER_POS_X - GAMEBOARD_ORIGIN_X + i] = 0;
	}
}
void InsertPlayer() {
	for (int i = 0; i < 6; i++) {
		UniBoard[PLAYER_POS_Y - GAMEBOARD_ORIGIN_Y][PLAYER_POS_X - GAMEBOARD_ORIGIN_X + i] = PLAYER;
	}
}

//�÷��̾� ��� �� ���� �Լ�
void ShowPlayer() {
	COORD ptr = { PLAYER_POS_X, PLAYER_POS_Y };
	InsertPlayer();
	for (int i = 0; i < 6; i++) { SetCurrentCursorPos(ptr.X + i, ptr.Y); printf("%c", PlayerModel[i]); }
	SetCurrentCursorPos(ptr.X, ptr.Y);
}
void HidePlayer() {
	COORD ptr = { PLAYER_POS_X, PLAYER_POS_Y };
	ErasePlayer();
	for (int i = 0; i < 6; i++) { SetCurrentCursorPos(ptr.X + i, ptr.Y); printf(" "); }
	SetCurrentCursorPos(ptr.X, ptr.Y);
}

//�÷��̾� ���� �浹 �Լ�
int DetectCollision_PlayerwithWall(int x, int y) {
	for (int i = 0; i < 6; i++) {
		if (UniBoard[y - GAMEBOARD_ORIGIN_Y][x - GAMEBOARD_ORIGIN_X + i] == 1) return 1;
	}
	return 0;
}
int DetectCollision_PlayerwithEnemy(int x, int y) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 5; k++) {
				if (EnemyUniModel[j][k] == ENEMY) { 
					if (ENEMY_POS_Y + j == PLAYER_POS_Y && ENEMY_POS_X + k == PLAYER_POS_X + i) return 1;
				}
			}
		}
	}
	return 0;
}

//������ ó���Լ�
void GetDamagedFromEnemy() {
	if (DetectCollision_PlayerwithEnemy(PLAYER_POS_X, PLAYER_POS_Y)) { ReduceLifeGauge(ENEMYDAMAGE); };
}

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
	if (!DetectCollision_PlayerwithWall(PLAYER_POS_X - speed, PLAYER_POS_Y)) PLAYER_POS_X -= speed;
	else PLAYER_POS_X = GAMEBOARD_ORIGIN_X + 2;
	ShowPlayer();
}
void shiftRight() {
	HidePlayer();
	if (!DetectCollision_PlayerwithWall(PLAYER_POS_X + speed, PLAYER_POS_Y)) PLAYER_POS_X += speed;
	else PLAYER_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW - strlen(PlayerModel);
	ShowPlayer();
}

//�÷��̾� ���� �Լ�
void InvalidatePlayer() {
	ShowPlayer();
	if (kbhit()) {
		if (GetAsyncKeyState(LEFT) & 0x8000) shiftLeft();
		if (GetAsyncKeyState(RIGHT) & 0x8000) shiftRight();
		if (GetAsyncKeyState(UP) & 0x8000) shiftUp();
		if (GetAsyncKeyState(DOWN) & 0x8000) shiftDown();
	}
	GetDamagedFromEnemy();
}
#endif // !PLAYER_H