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
#include <stdlib.h>

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
        total_buys = buy_in;
    };
    void re_buy(int rebuy){
        stack += rebuy;
        total_buys += rebuy;
    }
    std::string name;
    int stack;
    int total_buys;
};

// this holds all the players
extern std::unordered_map< std::string, Player* > players;
// this is the table of players
extern std::vector< Player* > table;

extern int little_blind;
extern int big_blind;
extern int dealer;

bool is_number(std::string s);
void print_instructions();
void get_players();
void load_players(std::string filename);
void error_in_player_entry();
bool add_player(std::string player_name, std::string buy_in);
bool fix_player(std::string player_name, std::string buy_in);
bool remove_player(std::string name);
bool load_from_file(std::string filename);
bool write_to_file(std::string filename);

#endif
