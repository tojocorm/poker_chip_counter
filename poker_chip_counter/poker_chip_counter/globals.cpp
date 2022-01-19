#include "globals.h"

void print_instructions(){
    cout << "Let's play poker: This will track stacks, allow for rebuys, or new players, and keep track of raises etc" << endl;
    cout << "Usage: in order to move a piece from a5 to a6, type command a5 a6." << endl;
    cout << "ie src dst;" << endl << endl;
}

void error_in_player_entry(){
    cout << "Please enter one of: " << endl;
    cout << "\"N name chipCount\" to add a player or add a player to the game who exists but is not currently playing"  << endl;
    cout << "\"C name chipCount\" to change a current players chipCount" << endl;
    cout << "\"R playerNameToRemove blank\" to remove a player" << endl;
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
            case 'N': {
                if( add_player(name, buy_in) ){
                    break;
                }
                error_in_player_entry();
                break;
            }
            case 'C': {
                if( fix_player(name, buy_in) ){
                    break;
                }
                error_in_player_entry();
                break;
            }
            case 'R': {
                if (remove_player(name) ){
                    break;
                }
                error_in_player_entry();
                break;
            }
            case 'B': {
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
            }
            default: {
                error_in_player_entry();
            }
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
        if(players[player_name]->get_buys() != 0){
            cout << "player name already taken!" << endl;
            return false;
        }
    }
    if(player_chips < 0){
        cout << "please enter a positive stack" << endl;
        return false;
    }
    else{
        cout << "Player: " << player_name << ", Stack: " << player_chips << endl;
        if(players.find(player_name) == players.end()){
            players[player_name] = new Player(player_name, player_chips);
        }
        else{
            players[player_name]->set_stack_and_buy(player_chips, player_chips);
        }
        table.push_back(players[player_name]);
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
        players[player_name]->set_stack_and_buy(player_chips, player_chips);
        return true;
    }
}

bool remove_player(std::string player_name){
    if(players.find(player_name) == players.end()){
        cout << "Player not yet playing" << endl;
        return true;
    }
    else{
        cout << "Player: " << player_name << " removed from game with Stack: " << players[player_name]->get_stack() << endl;
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

bool load_from_file(std::string no_base){
    std::string filename = base_directory + no_base;
    std::ifstream File(filename);

    if(!File.is_open()){
        std::cout << "could not open file: " << filename << endl;
        return false;
    }
    std::string in;
    if(!getline(File, in)){
        std::cout << "empty file, try again" << endl;
        return false;
    };
    if(in != "POKER HISTORY"){
        cout << "Not a history file" << endl;
        return false;
    }
    
    read_from_file(File);
    File.close();

    get_players();
    return true;
}

bool write_to_file(std::string filename){
    std::ofstream myfile (filename);
    if (myfile.is_open()){
        myfile << "POKER HISTORY" << endl;
        for(auto it = players.begin(); it != players.end(); ++it){
            myfile << it->second->get_name();
            if(it->second->get_buys() != 0){
                myfile << " " << it->second->get_buys() << " " << it->second->get_stack();
            }
            myfile << endl;
            std::vector<std::pair<int, int> > history = it->second->get_history();
            for(size_t i = 0; i < history.size(); ++i){
                myfile << history[i].first << " " << history[i].second;
                if(i != (history.size() - 1)){
                    myfile << " ";
                }
            }
            myfile << endl;
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file";
        return false;
    }
    return true;
}

// This function returns a vector of strings split by spaces in input
std::vector<std::string> split_space(std::string input){
    std::vector<std::string> ret_vec;
    size_t pos = 0;
    std::string delimiter = " ";
    // While we can find a delimiter
    while ((pos = input.find(delimiter)) != std::string::npos) {
        // Find the token from the index 0 position of the delimiter
        std::string token = input.substr(0, pos);
        // Add token to return
        ret_vec.push_back(token);
        // Erase token through next delimiter
        input.erase(0, pos + 1);
    }

    // Push back the last pathname
    ret_vec.push_back(input);
    return ret_vec;
}

void read_from_file(std::ifstream &File){
    std::string in;
    while(getline(File, in)){
        std::vector<std::string> first_line = split_space(in);
        std::string name = first_line[0];
        int curr_stack;
        int curr_buys;

        // game in progress
        if(first_line.size() > 1){
            curr_stack = std::stoi(first_line[2]);
            curr_buys = std::stoi(first_line[1]);
            players[name] = new Player(name, curr_buys);
            players[name]->set_stack_and_buy(curr_stack, curr_buys);
            table.push_back(players[name]);
            cout << "Player initialized with name: " << name << ", current buys: " << curr_buys << ", current stack: " << curr_stack << endl;
        }

        // new game or new player
        else{
            cout << "How many chips would you like player: " << name << ", to buy in with -- enter 0 if not playing." << endl;
            cin >> curr_buys;
            if(curr_buys != 0){
                players[name] = new Player(name, curr_buys);
                table.push_back(players[name]);
                cout << "Player initialized with name: " << name << ", current buys: " << curr_buys << ", current stack: " << curr_buys << endl;
            }
            else{
                cout << "Player: " << name << " not playing in this game" << endl;
                players[name] = new Player(name, 0);
            }
        }

        getline(File, in);
        std::vector<std::string> history = split_space(in);
        std::vector<std::pair<int, int> > history_player;
        for(size_t i = 0; i < history.size()/2; ++i){
            std::pair<int, int> in_out = std::make_pair(std::stoi(history[2*i]), std::stoi(history[2*i + 1]));
            history_player.push_back(in_out);
        }
        players[name]->set_history(history_player);
    }
    
    cout << endl << endl;
    for(size_t i = 0; i < table.size(); ++i){
        cout << "Player playing with name: " << table[i]->get_name() << ", current buys: " << table[i]->get_buys() << ", current stack: " << table[i]->get_stack() << endl;
    }

}


void end_of_game(std::string filename){
    cout << "End of game after " << hand_num << " hands"<< endl;
    for(auto it = players.begin(); it != players.end(); ++it){
        int stack = it->second->get_stack();
        int buys = it->second->get_buys();
        std::vector<std::pair<int, int> > history = it->second->get_history();
        history.push_back(std::make_pair(buys, stack));
        it->second->set_history(history);
        it->second->set_stack_and_buy(0, 0);
        int buys_tot = 0;
        int cash_out_tot = 0;
        for(int i = 0; i < history.size(); ++i){
            buys_tot += history[i].first;
            cash_out_tot += history[i].second;
        }
        cout << "Player " << it->first << " cashes out with " << stack << " and a overall wins of " << cash_out_tot - buys_tot << endl;
        if(filename != ""){
            filename = base_directory + filename;
            write_to_file(filename);
        }
    }
}

void create_players(){
    std::string resp;
    bool exit = false;
    while(!exit){
        cout << "New game (\"N\") or load from existing file (\"L\")?" << endl;
        cin >> resp;
        if(resp.size() != 1){
            continue;
        }
        char response = resp[0];
        switch (response) {
            case 'N': {
                get_players();
                exit = true;
                break;
            }
            case 'L': {
                cout << "what file would you like to read from?" << endl;
                std::string filename;
                cin >> filename;
                exit = load_from_file(filename);
                if(exit){
                    infile_glob = filename;
                    tempoutfile = base_directory + "poker_temp_" + filename;
                }
                break;
            }
            default: {
                break;
            }
        }
    }
}

std::string get_out_file(){
    std::string resp;
    while(true){
        cout << "Would you like to save the current game; Yes \"Y\" No \"N\"" << endl;

        cin >> resp;
        if(resp.size() != 1){
            continue;
        }
        char response = resp[0];
        switch (response) {
            case 'Y': {
                std::string filename = "";
                while(filename.size() < 1){
                    cout << "Enter filename of file to write to:" << endl;
                    cin >> filename;
                }
                return filename;
            }
            case 'N': {
                cout << "Confirm that you would like to delete all data from this game - enter \"Y\", else enter anything else" << endl;
                cin >> resp;
                if(resp.size() != 1){
                    continue;
                }
                if(resp[0] != 'Y'){
                    continue;
                }
                cout << "Game data (not starter file) deleted" << endl;
                return "";
            }
            default: {
                break;
            }
        }
    }
}

void delete_data(){
    if( std::remove(tempoutfile.c_str()) != 0 ){
        cout << "Error: temp file not deleted" << endl;
    }
    else{
        cout << "Tempfile successfully deleted" << endl;
    }
    for(auto it = players.begin(); it != players.end(); ++it){
        delete it->second;
    }
}
