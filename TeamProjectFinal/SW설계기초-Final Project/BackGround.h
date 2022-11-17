#pragma once
#include <stdio.h>
#include <Windows.h>
#include "VariableSets.h"
#ifndef BACKGROUND_H
#define BACKGROUND_H

//게임영역 이산 테이블 선언
void InitUniBoard() {
	for (int i = 0; i <= GAMEBOARD_COLUMN; i++) {
		UniBoard[i][0] = UniBoard[i][GAMEBOARD_ROW + 1] = UniBoard[i][1] = UniBoard[i][GAMEBOARD_ROW] = 1;
	}
	for (int j = 0; j <= GAMEBOARD_ROW + 1; j++) {
		UniBoard[0][j] = UniBoard[GAMEBOARD_COLUMN][j] = 1;
	}
}

//게임영역 백그라운드 출력
void ShowBackGround() {
	COORD b_ptr = { BACKGROUND_ORIGIN_X, BACKGROUND_ORIGIN_Y };
	for (int i = 0; i < BACKGROUND_COLUMN - GAMEBOARD_COLUMN; i++) {
		SetCurrentCursorPos(b_ptr.X, b_ptr.Y + i);
		if(i == 0) printf("┏");
		else printf("┃");
		SetCurrentCursorPos(b_ptr.X + BACKGROUND_ROW, b_ptr.Y + i);
		if (i == 0) printf("┓");
		else printf("┃");
	}
	SetCurrentCursorPos(b_ptr.X, b_ptr.Y);
	for (int i = 2; i < BACKGROUND_ROW; i += 2) {
		SetCurrentCursorPos(b_ptr.X + i, b_ptr.Y);
		printf("━");
	}
	SetCurrentCursorPos(b_ptr.X, b_ptr.Y);

	COORD ptr = { GAMEBOARD_ORIGIN_X, GAMEBOARD_ORIGIN_Y };
	for (int i = 0; i <= GAMEBOARD_COLUMN; i++) {
		SetCurrentCursorPos(ptr.X, ptr.Y + i);
		if (i == 0) printf("┣");
		else if (i == GAMEBOARD_COLUMN) printf("┗");
		else printf("┃");
		SetCurrentCursorPos(ptr.X + GAMEBOARD_ROW, ptr.Y + i);
		if (i == 0) printf("┫");
		else if (i == GAMEBOARD_COLUMN) printf("┛");
		else printf("┃");
	}
	SetCurrentCursorPos(ptr.X, ptr.Y);
	for (int i = 2; i < GAMEBOARD_ROW; i += 2) {
		SetCurrentCursorPos(ptr.X + i, ptr.Y);
		printf("━");
		SetCurrentCursorPos(ptr.X + i, ptr.Y + GAMEBOARD_COLUMN);
		printf("━");
	}
	SetCurrentCursorPos(ptr.X, ptr.Y);
}

//이산 테이블 출력
void ShowUniBoard() {
	SetCurrentCursorPos(GAMEBOARD_ORIGIN_X, GAMEBOARD_ORIGIN_Y);
	COORD ptr = GetCurrentCursorPos();
	for (int i = 0; i <= GAMEBOARD_COLUMN; i++) {
		for (int j = 0; j < GAMEBOARD_ROW + 2; j++) {
			SetCurrentCursorPos(ptr.X + j, ptr.Y + i);
			printf("%d", UniBoard[i][j]);
		}
	}
	SetCurrentCursorPos(ptr.X, ptr.Y);
}
#endif // !BACKGROUND_H