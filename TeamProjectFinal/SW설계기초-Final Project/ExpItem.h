#pragma once
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Timer.h"
#ifndef EXPITEM_H
#define EXPITEM_H
//-----------------Item Creation Functions----------------------

//Calculating Item Frame Buffer
int CalculateExpTimeBuffer() {
	if (TimeCheckerEnd() - PausingTime - ExpInputTime > EXPTIMEBUFFER) { ExpInputTime += EXPTIMEBUFFER; return 0; }
	else return 1;
}

//Hide item on board
void HideExp() {
	SetCurrentCursorPos(EXP_POS_X, EXP_POS_Y);
	printf("  ");
}

//Show exp on board
void ShowExp() {
	SetCurrentCursorPos(EXP_POS_X, EXP_POS_Y);
	printf("��");
}

//DetectCollision with palyer
int DetectCollision_ExpwithPlayer() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 2; j++) {
			if (EXP_POS_Y == PLAYER_POS_Y && EXP_POS_X + j == PLAYER_POS_X + i)  return 1;
		}
	}
	return 0;
}

//Creating exp in certain time
void CreateExp() {
	if ((TimeCheckerEnd() - PausingTime > ExpCreationLoop * ExpCreateTime)) {		// 10 * n second create exp
		if (expFLAG == 1) { HideExp(); expFLAG = 0; }
		EXP_POS_X = rand() % (GAMEBOARD_ROW - 2) + GAMEBOARD_ORIGIN_X + 2;
		EXP_POS_Y = rand() % (GAMEBOARD_COLUMN - 1) + GAMEBOARD_ORIGIN_Y + 1;
		ExpInputTime = TimeCheckerEnd() - PausingTime;
		expFLAG = 1;
		ShowExp();
		ExpCreationLoop++;
	}
}

// level up

void LevelUp() {
	if (EXP == levelFLAG[PlayerLevel - 1]) { PlayerLevel++; }
}

// get exp
void GetExp() {
	EXP++; LevelUp();
	SetCurrentCursorPos(0, 0); printf("%d %d", EXP, PlayerLevel);  // Ȯ�ο� ���
}



//--------------------------------------------------------
//-----------------Invalidating Item---------------------
void InvalidateExp() {

	if (!CalculateExpTimeBuffer()) {
		CreateExp();
		if (expFLAG == 1 && DetectCollision_ExpwithPlayer()) {
			HideExp();
			GetExp();
			expFLAG = 0;
		}
		else if (expFLAG == 1) {	//����ġ�� �Ѿ��̳� �������� �������� ���� �����ϱ� ���� ���
			ShowExp();			// 2��Ʈ�� ����ϴٺ��� �ָ��ϰ� ��ģ ��� ������ ��ĭ �и��� ������ ������ ������ ����
		}
	}
}
#endif // !EXPITEM_H
