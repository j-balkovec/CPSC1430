/** DOCUMENTATION
* @file Player.h
* @author Jakob Balkovec
* @brief Header file for the Player class.
* This file defines the Player class, 
* which represents a player in the Tic-Tac-Toe game.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
  char symbol;
  int points;
  
public:
  Player(char symbol);
  char get_symbol();
  void award_point();
  int get_points();
};
#endif //PLAYER_H
