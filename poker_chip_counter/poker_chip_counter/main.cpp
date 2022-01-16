#include "globals.h"
#include "gui.h"



std::unordered_map< std::string, Player* > players;
// this is the table of players
std::vector< Player* > table;

int little_blind;
int big_blind;
int dealer;
void run_game(){
    print_instructions();
    cout << "New game (\"N\") or load from existing file (\"L\")?" << endl;
    char response;
    cin >> response;
    bool exit = false;
    while(!exit){
        switch(response) {
            case 'N' :
                get_players();
                exit = true;
            case 'L' :
                cout << "what file would you like to read from?" << endl;
                std::string filename;
                cin >> filename;
                load_players(filename);
                exit = true;
            default :
                cout << "New game (\"N\") or load from existing file (\"L\")?" << endl;
        }
    }
    dealer = rand() % players.size();
    
}



int main(int argc, char *argv[])
{

    run_game();
}
