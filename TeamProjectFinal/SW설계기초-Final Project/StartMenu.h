#pragma once
#pragma warning(disable:4996)
#include <conio.h>
#include "CursorFunctions.h"
#include "BackGround.h"
#ifndef STARTMENU_H
#define STARTMENU_H

#define SPACE 32
#define QUIT 120

//인트로 화면 출력
void ShowIntro() {
	COORD center = { BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 };
	int modifiedX = center.X - 52, modifiedY = center.Y - 5;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				SetCurrentCursorPos(modifiedX + i * 12 + 2 * k, modifiedY + j);
				if (IntroModel[i][j][k] == 1) printf("■");
			}
		}
	}
	SetCurrentCursorPos(center.X - 12, center.Y + 5);
	printf("Press SpaceBar to Start");
	SetCurrentCursorPos(center.X - 8, center.Y + 7);
	printf("Press x to Exit");
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X, BACKGROUND_ORIGIN_Y);
}

//인트로 화면 삭제
void HideIntro() {
	COORD center = { BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 };
	int modifiedX = center.X - 52, modifiedY = center.Y - 5;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				SetCurrentCursorPos(modifiedX + i * 12 + 2 * k, modifiedY + j);
				if (IntroModel[i][j][k] == 1) printf("  ");
			}
		}
	}
	for (int i = 0; i < 24; i++) { SetCurrentCursorPos(center.X - 12 + i, center.Y + 5); puts(" "); }
	for (int i = 0; i < 16; i++) { SetCurrentCursorPos(center.X - 8 + i, center.Y + 7); puts(" "); }
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X, BACKGROUND_ORIGIN_Y);
}

//게임 시작 메뉴
void StartMenu() {
	ShowIntro();
	while (1) {
		if (kbhit()) {
			switch (getch()) {
			case SPACE: HideIntro(); return;
			case QUIT: return;
			default: break;
			}
		}
	}
}
#endif // !STARTMENU_H