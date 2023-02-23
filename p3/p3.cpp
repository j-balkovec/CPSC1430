/** DOCUMENTATION
* @file p3.cpp
* @author Jakob Balkovec
* @typedef Project 3
* @brief Driver code for my Project 3 ("TIC-TAC_TOE with classes")
*/

#include <iostream>
#include "board.h"
#include "player.h"


char const YES = 'Y';

/** DOCUMENTATION
 * @brief Displays a welcome message to the player
 */
void welcome() {
    std::cout << "Welcome to the game of TIC-TAC-TOE!\n";
    std::cout << "Press [Enter] to continue\n\n";
    std::cin.ignore();
}

/** DOCUMENTATION
 * @brief Displays a goodbye message to the player
 */
void goodbye() {
    std::cout << "\nOk, Goodbye and thank you for playing!\n";
    std::cin.ignore();
}

/**
 * @brief The main function of the Tic-Tac-Toe game.
 *
 * This function initializes the players, gets the size of the board from the user, 
 * creates the board, displays the board, takes input from the players, 
 * updates the board, checks the winner, announces the winner, displays the scores, 
 * and finally, asks the user if they want to play again.
 * If the user does not want to play again, 
 * the function calls the `goodbye` function.
 */
int main() {
    std::cout << std::endl << std::endl;
    welcome();

  // initialize the players
  Player player_1('X');
  Player player_2('O');
  int board_size;
  int row = 0;
  int col = 0;
  char choice;
  bool can_place_1;
  bool can_place_2;
  
  char player_1_symbol = player_1.get_symbol();
  char player_2_symbol = player_2.get_symbol();
  
  std::cout << "\n\nEnter the size of the board: ";
  std::cin >> board_size;
  
  // create the board
  Board game_board(board_size);
  do{
    while (!game_board.is_full() && !game_board.is_winner(player_1) 
           && !game_board.is_winner(player_2)) {
      
      game_board.display(board_size); //displays empty board
      game_board.get_move_input(player_1);
      
        can_place_1 = game_board.occupied(row-1, col-1);
        while(can_place_1 == true) {
            game_board.get_move_input(player_2); 
        }
      game_board.update(row-1, col-1, player_1_symbol); //-1 cuz we index from 0
      
      if (!game_board.is_full() && !game_board.is_winner(player_1) 
          && !game_board.is_winner(player_2)) {
        
        game_board.display(board_size);
        game_board.get_move_input(player_2);

        can_place_2 = game_board.occupied(row-1, col-1);
        while(can_place_2 == true) {
            game_board.get_move_input(player_2); 
        }

        game_board.update(row-1, col-1, player_2_symbol); //-1 cuz we index from 0
      }
    }
    
    
    // display the final board
    game_board.display(board_size);
    
    // announce the winner
    if (game_board.is_winner(player_1)) {
      std::cout << "Player [" << player_1.get_symbol() << "] wins!" << std::endl;
      player_1.award_point();
      
    } else if (game_board.is_winner(player_2)) {
      std::cout << "Player [" << player_2.get_symbol() << "] wins!" << std::endl;
      player_2.award_point();
      
    } else {
      std::cout << "It's a draw!" << std::endl;
    }
    
    // display the scores
    std::cout << "Player [" << player_1.get_symbol() << "]: " << player_1.get_points() << " points" << std::endl;
    std::cout << "Player [" << player_2.get_symbol() << "]: " << player_2.get_points() << " points" << std::endl;
    

            std::cout << std::endl;
        std::cout << "Wish to play again? (Y/N): ";
        std::cin >> choice;
    } while (choice == YES);
    if (choice != YES) {
        goodbye();
    }
    std::cout << std::endl << std::endl;
    return 0;
}
