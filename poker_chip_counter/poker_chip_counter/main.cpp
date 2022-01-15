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
    get_players();
    dealer = rand() % players.size();
    
}



int main(int argc, char *argv[])
{

    run_game();
}
