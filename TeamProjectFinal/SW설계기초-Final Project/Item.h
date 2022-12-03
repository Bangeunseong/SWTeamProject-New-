#pragma once
#pragma warning(disable:4996)
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Player.h"
#include "Bullet.h"
#include "Timer.h"
#include "UI.h"
#include "SoundPlay.h"

#ifndef ITEM_H
#define ITEM_H

//----------------------------------------------------------------------------
//------------------Movement of Player Using FlashItem-------------------
void ShowFlashPlayer() {
	if (Invinsible) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERINVINSIBLEINDICATECOLOR);
	else if (UsingSkill > 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERUSINGSKILLCOLOR);
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYERCOLOR);
	
	int Modellen;
	if (PlayerLevel < 4) Modellen = PlayerLevel * 2;
	else Modellen = 6;
	for (int i = 0; i < Modellen; i++) { SetCurrentCursorPos(PLAYER_POS_X + i, PLAYER_POS_Y); printf("%c", PlayerModel[PlayerModelIndex][PlayerLevel - 1][i]); }
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	SetCurrentCursorPos(PLAYER_POS_X, PLAYER_POS_Y);
}

void HideFlashPlayer() {
	int Modellen;
	if (PlayerLevel < 4) Modellen = PlayerLevel * 2;
	else Modellen = 6;
	for (int i = 0; i < Modellen; i++) { SetCurrentCursorPos(PLAYER_POS_X + i, PLAYER_POS_Y); printf(" "); }
	SetCurrentCursorPos(PLAYER_POS_X, PLAYER_POS_Y);
}


int DetectCollision_FlashPlayerwithWall(int x, int y) {
	int Modellen;
	if (PlayerLevel < 4) Modellen = PlayerLevel * 2;
	else Modellen = 6;
	for (int i = 0; i < Modellen; i++) {
		if ((x + i < GAMEBOARD_ORIGIN_X + 2 || x + i >= GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW) || (y <= GAMEBOARD_ORIGIN_Y || y >= GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN)) return 1;
	}
	return 0;
}


void flashUp() {
	HideFlashPlayer();
	if (!DetectCollision_FlashPlayerwithWall(PLAYER_POS_X, PLAYER_POS_Y - FLASHDISTANCE)) PLAYER_POS_Y -= FLASHDISTANCE;
	else PLAYER_POS_Y = GAMEBOARD_ORIGIN_Y + 1;
	ShowFlashPlayer();
}
void flashDown() {
	HideFlashPlayer();
	if (!DetectCollision_FlashPlayerwithWall(PLAYER_POS_X, PLAYER_POS_Y + FLASHDISTANCE)) PLAYER_POS_Y+= FLASHDISTANCE;
	else PLAYER_POS_Y = GAMEBOARD_ORIGIN_Y + GAMEBOARD_COLUMN - 1;
	ShowFlashPlayer();
}
void flashLeft() {
	HideFlashPlayer();
	if (!DetectCollision_FlashPlayerwithWall(PLAYER_POS_X - FLASHDISTANCE * 2, PLAYER_POS_Y)) PLAYER_POS_X = PLAYER_POS_X -= FLASHDISTANCE * 2;
	else PLAYER_POS_X = GAMEBOARD_ORIGIN_X + 2;
	ShowFlashPlayer();
}
void flashRight() {
	HideFlashPlayer();
	if (!DetectCollision_FlashPlayerwithWall(PLAYER_POS_X + FLASHDISTANCE * 2, PLAYER_POS_Y)) PLAYER_POS_X = PLAYER_POS_X += FLASHDISTANCE *2;
	else PLAYER_POS_X = GAMEBOARD_ORIGIN_X + GAMEBOARD_ROW - 6;
	ShowFlashPlayer();
}

//---------------------------------------------------------------------------
//------------------------Ability of each item------------------------------

void itemSpeedUp() { CurSpeed += SPEEDINCREASERATE; }	//Speed Increase to +0.5
void itemBulletSpeedDown() { BulletSpeed /= 2.0; };					//BulletSpeed down to divided 2.0
void itemInvinsibility() { Invinsible = 1; }										//Invinsible
void itemFlash() {																		//Flash to direction
	if (flashCount >= 2) return;
	if (!flashFLAG) flashFLAG = 1;
	if (GetAsyncKeyState(LEFT) & 0x8000) flashLeft();
	if (GetAsyncKeyState(RIGHT) & 0x8000) flashRight();
	if (GetAsyncKeyState(UP) & 0x8000) flashUp();
	if (GetAsyncKeyState(DOWN) & 0x8000) flashDown();
	flashCount++; 
};
void itemDeleteBullet() {															//Delete all bullet on gameboard
	for (int i = 0; i < BULLETCOUNT; i++) {
		bullet[i].cnt = 0;
        HideBullet(i);
		bullet[i].BULLET_POS_X = ENEMY_ORIGIN_POS_X;
		bullet[i].BULLET_POS_Y = ENEMY_ORIGIN_POS_Y;
		bullet[i].BulletActivation = bullet[i].CollisionPlayer = bullet[i].CollisionWall = 0;
	}
	PatternCycle = 0;
	BULLETCOUNT = 0;
};															

//-------------------------------------------------------------
//------------------Item Status Functions--------------------


int inventoryCheck() {	//Check the item inventory
	if (SubSkill != 0) return 2;
	else { 
		if (CurSkill != 0) return 1;
		return 0;
	}
}


void SwapItem() {		//Swap item
	if (inventoryCheck() == 2) {
		HidePreviousCurrentNSubSkill();
		int tmp = CurSkill;
		CurSkill = SubSkill;
		SubSkill = tmp;
		ShowCurrentNSubSkill();
	}
}

//Getting item
void getItem() { SubSkill = CurSkill; CurSkill = ItemNumber; }

//------------------------------------------------------------------
//-----------------Activating item skill functions------------------

//Activating Using skill
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

//Deactivate item(Invalidate Using Skill)
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

//Activate Item(Invalidate Current Skill)
void ActivateSkillItem() {
	if (UsingSkill != 0) { if (flashFLAG != 0) itemFlash(); return; }
	if (!CurSkill) return;
	HidePreviousCurrentNSubSkill();									
	UsingSkill = CurSkill; CurSkill = SubSkill; SubSkill = 0;	
	itemTrigger(UsingSkill);													
	SkillActivationTime = TimeCheckerEnd() - PausingTime;						
	ShowCurrentNSubSkill();												
}

//Checking Skill Activation Time
void SkillTimeCheck() {
	if (!UsingSkill) return;
	if (TimeCheckerEnd() - PausingTime - SkillActivationTime > SkillTime) DeactivateSkillItem();
}


//----------------------------------------------------------------
//-----------------Item Creation Functions----------------------

//Calculating Item Frame Buffer
int CalculateItemTimeBuffer() {
	if (TimeCheckerEnd() - PausingTime - ItemInputTime > ITEMTIMEBUFFER) { ItemInputTime += ITEMTIMEBUFFER; return 0; }
	else return 1;
}

//Hide item on board
void HideItem() {
	SetCurrentCursorPos(ITEM_POS_X, ITEM_POS_Y);
	printf(" ");
}

//Show item on board
void ShowItem() {
	SetCurrentCursorPos(ITEM_POS_X, ITEM_POS_Y);
	printf("%c", itemList[ItemNumber - 1]);
}

//DetectCollision with wall
int DetectCollision_ItemwithWall(int x, int y) {
	if (UniBoard[y - GAMEBOARD_ORIGIN_Y][x - GAMEBOARD_ORIGIN_X] == WALL) return 1;
	return 0;
}

//Creating item in certain time
void CreateItem() {
	if (TimeCheckerEnd() - PausingTime > ItemCreationLoop * 15.0) {		//every one third of stagetime create item
		ITEM_POS_X = rand() % (GAMEBOARD_ROW - 2) + GAMEBOARD_ORIGIN_X + 2;		//
		ITEM_POS_Y = GAMEBOARD_ORIGIN_Y + 1;							
		ItemNumber = rand() % 5 + 1;													
		ItemInputTime = TimeCheckerEnd() - PausingTime;					
		itemFLAG = 1;																			
		ShowItem();																				
		ItemCreationLoop++;																
	}
}
//Creating item in certain time(for infinite mode)
void CreateItemInInfiniteMode() {
	if (TimeCheckerEnd() - PausingTime > 15.0 * ItemCreationLoop) {
		ITEM_POS_X = rand() % (GAMEBOARD_ROW - 2) + GAMEBOARD_ORIGIN_X + 2;	
		ITEM_POS_Y = GAMEBOARD_ORIGIN_Y + 1;							
		ItemNumber = rand() % 5 + 1;													
		ItemInputTime = TimeCheckerEnd() - PausingTime;					
		itemFLAG = 1;																			
		ShowItem();																				
		ItemCreationLoop++;																
	}
}

//reset item
void ResetItem() { HideItem(); itemFLAG = 0; }

//moving item down
void shiftItemDown() {
	HideItem();
	if (ItemCollisionDetected) {
		mciSendCommandW(dwIDSE_ITEM, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		PlayGETITEMSound();
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

//--------------------------------------------------------
//-----------------Invalidating Item---------------------
void InvalidateItem() {
	if (!itemFLAG) { if (!GameMode) CreateItem(); else CreateItemInInfiniteMode(); }
	else { 
		if (!CalculateItemTimeBuffer()) shiftItemDown();
		else {
			if (ItemCollisionDetected) {
				mciSendCommandW(dwIDSE_ITEM, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
				PlayGETITEMSound();
				ItemCollisionDetected = 0;
				HideItem(); ResetItem();
				HidePreviousCurrentNSubSkill();
				getItem();
				ShowCurrentNSubSkill();
				return;
			}
		}
	}
}
#endif  //!ITEM_H
