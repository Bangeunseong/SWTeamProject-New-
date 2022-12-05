#pragma once
#include "CursorFunctions.h"
#include "VariableSets.h"
#include "Timer.h"
#ifndef WEAPONITEM_H
#define WEAPONITEM_H

void HideWeaponItem(int Weapon_number) {
	SetCurrentCursorPos(weapon[Weapon_number % MAXWEAPONCREATE].WEAPON_POS_X, weapon[Weapon_number % MAXWEAPONCREATE].WEAPON_POS_Y);
	printf(" ");
}

void ShowWeaponItem(int Weapon_number) {
	SetCurrentCursorPos(weapon[Weapon_number % MAXWEAPONCREATE].WEAPON_POS_X, weapon[Weapon_number % MAXWEAPONCREATE].WEAPON_POS_Y);
	printf("%c", WeaponItemModel[weapon[Weapon_number % MAXWEAPONCREATE].WeaponNumber]);
}

void SetWeaponItemModelNumber(int Weapon_number) {
	weapon[Weapon_number % MAXWEAPONCREATE].WeaponNumber = rand() % 2 + 1;
}

#endif // !WEAPONITEM_H
