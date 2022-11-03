#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <time.h>
#include "BackGround.h"
#include "Player.h"
#ifndef UI_H
#define UI_H

//플레이어의 위치 및 라이프 게이지, 속도
int SelectedLife = 5; int CurrentLife; int *LifeGauge; int PlayerPos = 0; int speed = 2;

//라이프 게이지 동적할당
void InitializeLifeGauge() { 
	LifeGauge = (int *)malloc(sizeof(int)*SelectedLife); for (int i = 0; i < SelectedLife; i++) LifeGauge[i] = 1;
	CurrentLife = SelectedLife;
	COORD ptr = { BACKGROUND_ORIGIN_X, BACKGROUND_ORIGIN_Y };
	int modifiedX = ptr.X + 2, modifiedY = ptr.Y + 1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	for (int i = 0; i < SelectedLife; i++) { SetCurrentCursorPos(modifiedX + i * 2, modifiedY); if (LifeGauge[i] == 1) printf("♥"); }
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

//라이프 게이지 감소
void ReduceLifeGauge(int damage) {
	CurrentLife -= damage;
	for (int i = 0; i < SelectedLife; i++) { if (i >= CurrentLife) LifeGauge[i] = 0; }
}

//라이프 게이지 UI 갱신
void InvalidateLifeGauge() {
	COORD ptr = { BACKGROUND_ORIGIN_X, BACKGROUND_ORIGIN_Y };
	int modifiedX = ptr.X + 2, modifiedY = ptr.Y + 1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	for (int i = 0; i < SelectedLife; i++) { 
		SetCurrentCursorPos(modifiedX + i * 2, modifiedY); 
		if (LifeGauge[i] == 1) printf("♥"); 
		else { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); printf("♥"); }
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

//맵 내 캐릭터 위치 갱신
void InvalidateMap() {
	COORD ptr = { BACKGROUND_ORIGIN_X + BACKGROUND_ROW, BACKGROUND_ORIGIN_Y };
	int modifiedX = ptr.X - 38, modifiedY = ptr.Y + 1;
	for (int i = 0; i < 19; i++) {
		SetCurrentCursorPos(modifiedX + 2 * i, modifiedY);
		if (i == 0) printf("├");
		else if (i == 18) printf("┤");
		else if (i % 6 == 0) printf("┼");
		else printf("┬");
		SetCurrentCursorPos(modifiedX + 2 * PlayerPos, modifiedY + 1);
		printf("↑");
	}
	SetCurrentCursorPos(GAMEBOARD_ORIGIN_X, GAMEBOARD_ORIGIN_Y);
}

//UI 갱신
void InvalidateUI() { InvalidateLifeGauge(); InvalidateMap(); }

#endif // !UI_H