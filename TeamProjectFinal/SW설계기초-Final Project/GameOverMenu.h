#pragma once
#include <conio.h>
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H
//------------------------���ӿ��� ���� ���� �Լ� �� UI�Լ�----------------------------
INPUT_RECORD rec;
DWORD dwNOER;
DWORD CIN;
DWORD mode;

//���� ���� ���� (��� �׸� �ʱ�ȭ)
int GameOver() {
	if (CurrentLife <= 0) { 
		HidePlayer(); HideEnemy();
		ClearPlayerPosition(); ClearEnemyPosition(); ClearBulletPosition();
		PlayerInputTime = 0; PlayerPos = 0; Invinsible = 0; CurSkill = SubSkill = UsingSkill = 0;
		EnemyInputTime = EnemyMovementTiming = 0; EnemySpeed = 1.0;
		DeactivateEnemySkill_Prison();
		itemFLAG = 0; ItemInputTime = 0; ItemCreationLoop = 1; flashFLAG = 0; flashCount = 0; 
		BulletInputTime = 0;
		BulletPatternStartTime = BulletPatternEndTime = 0;
		PausedTime = PausingTime = 0; CurrentTime = 1; StageNumber = 1;
		Min = Sec = MiSec = 0;
		free(LifeGauge); 
		return 1;
	}
	return 0;
}

//�ɼ� ���� �ڽ� ���
void CreateOptionSelectionBox(int x, int y) {
	COORD ptr = { x,y };
	for (int i = 0; i < OPTIONSELECTIONBOX_COLUMN; i++) {
		SetCurrentCursorPos(ptr.X, ptr.Y + i);
		if (i == 0) printf("��");
		else if (i == OPTIONSELECTIONBOX_COLUMN - 1) printf("��");
		else printf("��");
		SetCurrentCursorPos(ptr.X + OPTIONSELECTIONBOX_ROW, ptr.Y + i);
		if (i == 0) printf("��");
		else if (i == OPTIONSELECTIONBOX_COLUMN - 1) printf("��");
		else printf("��");
	}
	SetCurrentCursorPos(ptr.X, ptr.Y);
	for (int i = 2; i < OPTIONSELECTIONBOX_ROW; i += 2) {
		SetCurrentCursorPos(ptr.X + i, ptr.Y);
		printf("��");
		SetCurrentCursorPos(ptr.X + i, ptr.Y + OPTIONSELECTIONBOX_COLUMN - 1);
		printf("��");
	}
}

//���ӿ��� �ΰ� ���
void ShowGameOver() {
	COORD center = { BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 };
	int modifiedX = center.X - 46, modifiedY = center.Y - 5;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				SetCurrentCursorPos(modifiedX + 2 * k, modifiedY + j);
				if (GameOverLogo[i][j][k] == 1) printf("��");
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

//���ӿ��� �ΰ� ����
void HideGameOver() {
	COORD ptr = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', CONSOLE_COLUMN * CONSOLE_ROW, ptr, &dw);
}

//���콺Ŭ�� ��ġ ��ȯ �Լ�
void GameOptionBoxClick(int *xx, int *yy) {
	while (1)
	{
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rec, 1, &dwNOER); // �ܼ�â �Է��� �޾Ƶ���.
		if (rec.EventType == MOUSE_EVENT) {// ���콺 �̺�Ʈ�� ���
			if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) { // ���� ��ư�� Ŭ���Ǿ��� ���
				int mouse_x = rec.Event.MouseEvent.dwMousePosition.X; // X�� �޾ƿ�
				int mouse_y = rec.Event.MouseEvent.dwMousePosition.Y; // Y�� �޾ƿ�

				*xx = mouse_x; //x���� �ѱ�
				*yy = mouse_y; //y���� �ѱ�
				break;
			}
		}
	}
}

//������ ������ ������ �� �ƴϸ� �ٽ� �� �� �����ϴ� â ���
int GameOverMenu() {
	HideGameOver();	//������ ��ü ����

	//system �Լ��� �� ���Ŀ� INPUT �ڵ� �ٽ� ��Ȱ��ȭ
	HANDLE CIN = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(CIN, &mode);
	SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);

	//��Ʈ�� ȭ�� ���
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
