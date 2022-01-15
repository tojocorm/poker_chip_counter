#include "globals.h"

std::string get_type(piece piece){
    switch(piece.type) {
        case Pawn :
            return "Pawn";
        case Bishop :
            return "Bishop";
        case Knight :
            return "Knight";
        case Rook :
            return "Rook";
        case King :
            return "King";
        case Queen :
            return "Queen";
        case Blank :
            return "Blank";
    }
    return "";
}
// return the points of the vector
int get_points(std::vector< piece > vec){
    std::vector<int> vals;
    vals.push_back(1);
    vals.push_back(3);
    vals.push_back(3);
    vals.push_back(5);
    vals.push_back(9);
    vals.push_back(0);

    int sum = 0;
    for(size_t i = 0; i < vec.size(); ++i){
        sum += vals[vec[i].type];
    }
    return sum;
}

char get_board_symbol(piece piece){
    // not sure how to do this but I weant these unicodes
    // https://en.wikipedia.org/wiki/Chess_symbols_in_Unicode
    int color = piece.color;
    if(color == White){
        switch(piece.type) {
            case Pawn :
                return 'P';
            case Bishop :
                return 'B';
            case Knight :
                return 'K';
            case Rook :
                return 'R';
            case King :
                return 'X';
            case Queen :
                return 'Q';
            case Blank :
                return 'o';
        }
    }
    switch(piece.type) {
        case Pawn :
            return 'p';
        case Bishop :
            return 'b';
        case Knight :
            return 'k';
        case Rook :
            return 'r';
        case King :
            return 'x';
        case Queen :
            return 'q';
        case Blank :
            return 'o';
    }
    return '\0';
}

bool valid_move(std::string play, bool check){
    if(play.length() != 5){
        return false;
    }
    if(letter_to_ind(play[0]) > 7 || letter_to_ind(play[0]) < 0){
        return false;
    }
    if(letter_to_ind(play[3]) > 7 || letter_to_ind(play[3]) < 0){
        return false;
    }
    if(num_to_ind(play[1]) > 7 || num_to_ind(play[1]) < 0){
        return false;
    }
    if(num_to_ind(play[4]) > 7 || num_to_ind(play[4]) < 0){
        return false;
    }
    if(play[2] != ' '){
        return false;
    }
    std::pair<std::pair<int, int>, std::pair<int, int>> to_from = get_move_indices(play);
    piece *moved_piece = &board[to_from.first.first][to_from.first.second];
    piece *new_location = &board[to_from.second.first][to_from.second.second];
    if(moved_piece->color != turn){
        return false;
    }
    if(new_location->type != Blank && new_location->color == turn){
        return false;
    }
    if(!legal_move(moved_piece, to_from, check)){
        return false;
    }
    return true;
}

void make_move(std::string play){
    std::pair<std::pair<int, int>, std::pair<int, int>> to_from = get_move_indices(play);
    piece *moved_piece = &board[to_from.first.first][to_from.first.second];
    piece *new_location = &board[to_from.second.first][to_from.second.second];

    piece taken_piece = board[to_from.second.first][to_from.second.second];
    new_location->type = moved_piece->type;
    new_location->color = moved_piece->color;

    moved_piece->type = Blank;
    moved_piece->color = -1;
    
    add_to_taken(taken_piece);

    return;
}
// 0 is neither check nor mate, 1 is check, 2 is mate -- this is for the other side (ie if it is whites turn, we are checking if the black king is checked)
int check_checkmate(int turn){
    std::pair<int, int> king = get_king_address(turn);
    for(int row = 0; row < 8; ++row){
        for(int col = 0; col < 8; ++col){
            
        }
    }
    return 0;
}

void print_instructions(){
    cout << "Let's play chess: White moves first!" << endl;
    cout << "Usage: in order to move a piece from a5 to a6, type command a5 a6." << endl;
    cout << "ie src dst;" << endl << endl;
}
// return row col in the vector
std::pair<std::pair<int, int>, std::pair<int, int>> get_move_indices(std::string play){
    int src_col = letter_to_ind(play[0]);
    int src_row = num_to_ind(play[1]);
    int dst_col = letter_to_ind(play[3]);
    int dst_row = num_to_ind(play[4]);

    std::pair<int, int> src = std::make_pair(src_row, src_col);
    std::pair<int, int> dst = std::make_pair(dst_row, dst_col);
    
    return std::make_pair(src, dst);
}

void add_to_taken(piece taken_piece){
    if(taken_piece.type == Blank){
        return;
    }
    if(takenPieces[turn].find(taken_piece.type) == takenPieces[turn].end()){
        takenPieces[turn][taken_piece.type] = 0;
    }
    takenPieces[turn][taken_piece.type] += 1;
    return;
}
            
int letter_to_ind(char val){
    return val - 'a';
}
int num_to_ind(char val){
    return val - '1';
}

bool legal_move(piece *moved_piece, std::pair<std::pair<int, int>, std::pair<int, int>> to_from, bool check){
    return true;
}

// find the address of the king !turn (white turn, black king) (-1 and -1 if not there)
std::pair<int, int> get_king_address(int turn){
    for(int row = 0; row < 8; ++row){
        for(int col = 0; col < 8; ++col){
            if(board[row][col].type == King && board[row][col].color == !turn){
                return std::make_pair(row, col);
            }
        }
    }
    return std::make_pair(-1, -1);
}
