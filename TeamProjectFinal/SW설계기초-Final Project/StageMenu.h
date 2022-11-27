#pragma once
#include "VariableSets.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "UI.h"
#ifndef STAGEMENU_H
#define STAGEMENU_H

//스테이지별 출력되는 화면
void ShowStageNumber() {
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 4, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2);
	printf("Stage %d", StageNumber);
	TimeCheckerStart(); 
	while (TimeCheckerEnd() < STAGEDURATIONTIME);
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 4, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2);
	for (int i = 0; i < 7; i++) printf(" ");
}

//스테이지 종료 조건
int StageOver() {
	if (StageEnemyHealth <= 0) {
		TotalSec += (int)(TimeCheckerEnd() - PausingTime) % 60;
		HidePlayer(); HideEnemy(); HideItem(); HideExp();
		ClearPlayerPosition(); ClearEnemyPosition(); ClearBulletPosition(); ClearAll_PBulletPosition();
		PlayerInputTime = 0; PlayerPos = 0; Invinsible = 0; UsingSkill = 0; P_BulletLaunchTime = 0;
		EnemyInputTime = EnemyMovementTiming = 0; EnemySpeed = 1.0;
		DeactivateEnemySkill_Prison();
		ItemInputTime = 0; ItemCreationLoop = 1; flashFLAG = 0; flashCount = 0; itemFLAG = 0;
		ExpInputTime = 0; ExpCreationLoop = 1; expFLAG = 0;
		BulletInputTime = 0;
		BulletPatternStartTime = BulletPatternEndTime = 0;
		PausedTime = PausingTime = 0; StageNumber++;
		Min = Sec = MiSec = 0;
		return 1; 
	}
	return 0;
}
#endif // !STAGEMENU_H
