//
// Created by Tim Liu on 2019-07-22.
//

#ifndef SORCERY_CARD_H
#define SORCERY_CARD_H


#include "Subject.h"
#include "Observer.h"
#include "State.h"
#include <string>
#include <memory>

class Card : public Subject<std::shared_ptr<Card>, Effect>, public Observer<std::shared_ptr<Card>, Effect>, public std::enable_shared_from_this<Card> {
protected:
    std::string name;
    std::string description;
    std::string type;
    int cost;
    int player;
    bool has_target;
    Effect effect;
    CollectionType belonging = CollectionType::DECK;

    int attack = 0;
    int defence = 0;
    int action_number = 0;
    int action_performed = 0;
    bool has_active = 0;
    int activated_cost = 0;
    int dmg_taken = 0;

public:
    Card(int player, bool);
    std::string get_name();
    std::string get_description();
    std::string get_type();
    int get_player();
    bool can_target();
    CollectionType get_belong();
    Effect get_effect();
    void set_belong(CollectionType);
    void set_reborn();
    void add_action();
    void add_damage(int);
    virtual void start_turn();
    virtual void take_dmg(Subject<std::shared_ptr<Card>, Effect> &whoFrom);
    virtual void take_buf(Subject<std::shared_ptr<Card>, Effect> &whoFrom);
    virtual void meb(Subject<std::shared_ptr<Card>, Effect> &whoFrom);
    virtual void mlb(Subject<std::shared_ptr<Card>, Effect> &whoFrom);
    virtual void end_turn();
    virtual void dec();
    virtual void reset();
    virtual int get_attack();
    virtual int get_defence();
    virtual bool has_activated();
    virtual bool get_activated_cost();
    virtual bool get_action_left();
    virtual void notify(Subject<std::shared_ptr<Card>, Effect> &whoFrom) override;
};


#endif //SORCERY_CARD_H
