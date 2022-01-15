#include "globals.h"

void print_instructions(){
    cout << "Let's play poker: This will track stacks, allow for rebuys, or new players, and keep track of raises etc" << endl;
    cout << "Usage: in order to move a piece from a5 to a6, type command a5 a6." << endl;
    cout << "ie src dst;" << endl << endl;
}

void error_in_player_entry(){
    cout << "Please enter one of: " << endl;
    cout << "\"N name chipCount\""  << endl;
    cout << "\"C name chipCount\"" << endl;
    cout << "\"B bigBlind littleBlind\"" << endl;
}
void get_players(){
    cout << "Please enter the name and chip count of each player you would like to add like this: \"N name chipCount\""  << endl;
    cout << "if you make a mistake, please enter \"C name chipCount\"" << endl;
    cout << "once you are finished, enter \"B bigBlind littleBlind\"" << endl;

    std::string name;
    char instruction;
    std::string buy_in;
    
    bool exit = false;
    while(!exit){
        cin >> instruction >> name >> buy_in;
        switch(instruction) {
            case 'N'  :
                if( add_player(name, std::stoi(buy_in)) ){
                    break;
                }
                error_in_player_entry();
            case 'C'  :
                if( fix_player(name, std::stoi(buy_in)) ){
                    break;
                }
                error_in_player_entry();
            case 'B'  :
                exit = true;
                big_blind = std::stoi(name);
                little_blind = std::stoi(buy_in);
                break;
            default :
                error_in_player_entry();
        }
    }
    
    
}

bool add_player(std::string player_name, int player_chips){
    if(players.find(player_name) != players.end()){
        cout << "player name already taken!" << endl;
        return false;
    }
    if(player_chips < 0){
        cout << "please enter a positive stack" << endl;
        return false;
    }
    else{
        cout << "Player: " << player_name << ", Stack: " << player_chips << endl;
        players[player_name] = new Player(player_name, player_chips);
        return true;
    }
}
bool fix_player(std::string player_name, int player_chips){
    
}
