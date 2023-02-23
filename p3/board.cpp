/** DOCUMENTATION
* @file board.cpp
* @author Jakob Balkovec
* @brief source file for my board in my TIC-TAC-TOE [p3]
*/

#include <iostream>
#include <iomanip>
#include "board.h"
#include "player.h"

/** DOCUMENTATION
* @brief Constructor for Board class.
* Initializes the size of the board and creates an 2D array of chars to represent the squares on the board.
* Each square is initialized to a space character (' ').
* @param size The size of the board (e.g. size=3 creates a 3x3 board).
* @pre The input size must be a positive integer.
* @post A new Board object will be created with 
* the specified size and all squares initialized to ' '.
*/
Board::Board(int size){
  this->size = size;
  squares = new char*[size];
  for (int i = 0; i < size; i++)
    squares[i] = new char[size];
  
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      squares[i][j] = ' '; //fill em so it doesnt cause an error
}

/** DOCUMENTATION
 *  @brief The destructor for the Board class
 *  This destructor is responsible for freeing
 *  the memory that was dynamically allocated by the class.
 *  @pre The Board object must have been initialized.
 *  @post All dynamically allocated memory associated with 
 *  the Board object will be freed.
 */
Board::~Board(){
  for (int i = 0; i < size; i++) {
    delete[] squares[i];
  }
  delete[] squares;
}

/** DOCUMENTATION
 *  @brief Displays the current state of the Board
 *  This function outputs the current state of the board,
 *  displaying the values of each square in a formatted manner.
 *  @param size The size of the board (number of squares on each side)
 *  @pre The input size must match the size of the current Board object.
 *  @post The current state of the Board will be displayed on the console.
 */
void Board::display(int size){
    std::cout << "    ";
    for (int i = 1; i <= size; i++) {
        std::cout <<std::setw(2) << "[" << i << "]";
    }
    std::cout << std::endl << std::endl;

    for (int i = 0; i < size; i++) {
        std::cout << ' ' << "[" <<i + 1 << "]";
        for (int j = 0; j < size; j++) {
            std::cout <<  std::setw(3) << squares[i][j] << ' ';
        }
        std::cout << std::endl << std::endl;
    }
}

/** DOCUMENTATION
 *  @brief Determines if the Board is full
 *  This function checks if all squares in the Board are filled.
 *  @return True if all squares are filled, false otherwise.
 *  @pre None.
 *  @post Returns true if board is full and false if board is empty.
 */
bool Board::is_full(){
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (squares[i][j] == ' ')
          return false;
      }
    }
    return true;
}

/** DOCUMENTATION
 *  @brief Determines if a player has won
 *  This function checks if the specified player has won the 
 *  game by having a full row, column, or diagonal of their symbol.
 *  @param player The player to check for a win
 *  @return True if the player has won, false otherwise.
 *  @pre The input player must be a valid player in the game.
 *  @post The win status of the specified player will be determined.
 */
bool Board::is_winner(Player player) {
  // Check rows
  for (int i = 0; i < size; i++) {
    int j;
    for (j = 0; j < size; j++) {
      if (squares[i][j] != player.get_symbol()) {
        break;
      }
    }
    if (j == size) {
      return true;
    }
  }

  // Check columns
  for (int i = 0; i < size; i++) {
    int j;
    for (j = 0; j < size; j++) {
      if (squares[j][i] != player.get_symbol()) {
        break;
      }
    }
    if (j == size) {
      return true;
    }
  }

  // Check diagonal from top-left to bottom-right
  int i;
  for (i = 0; i < size; i++) {
    if (squares[i][i] != player.get_symbol()) {
      break;
    }
  }
  if (i == size) {
    return true;
  }

  // Check diagonal from top-right to bottom-left
  for (i = 0; i < size; i++) {
    if (squares[i][size - i - 1] != player.get_symbol()) {
      break;
    }
  }
  if (i == size) {
    return true;
  }

  return false;
}

/** DOCUMENTATION
* @brief updates the square on the board with the given symbol
* @param row row number (starts from 1)
* @param col column number (starts from 1)
* @param player_symbol symbol to be updated on the board
*/
void Board::update(int row, int col, char player_symbol)
{
    squares[row-1][col-1] = player_symbol;
}

/** DOCUMENTATION
 * @brief       Asks player to input the row and column for their move
 * @param[in,out] player Reference to the player object to store their move
 * @pre player is initialized
 * @post row and column of player's move are stored in player object
 */
void Board::get_move_input(Player &player) {
  int row, col;
  std::cout << "*** Player [" << player.get_symbol() << "] turn ***\n";
  std::cout << "[ROW]: ";
  std::cin >> row;
  
  //input validation
  while (row > size-1 || row <= 0) {
    std::cout << "\nInvalid entry!\n";
    std::cout << "Re-enter [ROW]: ";
    std::cin >> row;
  }
  std::cout << "[COL]: ";
  std::cin >> col;
  
  while (col > size-1 || col <= 0) {
    std::cout << "\nInvalid entry!\n";
    std::cout << "Re-enter [COL]: ";
    std::cin >> col;
  }
}
/** DOCUMENTATION
* @pre None.
* @post Return true if the square is occupied, false otherwise.
* @param row Row index of the square to be checked.
* @param col Column index of the square to be checked.
* @return True if the square is occupied, false otherwise.
*/
bool Board::occupied(int row, int col) { //should I pass by reference
  bool free_space;

  if(squares[row][col] != ' ') {
    free_space = true;
  }
  else{
    free_space = false;
  }
  return free_space;
}

