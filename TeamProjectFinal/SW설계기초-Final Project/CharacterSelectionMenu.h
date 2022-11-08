#pragma once
#include <Windows.h>
#include <stdio.h>
#include "ResizeConsole.h"
#include "CursorFunctions.h"
#include "Player.h"
#include "PlayerInfo.h"
#ifndef CHARACTERSELECTION_H
#define CHARACTERSELECTION_H

//캐릭터 박스 Dimension
#define CHARACTERBOX_ROW 28
#define CHARACTERBOX_COLUMN 20
#define CHARACTERBOX_ORIGIN_X 6
#define CHARACTERBOX_ORIGIN_Y 12

INPUT_RECORD rec;
DWORD dwNOER;
DWORD CIN;
DWORD mode;

//캐릭터 선택 박스 만드는 함수
void CreateSelectionBox(int x, int y) {
	COORD ptr = { x,y };
	for (int i = 0; i <= CHARACTERBOX_COLUMN; i++) {
		SetCurrentCursorPos(ptr.X, ptr.Y + i);
		if (i == 0) printf("┏");
		else if (i == CHARACTERBOX_COLUMN) printf("┗");
		else printf("┃");
		SetCurrentCursorPos(ptr.X + CHARACTERBOX_ROW, ptr.Y + i);
		if (i == 0) printf("┓");
		else if (i == CHARACTERBOX_COLUMN) printf("┛");
		else printf("┃");
	}
	SetCurrentCursorPos(ptr.X, ptr.Y);
	for (int i = 2; i < CHARACTERBOX_ROW; i += 2) {
		SetCurrentCursorPos(ptr.X + i, ptr.Y);
		printf("━");
		SetCurrentCursorPos(ptr.X + i, ptr.Y + CHARACTERBOX_COLUMN);
		printf("━");
	}
}

//마우스 클릭 이벤트 받는 함수
void CharacterBoxClick(int *xx, int *yy) {
	while (1)
	{
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rec, 1, &dwNOER); // 콘솔창 입력을 받아들임.
		if (rec.EventType == MOUSE_EVENT) {// 마우스 이벤트일 경우
			if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) { // 좌측 버튼이 클릭되었을 경우
				int mouse_x = rec.Event.MouseEvent.dwMousePosition.X; // X값 받아옴
				int mouse_y = rec.Event.MouseEvent.dwMousePosition.Y; // Y값 받아옴

				*xx = mouse_x; //x값을 넘김
				*yy = mouse_y; //y값을 넘김
				break;
			}
		}
	}
}

//캐릭터 선택 박스 출력 함수
void ShowCharacterBox() {
	//Print Text
	SetCurrentCursorPos(CHARACTERBOX_ORIGIN_X + CHARACTERBOX_ROW * 2 - CHARACTERBOX_ROW / 2 - 17, CHARACTERBOX_ORIGIN_Y - 5);
	printf("------------SELECT YOUR CHARACTER------------");

	//Character Box Number 1
	CreateSelectionBox(CHARACTERBOX_ORIGIN_X, CHARACTERBOX_ORIGIN_Y);
	SetCurrentCursorPos(CHARACTERBOX_ORIGIN_X + CHARACTERBOX_ROW / 2 - 2, CHARACTERBOX_ORIGIN_Y + CHARACTERBOX_COLUMN / 2);
	printf("<OAAO>");
	SetCurrentCursorPos(CHARACTERBOX_ORIGIN_X + CHARACTERBOX_ROW / 2 - 10, CHARACTERBOX_ORIGIN_Y + CHARACTERBOX_COLUMN + 2);
	printf("Health : 7   Speed : 1");

	//Character Box Number 2
	CreateSelectionBox(CHARACTERBOX_ORIGIN_X + CHARACTERBOX_ROW + 5, CHARACTERBOX_ORIGIN_Y);
	SetCurrentCursorPos(CHARACTERBOX_ORIGIN_X + CHARACTERBOX_ROW * 2 - CHARACTERBOX_ROW / 2 + 3, CHARACTERBOX_ORIGIN_Y + CHARACTERBOX_COLUMN / 2);
	printf("<-AA->");
	SetCurrentCursorPos(CHARACTERBOX_ORIGIN_X + CHARACTERBOX_ROW * 2 - CHARACTERBOX_ROW / 2 - 5, CHARACTERBOX_ORIGIN_Y + CHARACTERBOX_COLUMN + 2);
	printf("Health : 5   Speed : 2");

	//Character Box Number 3
	CreateSelectionBox(CHARACTERBOX_ORIGIN_X + CHARACTERBOX_ROW * 2 + 10, CHARACTERBOX_ORIGIN_Y);
	SetCurrentCursorPos(CHARACTERBOX_ORIGIN_X + CHARACTERBOX_ROW * 3 - CHARACTERBOX_ROW / 2 + 8, CHARACTERBOX_ORIGIN_Y + CHARACTERBOX_COLUMN / 2);
	printf("<-[]->");
	SetCurrentCursorPos(CHARACTERBOX_ORIGIN_X + CHARACTERBOX_ROW * 3 - CHARACTERBOX_ROW / 2, CHARACTERBOX_ORIGIN_Y + CHARACTERBOX_COLUMN + 2);
	printf("Health : 3   Speed : 3");
}

//캐릭터 박스 숨기는 함수
void HideCharacterBox() {
	COORD ptr = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', CONSOLE_ROW * CONSOLE_COLUMN, ptr, &dw);
}

//캐릭터 선택 화면 출력 함수
void ShowCharacterSelectionMenu() {

	//캐릭터 선택 창 띄우기
	ShowCharacterBox();

	//마우스 클릭을 통해 받은 출력 값을 가지고 명령 수행
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	int xx, yy;
	while (1) {
		CharacterBoxClick(&xx, &yy);
		if (yy >= CHARACTERBOX_ORIGIN_Y && yy <= CHARACTERBOX_ORIGIN_Y + CHARACTERBOX_COLUMN) {
			if (xx >= CHARACTERBOX_ORIGIN_X && xx <= CHARACTERBOX_ORIGIN_X + CHARACTERBOX_ROW) {
				SelectedLife = 7; SelectedSpeed = CurSpeed = 1; memcpy(PlayerModel, "<OAAO>", sizeof(char) * 6); break;
			}
			else if (xx >= CHARACTERBOX_ORIGIN_X + CHARACTERBOX_ROW + 5 && xx <= CHARACTERBOX_ORIGIN_X + CHARACTERBOX_ROW * 2 + 5) {
				SelectedLife = 5; SelectedSpeed = CurSpeed = 2; memcpy(PlayerModel, "<-AA->", sizeof(char) * 6); break;
			}
			else if (xx >= CHARACTERBOX_ORIGIN_X + CHARACTERBOX_ROW * 2 + 10 && xx <= CHARACTERBOX_ORIGIN_X + CHARACTERBOX_ROW * 3 + 10) {
				SelectedLife = 3; SelectedSpeed = CurSpeed = 3; memcpy(PlayerModel, "<-[]->", sizeof(char) * 6); break;
			}
		}
	}
	
	//캐릭터 선택 창 지우기
	HideCharacterBox();
}

#endif // !CHARACTERSELECTION_H