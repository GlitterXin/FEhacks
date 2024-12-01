#include "gbafe.h"

extern u8 GodWings;

void SetWorkingMoveCosts(const s8 mct[TERRAIN_COUNT]) {
    bool hasGodWings = UnitHasItem(gActiveUnit, GodWings);

    for (int i = 0; i < TERRAIN_COUNT; ++i) {
        gWorkingTerrainMoveCosts[i] = (hasGodWings) ? 1 : mct[i];
    }
}
