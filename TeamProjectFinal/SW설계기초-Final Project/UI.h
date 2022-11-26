#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Timer.h"
#ifndef UI_H
#define UI_H

//�ʱ� X, Y��ǥ
int modifiedX_Text = BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 28;
int modifiedY_Text = BACKGROUND_ORIGIN_Y;



//�������� ��ȣ ���
void InvalidatePlayerLevel() {
	COORD ptr = { BACKGROUND_ORIGIN_X, BACKGROUND_ORIGIN_Y };
	int modifiedX = ptr.X + 2, modifiedY = ptr.Y + 1;
	SetCurrentCursorPos(modifiedX, modifiedY);
	if(PlayerLevel < PLAYERMAXLEVEL) printf("P_Level %d", PlayerLevel);
	else { 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); 
		printf("MaxLevel!"); 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}

//---------------������ ������ ���� �Լ�----------------
//������ ������ �����Ҵ�
void InitializeLifeGauge() { 
	LifeGauge = (int *)malloc(sizeof(int)*SelectedLife); for (int i = 0; i < SelectedLife; i++) LifeGauge[i] = 1;
	CurrentLife = SelectedLife;
	COORD ptr = { BACKGROUND_ORIGIN_X, BACKGROUND_ORIGIN_Y };
	int modifiedX = ptr.X + 2, modifiedY = ptr.Y + 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	for (int i = 0; i < SelectedLife; i++) { SetCurrentCursorPos(modifiedX + i * 2, modifiedY); if (LifeGauge[i] == 1) printf("��"); }
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	SetCurrentCursorPos(ptr.X, ptr.Y);
}

//������ ������ UI ����
void InvalidateLifeGauge() {
	COORD ptr = { BACKGROUND_ORIGIN_X, BACKGROUND_ORIGIN_Y };
	int modifiedX = ptr.X + 2, modifiedY = ptr.Y + 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	for (int i = 0; i < SelectedLife; i++) { 
		SetCurrentCursorPos(modifiedX + i * 2, modifiedY); 
		if (LifeGauge[i] == 1) printf("��"); 
		else { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); printf("��"); }
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	SetCurrentCursorPos(ptr.X, ptr.Y);
}
//----------------------------------------------------------

//-----------------Enemy Health Bar UI ���� �Լ�----------------------

void ShowEnemyHealthBar() {
	COORD ptr = { BACKGROUND_ORIGIN_X + BACKGROUND_ROW, BACKGROUND_ORIGIN_Y };
	int modifiedX = ptr.X - 45, modifiedY = ptr.Y + 2;
	SetCurrentCursorPos(modifiedX, modifiedY); printf("HP [");
	for (int i = 0; i < BASEENEMYHEALTHFORUI; i++) printf("|");
	printf("]");
}

//Enemy Health Bar ����
void InvalidateEnemyHealthBar() {
	COORD ptr = { BACKGROUND_ORIGIN_X + BACKGROUND_ROW, BACKGROUND_ORIGIN_Y };
	int modifiedX = ptr.X - 41, modifiedY = ptr.Y + 2;
	for (int i = StageEnemyHealth / (Enemy_Health[StageNumber - 1] / BASEENEMYHEALTHFORUI); i < BASEENEMYHEALTHFORUI; i++) {
		SetCurrentCursorPos(modifiedX + i, modifiedY);
		printf(" ");
	}
	SetCurrentCursorPos(GAMEBOARD_ORIGIN_X, GAMEBOARD_ORIGIN_Y);
}
//-----------------------------------------------------
//---------------�ð� ǥ�� �� �������� ��ȣ UI �Լ�--------------

void ShowStoryModeTime() {
	COORD ptr = { BACKGROUND_ORIGIN_X + BACKGROUND_ROW, BACKGROUND_ORIGIN_Y };
	int modifiedX = ptr.X - 24, modifiedY = ptr.Y + 1;
	SetCurrentCursorPos(modifiedX, modifiedY);
	printf("Stage %d | %02d : %02d : %02d", StageNumber, Min, Sec, MiSec);
	SetCurrentCursorPos(GAMEBOARD_ORIGIN_X, GAMEBOARD_ORIGIN_Y);
}

void InvalidateStoryModeTime() {
	ShowStoryModeTime();
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	MiSec = (int)(CheckedTime * 100) % 100;
	Sec = (int)(CheckedTime) % 60;
	Min = (int)(CheckedTime) / 60;
}

void ShowInfiniteModeTime() {
	COORD ptr = { BACKGROUND_ORIGIN_X + BACKGROUND_ROW, BACKGROUND_ORIGIN_Y };
	int modifiedX = ptr.X - 20, modifiedY = ptr.Y + 1;
	SetCurrentCursorPos(modifiedX, modifiedY);
	printf("Time | %02d : %02d : %02d", Min, Sec, MiSec);
	SetCurrentCursorPos(GAMEBOARD_ORIGIN_X, GAMEBOARD_ORIGIN_Y);
}
void InvalidateInfiniteModeTime() {
	ShowInfiniteModeTime();
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	MiSec = (int)(CheckedTime * 100) % 100;
	Sec = (int)(CheckedTime) % 60;
	Min = (int)(CheckedTime) / 60;
}

//-----------------------------------------------------------------
//--------------��ų UI ���� �Լ�------------------

//�� ������ų �� ������ų �����
void HidePreviousCurrentNSubSkill() {
	int Skillstrlen = Strlen(Skillstr), SubSkillstrlen = Strlen(SubSkillstr);
	int Currentlen = Strlen(SkillSets[CurSkill]), Sublen = Strlen(SkillSets[SubSkill]);
	int len = 12;
	for (int i = 1; i <= 2; i++) {
		for (int j = 0; j <= len; j++) {
			SetCurrentCursorPos(modifiedX_Text + j, modifiedY_Text + i);
			printf(" ");
		}
	}
}

//���� ������ų �� ������ų  ���
void ShowCurrentNSubSkill() {
	SetCurrentCursorPos(modifiedX_Text, modifiedY_Text + 1);
	printf("%s%s", Skillstr, SkillSets[CurSkill]);
	SetCurrentCursorPos(modifiedX_Text, modifiedY_Text + 2);
	printf("%s%s", SubSkillstr, SkillSets[SubSkill]);
}

//---------------------------------------------------

#endif // !UI_H