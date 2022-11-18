#pragma once
#pragma warning(disable:4996)
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Bullet.h"
#include "Timer.h"
#include "UI.h"

#ifndef ITEM_H
#define ITEM_H

//�÷��̾� ��� �Լ�
void ShowFlashPlayer() {
	if (Invinsible) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERINVINSIBLEINDICATECOLOR);
	else if (UsingSkill > 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERUSINGSKILLCOLOR);
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERCOLOR);
	for (int i = 0; i < 6; i++) { SetCurrentCursorPos(PLAYER_POS_X + i, PLAYER_POS_Y); printf("%c", PlayerModel[i]); }
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	SetCurrentCursorPos(PLAYER_POS_X, PLAYER_POS_Y);
}
//�÷��̾� ���� �Լ�
void HideFlashPlayer() {
	for (int i = 0; i < 6; i++) { SetCurrentCursorPos(PLAYER_POS_X + i, PLAYER_POS_Y); printf(" "); }
	SetCurrentCursorPos(PLAYER_POS_X, PLAYER_POS_Y);
}

//�뽬 ��ų ��� �� �浹 �˻� �Լ�
int DetectCollision_FlashPlayerwithWall(int x, int y) {
	for (int i = 0; i < 6; i++) {
		if ((x + i < GAMEBOARD_ORIGIN_X + 2 || x + i >= GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW) || (y <= GAMEBOARD_ORIGIN_Y || y >= GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN)) return 1;
	}
	return 0;
}

//�뽬 ��ų �Լ�
void flashUp() {
	HideFlashPlayer();
	if (!DetectCollision_PlayerwithWall(PLAYER_POS_X, PLAYER_POS_Y - FLASHDISTANCE)) PLAYER_POS_Y -= FLASHDISTANCE;
	else PLAYER_POS_Y = GAMEBOARD_ORIGIN_Y + 1;
	ShowFlashPlayer();
}
void flashDown() {
	HideFlashPlayer();
	if (!DetectCollision_PlayerwithWall(PLAYER_POS_X, PLAYER_POS_Y + FLASHDISTANCE)) PLAYER_POS_Y+= FLASHDISTANCE;
	else PLAYER_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN - 1;
	ShowFlashPlayer();
}
void flashLeft() {
	HideFlashPlayer();
	if (!DetectCollision_PlayerwithWall(PLAYER_POS_X - FLASHDISTANCE * 2, PLAYER_POS_Y)) PLAYER_POS_X = PLAYER_POS_X -= FLASHDISTANCE * 2;
	else PLAYER_POS_X = GAMEBOARD_ORIGIN_X + 2;
	ShowFlashPlayer();
}
void flashRight() {
	HideFlashPlayer();
	if (!DetectCollision_PlayerwithWall(PLAYER_POS_X + FLASHDISTANCE * 2, PLAYER_POS_Y)) PLAYER_POS_X = PLAYER_POS_X += FLASHDISTANCE *2;
	else PLAYER_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW - 6;
	ShowFlashPlayer();
}

//-------------------�����ۺ� �۵��Լ�-----------------------

void itemSpeedUp() { CurSpeed += SPEEDINCREASERATE; }	//�÷��̾� ĳ���� �ӵ� ����
void itemBulletSpeedDown() { BulletSpeed /= 2.0; };					//ź�� �ӵ� ����
void itemInvinsibility() { Invinsible = 1; }										//���� ����
void itemFlash() {																		//�뽬 ��ų
	if (flashCount >= 2) return;
	if (!flashFLAG) flashFLAG = 1;
	if (GetAsyncKeyState(LEFT) & 0x8000) flashLeft();
	if (GetAsyncKeyState(RIGHT) & 0x8000) flashRight();
	if (GetAsyncKeyState(UP) & 0x8000) flashUp();
	if (GetAsyncKeyState(DOWN) & 0x8000) flashDown();
	flashCount++; 
};
void itemDeleteBullet() {	//�����ǿ� �����ϴ� �Ѿ˵� ��� ����
	for (int i = 0; i < BULLETCOUNT; i++) {
		HideBullet(i);
		bullet[i].BULLET_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW / 2 - 3;
		bullet[i].BULLET_POS_Y = GAMEBOARD_ORIGIN_Y + 5;
		bullet[i].BulletActivation = bullet[i].CollisionPlayer = bullet[i].CollisionWall = 0;
	}
	PatternCycle = 0;
	BULLETCOUNT = 0;
};															

//----------------------------------------------------------------
//------------------������ �κ��丮 ���� �Լ�--------------------

//������ ��ų �κ��丮 ���� Ȯ��
int inventoryCheck() {
	if (SubSkill != 0) return 2;
	else { 
		if (CurSkill != 0) return 1;
		return 0;
	}
}

//������ ��ų ��ü �Լ�
void SwapItem() {
	if (inventoryCheck() == 2) {
		HidePreviousCurrentNSubSkill();
		int tmp = CurSkill;
		CurSkill = SubSkill;
		SubSkill = tmp;
		ShowCurrentNSubSkill();
	}
}

//������ �����Լ�
void getItem() { SubSkill = CurSkill; CurSkill = ItemNumber; }

//---------------------------------------------------------------
//------------------������ ��� ���� �Լ�---------------------

//�������� ������ ���� �۵��ϴ� ��ų
void itemTrigger(int UsingSkill) {
	switch (UsingSkill) {
	case 1: itemSpeedUp();  break;
	case 2: itemBulletSpeedDown(); break;
	case 3: itemInvinsibility(); break;
	case 4: itemFlash(); break;
	case 5: itemDeleteBullet(); break;
	default: break;
	}
}

//������ ��ų ���� �Լ�
void DeactivateSkillItem() { 
	switch (UsingSkill) {
	case 1: CurSpeed = SelectedSpeed; break;
	case 2: BulletSpeed *= 2.0; break;
	case 3: Invinsible = 0; break;
	case 4: flashFLAG = 0; flashCount = 0; break;
	case 5: break;
	default: break;
	}
	UsingSkill = 0;
}

//������ ��ų �ߵ� �Լ�
void ActivateSkillItem() {
	if (UsingSkill != 0) { if (flashFLAG != 0) itemFlash(); return; }
	if (!CurSkill) return;
	HidePreviousCurrentNSubSkill();									//UI ������ ���� ���� �����Լ�
	UsingSkill = CurSkill; CurSkill = SubSkill; SubSkill = 0;	//�� ��ų�� ���� ��ų Swap
	itemTrigger(UsingSkill);													//��ų �ߵ�
	SkillActivationTime = TimeCheckerEnd();						//��ų �ߵ� �ð� ���
	ShowCurrentNSubSkill();												//UI ������ ���� ���� ����Լ�
}

//������ ��ų ���ӽð� üũ �Լ�
void SkillTimeCheck() {
	if (!UsingSkill) return;
	if (TimeCheckerEnd() - PausingTime - SkillActivationTime > SkillTime) DeactivateSkillItem();
}


//----------------------------------------------------------------
//-----------------������ �����Ʈ ���� �Լ�------------------

//������ ������ ������ �Լ�
int CalculateItemTimeBuffer() {
	if (TimeCheckerEnd() - PausingTime - ItemInputTime > ITEMTIMEBUFFER) { ItemInputTime += ITEMTIMEBUFFER; return 0; }
	else return 1;
}

//������ ���� �Լ�
void HideItem() {
	SetCurrentCursorPos(ITEM_POS_X, ITEM_POS_Y);
	printf(" ");
}

//������ ��� �Լ�
void ShowItem() {
	SetCurrentCursorPos(ITEM_POS_X, ITEM_POS_Y);
	printf("%c", itemList[ItemNumber - 1]);
}

//������ �浹 �˻� �Լ�
int DetectCollision_ItemwithWall(int x, int y) {
	if (y >= GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN) return 1;
	return 0;
}

//������ ���� �Լ�
void CreateItem() {
	if ((TimeCheckerEnd() - PausingTime > ItemCreationLoop *(StageTime[StageNumber - 1]) / 3.0) && ItemCreationLoop < 3) {
		ITEM_POS_X = rand() % (GAMEBOARD_ROW - 1) + GAMEBOARD_ORIGIN_X + 2;	//�ʱ� ���� X��ǥ
		ITEM_POS_Y = GAMEBOARD_ORIGIN_Y + 1;	//�ʱ� Y��ǥ
		ItemNumber = rand() % 5 + 1;							//������ �ѹ� ���� ����
		ItemInputTime = TimeCheckerEnd() - PausingTime;					//������ ���� �ð� ���
		itemFLAG = 1;													//���� ���� �� ������ ������ ���� ���� 1
		ShowItem();														//������ ���
		ItemCreationLoop++;										//������� ����� ������ ����
	}
}

//������ �׸� �ʱ�ȭ �Լ�
void ResetItem() { HideItem(); itemFLAG = 0; }

//������ ��ǥ 1�� ���ҽ�Ű�� �Լ�
void shiftItemDown() {
	HideItem();
	if (ItemCollisionDetected) {
		ItemCollisionDetected = 0;
		ResetItem(); 
		HidePreviousCurrentNSubSkill(); 
		getItem(); 
		ShowCurrentNSubSkill();
		return; 
	}
	if (DetectCollision_ItemwithWall(ITEM_POS_X, ITEM_POS_Y + 1)) { ResetItem(); return; }
	else ITEM_POS_Y++;
	
	ShowItem();
}

//-------------------------------------------------------------
//-----------------������ ���� �Լ�(��ü)--------------------
void InvalidateItem() {
	if (!itemFLAG) CreateItem();
	else { if (!CalculateItemTimeBuffer()) { shiftItemDown(); } }
}
#endif  //!ITEM_H