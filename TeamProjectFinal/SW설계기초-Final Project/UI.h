#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "CursorFunctions.h"
#include "BackGround.h"
#include "PlayerInfo.h"
#include "Timer.h"
#ifndef UI_H
#define UI_H


//-----------------다양한 변수들-----------------
//Modified 함수
int Strlen(const char *src) {
	int cnt = 0;
	for (const char *p = src; *p != '-'; p++) cnt++;
	return cnt + 1;
}

//초기 X, Y좌표
int modifiedX_Text = BACKGROUND_ORIGIN_X + 2;
int modifiedY_Text = BACKGROUND_ORIGIN_Y + 2;
//----------------------------------------------------

//---------------라이프 게이지 관련 함수----------------
//라이프 게이지 동적할당
void InitializeLifeGauge() { 
	LifeGauge = (int *)malloc(sizeof(int)*SelectedLife); for (int i = 0; i < SelectedLife; i++) LifeGauge[i] = 1;
	CurrentLife = SelectedLife;
	COORD ptr = { BACKGROUND_ORIGIN_X, BACKGROUND_ORIGIN_Y };
	int modifiedX = ptr.X + 2, modifiedY = ptr.Y + 1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	for (int i = 0; i < SelectedLife; i++) { SetCurrentCursorPos(modifiedX + i * 2, modifiedY); if (LifeGauge[i] == 1) printf("♥"); }
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	SetCurrentCursorPos(ptr.X, ptr.Y);
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

		ShowPlayerPosCursor(modifiedX + second - 1, modifiedY + 1);
		if (DetectTimeFromTimeChecker()) { 
			HidePlayerPosCursor(modifiedX + second - 1, modifiedY + 1);
			second++; PlayerPos++;
		}
	}
	SetCurrentCursorPos(GAMEBOARD_ORIGIN_X, GAMEBOARD_ORIGIN_Y);
}
//-----------------------------------------------------

//--------------스킬 관련 함수-----------------
//스킬 사용 시 스킬 갱신
int InvalidateCurrentSkill() {
	if (SubSkill == 0) return 0;
	if (CurSkill == 0) { int tmp = CurSkill; CurSkill = SubSkill; SubSkill = tmp; return 1; }
	else return 0;
}

//전 보유스킬 및 보조스킬 숨기기
void HidePreviousCurrentNSubSkill() {
	int Skillstrlen = Strlen(Skillstr), SubSkillstrlen = Strlen(SubSkillstr);
	int Currentlen = Strlen(SkillSets[CurSkill]), Sublen = Strlen(SkillSets[SubSkill]);
	for (int i = 0; i < Skillstrlen + SubSkillstrlen + Currentlen + Sublen + 2; i++) {
		SetCurrentCursorPos(modifiedX_Text + i, modifiedY_Text);
		if (i >= Skillstrlen && i < Currentlen + Skillstrlen) printf(" ");
		else if (i >= Currentlen + Skillstrlen + SubSkillstrlen + 2) printf(" ");
	}
}

//현재 보유스킬 및 보조스킬  출력
void ShowCurrentNSubSkill() {
	int Skillstrlen = Strlen(Skillstr), SubSkillstrlen = Strlen(SubSkillstr);
	int Currentlen = Strlen(SkillSets[CurSkill]), Sublen = Strlen(SkillSets[SubSkill]);
	for (int i = 0; i < Skillstrlen + SubSkillstrlen + Currentlen + Sublen + 2; i++) {
		SetCurrentCursorPos(modifiedX_Text + i, modifiedY_Text);
		if (i >= Skillstrlen && i < Currentlen + Skillstrlen) printf("%c", SkillSets[CurSkill][i - Skillstrlen]);
		else if (i >= Currentlen + Skillstrlen + SubSkillstrlen + 2) printf("%c", SkillSets[SubSkill][i - (Currentlen + Skillstrlen + SubSkillstrlen + 2)]);
	}
}

//스킬 텍스트 갱신
void InvalidateSkillUI() {
	SetCurrentCursorPos(modifiedX_Text, modifiedY_Text);
	printf(Skillstr);
	SetCurrentCursorPos(modifiedX_Text + Strlen(SkillSets[CurSkill]) + Strlen(Skillstr) + 2, modifiedY_Text);
	printf(SubSkillstr);
	ShowCurrentNSubSkill();
	if (InvalidateCurrentSkill())
		HidePreviousCurrentNSubSkill();
}
//---------------------------------------------------

//UI 갱신
void InvalidateUI() { InvalidateMap(); InvalidateSkillUI(); }

#endif // !UI_H