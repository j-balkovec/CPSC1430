// Author: Jakob Balkovec
// Assigment Type: project
// Assigment number: 2
/*
 * @brief:
 * The program is an ASCII art editor that allows the user to create and edit grids of characters.
 * It provides various commands such as painting, transforming, loading and saving the grid from/to a file,
 * adding or removing rows and columns.
 * The program will run in an infinite loop, prompting the user for input and performing
 * the corresponding action until the user chooses to quit the program.
 */

#include <cmath>
#include <csignal>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

/// @brief A struct representing a grid of characters
struct TextGrid {
    char       **tiles;
    unsigned int height;
    unsigned int width;
};

char const QUIT      = 'Q';
char const PAINT     = 'P';
char const TRANSFORM = 'T';
char const LOAD      = 'L';
char const SAVE      = 'S';
char const ADDROW    = 'R';
char const REMROW    = 'r';
char const ADDCOL    = 'C';
char const REMCOL    = 'c';
char const COUNT     = 'X';
char const MAKEFILE  = 'M';
char const DIAMOND   = 'D';

/** DOCUMENTATION
 * @brief A signal handler function that exits the program with success status
 * @pre The signal number is valid and the program has received the signal
 * @post The program exits with success status
 * @param signal the signal number
 */
void signal_handler(int signal) {
    exit(EXIT_SUCCESS);
}

/** DOCUMENTATION
 * @brief Prints the list of commands for the ASCII Art Editor and prompts the user for input
 * @pre The program is running and the user is interacting with the program
 * @post The user is aware of the available commands and has been prompted for input
 */
void commands() {
    std::cout << "*** Welcome to the ASCII Art Editor ***\n"
              << "*** The Grid is labeled from [0-7] DOWN and [0-15] ACROSS ***\n\n"
              << "Press [Enter] to continue ";
    std::cin.get();
    std::cout << "\n\n"
              << "Commands\n\n"
              << "Q - Quit\n"
              << "P - Paint [Enter x, y, fill]\n"
              << "T - Transform [Enter target, replacement]\n"
              << "L - Load [Enter filepath]\n"
              << "S - Save [Enter filepath]\n"
              << "R - add Row [Enter fill]\n"
              << "r - remove Row [Enter]\n" // do I need fill
              << "C - add Column [Enter fill\n"
              << "c - remove Column [Enter]\n" // do I need fill
              << "M - Make a new file [Enter rows, cols, filepath]\n"
              << "D - Prints a  diamond [Enter size, fill]\n"
              << "X - show Chars in table [Enter filepath]\n\n";
    std::cout << "Press [Enter] to continue";
    std::cin.get();
    std::cout << "\n\n";
}

/** DOCUMENTATION [TESTING ONLY]
 * @brief This program prompts the user for a file path, opens the file, reads it line by line and counts the number of
 * rows, columns, and characters in the file. If the file cannot be opened, the program exits with an error message. It
 * then outputs the number of rows, columns, the product of rows and columns, and the number of characters in the file.
 *
 * @pre User must provide a valid file path to a readable file.
 * @post The program will output the number of rows, columns, the product of rows and columns, and the number of
 * characters in the file. If the file cannot be opened, the program will exit with an error message.
 */
void count_chars(std::string file_path) {

    std::ifstream file(file_path);
    if (file.bad() == true) {
        std::cout << "\nFile not found\n" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string  line;
    unsigned int rows = 0, columns = 0, characters = 0;

    while (std::getline(file, line)) {
        rows++;
        columns = line.length() > columns ? line.length() : columns;
        characters += line.length();
    }
    std::cout << std::endl << std::endl;

    std::cout << file_path;
    std::cout << "\nROWS: " << rows << std::endl;
    std::cout << "COLS: " << columns << std::endl;
}

/** DOCUMENTATION
 * @brief Writes a diamond shape of the specified `symbol` and `size` to the file `rhianna.txt`.
 *
 * @param size The size of the diamond shape.
 * @param symbol The character to use to draw the diamond.
 *
 * @return A TextGrid structure containing the grid representation of the diamond shape.
 *
 * @pre `size` must be non-negative.
 * @pre `symbol` must be a printable character.
 *
 * @post A file named `rhianna.txt` will be created or overwritten, containing the diamond shape.
 * @post The TextGrid structure returned will contain the grid representation of the diamond shape.
 */
TextGrid print_diamond(unsigned short int size, char symbol) {
    std::ofstream diamond_file;
    diamond_file.open("rhianna.txt");
    TextGrid grid;
    grid.height = 2 * size + 1;
    grid.width  = 2 * size + 1;

    if (diamond_file.is_open()) {
        grid.tiles = new char *[grid.height];
        for (unsigned int i = 0; i < grid.height; ++i) {
            grid.tiles[i] = new char[grid.width];
            for (unsigned int j = 0; j < grid.width; ++j) {
                if (abs(i - size) + abs(j - size) <= size) {
                    grid.tiles[i][j] = symbol;
                } else {
                    grid.tiles[i][j] = ' ';
                }
            }
        }

        for (unsigned int i = 0; i < grid.height; ++i) {
            for (unsigned int j = 0; j < grid.width; ++j) {
                diamond_file << grid.tiles[i][j];
            }
            diamond_file << std::endl;
        }
    } else {
        std::cout << "Error opening file\n\n";
        abort();
    }
    diamond_file.close();
    return grid;
}

/** DOCUMENTATION
 * @brief Creates a file filled with asterisks
 *
 * This function creates a file of given name, and fills it with asterisks in a grid pattern.
 * The grid is represented by the `TextGrid` struct, which is returned by the function.
 * The height and width of the grid are specified by `row` and `col`, respectively.
 *
 * @param row The number of rows in the grid
 * @param col The number of columns in the grid
 * @param file_name The name of the file to create
 * @return A `TextGrid` object representing the filled grid
 */
TextGrid make_file(unsigned int row, unsigned int col, std::string file_name) {

    char const BASIC = '*';
    TextGrid   grid;
    grid.height = row;
    grid.width  = col;
    grid.tiles  = new char *[row];
    for (unsigned int i = 0; i < row; ++i) {
        grid.tiles[i] = new char[col];
        for (unsigned int j = 0; j < col; ++j) {
            grid.tiles[i][j] = BASIC;
        }
    }

    std::ofstream new_file(file_name);

    if (new_file.is_open()) {
        for (unsigned int i = 0; i < row; ++i) {
            for (unsigned int j = 0; j < col; ++j) {
                new_file << grid.tiles[i][j];
            }
            new_file << '\n';
        }
    } else {
        std::cout << "Error\n\n";
        abort();
    }
    new_file.close();
    return grid;
}

/** DOCUMENTATION
 * @brief Loads a grid of characters from a file and returns it as a TextGrid struct
 * @pre The file_path parameter is a valid file path to an existing file containing a grid of characters
 * @post A TextGrid struct is returned, containing the characters from the file in a 2D array,
 *       and the dimensions of the grid are set in the struct's height and width members
 * @param file_path the path to the file containing the grid of characters
 * @return A TextGrid struct containing the characters from the file in a 2D array,
 *         and the dimensions of the grid set in the struct's height and width members
 * @bug does not load file after it has been modified, I think it has to do with size of the array
 */
TextGrid load_grid(std::string file_path) {

    // var declarations
    TextGrid grid;
    grid.height = 0;
    std::string line;
    // var declarations

    // file opening
    std::ifstream file;
    file.open(file_path);
    // file opening

    if (file.fail()) {
        std::cout << "\nFile can't be read or file can't be found\n\n";
        abort();
    } else {
        while (std::getline(file, line)) { // dynamic adaptation to any file
            grid.height++;
            grid.width = line.size(); // i dont like this
        }

        file.clear();                 // clearing the error flags
        file.seekg(0, std::ios::beg); // moving the get pointer to the beging

        grid.tiles = new char *[grid.height];

        for (unsigned int i = 0; i < grid.height; i++) {
            std::getline(file, line);             // reading data from the file
            grid.tiles[i] = new char[grid.width]; // allocating memory
            for (unsigned int j = 0; j < grid.width; j++) {
                grid.tiles[i][j] = line[j];
            }
        }
    }
    file.close(); // closing the file
    return grid;
}

/** DOCUMENTATION
 * @brief saves a grid of characters to a file from a TextGrid struct
 * @pre The grid parameter is a valid TextGrid struct containing a 2D array of characters
 *      and the file_path parameter is a valid file path for the file to be written to
 * @post The characters from the TextGrid struct's 2D array are written to the specified file
 * @param grid a valid TextGrid struct containing a 2D array of characters
 * @param file_path a valid file path for the file to be written to
 * @bug does not work in combination with load file [L]
 */
void save_grid(TextGrid &grid, std::string file_path) {
    std::ofstream file(file_path); // writing to files

    for (unsigned int i = 0; i < grid.height; i++) {
        for (unsigned int j = 0; j < grid.width; j++) {
            file << grid.tiles[i][j]; // writing the array to a file
        }
        file << std::endl;
    }
    file.close(); // closing the file
}

/** DOCUMENTATION
 * @brief Paints a specific tile in the grid with a specified character
 * @pre The x and y parameters are valid indices within the dimensions of the TextGrid struct's
 *      2D array and the grid parameter is a valid TextGrid struct
 * @post The tile at the specified x and y indices in the TextGrid struct's 2D array
 *       is painted with the specified fill character
 * @param grid a valid TextGrid struct containing a 2D array of characters
 * @param x the x coordinate of the tile to be painted
 * @param y the y coordinate of the tile to be painted
 * @param fill the character to be used for painting the tile
 */
void paint(TextGrid &grid, unsigned int x, unsigned int y, char fill) {
    if (x < grid.width && y < grid.height) {
        grid.tiles[y][x] = fill; // changing a symbol on the grid
    }
}

/** DOCUMENTATION
 * @brief Replaces all occurrences of a specific character in the grid with another character
 * @pre The grid parameter is a valid TextGrid struct containing a 2D array of characters
 * @post All occurrences of the target character in the TextGrid struct's 2D array
 *       are replaced with the replacement character
 * @param grid a valid TextGrid struct containing a 2D array of characters
 * @param target the character to be replaced
 * @param repl the character to replace the target character with
 */
void transform(TextGrid &grid, char target, char repl) {
    for (unsigned int i = 0; i < grid.height; i++) {
        for (unsigned int j = 0; j < grid.width; j++) {
            if (grid.tiles[i][j] == target) {
                grid.tiles[i][j] = repl; // replaces char
            }
        }
    }
}

/** DOCUMENTATION
 * @brief Adds a new row to the grid filled with a specified character
 * @pre The grid parameter is a valid TextGrid struct containing a 2D array of characters
 * @post A new row is added to the TextGrid struct's 2D array, filled with the specified fill character,
 *       and the height of the grid is incremented by 1
 * @param grid a valid TextGrid struct containing a 2D array of characters
 * @param fill the character to fill the new row with
 */
void add_row(TextGrid &grid, char fill) {

    // allocating memory
    char **new_tiles = new char *[grid.height + 1];
    // allocating memory

    for (unsigned int i = 0; i < grid.height; i++) {
        new_tiles[i] = grid.tiles[i];
    }
    new_tiles[grid.height] = new char[grid.width];
    for (unsigned int j = 0; j < grid.width; j++) {
        new_tiles[grid.height][j] = fill; // adds row of new chars
    }
    grid.height++; //+1 height cuz we add row

    // deallocating memory fro the whole array
    delete[] grid.tiles;
    // deallocating memory for the whole array

    grid.tiles = new_tiles;
}

/** DOCUMENTATION
 * @brief Removes the last row of the grid
 * @pre The grid parameter is a valid TextGrid struct containing a 2D array of characters,
 *      and grid height should be greater than 0
 * @post The last row of the TextGrid struct's 2D array is removed and the height of the grid is decremented by 1
 * @param grid a valid TextGrid struct containing a 2D array of characters
 */
void remove_row(TextGrid &grid) {
    if (grid.height > 0) {
        if (grid.height == 1) {
            std::cout << "\nThere is no Columns left that you can remove!\n";
            abort(); // probs shouldn't
        }

        // allocating memory
        char **new_tiles = new char *[grid.height - 1];
        // allocating memory

        for (unsigned int i = 0; i < grid.height - 1; i++) {
            new_tiles[i] = new char[grid.width]; // alloc
            for (unsigned int j = 0; j < grid.width; j++) {
                new_tiles[i][j] = grid.tiles[i][j];
            }
        }
        grid.height--; //-1 cuz remove one row
        for (unsigned int i = 0; i < grid.height; i++) {

            // deallocating memory top part
            delete[] grid.tiles[i];
            // deallocating memory
        }

        // deallocating memory for the rest
        delete[] grid.tiles;
        // deallocating memory for the rest

        grid.tiles = new_tiles;
    }
}

/** DOCUMENTATION
 * @brief Adds a new column to the grid filled with a specified character
 * @pre The grid parameter is a valid TextGrid struct containing a 2D array of characters
 * @post A new column is added to the TextGrid struct's 2D array,
 *       filled with the specified fill character, and the width of the grid is incremented by 1
 * @param grid a valid TextGrid struct containing a 2D array of characters
 * @param fill the character to fill the new column with
 */
void add_column(TextGrid &grid, char fill) {
    for (unsigned int i = 0; i < grid.height; i++) {

        // allocating memory
        char *new_row = new char[grid.width + 1]; // alloc
        // allocating memory

        for (unsigned int j = 0; j < grid.width; j++) {
            new_row[j] = grid.tiles[i][j]; // adds new row into the 2D array
        }
        new_row[grid.width] = fill;
        // deallocating memory for the whole array
        delete[] grid.tiles[i];
        // deallocating memory fpr the whole array

        grid.tiles[i] = new_row; // new col of chars
    }
    grid.width++; //+1 width because we add col
}

/** DOCUMENTATION
 * @brief Removes the last column of the grid
 * @pre The grid parameter is a valid TextGrid struct containing a 2D array of characters,
 *      and grid width should be greater than 0
 * @post The last column of the TextGrid struct's 2D array is removed and the width of the grid is decremented by 1
 * @param grid a valid TextGrid struct containing a 2D array of characters
 */
void remove_column(TextGrid &grid) {
    if (grid.width > 0) {
        if (grid.width == 1) {
            std::cout << "\nThere is no Columns left that you can remove!\n";
            abort(); // abortion [probs shouldn't abort here]
        }
        for (unsigned int i = 0; i < grid.height; i++) {

            // allocating memory
            char *new_row = new char[grid.width - 1];
            // allocating memory

            for (unsigned int j = 0; j < grid.width - 1; j++) {
                new_row[j] = grid.tiles[i][j]; // removes row
            }
            // allocating memory for the whole array
            delete[] grid.tiles[i];
            // allocating memory for the whole array

            grid.tiles[i] = new_row; // new row of chars
        }
        grid.width--; // -1 cuz we remove one col
    }
}

/** DOCUMENTATION
 * @brief Prints the contents of the grid to the console
 * @pre The grid parameter is a valid TextGrid struct containing a 2D array of characters
 * @post The contents of the TextGrid struct's 2D array are printed to the console, with each row on a new line
 * @param grid a valid TextGrid struct containing a 2D array of characters
 */
void show(TextGrid &grid) { // this is so fucking inneficitent by big O
    for (unsigned int i = 0; i < grid.height; i++) {
        for (unsigned int j = 0; j < grid.width; j++) {
            std::cout << grid.tiles[i][j]; // prints grid
        }
        std::cout << std::endl;
    }
}

/** DOCUMENTATION
 * @brief: The function check_input() checks if the input command is valid or not.
 * @param command : The command entered by the user.
 * @return :  returns true if the command is valid, else returns false.
 *
 * The function checks if the command entered by the user is present in the array of valid commands.
 * @post: returns true if command is in COMMANDS array else returns false
 */
bool check_input(std::string some_string) {
    if (some_string.length() > 1) {
        return false;
    }
    return true;
}

/** DOCUMENTATION
 * @brief: The function get_input() is used to obtain a single character input from the user.
 * @pre: None
 * @post: The function get_input() returns a single character input obtained from the user via the getchar() function.
 */
std::string get_input() {
    std::string command;
    std::cin >> command;
    return command;
}

/** DOCUMENTATION
 * @brief main function sets up the initial grid, displays the commands
 *        and enters an infinite loop where the user can input commands to manipulate the grid.
 * @pre The program has started and the TextGrid struct and related functions have been defined.
 * @post The program has ended and the grid has been manipulated according to the user's commands.
 * @return EXIT_SUCESS which is the same as 0 if the execution is sucessful.
 */
int main(int argc, char *argv[]) { // can remove stuff inside

    std::cout << std::endl << std::endl;

    std::signal(SIGABRT, signal_handler); // for some reason when I use exit() or return the program wouldn't exit
    // it would only exit the function

    // declarations
    TextGrid grid;
    TextGrid new_grid;

    grid.height = 8;
    grid.width  = 16;
    grid.tiles  = new char *[grid.height];
    bool is_valid;
    // declarations

    commands(); // displays the commands

    for (unsigned int i = 0; i < grid.height; i++) {
        grid.tiles[i] = new char[grid.width];
        for (unsigned int j = 0; j < grid.width; j++) {
            grid.tiles[i][j] = '`';
        }
    }
    show(grid); // prints grid first

    while (true) {
        std::string string_command = get_input();
        is_valid                   = check_input(string_command);
        char command               = string_command[0];

        if (is_valid == false) {
            std::cout << "\n*** Only char commands allowed! ***\n" << std::endl;
        } else {
            switch (command) {
            case QUIT:
                abort(); // or exit(1) or exit (EXIT_SUCESS) or return 0;
                break;
            case PAINT: {
                unsigned int x;
                unsigned int y;
                char         fill;
                std::cin >> x >> y >> fill; // separated by a whitespace char
                paint(grid, x, y, fill);
                show(grid);
                break;
            }
            case TRANSFORM: {
                char target;
                char repl;
                std::cin >> target >> repl;
                transform(grid, target, repl);
                show(grid);
                break;
            }
            case LOAD: {
                std::string filepath;
                std::cin >> filepath; // assuming no whitespaces are in the filepath
                grid = load_grid(filepath);
                show(grid);
                break;
            }
            case SAVE: {
                std::string filepath;
                std::cin >> filepath; // assuming no whitespaces are in the filepath
                save_grid(grid, filepath);
                break;
            }
            case ADDROW: {
                char fill;
                std::cin >> fill;
                add_row(grid, fill);
                show(grid);
                break;
            }
            case REMROW: {
                remove_row(grid);
                show(grid);
                break;
            }
            case ADDCOL: {
                char fill;
                std::cin >> fill;
                add_column(grid, fill);
                show(grid);
                break;
            }
            case REMCOL: {
                remove_column(grid);
                show(grid);
                break;
            }
            case MAKEFILE: {
                unsigned int rows;
                unsigned int cols;
                std::string  file_name;
                std::cin >> rows >> cols >> file_name;
                new_grid = make_file(rows, cols, file_name);
                show(new_grid);
                break;
            }
            case DIAMOND: {
                unsigned short int size;
                char               fill;
                std::cin >> size >> fill;
                grid = print_diamond(size, fill);
                show(grid);
                std::cout << "\nShine bright like a diamond! - Rhianna\n";
                break;
            }
            case COUNT: {
                std::string file_path;
                std::cin >> file_path;
                count_chars(file_path);
                break;
            }
            default:
                std::cout << "\n*** Invalid command! ***\n" << std::endl;
                break;
            }
        }
    }

    for (unsigned int i = 0; i < grid.height; i++) {
        delete[] grid.tiles[i];
    }
    delete[] grid.tiles;
    std::cout << std::endl << std::endl;

    return EXIT_SUCCESS; // same as return 0;
}
