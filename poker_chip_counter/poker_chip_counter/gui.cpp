#include "gui.h"

// prints the board from the perspective of turn
void print_board(){
    // invert turn -- everything for the current turn should be printed last
    int player = !turn;
    cout << "Game Board, Move " << move << ":" << endl << endl;
    
    pieces_taken(player);
    
    cout_board(turn);
    
    pieces_taken(turn);
}

void print_space(piece piece){
    char symbol = get_board_symbol(piece);
    cout << symbol << " ";
}

void pieces_taken(int player){
    player == White ? cout << "White" : cout << "Black";

    cout << " has taken pieces: ";
    for(auto it = takenPieces[player].begin(); it != takenPieces[player].end(); ++it){
        pieceType type = it->first;
        int num = it->second;
        for(int i = 0; i < num; ++i){
            piece piece(White, type);
            cout << get_type(piece) << ", ";
        }
    }
    cout << endl << endl;
}

void cout_board(int turn){
    if(turn == White){
        cout << "   a b c d e f g h" << endl << endl;
        for(int i = (int)board.size() - 1; i >= 0; --i){
            cout << i + 1 << "  ";
            for(int j = 0; j < 8; ++j){
                print_space(board[i][j]);
            }
            cout << endl;
        }
        cout << endl;
    }
    else{
        cout << "   h g f e d c b a" << endl << endl;
        for(size_t i = 0; i < board.size(); ++i){
            cout << i + 1 << "  ";
            for(int j = 7; j >= 0; --j){
                print_space(board[i][j]);
            }
            cout << endl;
        }
        cout << endl;
    }
}
