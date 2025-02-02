#include "gbafe.h"

void GoldInterests() {
	u32 current_gold = gPlaySt.partyGoldAmount;
	u8 bonus = gEventSlots[EVT_SLOT_B];
	u32 interests = (current_gold * bonus) / 100;

	if (interests > 0) {
	sub_8024E20(interests);
	}
}