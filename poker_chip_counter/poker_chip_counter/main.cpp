#include "globals.h"
#include "gui.h"


std::vector< std::unordered_map< pieceType, int > > takenPieces;

// this is stored from whites perspective -- this means that a1 is indexed at [1][1]
std::vector< std::vector< piece > > board;

int move = 0;
int turn = White;
void run_game(){
    print_instructions();

    turn = White;
    print_board();
    std::vector<std::string > move_vec{"White's ", "Black's "};

    cout << move_vec[turn] << "move: ";
    bool check = false;
    std::string play;
    std::string src;
    std::string dst;
    
    while(cin >> src >> dst){
        play = src + " " + dst;
        while(!valid_move(play, check)){
            cout << "Invalid Move -- try again: ";
            cin >> src >> dst;
            play = src + " " + dst;
        }
        make_move(play);
        
        switch(check_checkmate(turn)){
            // neither
            case(0) :
                cout << "NOTHING" << endl;

            // check
            case(1) :
                cout << "CHECK" << endl;
                check = true;

            // check mate
            case(2) :
                cout << "MATE" << endl;
                break;
        }
        turn = !turn;
        print_board();
        check ? cout << "Must respond to Check" : cout << "";
        cout << move_vec[turn] << "move: ";
    }
    
}



int main(int argc, char *argv[])
{
    std::vector<piece> empty;
    std::vector<piece> pawns;
    std::vector<piece> row;
    piece rook(White, Rook);
    piece bishop(White, Bishop);
    piece queen(White, Queen);
    piece king(White, King);
    piece knight(White, Knight);

    row.push_back(rook);
    row.push_back(knight);
    row.push_back(bishop);
    row.push_back(queen);
    row.push_back(king);
    row.push_back(bishop);
    row.push_back(knight);
    row.push_back(rook);
    
    piece blank(-1, Blank);
    piece pawn(White, Pawn);
    for(int i = 0; i < 8; ++i){
        empty.push_back(blank);
        pawns.push_back(pawn);
    }
    std::unordered_map< pieceType, int > map;
    takenPieces.push_back(map);
    takenPieces.push_back(map);

    board.push_back(row);
    board.push_back(pawns);
    for(int i = 0; i < 4; i ++){
        board.push_back(empty);
    }
    for(int i = 0; i < 8; ++i){
        pawns[i].color = Black;
        row[i].color = Black;
    }
    board.push_back(pawns);
    board.push_back(row);
    
    run_game();
}
