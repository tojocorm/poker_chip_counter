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
    cout << "\"R playerNameToRemove blank\"" << endl;
    cout << "\"B littleBlind bigBlind\" -- if you enter this, the initial player setup time will be over" << endl;
}
void get_players(){
    error_in_player_entry();

    std::string name;
    char instruction;
    std::string buy_in;
    
    bool exit = false;
    while(!exit){
        cin >> instruction >> name >> buy_in;
        switch(instruction) {
            case 'N'  :
                
                if( add_player(name, buy_in) ){
                    break;
                }
                error_in_player_entry();
                break;
            case 'C'  :
                if( fix_player(name, buy_in) ){
                    break;
                }
                error_in_player_entry();
                break;
            case 'R' :
                if (remove_player(name) ){
                    break;
                }
                error_in_player_entry();
                break;
            case 'B'  :
                if(!is_number(name) || !is_number(buy_in)){
                    cout << "Blinds must be integers" << endl;
                    error_in_player_entry();
                    break;
                }
                exit = true;
                big_blind = std::stoi(buy_in);
                little_blind = std::stoi(name);
                cout << "Blinds are " << little_blind << " and " << big_blind << endl;
                break;
            default :
                error_in_player_entry();
        }
    }
    
    
}

bool add_player(std::string player_name, std::string buy_in){
    if(!is_number(buy_in)){
        cout << "buy in must be an integer" << endl;
        return false;
    }
    int player_chips = std::stoi(buy_in);
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
bool fix_player(std::string player_name, std::string buy_in){
    if(!is_number(buy_in)){
        cout << "buy in must be an integer" << endl;
        return false;
    }
    int player_chips = std::stoi(buy_in);
    if(players.find(player_name) == players.end()){
        cout << "Player not yet playing, please add player!" << endl;
        return false;
    }
    if(player_chips < 0){
        cout << "please enter a positive stack" << endl;
        return false;
    }
    else{
        cout << "Player: " << player_name << ", Stack: " << player_chips << endl;
        players[player_name]->stack = player_chips;
        return true;
    }
}

bool remove_player(std::string player_name){
    if(players.find(player_name) == players.end()){
        cout << "Player not yet playing" << endl;
        return true;
    }
    else{
        cout << "Player: " << player_name << " removed from game with Stack: " << players[player_name]->stack << endl;
        delete players[player_name];
        players.erase(player_name);
        return true;
    }
}

bool is_number(std::string s){
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
