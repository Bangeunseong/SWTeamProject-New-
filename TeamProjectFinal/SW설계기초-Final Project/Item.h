#pragma once
#include <time.h>
#include <stdlib.h>
#include "VariableSets.h"
#ifndef ITEM_H
#define ITEM_H
/*
//������ ���� ��ġ (X��ǥ ����)
void SetRandomItem_Pos_X() { 
	while (ITEM_POS_X >= ENEMY_POS_X && ITEM_POS_X < ENEMY_POS_X + strlen(EnemyUniModel[0]))
		ITEM_POS_X = rand() % ((GAMEBOARD_ROW - 1) + (GAMEBOARD_ORIGIN_X + 2));
}

//������ �浹�˻� �Լ�
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

//������ ������ �Լ�
void shiftItemDown() {

}
*/
#endif // !ITEM_H