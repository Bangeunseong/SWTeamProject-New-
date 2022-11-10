#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "VariableSets.h"
#include "CursorFunctions.h"
#include "Timer.h"
#ifndef UI_H
#define UI_H

//초기 X, Y좌표
int modifiedX_Text = BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 28;
int modifiedY_Text = BACKGROUND_ORIGIN_Y;

//스테이지 번호 출력
void InvalidateStageNumber() {
	COORD ptr = { BACKGROUND_ORIGIN_X, BACKGROUND_ORIGIN_Y };
	int modifiedX = ptr.X + 2, modifiedY = ptr.Y + 1;
	SetCurrentCursorPos(modifiedX, modifiedY);
	printf("Stage : %d", StageNumber);
}

//---------------라이프 게이지 관련 함수----------------
//라이프 게이지 동적할당
void InitializeLifeGauge() { 
	LifeGauge = (int *)malloc(sizeof(int)*SelectedLife); for (int i = 0; i < SelectedLife; i++) LifeGauge[i] = 1;
	CurrentLife = SelectedLife;
	COORD ptr = { BACKGROUND_ORIGIN_X, BACKGROUND_ORIGIN_Y };
	int modifiedX = ptr.X + 2, modifiedY = ptr.Y + 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	for (int i = 0; i < SelectedLife; i++) { SetCurrentCursorPos(modifiedX + i * 2, modifiedY); if (LifeGauge[i] == 1) printf("♥"); }
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	SetCurrentCursorPos(ptr.X, ptr.Y);
}

//라이프 게이지 UI 갱신
void InvalidateLifeGauge() {
	COORD ptr = { BACKGROUND_ORIGIN_X, BACKGROUND_ORIGIN_Y };
	int modifiedX = ptr.X + 2, modifiedY = ptr.Y + 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	for (int i = 0; i < SelectedLife; i++) { 
		SetCurrentCursorPos(modifiedX + i * 2, modifiedY); 
		if (LifeGauge[i] == 1) printf("♥"); 
		else { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); printf("♥"); }
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	SetCurrentCursorPos(ptr.X, ptr.Y);
}
//----------------------------------------------------------

//-----------------맵 관련 함수----------------------
//맵 내 캐릭터 위치 커서 숨기는 함수
void HidePlayerPosCursor(int x, int y) {
	SetCurrentCursorPos(x, y);
	printf("  ");
}

//맵 내 캐릭터 위치 커서 나타내는 함수
void ShowPlayerPosCursor(int x, int y) {
	SetCurrentCursorPos(x, y);
	printf("↑");
}

//맵 그리기
void ShowMap() {
	COORD ptr = { BACKGROUND_ORIGIN_X + BACKGROUND_ROW, BACKGROUND_ORIGIN_Y };
	int modifiedX = ptr.X - 32, modifiedY = ptr.Y + 1;
	for (int i = 0; i <= MAPLENGTH; i++) {
		SetCurrentCursorPos(modifiedX + 2 * i, modifiedY);
		if (i == 0) printf("├");
		else if (i == MAPLENGTH) printf("┤");
		else if (i % 5 == 0) printf("┼");
		else printf("┬");
	}
	SetCurrentCursorPos(GAMEBOARD_ORIGIN_X, GAMEBOARD_ORIGIN_Y);
}

//맵 내 캐릭터 위치 갱신
void InvalidateMap() {
	COORD ptr = { BACKGROUND_ORIGIN_X + BACKGROUND_ROW, BACKGROUND_ORIGIN_Y };
	int modifiedX = ptr.X - 32, modifiedY = ptr.Y + 1;
	ShowPlayerPosCursor(modifiedX + CurrentTime - 1, modifiedY + 1);
	if (TimeCheckerEnd() > CurrentTime * (StageTime[StageNumber - 1] / (MAPLENGTH * 2))) {
		HidePlayerPosCursor(modifiedX + CurrentTime - 1, modifiedY + 1);
		CurrentTime++; PlayerPos++;
	}
	SetCurrentCursorPos(GAMEBOARD_ORIGIN_X, GAMEBOARD_ORIGIN_Y);
}
//-----------------------------------------------------

//--------------스킬 UI 관련 함수------------------

//전 보유스킬 및 보조스킬 숨기기
void HidePreviousCurrentNSubSkill() {
	int Skillstrlen = Strlen(Skillstr), SubSkillstrlen = Strlen(SubSkillstr);
	int Currentlen = Strlen(SkillSets[CurSkill]), Sublen = Strlen(SkillSets[SubSkill]);
	int len = 23;
	for (int i = 1; i <= 2; i++) {
		for (int j = 0; j <= len; j++) {
			SetCurrentCursorPos(modifiedX_Text + j, modifiedY_Text + i);
			printf(" ");
		}
	}
}

//현재 보유스킬 및 보조스킬  출력
void ShowCurrentNSubSkill() {
	SetCurrentCursorPos(modifiedX_Text, modifiedY_Text + 1);
	printf("%s %s", Skillstr, SkillSets[CurSkill]);
	SetCurrentCursorPos(modifiedX_Text, modifiedY_Text + 2);
	printf("%s %s", SubSkillstr, SkillSets[SubSkill]);
}

//---------------------------------------------------

#endif // !UI_H