/** DOCUMENTATION
* @file player.cpp
* @author Jakob Balkovec
* @brief source file for my player in my TIC-TAC-TOE [p3]
*/

#include "player.h"
#include "board.h"
#include <iostream>


/** DODCUMENTATION
* @brief Constructor for class Player
* This constructor initializes the symbol and points
* of a player.
* @param symbol The symbol representing a player's moves
* on the Tic-Tac-Toe board.
*/
Player::Player(char symbol) : symbol(symbol), points(0) {}

/** DOCUMENTATION
* @brief Getter for the player's symbol
* This function returns the symbol representing a player's moves
* on the Tic-Tac-Toe board.
* @return The symbol representing the player.
*/
char Player::get_symbol() {
return symbol;
}

/**
* @brief Increments the player's points
* This function increments the points of a player by 1.
*/
void Player::award_point() {
this->points++;
}

/** DOCUMENTATION
* @brief Getter for the player's points
* This function returns the number of points a player has scored.
* @return The number of points the player has scored.
*/
int Player::get_points() {
return points;
}

