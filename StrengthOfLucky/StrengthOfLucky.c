#include "gbafe.h"  
  
extern u8 ItemID;  
  
void BattleGenerateHitAttributes(struct BattleUnit* attacker, struct BattleUnit* defender) {  
    short attack, defense;  
  
    gBattleStats.damage = 0;  
  
    BattleCheckSureShot(attacker);  
  
    if (!(gBattleHitIterator->attributes & BATTLE_HIT_ATTR_SURESHOT)) {  
        if (!BattleRoll2RN(gBattleStats.hitRate, TRUE)) {  
            gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_MISS;  
            return;  
        }  
    }  
  
    attack = gBattleStats.attack;  
    defense = gBattleStats.defense;  
  
    BattleCheckGreatShield(attacker, defender);  
  
    if (!(gBattleHitIterator->attributes & BATTLE_HIT_ATTR_GREATSHLD)) {  
        BattleCheckPierce(attacker, defender);  
    }  
  
    if (gBattleHitIterator->attributes & BATTLE_HIT_ATTR_PIERCE) {  
        defense = 0;  
    }  
  
    gBattleStats.damage = attack - defense;  
  
    if (gBattleHitIterator->attributes & BATTLE_HIT_ATTR_GREATSHLD) {  
        gBattleStats.damage = 0;  
    }  
  
    if (BattleRoll1RN(gBattleStats.critRate, FALSE) == TRUE) {  
        if (BattleCheckSilencer(attacker, defender)) {  
            gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_SILENCER;  
            gBattleStats.damage = BATTLE_MAX_DAMAGE;  
            gBattleHitIterator->attributes &= ~BATTLE_HIT_ATTR_GREATSHLD;  
        } else {  
            gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_CRIT;  
            gBattleStats.damage *= 3;  
        }  
    }  
  
    if (gBattleStats.damage > BATTLE_MAX_DAMAGE) {  
        gBattleStats.damage = BATTLE_MAX_DAMAGE;  
    }  
  
    if (gBattleStats.damage < 0) {  
        gBattleStats.damage = 0;  
    }  
  
    if (gBattleStats.damage < defender->unit.curHP) {  
        for (int i = 0; i < 5; ++i) {  
            if (GetItemIndex(attacker->unit.items[i]) == ItemID) {  
                if (BattleRoll1RN(attacker->unit.lck, FALSE) == TRUE) {  
                    gBattleStats.damage = defender->unit.curHP;  
                    attacker->unit.items[i] = GetItemAfterUse(attacker->unit.items[i]);  
                    break;  
                }  
            }  
        }  
    }  
  
    BattleCheckPetrify(attacker, defender);  
  
    if (gBattleStats.damage != 0) {  
        attacker->nonZeroDamage = TRUE;  
    }  
}