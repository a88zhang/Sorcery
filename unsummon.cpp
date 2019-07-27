//
//  Unsummon.cpp
//  Sorcery
//
//  Created by An Zhang on 2019-07-25.
//  Copyright © 2019 An Zhang. All rights reserved.
//
#include "unsummon.h"

Unsummon::Unsummon(int player) : Spell(player) {
    name = "Unsummon";
    description = "Return target minion to its owner's hand";
    type = "Spell";
    cost = 1;
    need_target = true;
    effect = Effect(EffectType::MLC, get_player(), 0, CollectionType::HAND);
}
