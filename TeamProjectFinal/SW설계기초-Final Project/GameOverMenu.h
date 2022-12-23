#pragma once
#include <conio.h>
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Npc.h"
#include "ExpItem.h"
#include "WeaponItem.h"
#include "Score.h"
#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H
//------------------------게임오버 조건 관련 함수 및 UI함수----------------------------
INPUT_RECORD rec;
DWORD dwNOER;
DWORD CIN;
DWORD mode;

//게임 종료 조건 (모든 항목 초기화)
int GameOver() {
	if (CurrentLife <= 0 || StageNumber > 3) { 
		TotalSec += (int)(TimeCheckerEnd() - PausingTime);
		HidePlayer(); HideEnemy(); HideItem(); for (int i = 0; i < NPC_COUNT; i++) HideNpc(i);
		ClearPlayerPosition(); ClearEnemyPosition(); ClearBulletPosition(); ClearAll_PBulletPosition(); ClearBulletPatternVisit(); ClearNpcPosition(); ClearAllExp(); ClearAllWeapon();
		DeactivateEnemySkill_Prison();

		mciSendCommandW(dwID, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		mciSendCommandW(dwIDSE_B, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		mciSendCommandW(dwIDSE_D, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		mciSendCommandW(dwIDSE_EXP, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		mciSendCommandW(dwIDSE_ITEM, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		mciSendCommandW(dwIDSE_NPCD, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		mciSendCommandW(dwIDSE_R, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		mciSendCommandW(dwIDSE_W, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		if (CurrentLife <= 0) PlayMISSIONFAILEDSound();
		else PlayMISSIONCOMPLETESound();
		ShowScore();
		TimeCheckerStart();
		while (TimeCheckerEnd() < ScorePrintDurationTime);
		HideScore();

		PlayerInputTime = 0; Invinsible = 0; CurSkill = SubSkill = UsingSkill = 0; PlayerLevel = 1; P_BulletLaunchTime = 0; EXP = 0; PlayerWeapon = 0;
		EnemyInputTime = EnemyMovementTiming = 0; EnemySpeed = 1.0;
		NpcInputTime = 0; NpcDirection = 0; NpcIsMoving = 0; NpcPatternStartTime = NpcPatternEndTime = 0; NpcKilledOver = 0; NpcKillCount = 0;
		itemFLAG = 0; ItemInputTime = 0; ItemCreationLoop = 1; flashFLAG = 0; flashCount = 0;
		BulletInputTime = 0;
		BulletPatternStartTime = BulletPatternEndTime = 0;
		Warningsignflag = 0;

		PausedTime = PausingTime = 0; StageNumber = 1;
		Min = Sec = MiSec = 0;
		free(LifeGauge);
		mciSendCommandW(dwID_MC, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		mciSendCommandW(dwID_MF, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		return 1;
	}
	return 0;
}

//옵션 선택 박스 출력
void CreateOptionSelectionBox(int x, int y) {
	COORD ptr = { x,y };
	for (int i = 0; i < OPTIONSELECTIONBOX_COLUMN; i++) {
		SetCurrentCursorPos(ptr.X, ptr.Y + i);
		if (i == 0) printf("┏");
		else if (i == OPTIONSELECTIONBOX_COLUMN - 1) printf("┗");
		else printf("┃");
		SetCurrentCursorPos(ptr.X + OPTIONSELECTIONBOX_ROW, ptr.Y + i);
		if (i == 0) printf("┓");
		else if (i == OPTIONSELECTIONBOX_COLUMN - 1) printf("┛");
		else printf("┃");
	}
	SetCurrentCursorPos(ptr.X, ptr.Y);
	for (int i = 2; i < OPTIONSELECTIONBOX_ROW; i += 2) {
		SetCurrentCursorPos(ptr.X + i, ptr.Y);
		printf("━");
		SetCurrentCursorPos(ptr.X + i, ptr.Y + OPTIONSELECTIONBOX_COLUMN - 1);
		printf("━");
	}
}

//게임오버 로고 출력
void ShowGameOver() {
	COORD center = { BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 };
	int modifiedX = center.X - 46, modifiedY = center.Y - 5;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				SetCurrentCursorPos(modifiedX + 2 * k, modifiedY + j);
				if (GameOverLogo[i][j][k] == 1) printf("■");
			}
		}
		modifiedX += 12;
		SetCurrentCursorPos(modifiedX, modifiedY);
	}
	CreateOptionSelectionBox(OptionSelectionBox_Origin_X, OptionSelectionBox_Origin_Y);
	SetCurrentCursorPos(OptionSelectionBox_Origin_X + (OPTIONSELECTIONBOX_ROW - strlen("Continue?")) / 2 + 1, OptionSelectionBox_Origin_Y + 1);
	printf("Continue?");
	CreateOptionSelectionBox(OptionSelectionBox_Origin_X + OPTIONSELECTIONBOX_ROW + 8, OptionSelectionBox_Origin_Y);
	SetCurrentCursorPos(OptionSelectionBox_Origin_X + OPTIONSELECTIONBOX_ROW + 8 + (OPTIONSELECTIONBOX_ROW - strlen("GiveUp")) / 2, OptionSelectionBox_Origin_Y + 1);
	printf("Give Up");
}

//게임오버 로고 숨김
void HideGameOver() {
	COORD ptr = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', CONSOLE_COLUMN * CONSOLE_ROW, ptr, &dw);
}

//마우스클릭 위치 반환 함수
void GameOptionBoxClick(int *xx, int *yy) {
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

//게임을 완전히 종료할 지 아니면 다시 할 지 선택하는 창 출력
int GameOverMenu() {
	HideGameOver();	//게임판 전체 삭제
	ShowRecordScore();
	HideGameOver();

	//system 함수를 쓴 이후엔 INPUT 핸들 다시 재활성화
	HANDLE CIN = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(CIN, &mode);
	SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);

	//인트로 화면 출력
	ShowGameOver();
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	int xx, yy; int flag = 0;
	while (1) {
		GameOptionBoxClick(&xx, &yy);
		if (yy >= OptionSelectionBox_Origin_Y && yy <= OptionSelectionBox_Origin_Y + OPTIONSELECTIONBOX_COLUMN) {
			if (xx >= OptionSelectionBox_Origin_X && xx <= OptionSelectionBox_Origin_X + OPTIONSELECTIONBOX_ROW) {
				break;
			}
			else if (xx >= OptionSelectionBox_Origin_X + OPTIONSELECTIONBOX_ROW + 8 && xx <= OptionSelectionBox_Origin_X + 2 * OPTIONSELECTIONBOX_ROW + 4) {
				flag = 1; break;
			}
		}
	}
	HideGameOver();
	return flag;
}
//--------------------------------------------------------------------------------------------
#endif // !GAMEOVERMENU_H
