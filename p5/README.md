# p5.cpp ReadMe

This program is a C++ implementation of an RPN (Reverse Polish Notation) calculator. The program takes a string of space-separated tokens and evaluates them, performing arithmetic operations on numbers using stacks and queues.

## File Structure

> p5.cpp: the main driver program.
> stack.h: header file for the Stack class.
> queue.h: header file for the Queue class.

## Usage

Compile the program using a C++ compiler, for example, g++ -o p5 p5.cpp stack.h queue.h.
Run the compiled program by executing ./p5.
Enter the RPN expression as space-separated tokens.
Dependencies

## This program requires the following dependencies:

stack.h: header file for the Stack class.
queue.h: header file for the Queue class.
stack.cpp: implementation file for the Stack class.
queue.cpp: implementation file for the Queue class.

### Functions in p5.cpp

OpId token_to_operation_id(std::string token): maps token strings to their corresponding operation IDs, if possible.
void welcome(): prints a welcome message and displays the available commands.
void goodbye(): prints a goodbye message.
bool is_numeric(std::string token): returns true if and only if the input string represents a non-empty string consisting only of roman numerals.
void evaluate(Stack &active_stack, Queue &active_queue, Stack &save_stack, Queue &save_queue, std::string token): evaluates the tokens (numbers and arithmetic operations) in the input string and performs the corresponding operations. It takes as arguments four objects: active_stack, active_queue, save_stack, and save_queue. The function modifies the stacks or queues with the corresponding operations listed in the OpId enum.

### Functions in Stack.cpp & Queue.cpp
The functions mostly incluide basic functions associated with stacks and queues such as: push(), pop(), enqueue() and dequeue().
I also added a size() and is_empty() function