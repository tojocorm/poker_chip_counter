#include "globals.h"
#include "gui.h"



std::unordered_map< std::string, Player* > players;
// this is the table of players
std::vector< Player* > table;

int little_blind;
int big_blind;
int dealer;
int hand_num;

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
                break;
            }
            default: {
                break;
            }
        }
    }
}
void run_game(){
    print_instructions();
    create_players();
    dealer = rand() % players.size();
    end_of_game("/Users/tobycormack/Desktop/SuperSenior/projects/poker_chip_counter/poker_chip_counter/poker_chip_counter/test1out.txt");
}




int main(int argc, char *argv[])
{

    run_game();
}
