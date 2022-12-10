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
// 출력
void ShowScore() {// 스코어 계산
	int CheckedTime = (int)(TimeCheckerEnd() - PausingTime);
	if (StageEnemyHealth > 0) StageClearBonusScore = 0;
	else StageClearBonusScore = StageNumber * 2000;
	int StageScore = (Enemy_Health[StageNumber - 1] - StageEnemyHealth) * 10 + NpcKillCount * 10 + StageClearBonusScore - CheckedTime; //1초 단위로 점수가 1점씩 차감
	TotalScore += StageScore;
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 14, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 2);
	printf("STAGE %d 에서 획득한 점수 = %d", StageNumber, StageScore);
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 8, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 4);
	printf("총 획득 점수 = %d", TotalScore);
}
// 삭제
void HideScore() {
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 14, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 2);
	for (int i = 0; i < 40; i++) printf(" ");
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 14, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 4);
	for (int i = 0; i < 40; i++) printf(" ");
}

// 파일로부터 데이터를 가져와서 구조체에 넣는 함수
void openFile() {
	FILE* fp = NULL;
	fp = fopen("Scoreboard.txt", "r");

	if (fp == NULL) {// 파일 열기의 성공여부 판단
		printf("파일 열기에 실패했습니다\n");
		return;
	}

	//파일에 저장된 데이터를 구조체 배열에 저장
	for (int i = 0; i < 10; i++)
		fscanf(fp, "%s %d", PlayerInfo[i].name, &(PlayerInfo[i].score));
	fclose(fp);
}

// 데이터를 파일에 저장하는 함수
void saveFile() {
	FILE* fp = NULL;

	fp = fopen("Scoreboard.txt", "w");

	if (fp == NULL) {// 파일 열기의 성공여부 판단
		printf("파일 열기에 실패했습니다\n");
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

	if (IndexFlag != -1) { // Top10 안에 들었을때
		SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 11, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 - 10);
		printf("TotalScore = %d 입니다", TotalScore);
		SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 24, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 - 8);
		printf("%d위를 달성했습니다! 점수를 등록하시겠습니까? y/n", IndexFlag + 1);

		while (1) {
			if (kbhit()) {
				switch (getch()) {
				case 'y':
					SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 40, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 - 4);
					printf("랭킹에 등록할 ID를 입력해 주세요(알파벳,숫자,특수문자 20자 미만) : ");
					gets_s(NameTmp, 20);
					for (int i = 9; i >= IndexFlag; i--) { // 랭킹 정렬
						strcpy(PlayerInfo[i + 1].name, PlayerInfo[i].name);
						PlayerInfo[i + 1].score = PlayerInfo[i].score;
					}
					strcpy(PlayerInfo[IndexFlag].name, NameTmp);
					PlayerInfo[IndexFlag].score = TotalScore;
					SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 24, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 - 2);
					printf("랭킹 등록이 완료되었습니다.");
					break;
				case 'n': 
					SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 24, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 - 4);
					printf("등록하지 않음을 선택하셨습니다.");
					break;
				default: continue;
				}
				break;
			}
		}
	}
	else { // 10순위에 들지 못했을때 
		SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 24, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 - 2);
		printf("TotalScore = %d 입니다. TOP 10 안에 들지 못하였습니다.", TotalScore);
	}

	// Top 10을 출력해준다.
	for (int j = 0; j < 10; j++) {
		SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 24, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + j);
		printf("%2d위\tID : %20s\tSCORE : %d", j + 1, PlayerInfo[j].name, PlayerInfo[j].score);
	}
	saveFile();
	TotalScore = 0;
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 24, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 11);
	printf("계속하려면 엔터 키를 누르세요...");
	while (1) { if (getch() ==VK_RETURN) return; }
}
#endif//!SCORE_H