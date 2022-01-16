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
    char response;
    bool exit = false;
    while(!exit){
        cout << "New game (\"N\") or load from existing file (\"L\")?" << endl;
        cin >> response;
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
                break;
            }
            default: {
                break;
            }
        }
    }
    dealer = rand() % players.size();
    
}



int main(int argc, char *argv[])
{

    run_game();
}
