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

//사용자 입력 키 아스키 코드
#define LEFT VK_LEFT
#define RIGHT VK_RIGHT
#define UP VK_UP
#define DOWN VK_DOWN
#define PLAYER 4
#define PLAYERCOLOR 3
#define PLAYERINVINSIBLEINDICATECOLOR 6

//플레이어 시작 위치
int PLAYER_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
int PLAYER_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN - 8;

//플레이어 우주선
char PlayerModel[6];
char PlayerUniModel[6] = { 4,4,4,4,4,4 };

//플레이어 무적상태 및 무적상태 지속시간, 총알 및 적 우주선과 충돌한 시간
int Invinsible = 0; int InvinsibleTime = 1; double CollisionTime = 0;

//플레이어 유니보드 위치 갱신 함수
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

//플레이어 출력 및 삭제 함수
void ShowPlayer() {
	COORD ptr = { PLAYER_POS_X, PLAYER_POS_Y };
	InsertPlayer();
	if (Invinsible) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERINVINSIBLEINDICATECOLOR);
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERCOLOR);
	for (int i = 0; i < 6; i++) { SetCurrentCursorPos(ptr.X + i, ptr.Y); printf("%c", PlayerModel[i]); }
	SetCurrentCursorPos(ptr.X, ptr.Y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void HidePlayer() {
	COORD ptr = { PLAYER_POS_X, PLAYER_POS_Y };
	ErasePlayer();
	for (int i = 0; i < 6; i++) { SetCurrentCursorPos(ptr.X + i, ptr.Y); printf(" "); }
	SetCurrentCursorPos(ptr.X, ptr.Y);
}

//플레이어 기준 충돌 함수
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

//데미지 처리함수
void GetDamagedFromEnemy() {
	if (Invinsible == 1) { if (TimeCheckerEnd() - CollisionTime > InvinsibleTime) Invinsible = 0; }
	if (DetectCollision_PlayerwithEnemy(PLAYER_POS_X, PLAYER_POS_Y) && Invinsible == 0) { 
		ReduceLifeGauge(ENEMYDAMAGE); 
		Invinsible = 1; CollisionTime = TimeCheckerEnd();		//무적상태로 만들고 충돌한 시간 갱신
	}
}

//사용자 입력 키에 따라 위치 변환 함수
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

//플레이어 갱신 함수
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