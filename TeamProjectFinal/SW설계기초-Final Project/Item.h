#pragma once
#pragma warning(disable:4996)
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Bullet.h"
#include "Timer.h"
#include "UI.h"

#ifndef ITEM_H
#define ITEM_H

//플레이어 출력 함수
void ShowFlashPlayer() {
	if (Invinsible) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERINVINSIBLEINDICATECOLOR);
	else if (UsingSkill > 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERUSINGSKILLCOLOR);
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERCOLOR);
	for (int i = 0; i < 6; i++) { SetCurrentCursorPos(PLAYER_POS_X + i, PLAYER_POS_Y); printf("%c", PlayerModel[i]); }
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	SetCurrentCursorPos(PLAYER_POS_X, PLAYER_POS_Y);
}
//플레이어 숨김 함수
void HideFlashPlayer() {
	for (int i = 0; i < 6; i++) { SetCurrentCursorPos(PLAYER_POS_X + i, PLAYER_POS_Y); printf(" "); }
	SetCurrentCursorPos(PLAYER_POS_X, PLAYER_POS_Y);
}

//대쉬 스킬 사용 시 충돌 검사 함수
int DetectCollision_FlashPlayerwithWall(int x, int y) {
	for (int i = 0; i < 6; i++) {
		if ((x + i < GAMEBOARD_ORIGIN_X + 2 || x + i >= GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW) || (y <= GAMEBOARD_ORIGIN_Y || y >= GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN)) return 1;
	}
	return 0;
}

//대쉬 스킬 함수
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

//-------------------아이템별 작동함수-----------------------

void itemSpeedUp() { CurSpeed += SPEEDINCREASERATE; }	//플레이어 캐릭터 속도 증가
void itemBulletSpeedDown() { BulletSpeed /= 2.0; };					//탄막 속도 감소
void itemInvinsibility() { Invinsible = 1; }										//무적 판정
void itemFlash() {																		//대쉬 스킬
	if (flashCount >= 2) return;
	if (!flashFLAG) flashFLAG = 1;
	if (GetAsyncKeyState(LEFT) & 0x8000) flashLeft();
	if (GetAsyncKeyState(RIGHT) & 0x8000) flashRight();
	if (GetAsyncKeyState(UP) & 0x8000) flashUp();
	if (GetAsyncKeyState(DOWN) & 0x8000) flashDown();
	flashCount++; 
};
void itemDeleteBullet() {	//보드판에 존재하는 총알들 모두 삭제
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
//------------------아이템 인벤토리 관련 함수--------------------

//아이템 스킬 인벤토리 상태 확인
int inventoryCheck() {
	if (SubSkill != 0) return 2;
	else { 
		if (CurSkill != 0) return 1;
		return 0;
	}
}

//아이템 스킬 교체 함수
void SwapItem() {
	if (inventoryCheck() == 2) {
		HidePreviousCurrentNSubSkill();
		int tmp = CurSkill;
		CurSkill = SubSkill;
		SubSkill = tmp;
		ShowCurrentNSubSkill();
	}
}

//아이템 습득함수
void getItem() { SubSkill = CurSkill; CurSkill = ItemNumber; }

//---------------------------------------------------------------
//------------------아이템 사용 관련 함수---------------------

//아이템의 종류에 따라 작동하는 스킬
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

//아이템 스킬 해제 함수
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

//아이템 스킬 발동 함수
void ActivateSkillItem() {
	if (UsingSkill != 0) { if (flashFLAG != 0) itemFlash(); return; }
	if (!CurSkill) return;
	HidePreviousCurrentNSubSkill();									//UI 갱신을 위해 넣은 숨김함수
	UsingSkill = CurSkill; CurSkill = SubSkill; SubSkill = 0;	//주 스킬과 보조 스킬 Swap
	itemTrigger(UsingSkill);													//스킬 발동
	SkillActivationTime = TimeCheckerEnd();						//스킬 발동 시간 기록
	ShowCurrentNSubSkill();												//UI 갱신을 위해 넣은 출력함수
}

//아이템 스킬 지속시간 체크 함수
void SkillTimeCheck() {
	if (!UsingSkill) return;
	if (TimeCheckerEnd() - PausingTime - SkillActivationTime > SkillTime) DeactivateSkillItem();
}


//----------------------------------------------------------------
//-----------------아이템 무브먼트 관련 함수------------------

//아이템 움직임 딜레이 함수
int CalculateItemTimeBuffer() {
	if (TimeCheckerEnd() - PausingTime - ItemInputTime > ITEMTIMEBUFFER) { ItemInputTime += ITEMTIMEBUFFER; return 0; }
	else return 1;
}

//아이템 삭제 함수
void HideItem() {
	SetCurrentCursorPos(ITEM_POS_X, ITEM_POS_Y);
	printf(" ");
}

//아이템 출력 함수
void ShowItem() {
	SetCurrentCursorPos(ITEM_POS_X, ITEM_POS_Y);
	printf("%c", itemList[ItemNumber - 1]);
}

//아이템 충돌 검사 함수
int DetectCollision_ItemwithWall(int x, int y) {
	if (y >= GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN) return 1;
	return 0;
}

//아이템 생성 함수
void CreateItem() {
	if ((TimeCheckerEnd() - PausingTime > ItemCreationLoop *(StageTime[StageNumber - 1]) / 3.0) && ItemCreationLoop < 3) {
		ITEM_POS_X = rand() % (GAMEBOARD_ROW - 1) + GAMEBOARD_ORIGIN_X + 2;	//초기 랜덤 X좌표
		ITEM_POS_Y = GAMEBOARD_ORIGIN_Y + 1;	//초기 Y좌표
		ItemNumber = rand() % 5 + 1;							//아이템 넘버 랜덤 생성
		ItemInputTime = TimeCheckerEnd() - PausingTime;					//아이템 생성 시간 기록
		itemFLAG = 1;													//게임 보드 내 아이템 아이콘 존재 유무 1
		ShowItem();														//아이템 출력
		ItemCreationLoop++;										//현재까지 출력한 아이템 갯수
	}
}

//아이템 항목 초기화 함수
void ResetItem() { HideItem(); itemFLAG = 0; }

//아이템 좌표 1씩 감소시키는 함수
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
//-----------------아이템 갱신 함수(본체)--------------------
void InvalidateItem() {
	if (!itemFLAG) CreateItem();
	else { if (!CalculateItemTimeBuffer()) { shiftItemDown(); } }
}
#endif  //!ITEM_H