#include "globals.h"
#include "gui.h"



std::unordered_map< std::string, Player* > players;
// this is the table of players
std::vector< Player* > table;

int little_blind;
int big_blind;

void run_game(){
    print_instructions();
    get_players();
    

    cout << move_vec[turn] << "move: ";

    std::string play;
    std::string src;
    std::string dst;
    
    while(cin >> src >> dst){

    }
    
}



int main(int argc, char *argv[])
{

    run_game();
}
