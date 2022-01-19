#include "globals.h"
#include "gui.h"



std::unordered_map< std::string, Player* > players;
// this is the table of players
std::vector< Player* > table;

int little_blind;
int big_blind;
int dealer;
int hand_num;
std::string infile_glob;
std::string tempoutfile = "";
std::string base_directory = "/Users/tobycormack/Desktop/SuperSenior/projects/poker_chip_counter/poker_chip_counter/poker_chip_counter/";

void run_game(){
    print_instructions();
    create_players();
    dealer = rand() % players.size();

    
    

    std::string outFile = get_out_file();
    end_of_game(outFile);
    delete_data();
}




int main(int argc, char *argv[])
{

    run_game();
}
