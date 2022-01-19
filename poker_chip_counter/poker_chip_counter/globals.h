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
#include <stdio.h>

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
    void set_stack_and_buy(int new_stack, int new_buy){
        stack = new_stack;
        total_buys = new_buy;
    }
    
    void set_history(std::vector<std::pair<int, int> > history_in){
        history = history_in;
        return;
    }
    
    std::vector<std::pair<int, int> > get_history(){
        return history;
    }
    
    int get_stack(){
        return stack;
    }
    int get_buys(){
        return total_buys;
    }
    std::string get_name(){
        return name;
    }

private:
    std::string name;
    int stack;
    int total_buys;
    std::vector<std::pair<int, int> > history;
};

// this holds all the players
extern std::unordered_map< std::string, Player* > players;
// this is the table of players
extern std::vector< Player* > table;

extern int little_blind;
extern int big_blind;
extern int dealer;
extern int hand_num;
extern std::string infile_glob;
extern std::string tempoutfile;
extern std::string base_directory;

bool is_number(std::string s);
void print_instructions();
void get_players();
void error_in_player_entry();
bool add_player(std::string player_name, std::string buy_in);
bool fix_player(std::string player_name, std::string buy_in);
bool remove_player(std::string name);
bool load_from_file(std::string no_base);
bool write_to_file(std::string filename);
std::vector<std::string> split_space(std::string buys);
void read_from_file(std::ifstream &File);
void end_of_game(std::string filename);
void create_players();
std::string get_out_file();
void delete_data();

#endif
