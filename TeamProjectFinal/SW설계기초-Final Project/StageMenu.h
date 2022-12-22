#pragma once
#include "VariableSets.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Npc.h"
#include "ExpItem.h"
#include "WeaponItem.h"
#include "Score.h"
#include "UI.h"
#ifndef STAGEMENU_H
#define STAGEMENU_H

//스테이지별 출력되는 화면
void ShownHideStageNumber() {
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 4, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 2);
	printf("Stage %d", StageNumber);
	TimeCheckerStart(); 
	while (TimeCheckerEnd() < STAGEDURATIONTIME);
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 4, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 2);
	for (int i = 0; i < 7; i++) printf(" ");
}

void ShowWarningSign() {
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 4, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 2);
	printf("!! Warning !!");
}

void HideWarningSign() {
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 4, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2 + 2);
	for (int i = 0; i < 14; i++) printf(" ");
}



//스테이지 종료 조건
int StageOver() {
	if (StageEnemyHealth <= 0) {
		TotalSec += (int)(TimeCheckerEnd() - PausingTime);
		HidePlayer(); HideEnemy(); HideItem(); for (int i = 0; i < NPC_COUNT; i++) HideNpc(i);
		ClearPlayerPosition(); ClearEnemyPosition(); ClearBulletPosition(); ClearAll_PBulletPosition(); ClearBulletPatternVisit(); ClearNpcPosition(); ClearAllExp(); ClearAllWeapon();
		DeactivateEnemySkill_Prison();
		
		mciSendCommandW(dwID, MCI_PLAY, MCI_PAUSE, (DWORD)(LPVOID)&playBgm);
		mciSendCommandW(dwID_MC, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		PlayMISSIONCOMPLETESound();
		ShowScore();
		TimeCheckerStart();
		while (TimeCheckerEnd() < ScorePrintDurationTime);
		HideScore();
		mciSendCommandW(dwID, MCI_PLAY, MCI_RESUME, (DWORD)(LPVOID)&playBgm);

		PlayerInputTime = 0; Invinsible = 0; UsingSkill = 0; P_BulletLaunchTime = 0; P_BulletSpeed = 1.0; 
		EnemyInputTime = EnemyMovementTiming = 0; EnemySpeed = 1.0;
		NpcInputTime = 0; NpcDirection = 0; NpcIsMoving = 0; NpcPatternStartTime = NpcPatternEndTime = 0; NpcKilledOver = 0; NpcKillCount = 0;
		ItemInputTime = 0; ItemCreationLoop = 1; flashFLAG = 0; flashCount = 0; itemFLAG = 0;
		BulletInputTime = 0;
		BulletPatternStartTime = BulletPatternEndTime = 0;
		Warningsignflag = 0;
		PausedTime = PausingTime = 0; StageNumber++;
		Min = Sec = MiSec = 0;
		return 1; 
	}
	return 0;
}
#endif // !STAGEMENU_H
