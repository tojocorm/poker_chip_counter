#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <cmath>
#include <assert.h>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::min;
enum pieceType {Pawn = 0, Bishop = 1, Knight = 2, Rook = 3, Queen = 4, King = 5, Blank = 6};

class piece
{
    public:
    piece(int Color, pieceType Type){
        type = Type;
        color = Color;
    };
    pieceType type;
    int color;
};

// for indexing into data structures
const int White = 0;
const int Black = 1;
// length 2, taken[White] is the map of pieces to quantity that white has taken from Black
extern std::vector< std::unordered_map< pieceType, int > > takenPieces;
// this is stored from whites perspective -- this means that a1 is indexed at [1][1]
extern std::vector< std::vector< piece > > board;
// whose turn is it
extern int turn;
// how many moves
extern int move;
// return string of the piece
std::string get_type(piece type);
// return the points of the vector
int get_points(std::vector< piece > vec);
// cout the space followed by an empty space
void print_space(piece type);
// return the symbol to be printed on the board
char get_board_symbol(piece type);
// check that, given who's turn it is and the move, is it valid
bool valid_move(std::string play, bool check);
// make the move
void make_move(std::string play);
// check if there is a checkmate
int check_checkmate(int turn);
// print the instructions
void print_instructions();
// get the indices in the vector of the moves
std::pair<std::pair<int, int>, std::pair<int, int>> get_move_indices(std::string play);
// add the taken piece to the data stucture
void add_to_taken(piece taken_piece);
// convert letter to an indices
int letter_to_ind(char val);
// convert an int char to ind
int num_to_ind(char val);
// can this piece move like this
bool legal_move(piece *moved_piece, std::pair<std::pair<int, int>, std::pair<int, int>> to_from, bool check);
// find the address of the king !turn (white turn, black king)
std::pair<int, int> get_king_address(int turn);

#endif
