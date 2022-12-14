#pragma once
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "SoundPlay.h"
#include "Timer.h"
#ifndef WEAPONITEM_H
#define WEAPONITEM_H

void HideWeaponItem(int Weapon_number) {
	SetCurrentCursorPos(weapon[Weapon_number % MAXWEAPONCREATE].WEAPON_POS_X, weapon[Weapon_number % MAXWEAPONCREATE].WEAPON_POS_Y);
	printf(" ");
}

void ShowWeaponItem(int Weapon_number) {
	SetCurrentCursorPos(weapon[Weapon_number % MAXWEAPONCREATE].WEAPON_POS_X, weapon[Weapon_number % MAXWEAPONCREATE].WEAPON_POS_Y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	printf("%c", WeaponItemModel[weapon[Weapon_number % MAXWEAPONCREATE].WeaponNumber]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void SetWeaponItem(int npc_number) {	//WeaponItem 설정
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	++WEAPONCOUNTEND;
	weapon[WEAPONCOUNTEND % MAXWEAPONCREATE].WEAPON_POS_X = npc[npc_number].NPC_POS_X;
	weapon[WEAPONCOUNTEND % MAXWEAPONCREATE].WEAPON_POS_Y = npc[npc_number].NPC_POS_Y;
	weapon[WEAPONCOUNTEND % MAXWEAPONCREATE].WeaponActivation = 1;
	weapon[WEAPONCOUNTEND % MAXWEAPONCREATE].WeaponCreationTime = CheckedTime;
	weapon[WEAPONCOUNTEND % MAXWEAPONCREATE].WeaponNumber = rand() % 3;		//Weaponnumber를 난수로 설정
}

void CreateWeaponItem(int npc_number) { 
	SetWeaponItem(npc_number);
	ShowWeaponItem(WEAPONCOUNTEND);
}

void DeleteWeaponItem(int Weapon_number) {
	HideWeaponItem(Weapon_number % MAXWEAPONCREATE);
	weapon[Weapon_number % MAXWEAPONCREATE].WeaponActivation = 0;	//WeaponItem 해제(충돌 함수에서 제외하기 위함)
	weapon[Weapon_number % MAXWEAPONCREATE].WEAPON_POS_X = weapon[Weapon_number % MAXWEAPONCREATE].WEAPON_POS_Y = 0;
}

void ClearAllWeapon() {
	for (int i = WEAPONCOUNTSTART; i <= WEAPONCOUNTEND; i++) {
		HideWeaponItem(i % MAXWEAPONCREATE);
		weapon[i % MAXWEAPONCREATE].WeaponActivation = weapon[i % MAXWEAPONCREATE].WEAPON_POS_X = weapon[i % MAXWEAPONCREATE].WEAPON_POS_Y = weapon[i % MAXWEAPONCREATE].WeaponCreationTime = weapon[i].WeaponNumber = 0;
	}
	WEAPONCOUNTSTART = 0; WEAPONCOUNTEND = -1;
}

int DetectCollision_WeaponwithPlayer(int Weapon_number) {
	if (!weapon[Weapon_number % MAXWEAPONCREATE].WeaponActivation) { if (Weapon_number == WEAPONCOUNTSTART) WEAPONCOUNTSTART++; return 0; }

	int Modellen;
	if (PlayerLevel < 4) Modellen = PlayerLevel * 2;
	else Modellen = 6;
	for (int i = 0; i < Modellen; i++) {
		if (weapon[Weapon_number % MAXWEAPONCREATE].WEAPON_POS_Y == PLAYER_POS_Y && weapon[Weapon_number % MAXWEAPONCREATE].WEAPON_POS_X == PLAYER_POS_X + i) { DeleteWeaponItem(Weapon_number); return 1; }
	}
	return 0;
}

void SwapWeapon(int Weapon_number) { 
	mciSendCommandW(dwIDSE_B, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	mciSendCommandW(dwIDSE_R, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
	PlayRELOADSound();
	PlayerWeapon = weapon[Weapon_number % MAXWEAPONCREATE].WeaponNumber;
}

void InvalidateWeaponItem() {
	double CheckedTime = TimeCheckerEnd() - PausingTime;
	for (int i = WEAPONCOUNTSTART; i <= WEAPONCOUNTEND; i++) {
		if (CheckedTime > weapon[i % MAXWEAPONCREATE].WeaponCreationTime + WeaponDurationTime) DeleteWeaponItem(i);
		if (DetectCollision_WeaponwithPlayer(i)) SwapWeapon(i);
		else { if (weapon[i % MAXWEAPONCREATE].WeaponActivation) ShowWeaponItem(i); }
	}
}
#endif // !WEAPONITEM_H
