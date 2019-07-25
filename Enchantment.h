//
// Created by Tim Liu on 2019-07-22.
//

#ifndef SORCERY_ENCHANTMENT_H
#define SORCERY_ENCHANTMENT_H

#include "Minion.h"

class Enchantment : public Minion {
protected:
    Minion *previous;
    Minion *base;
public:
    virtual ~Enchantment() = default;
};

#endif //SORCERY_ENCHANTMENT_H
