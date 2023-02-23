/** DOCUMENTATION
 * @file p4.cpp
 * @author Jakob Balkovec
 * @typedef Project 3
 * @brief Driver code for my Project 4 ("To-Do List Editor")
 */

#include <iostream>
#include "list.h"
#include <csignal>
#include <string>

char const QUIT = 'Q';
char const ADD = '+';
char const REMOVE = '-';
char const RAISE = '^';
char const LOWER = 'v';
char const CHECK = '>';
char const UNCHECK = '<';
char const SHOW = '*';

// std::string const QUIT = "Q";
// std::string const ADD = "+";
// std::string const REMOVE = "-";
// std::string const RAISE = "^";
// std::string const LOWER = "v";
// std::string const CHECK = ">";
// std::string const UNCHECK = "<";

/** DOCUMENTATION
 * @brief prints a welcome message and displays the commands
 * @pre None
 * @post displays commands
 * @return None
*/
void welcome() {
  std::cout << "Welcome to the To-Do List Editor!\n\n";
  std::cout << "*** COMMANDS ***\n\n"
            << "[Q] - Quit\n"
            << "[*] - Show To-Do list\n"
            << "[+] - Add -> enter std::string [Entry]\n"
            << "[-] - Remove -> enter std::string [Entry]\n"
            << "[^] - Raise -> enter std::string [Entry]\n"
            << "[v] - Lower -> enter std::string [Entry]\n"
            << "[>] - Check -> enter std::string [Entry]\n"
            << "[<] - Uncheck -> enter std::string [Entry]\n\n";
}

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
 * @brief Displays a goodbye message to the player
 * @pre None
 * @post displays goodbye message
 * @return None
 */
void goodbye() {
  std::cout << "\n\nI hope you completed all your tasks!\n";
  std::cout << "Goodbye!\n";
}

/** DOCUMENTATION
 * @brief: The function check_input() checks if the input command is valid or not.
 * @param command : The command entered by the user.
 * @return :  returns true if the command is valid, else returns false.
 *
 * The function checks if the command entered by the user is present in the array of valid commands.
 * @post: returns true if command is in COMMANDS array else returns false
 */
bool check_input(std::string some_string) { //could make it int and return intigers
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

int main() { //?whats the difference between int main(void) & int main() & int main(int argc, char *argv[])
  std::cout << "\n\n";
  //welcome(); //!add back
  
  TodoList my_list; //create list
  bool is_valid; //input validation
  
  std::signal(SIGABRT, signal_handler);
  
  while (true) {
    std::string string_command = get_input();
    if(string_command.size() == 0){ //if user presses enter
      my_list.show();
      continue;
    }

    is_valid = check_input(string_command);
    char command = string_command[0];

    if(is_valid){
      switch (command) {
      case QUIT: { //?#1
        //goodbye(); //! add back
        std::cout << "\n\n\n";
        abort();
        break;
      }
       //.empty() returns a boolean whether a string is empty or not 
        //? do I need a loop for multiple entries?
      case ADD: { //?#2
        std::string input;
        std::getline(std::cin, input);
        if(input.empty() == true) {
          std::cout << "\nNo entry text provided\n" << std::endl;
          my_list.show();
          break;
        }else{
          if(input.length() == 0){
            my_list.show();
          }else{
            my_list.add_entry(input);
            my_list.show();
          }
        }
        break;
      }
        
      case REMOVE: { //?#3
        std::string input;
        std::getline(std::cin, input);

        if(input.empty() == true){
          std::cout << "\nNo entry text provided\n" << std::endl;
        }else{
          my_list.remove_entry(input);
          my_list.show();  
        }
        break;                  
      }
        
      case RAISE: {
        std::string input;
        std::getline(std::cin, input);

        if(input.empty() == true){
          std::cout << "\nNo entry text provided\n" << std::endl;
        }else{
          my_list.raise(input);
          my_list.show();  
        }
        break;
      }
        
      case LOWER: {
        std::string input;
        std::getline(std::cin, input);

        if(input.empty() == true){
          std::cout << "\nNo entry text provided\n" << std::endl;
        }else{
          my_list.lower(input);
          my_list.show();  
        }
        break;                    
      }
        
      case CHECK: {
        std::string input;
        std::getline(std::cin, input);

        if(input.empty() == true){
          std::cout << "\nNo entry text provided\n" << std::endl;
        }else{
          my_list.check(input);
          my_list.show();  
        }
        break;                    
      }
        
      case UNCHECK: {
        std::string input;
        std::getline(std::cin, input); 

        if(input.empty() == true){
          std::cout << "\nNo entry text provided\n" << std::endl;
        }else{
          my_list.uncheck(input);
          my_list.show();  
        }
        break;                   
      }

      case SHOW: {
        std::cout << "\n\n";
        my_list.show();
        std::cout << "\n\n";
        break;
      }  

      default: {
        std::cout << "Unrecognized command\n" << std::endl; //! should I also show list
        my_list.show();
        break;                                        
      }
      }
    }
  }
      //!my_list.show();
  
  std::cout << "\n\n\n";
  return EXIT_SUCCESS;
}

/** CHECK-LIST 
 * Do I need a clear screen function so the same output isn't printed twice
 * Function decompostion
 * @todo handle invalid command or already existing entry -> another methods that compares links in the list
 *       to the string input
 * @bug doesn't re print the list if [Enter] key is pressed
 * @bug make it so that if there is no string enrty it says no entryu provided
 * @todo add a scan function that itterates through the list and checks if the user input string
 * exists on the list, if not it says something like "DNE"...
 * @bug raise command dumps core
 * @bug raise lowers the task (mega bug)
 * @bug prints unrecognized command twice
 * @bug is entered [+B instead of + B] nothing happens
*/


/** Lab9 UNIT TESTING
 * @test #1 [input_1] PASSED[YES] -> matches [output_1]
 * @test #2 [input_2] PASSED[YES] -> matches [output_2]
 * @test #3 [input_3] PASSED[YES] -> matches [output_3]
 * @test #4 [input_4] PASSED[SOMEHWAT] -> does not match [output_4]
 * 
*/