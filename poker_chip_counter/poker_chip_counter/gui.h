#ifndef GUI_H
#define GUI_H

#include "globals.h"

// prints the board from the perspective of turn
void print_board();
// prints a specific square on the board
void print_space(pieceType type);
// prints the pieces taken by the player
void pieces_taken(int player);

void cout_board(int turn);


#endif
