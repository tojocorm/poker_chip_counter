#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <cmath>
#include <assert.h>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::min;

class Player
{
    public:
    Player(std::string name_str, int buy_in){
        stack = buy_in;
        name = name_str;
    };
    void re_buy(int rebuy){
        stack += rebuy;
    }
    std::string name;
    int stack;
};

// this holds all the players
extern std::unordered_map< std::string, Player* > players;
// this is the table of players
extern std::vector< Player* > table;

extern int little_blind;
extern int big_blind;
bool is_number(std::string s);
void print_instructions();
void get_players();
void error_in_player_entry();
bool add_player(std::string player_name, std::string buy_in);
bool fix_player(std::string player_name, std::string buy_in);
bool remove_player(std::string name);

#endif
