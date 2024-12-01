#include "gbafe.h"

extern u8 SpecialWeaponID;

void KillWithSpecialWeapon() {
	if (GetItemIndex(gBattleActor.weaponBefore) == SpecialWeaponID || GetItemIndex(gBattleTarget.weaponBefore) == SpecialWeaponID) {
		SetFlag(0x7B);
    }
}