// Author: Jakob Balkovec
// Assigment Type: project
// Assigment number: 1
// game of tic-tac-toe in C++

#include <iostream>
#include <string>

int const         COLSIZE = 3;
int const         ROWSIZE = 3;

std::string const SPACE5  = "     ";
std::string const SPACE4  = "    ";
std::string const SPACE3  = "   ";
std::string const SPACE2  = "  ";

std::string const LABEL1  = "[1]";
std::string const LABEL2  = "[2]";
std::string const LABEL3  = "[3]";

std::string const HORLINE = "---+---+---";

char const        SPACE1  = ' ';

char const        SYMBOLX = 'X';
char const        SYMBOLO = 'O';

char const        LINE    = '|';
char const        YES     = 'Y';

// PRE:  NONE
// POST: NONE
// DESC: prints a welcome message

void welcome() {
    std::cout << "Welcome to the game of TIC-TAC-TOE!\n";
    std::cout << "Press enter to display the board\n\n";
    std::cin.ignore();
}

// PRE:  NONE
// POST: NONE
// DESC: prints a goodbye message

void goodbye() {
    std::cout << "\nOk, Goodbye and thank you for playing!\n";
    std::cin.ignore();
}

// PRE:  board has to exist
// POST: prints an empty board
// DESC: prints an empty board with numbered rows and cols

void print_board(char board[ROWSIZE][COLSIZE]) {

    std::cout << SPACE5 << LABEL1 << SPACE1 << LABEL2 << SPACE1 << LABEL3 << std::endl; // probs shouldnt hardcode
    std::cout << std::endl;
    for (int i = 0; i < COLSIZE; i++) {
        std::cout << "[" << i + 1 << "]" << SPACE2; // numbers
        for (int j = 0; j < COLSIZE; j++) {         // only exectues twice for vertical lines
            std::cout << SPACE1 << board[i][j];
            if (j < COLSIZE - 1) {
                std::cout << SPACE1 << LINE;
            }
        }
        std::cout << std::endl;
        if (i < COLSIZE - 1) {
            std::cout << SPACE5 << HORLINE << std::endl;
        }
    }
    std::cout << "\n";
}

// PRE:  board has to exist
// POST: returns a board filled with spaces
// DESC: using nested for-loops the function fills the board with spaces, and it updates the board in the main with
// symbols

void fill_board(char board[ROWSIZE][COLSIZE]) {
    for (int i = 0; i < ROWSIZE; i++) {
        for (int k = 0; k < COLSIZE; k++) {
            board[i][k] = ' '; // default for empty board
        }
    }
}

// PRE: row and col have to exist in the scope
// POST: stores 2 integers row and col
// DESC: prompts the user to enter 2 intigers (row & col)
//       both passed as references, used as coordinates to update the board

void pick_spot(int &row, int &col) {

    std::cout << std::endl;
    std::cout << "Row [1-3]:" << SPACE1;
    std::cin >> row;
    while (row > ROWSIZE || row <= 0) {
        std::cout << "\nInvalid entry!\n";
        std::cout << "Re-enter Row [1-3]:" << SPACE1;
        std::cin >> row;
    }
    std::cout << "Col [1-3]:" << SPACE1;
    std::cin >> col;
    std::cout << "\n";

    while (col > COLSIZE || col <= 0) {
        std::cout << "\nInvalid entry!\n";
        std::cout << "Re-enter Col [1-3]:" << SPACE1;
        std::cin >> row;
        std::cout << "\n";
    }
}

// PRE:  board has to exist and cant be empty
// POST: returns a boolean if someone won the game (checks for patterns)
// DESC: the fucntion takes in the 2D array and checks for "winning" patterns in TIC-TAC-TOE
//       if there is a pettern with X or O on the board it returns true else it return false

bool check_win(char board[ROWSIZE][COLSIZE]) {

    // horizontal
    if (board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][0] != SPACE1) {
        return true;
    } else if (board[1][0] == board[1][1] && board[1][1] == board[1][2] && board[1][0] != SPACE1) {
        return true;
    } else if (board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] != SPACE1) {
        return true;
        // horizontal

        // vertical
    } else if (board[0][0] == board[1][0] && board[1][0] == board[2][0] && board[0][0] != SPACE1) {
        return true;
    } else if (board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[0][1] != SPACE1) {
        return true;
    } else if (board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2] != SPACE1) {
        return true;
        // vertical

        // diagonaly
    } else if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] != SPACE1) {
        return true;
    } else if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] != SPACE1) {
        return true;
        // diagonaly

        // default
    } else {
        return false; // false if there is no winning patern
    }
    // default
}

// PRE:  board has to exist
// POST: places a symbol in the desired spot
// DESC: the fucntion calls pick_spot and checks if the spot (coordianates) have already been occupied
//       if the spot has not been occupied it places a symbol (X, O) on the board[row-1][col-1]

void take_turn(char symbol, char board[ROWSIZE][COLSIZE]) {

    int row;
    int col;

    pick_spot(row, col);

    while (board[row - 1][col - 1] != ' ') { // cuz the labels are from 1 to 3
        std::cout << "Space is already occupied, select another one!\n";
        pick_spot(row, col);
    }

    board[row - 1][col - 1] = symbol; // cuz the labels are from 1 to 3
}

// PRE:  board has to exist
// POST: retrurns a boolean whether the board is full or not
// DESC: the function takes in a 2D array and checks if all the spaces have been filled

bool board_full(char board[ROWSIZE][COLSIZE]) {
    for (int i = 0; i < ROWSIZE; i++) {
        for (int k = 0; k < COLSIZE; k++) {
            if (board[i][k] == SPACE1) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Main function of the TTT program
 *
 * @pre None
 *
 * @post The program will display a welcome message, play a game of Tic-Tac-Toe,
 * keep track of wins for each player, ask the user if they want to play again,
 * display a goodbye message
 *
 * @param None
 * @return None/or int because its int main
 */

int main() {
    std::cout << "\n\n";

    char         choice;
    char         board[ROWSIZE][COLSIZE];
    unsigned int x_win;
    unsigned int o_win;
    welcome();

    do {
        fill_board(board);
        print_board(board);

        bool p1_turn = true;
        bool done    = check_win(board);

        while (done == false) {
            if (p1_turn) {
                std::cout << "\nPlayer [1]'s turn\n";
                take_turn(SYMBOLX, board); // const for symbol
            } else {
                std::cout << "\nPlayer [2]'s turn\n";
                take_turn(SYMBOLO, board); // const for symbol
            }

            print_board(board);
            done = check_win(board);

            if (p1_turn == true && done == true) {
                std::cout << "Winner: Player " << SYMBOLX << std::endl;
                std::cout << "Loser: Player " << SYMBOLO << std::endl;
                x_win++;
            } else if (p1_turn == false && done == true) {
                std::cout << "Winner: Player " << SYMBOLO << std::endl;
                std::cout << "Loser: Player " << SYMBOLX << std::endl;
                o_win++;
            } else if (board_full(board) == true && done == false) {
                std::cout << "It's a draw!\n";
                done = true;
                // x_win = x_win;
                // o_win = o_win;
            } else {
                // got noting to put in here
            }
            p1_turn = !p1_turn; // to switch players
        }

        // gramaticly correct
        if (x_win != 1) {
            std::cout << "\n\nPlayer [" << SYMBOLX << "] won " << x_win << " times\n";
        } else if (x_win == 1) {
            std::cout << "\n\nPlayer [" << SYMBOLX << "] won " << x_win << " time\n";
        }

        if (o_win != 1) {
            std::cout << "Player [" << SYMBOLO << "] won " << o_win << " times\n";
        } else if (o_win == 1) {
            std::cout << "Player [" << SYMBOLO << "] won " << o_win << " time\n";
        }
        // gramaticly correct

        std::cout << std::endl;
        std::cout << "Wish to play again? (Y/N): ";
        std::cin >> choice;
    } while (choice == YES);
    if (choice != YES) {
        goodbye();
    }

    std::cout << "\n\n";
    return 0;
}
