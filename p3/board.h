/** DOCUMENTATION
* @file Board.h
* @author Jakob Balkovec
* @brief Header file for the Board class.
* This file defines the Board class, 
* which represents a board in the Tic-Tac-Toe game.
*/

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "player.h"

class Board {
private:
  char** squares;
  int size;
  
public:
  Board(int size);
  ~Board();
  void display(int size);
  bool is_full();
  bool is_winner(Player player);
  void update(int row, int col, char player_symbol);
  void get_move_input(Player &player);
  bool occupied(int row, int col);
};

#endif //BOARD_H
