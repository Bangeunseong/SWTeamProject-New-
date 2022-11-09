#pragma once
#include <time.h>
#include <stdlib.h>
#include "VariableSets.h"
#ifndef ITEM_H
#define ITEM_H
/*
//아이템 생성 위치 (X좌표 설정)
void SetRandomItem_Pos_X() { 
	while (ITEM_POS_X >= ENEMY_POS_X && ITEM_POS_X < ENEMY_POS_X + strlen(EnemyUniModel[0]))
		ITEM_POS_X = rand() % ((GAMEBOARD_ROW - 1) + (GAMEBOARD_ORIGIN_X + 2));
}

//아이템 충돌검사 함수
int DetectCollision_Item(int x, int y) {
	if (y == GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN) return 1;
	if (y == PLAYER_POS_Y) {
		int len = strlen(PlayerUniModel);
			for (int i = 0; i < len; i++) if (x == PLAYER_POS_X + i) return 1;
	}
	return 0;
}

void HideItem() {

}

//아이템 움직임 함수
void shiftItemDown() {

}
*/
#endif // !ITEM_H