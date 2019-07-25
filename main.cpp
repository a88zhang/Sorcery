#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iomanip>

int main(int argc, char *argv[]) {
    std::cin.exceptions(std::ios::eofbit|std::ios::failbit);
    std::string deck_1 = "default.deck";
    std::string deck_2 = "default.deck";
    bool test_mode = false;
    bool graphics_mode = false;
    bool init = false;
    std::string init_cmd = "";
    std::string cmd;
    std::string p1_name;
    std::string p2_name;

    try {
        for (int i = 0; i < argc; i ++) {
            cmd = std::string(argv[i]);
            if (cmd == "-deck1") { // not using default deck for deck 1
                if (i + 1 == argc)
                    throw std::out_of_range("Need filename for deck 1");
                ++ i;
                deck_1 = std::string(argv[i]);
                std::ifstream ifs(deck_1);
                if (!ifs.is_open())
                    throw std::out_of_range("File for deck 1 not found");
            }
            else if (cmd == "-deck2") { // not using default deck for deck 2
                if (i + 1 == argc)
                    throw std::out_of_range("Need filename for deck 2");
                ++ i;
                deck_2 = std::string(argv[i]);
                std::ifstream ifs(deck_2);
                if (!ifs.is_open())
                    throw std::out_of_range("File for deck 2 not found");
            }
            else if (cmd == "-test") { // enable test mode of the program
                test_mode = true;
            }
            else if (cmd == "-graphics") { // enable graphics for the program
                graphics_mode = true;
            }
            else if (cmd == "-init") { // initialize the game with the input file
                if (i + 1 == argc)
                    throw std::out_of_range("Need filename for the initialize file");
                ++ i;
                init = true;
                init_cmd = std::string(argv[i]);
                std::ifstream ifs(init_cmd);
                if (!ifs.is_open())
                    throw std::out_of_range("File not found");
            }
        }
    }
    catch (std::out_of_range e) { // catch any exceptions
        std::cerr<<e.what()<<std::endl; // print the corresponding message the that particular exception
        return 1;
    }

    if (graphics_mode) {
        std::cout<<"graphics mode activated"<<std::endl;
        // do graphics stuff
    }

    std::ifstream ifs;
    std::istringstream iss;
    if (init) {
        std::cout<<"initializing mode activated"<<std::endl;
        ifs.open(init_cmd);
    }

    std::cout<<"Player 1: ";
    if (init && getline(ifs, p1_name)) {
        std::cout<<p1_name<<std::endl;
    }
    else {
        init = false;
        getline(std::cin, p1_name);
    }

    std::cout<<"Player 2: ";
    if (init && getline(ifs, p2_name)) {
        std::cout<<p2_name<<std::endl;
    }
    else {
        init = false;
        getline(std::cin, p2_name);
    }

    // read in deck

    while (true) {
        try {
            if (init) {
                if (!getline(ifs, cmd)) {
                    init = false;
                    continue;
                }
            }
            else if (!getline(std::cin, cmd))
                throw 0;

            iss.clear();
            iss.str(cmd);
            iss >> cmd;
            if (cmd == "help") { // display the help message
                std::cout << "Commands: help -- Display this message." << std::endl;
                std::cout << std::setw(10) << "end -- End the current player's turn" << std::endl;
                std::cout << std::setw(10) << "quit -- End the game." << std::endl;
                std::cout << std::setw(10) << "attack minion other-minion -- Orders minion to attack other-minion."
                          << std::endl;
                std::cout << std::setw(10) << "attack minion -- Orders minion to attack the opponent." << std::endl;
                std::cout << std::setw(10)
                          << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player."
                          << std::endl;
                std::cout << std::setw(10)
                          << "use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player."
                          << std::endl;
                std::cout << std::setw(10)
                          << "inspect minion -- View a minion’s card and all enchantments on that minion."
                          << std::endl;
                std::cout << std::setw(10) << "hand -- Describe all cards in your hand." << std::endl;
                std::cout << std::setw(10) << "board -- Describe all cards on the board." << std::endl;
            } else if (cmd == "end") { // end one player's turn
                std::cout<<"end"<<std::endl;
            } else if (cmd == "quit") { // end the game
                std::cout << "Game Ended, Thanks for Playing" << std::endl;
                std::cout << "Coded by Tony Monster, Tim the Banker, and Kevin the Ripper" << std::endl;
                std::cout << "All Rights Reserved, 07/2019" << std::endl;
                break;
            } else if (cmd == "draw" && test_mode) { // draw a card (test mode only)
                std::cout<<"draw"<<std::endl;
            } else if (cmd == "discard" && test_mode) { // discard a card (test mode only)
                std::cout<<"discard"<<std::endl;
            } else if (cmd == "attack") { // minions attack
                int index_1, index_2;
                if (iss.eof()) // not getting the index of the minion
                    throw 1;
                iss >> index_1;
                if (iss.eof()) { // minion at index_1 attack opposing player
                    std::cout<<"minion "<<index_1<<" attacks opposing player."<<std::endl;
                }
                else { // minion at index_1 attack minion at index_2
                    iss >> index_2;
                    std::cout<<"minion "<<index_1<<" attacks minion "<<index_2<<"."<<std::endl;
                }
            } else if (cmd == "play") { // play player's card
                int index_1, index_2;
                int player;
                if (iss.eof()) // not getting the index of the card
                    throw 2;
                iss>>index_1;
                if (iss.eof()) // not getting the index of the target player
                    // need modification for no-target spells, or summon a minion
                    throw 3;
                iss>>player;
                if (iss.eof()) // not getting the index of the target minion
                    throw 4;
                if (player != 1 && player != 2)
                    throw std::out_of_range("Player does not exist, please provide which player you would like to target on.");
                iss>>index_2;
                std::cout<<"play card "<<index_1<<" target on player "<<player<<"'s minion "<<index_2<<"."<<std::endl;
            } else if (cmd == "use") { // use minion's ability
                // need to check if the minion has activated ability
                int index_1, index_2;
                int player;
                if (iss.eof()) // not getting the index of the minion
                    throw 5;
                iss >> index_1;
                if (iss.eof()) // not getting the index of the target player
                    // need modification for no-target spells
                    throw 3;
                iss>>player;
                if (iss.eof()) // not getting the index of the target minion
                    throw 4;
                if (player != 1 || player != 2)
                    throw std::out_of_range("Player does not exist, please provide which player you would like to target on.");
                iss>>index_2;
                std::cout<<"use card "<<index_1<<"'s ability on player "<<player<<"'s minion "<<index_2<<"."<<std::endl;
            } else if (cmd == "inspect") { // inspect minion
                int index;
                if (iss.eof()) // not getting the index of the inspected minion
                    throw 6;
                iss>>index;
                std::cout<<"inspect minion "<<index<<std::endl;
            } else if (cmd == "hand") { // show the hand of the activated player
                std::cout<<"hand"<<std::endl;
            } else if (cmd == "board") { // display the board of the game
                std::cout<<"board"<<std::endl;
            } else {
                std::cout << "No command named " << cmd << " found." << std::endl;
                std::cout << "To see all commands available, use help command (lowercase)" << std::endl;
            }
        }

        catch (std::ios::failure &) { return 0; }  // Any I/O failure quits
        catch (std::out_of_range e) { std::cout<<e.what()<<std::endl; }
        catch (int i) {
            switch (i) {
                case 1:
                    std::cout<<"Please provide which minion you would like to attack with."<<std::endl;
                    break;
                case 2:
                    std::cout<<"Please provide which card you would like to play."<<std::endl;
                    break;
                case 3:
                    std::cout<<"Please specify which player you would like to target on."<<std::endl;
                    break;
                case 4:
                    std::cout<<"Please specify which minion you would like to target on."<<std::endl;
                    break;
                case 5:
                    std::cout<<"Please provide which minion's ability you would like to use."<<std::endl;
                    break;
                case 6:
                    std::cout<<"Please provide which minion you would like to inspect."<<std::endl;
                    break;
            }
        }
    }
    return 0;
}