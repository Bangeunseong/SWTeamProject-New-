#pragma once
#include "VariableSets.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "UI.h"
#ifndef STAGEMENU_H
#define STAGEMENU_H

//���������� ��µǴ� ȭ��
void ShowStageNumber() {
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 4, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2);
	printf("Stage %d", StageNumber);
	TimeCheckerStart(); 
	while (TimeCheckerEnd() < STAGEDURATIONTIME);
	SetCurrentCursorPos(BACKGROUND_ORIGIN_X + BACKGROUND_ROW / 2 - 4, BACKGROUND_ORIGIN_Y + BACKGROUND_COLUMN / 2);
	for (int i = 0; i < 7; i++) printf(" ");
}

//�������� ���� ����
int StageOver() {
	if (StageEnemyHealth <= 0) {
		HidePlayer(); HideEnemy(); HideItem();
		ClearPlayerPosition(); ClearEnemyPosition(); ClearBulletPosition(); ClearAll_PBulletPosition();
		PlayerInputTime = 0; PlayerPos = 0; Invinsible = 0; UsingSkill = 0; P_BulletLaunchTime = 0;
		EnemyInputTime = EnemyMovementTiming = 0; EnemySpeed = 1.0;
		DeactivateEnemySkill_Prison();
		ItemInputTime = 0; ItemCreationLoop = 1; flashFLAG = 0; flashCount = 0; itemFLAG = 0;
		BulletInputTime = 0;
		BulletPatternStartTime = BulletPatternEndTime = 0;
		PausedTime = PausingTime = 0; StageNumber++;
		return 1; 
	}
	return 0;
}
#endif // !STAGEMENU_H
