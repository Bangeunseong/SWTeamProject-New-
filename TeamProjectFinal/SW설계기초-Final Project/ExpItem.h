#pragma once
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Timer.h"
#ifndef EXPITEM_H
#define EXPITEM_H
//-----------------Item Creation Functions----------------------

//Hide item on board
void HideExp(int Exp_number) {
	SetCurrentCursorPos(exp[Exp_number].EXP_POS_X, exp[Exp_number].EXP_POS_Y);
	printf("  ");
}

//Show exp on board
void ShowExp(int Exp_number) {
	SetCurrentCursorPos(exp[Exp_number].EXP_POS_X, exp[Exp_number].EXP_POS_Y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("★");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

//Creating exp in gameboard
void CreateExp(int npc_number) {
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	++EXPCOUNTEND;
	exp[EXPCOUNTEND % MAXEXPCREATE].EXP_POS_X = npc[npc_number].NPC_POS_X;
	exp[EXPCOUNTEND % MAXEXPCREATE].EXP_POS_Y = npc[npc_number].NPC_POS_Y;
	exp[EXPCOUNTEND % MAXEXPCREATE].ExpActivation = 1;
	exp[EXPCOUNTEND % MAXEXPCREATE].ExpCreationTime = CheckedTime;
	ShowExp(EXPCOUNTEND % MAXEXPCREATE);
}

//Deleting exp in gameboard
void DeleteExp(int Exp_number) { 
	HideExp(Exp_number % MAXEXPCREATE);
	exp[Exp_number % MAXEXPCREATE].ExpActivation = 0;
	exp[Exp_number % MAXEXPCREATE].EXP_POS_X = exp[Exp_number % MAXEXPCREATE].EXP_POS_Y = 0;
}

void ClearAllExp() {
	for (int i = EXPCOUNTSTART; i <= EXPCOUNTEND; i++) {
		HideExp(i % MAXEXPCREATE); exp[i % MAXEXPCREATE].ExpActivation = exp[i % MAXEXPCREATE].ExpCreationTime = 0;
	}
}

//DetectCollision with player
int DetectCollision_ExpwithPlayer(int Exp_number) {
	if (!exp[Exp_number % MAXEXPCREATE].ExpActivation) { if (Exp_number == EXPCOUNTSTART) EXPCOUNTSTART++; return 0; }

	int Modellen;
	if (PlayerLevel < 4) Modellen = PlayerLevel * 2;
	else Modellen = 6;
	for (int i = 0; i < Modellen; i++) {
		for (int k = 0; k < 2; k++) {
			if (exp[Exp_number % MAXEXPCREATE].EXP_POS_Y == PLAYER_POS_Y && exp[Exp_number % MAXEXPCREATE].EXP_POS_X + k == PLAYER_POS_X + i) { DeleteExp(Exp_number); return 1; }
		}
	}
	return 0;
}

// level up
void LevelUp() { if (EXP == levelFLAG[PlayerLevel - 1]) PlayerLevel++; }

// get exp
void GetExp() {
	mciSendCommandW(dwIDSE_EXP, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
	PlayGETEXPSound();
	EXP++; LevelUp();
}

//--------------------------------------------------------
//-----------------Invalidating Item---------------------
void InvalidateExp() {
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	for (int i = EXPCOUNTSTART; i <= EXPCOUNTEND; i++) {
		if (CheckedTime > exp[i % MAXEXPCREATE].ExpCreationTime + ExpDurationTime) DeleteExp(i);
		if (DetectCollision_ExpwithPlayer(i % MAXEXPCREATE)) GetExp();
		else { if (exp[i % MAXEXPCREATE].ExpActivation) ShowExp(i % MAXEXPCREATE); }
	}
}
#endif // !EXPITEM_H
