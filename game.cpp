    //
// Created by Tim Liu on 2019-07-26.
//

#include "game.h"
#include "ascii_graphics.h"
#include <vector>

using namespace std;

Game::Game(string p1, string p2) {
    players[0] = make_shared<Player>(p1, 0);
    players[1] = make_shared<Player>(p2, 1);
    CurrPlayer = 0;
    OtherPlayer = 1;
    game_end = false;
    game_begin = false;

    deck->attach(hand);
    hand->attach(board);
    board->attach(hand);
    board->attach(players[0]);
    board->attach(players[1]);
    board->attach(grave);
    grave->attach(board);

    this->attach(board);
}

void Game::init_deck(int player, std::string filename) {
    deck->load_deck(filename, player);
}

int Game::getCurrPlayer() {
    return CurrPlayer;
}

int Game::getOtherPlayer() {
    return OtherPlayer;
}

void Game::Gamepush(std::shared_ptr<Collection> where, int who, std::shared_ptr<Card> c) {
    where->push_card(who, c);
}

void Game::Gamepop(std::shared_ptr<Collection> where, int who, std::shared_ptr<Card> c) {
    where->pop_card(who, c);
}

void Game::move(std::shared_ptr<Collection> source, std::shared_ptr<Collection> dest, std::shared_ptr<Card> the_card) {
    source->pop_card(this->getCurrPlayer(), the_card);
    dest->push_card(this->getCurrPlayer(), the_card);
}

shared_ptr<Player> Game::getPlayer1() {
    return this->players[0];
}

shared_ptr<Player> Game::getPlayer2() {
    return this->players[1];
}
/*
void Game::setDeck(string filename, int player) {
    this->deck->load_deck(filename, player);
}
*/
void Game::init_game() {
    for (int i = 0; i < 4; i++) {
        deck->pop_top(CurrPlayer);
    }
    for (int i = 0; i < 4; i++) {
        deck->pop_top(1 - CurrPlayer);
    }
}

void Game::draw() {
    if (hand->get_size(CurrPlayer) < 5 && deck->get_size(CurrPlayer) > 0) {
        deck->pop_top(CurrPlayer);
    }
}

bool Game::getEnd() {
    return game_end;
}

bool Game::getBegin() {
    return game_begin;
}

void Game::prettyprint() {
    //bool test = false; // test only, need to delete


    // top board
    cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
    for (int i = 0; i < 33*5; i++) {
        cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl;


    // player 1 ritual, player, graveyard
    vector<card_template_t> player1_line;

    if (!board->get_ritual(0).empty()) {
        std::shared_ptr<Card> r =  board->get_ritual(0)[0];
        player1_line.emplace_back(display_ritual(r->get_name(), r->get_cost(), r->get_activated_cost(), r->get_description(), r->get_defence()));
    } else {
        player1_line.emplace_back(CARD_TEMPLATE_BORDER);
    }
    player1_line.emplace_back(CARD_TEMPLATE_EMPTY);
    player1_line.emplace_back(display_player_card(1, players[0]->getName(), players[0]->getHealth(), players[0]->getMagic()));
    player1_line.emplace_back(CARD_TEMPLATE_EMPTY);
    if (!grave->get_list(0).empty()) {
        std::shared_ptr<Card> c = grave->get_list(0).back();
        if (c->has_activated_r()) {
            player1_line.emplace_back(display_minion_activated_ability(c->get_name(), c->get_cost(), c->get_attack(), c->get_defence(), c->get_activated_cost(), c->get_description()));
        } else {
            player1_line.emplace_back(display_minion_triggered_ability(c->get_name(), c->get_cost(), c->get_attack(), c->get_defence(), c->get_description()));
        }
    } else {
        player1_line.emplace_back(CARD_TEMPLATE_BORDER);
    }
    for (int i = 0; i < CARD_TEMPLATE_BORDER.size(); i++) {
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN; // external
        for (int j = 0; j < 5; j++) {
            cout << player1_line.at(j).at(i);
        }
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN; // external
        cout << endl;
    }


    // player 1 minion
    vector<card_template_t> player1_minions;
    int player1_minion_num = 0;
    player1_minion_num = board->get_list(0).size();
    for (int i = 0; i < player1_minion_num; ++i) {
        std::shared_ptr<Card> c = board->get_list(0)[i];
        if (c->has_activated_r()) {
            player1_minions.emplace_back(display_minion_activated_ability(c->get_name(), c->get_cost(), c->get_attack(), c->get_defence(), c->get_activated_cost(), c->get_description()));
        } else {
            player1_minions.emplace_back(display_minion_triggered_ability(c->get_name(), c->get_cost(), c->get_attack(), c->get_defence(), c->get_description()));
        }
    }
    for (int i = 0; i < 5 - player1_minion_num; ++i) {
        player1_minions.emplace_back(CARD_TEMPLATE_BORDER);
    }
    for (int i = 0; i < CARD_TEMPLATE_BORDER.size(); ++i) {
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
        for (int j = 0; j < 5; j++) {
            cout << player1_minions.at(j).at(i);
        }
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
        cout << endl;
    }


    // centre graphic
    for (int i = 0; i < CENTRE_GRAPHIC.size(); i++) {
        cout << CENTRE_GRAPHIC.at(i) << endl;
    }

    // player 2 minion
    vector<card_template_t> player2_minions;
    int player2_minion_num = 0;
    player2_minion_num = board->get_list(1).size();
    for (int i = 0; i < player2_minion_num; ++i) {
        std::shared_ptr<Card> c = board->get_list(1)[i];
        if (c->has_activated_r()) {
            player2_minions.emplace_back(display_minion_activated_ability(c->get_name(), c->get_cost(), c->get_attack(), c->get_defence(), c->get_activated_cost(), c->get_description()));
        } else {
            player2_minions.emplace_back(display_minion_triggered_ability(c->get_name(), c->get_cost(), c->get_attack(), c->get_defence(), c->get_description()));
        }
    }
    for (int i = 0; i < 5 - player2_minion_num; ++i) {
        player2_minions.emplace_back(CARD_TEMPLATE_BORDER);
    }
    for (int i = 0; i < CARD_TEMPLATE_BORDER.size(); ++i) {
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
        for (int j = 0; j < 5; j++) {
            cout << player2_minions.at(j).at(i);
        }
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
        cout << endl;
    }

    // player 2 ritual, player, graveyard
    vector<card_template_t> player2_line;
    if (!board->get_ritual(1).empty()) {
        std::shared_ptr<Card> r =  board->get_ritual(1)[0];
        player2_line.emplace_back(display_ritual(r->get_name(), r->get_cost(), r->get_activated_cost(), r->get_description(), r->get_defence()));
    } else {
        player2_line.emplace_back(CARD_TEMPLATE_BORDER);
    }
    player2_line.emplace_back(CARD_TEMPLATE_EMPTY);
    player2_line.emplace_back(display_player_card(2, players[1]->getName(), players[1]->getHealth(), players[1]->getMagic()));
    player2_line.emplace_back(CARD_TEMPLATE_EMPTY);
    if (!grave->get_list(1).empty()) {
        std::shared_ptr<Card> c = grave->get_list(1).back();
        if (c->has_activated_r()) {
            player2_line.emplace_back(display_minion_activated_ability(c->get_name(), c->get_cost(), c->get_attack(), c->get_defence(), c->get_activated_cost(), c->get_description()));
        } else {
            player2_line.emplace_back(display_minion_triggered_ability(c->get_name(), c->get_cost(), c->get_attack(), c->get_defence(), c->get_description()));
        }
    } else {
        player2_line.emplace_back(CARD_TEMPLATE_BORDER);
    }
    for (int i = 0; i < CARD_TEMPLATE_BORDER.size(); i++) {
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN; // external
        for (int j = 0; j < 5; j++) {
            cout << player2_line.at(j).at(i);
        }
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN; // external
        cout << endl;
    }

    //bottom board
    cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
    for (int i = 0; i < 33*5; i++) {
        cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << endl;
}

void Game::startTurn() {
    draw();
    setState(Effect(EffectType::SOT, CurrPlayer, 0, CollectionType::BOARD, 0, 0, 2, 0));
    notifyObservers();
    setState(Effect(EffectType::SOT, CurrPlayer, 0, CollectionType::BOARD, 0, 0, 3, 0));
    notifyObservers();
}

void Game::endTurn() {
    setState(Effect(EffectType::EOT, CurrPlayer, 0, CollectionType::BOARD, 2));
    notifyObservers();
    CurrPlayer = 1 - CurrPlayer;
    OtherPlayer = 1 - OtherPlayer;
}
void Game::MinionattackPlayer(int index_1) {
    try {
        board->attackPlayer(CurrPlayer, index_1);
    } catch (int e) {
        throw e;
    }
}

void Game::MinionattackMinion(int index_1, int index_2) {
    try {
        board->attackMinion(CurrPlayer, index_1, index_2);
    } catch (int e) {
        throw e;
    }
}
void Game::PlayCard(int index_1, int player, int index_2) {
    try {
        hand->pop_selected(CurrPlayer, index_1, player, index_2);
    } catch (int e) {
        throw e;
    }
}
void Game::checkAbility(int index_1){}
void Game::UseCard(int index_1, int player, int index_2){
    try {
        board->useCard(CurrPlayer, index_1, player, index_2);
    } catch (int e) {
        throw e;
    }
}
void Game::InspectMinion(int index_1){}

void Game::ShowHand() {
    int player = getCurrPlayer();
    int size = hand->get_size(player);
    cout << "HAND SIZE" << size << std::endl;
    vector<card_template_t> player_hand;
    for (int i = 0; i < size; ++i) {
        shared_ptr<Card> temp = hand->get_list(player).at(i);
        if (temp->get_type() == "Spell")
            player_hand.emplace_back(display_spell(temp->get_name(), temp->get_cost(), temp->get_description()));
        else if (temp->get_type() == "Minion") {
            if (temp->has_activated_r()) {
                player_hand.emplace_back(display_minion_activated_ability(temp->get_name(), temp->get_cost(), temp->get_attack(), temp->get_defence(), temp->get_activated_cost(), temp->get_description()));
            } else {
                player_hand.emplace_back(display_minion_triggered_ability(temp->get_name(), temp->get_cost(), temp->get_attack(), temp->get_defence(), temp->get_description()));
            }
        } else if (temp->get_type() == "Ritual") {
            player_hand.emplace_back(display_ritual(temp->get_name(), temp->get_cost(), temp->get_activated_cost(), temp->get_description(), temp->get_defence()));
        } else if (temp->get_type() == "Enchantment") {
            if (temp->get_attack() == 0) {
                player_hand.emplace_back(display_enchantment(temp->get_name(), temp->get_cost(), temp->get_description()));
            } else {
                string att = (temp->get_attack() > 0 ? "+" + to_string(temp->get_attack()) : "*" + to_string(-temp->get_attack()));
                string def = (temp->get_defence() > 0 ? "+" + to_string(temp->get_defence()) : "*" + to_string(-temp->get_defence()));
                player_hand.emplace_back(display_enchantment_attack_defence(temp->get_name(), temp->get_cost(), temp->get_description(), att, def));
            }
        }
    }

    for (int i = 0; i < CARD_TEMPLATE_BORDER.size(); i++) {
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN; // external
        for (int j = 0; j < player_hand.size(); j++) {
            cout << player_hand.at(j).at(i);
        }
        cout << EXTERNAL_BORDER_CHAR_UP_DOWN; // external
        cout << endl;
    }

}

std::string Game::getWinner() {
    if (players[0]->getHealth() <= 0) {
        return players[1]->getName();
    } else if (players[1]->getHealth() <= 0) {
        return players[0]->getName();
    } else {
        return "None";
    }
}

void Game::notify(Subject<std::shared_ptr<Card>, Effect> &whoFrom) {
    if (whoFrom.getState().type == EffectType::RES) {
        grave->pop_top(whoFrom.getState().player);
    }
}