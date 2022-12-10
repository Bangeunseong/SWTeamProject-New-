#pragma once
#pragma warning(disable:4996)
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Timer.h"
#include "Enemy.h"
#include<string.h>
#include<stdio.h>
#ifndef SCORE_H
#define SCORE_H
// ���
void ShowScore() {// ���ھ� ���
	int CheckedTime = (int)(TimeCheckerEnd() - PausingTime);
	if (StageEnemyHealth > 0) StageClearBonusScore = 0;
	else StageClearBonusScore = StageNumber * 2000;
	int StageScore = (Enemy_Health[StageNumber - 1] - StageEnemyHealth) * 10 + NpcKillCount * 10 + StageClearBonusScore - CheckedTime; //1�� ������ ������ 1���� ����
	TotalScore += StageScore;
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 14, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 2);
	printf("STAGE %d ���� ȹ���� ���� = %d", StageNumber, StageScore);
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 8, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 4);
	printf("�� ȹ�� ���� = %d", TotalScore);
}
// ����
void HideScore() {
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 14, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 2);
	for (int i = 0; i < 40; i++) printf(" ");
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 14, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 4);
	for (int i = 0; i < 40; i++) printf(" ");
}

// ���Ϸκ��� �����͸� �����ͼ� ����ü�� �ִ� �Լ�
void openFile() {
	FILE* fp = NULL;
	fp = fopen("Scoreboard.txt", "r");

	if (fp == NULL) {// ���� ������ �������� �Ǵ�
		printf("���� ���⿡ �����߽��ϴ�\n");
		return;
	}

	//���Ͽ� ����� �����͸� ����ü �迭�� ����
	for (int i = 0; i < 10; i++)
		fscanf(fp, "%s %d", PlayerInfo[i].name, &(PlayerInfo[i].score));
	fclose(fp);
}

// �����͸� ���Ͽ� �����ϴ� �Լ�
void saveFile() {
	FILE* fp = NULL;

	fp = fopen("Scoreboard.txt", "w");

	if (fp == NULL) {// ���� ������ �������� �Ǵ�
		printf("���� ���⿡ �����߽��ϴ�\n");
		return;
	}
	for (int i = 0; i < 10; i++)
		fprintf(fp, "%s %d\n", PlayerInfo[i].name, PlayerInfo[i].score);
	fclose(fp);
}

void ShowRecordScore() {
	int IndexFlag = -1;
	char key, buffer; char NameTmp[20];
	
	openFile();
	for (int i = 0; i < 10; i++) {
		if (TotalScore > PlayerInfo[i].score) {
			IndexFlag = i; break;
		}
	}

	if (IndexFlag != -1) { // Top10 �ȿ� �������
		SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 11, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 - 10);
		printf("TotalScore = %d �Դϴ�", TotalScore);
		SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 24, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 - 8);
		printf("%d���� �޼��߽��ϴ�! ������ ����Ͻðڽ��ϱ�? y/n", IndexFlag + 1);

		while (1) {
			if (kbhit()) {
				switch (getch()) {
				case 'y':
					SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 40, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 - 4);
					printf("��ŷ�� ����� ID�� �Է��� �ּ���(���ĺ�,����,Ư������ 20�� �̸�) : ");
					gets_s(NameTmp, 20);
					for (int i = 9; i >= IndexFlag; i--) { // ��ŷ ����
						strcpy(PlayerInfo[i + 1].name, PlayerInfo[i].name);
						PlayerInfo[i + 1].score = PlayerInfo[i].score;
					}
					strcpy(PlayerInfo[IndexFlag].name, NameTmp);
					PlayerInfo[IndexFlag].score = TotalScore;
					SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 24, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 - 2);
					printf("��ŷ ����� �Ϸ�Ǿ����ϴ�.");
					break;
				case 'n': 
					SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 24, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 - 4);
					printf("������� ������ �����ϼ̽��ϴ�.");
					break;
				default: continue;
				}
				break;
			}
		}
	}
	else { // 10������ ���� �������� 
		SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 24, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 - 2);
		printf("TotalScore = %d �Դϴ�. TOP 10 �ȿ� ���� ���Ͽ����ϴ�.", TotalScore);
	}

	// Top 10�� ������ش�.
	for (int j = 0; j < 10; j++) {
		SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 24, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + j);
		printf("%2d��\tID : %20s\tSCORE : %d", j + 1, PlayerInfo[j].name, PlayerInfo[j].score);
	}
	saveFile();
	TotalScore = 0;
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 24, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 11);
	printf("����Ϸ��� ���� Ű�� ��������...");
	while (1) { if (getch() ==VK_RETURN) return; }
}
#endif//!SCORE_H