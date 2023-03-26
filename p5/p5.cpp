// PATH: /home/st/jbalkovec/1430CPSC/Projects/p5/p5.cpp
/** DOCUMENTATION
 * @file p5.cpp
 * @author Jakob Balkovec
 * @typedef Project 5
 * @brief Driver code for my Project 5 ("RPN Calculator")
 */

#include "queue.h"
#include "stack.h"
#include <iostream>

/** @note
 * OpId is an enum (short for enumeration). Enums assign names
 * to integer values, allowing us to map things to a set of
 * integer identifiers
 */
enum OpId {
    BAD  = 0, // Does not correspond to any operation
    ADD  = 1,
    SUB  = 2,
    MUL  = 3,
    DIV  = 4,
    TOP  = 5,
    POP  = 6,
    DUP  = 7,
    COND = 8,
    ENQ  = 9,
    DEQ  = 10,
    SAVE = 11,
    LOAD = 12,
    END  = 1024
};

/** @note
 * To represent the mapping between operations and their string
 * representation, we will make this helper struct to act as an
 * entry in our list of mappings
 */
struct Operation {
    std::string name;
    OpId        id;
};

/** @note
 * The mapping of operation string representations to their
 * integer id
 */
Operation const OPERATIONS[] = {
    {"add", ADD},
    {"sub", SUB},
    {"mul", MUL},
    {"div", DIV},
    {"top", TOP},
    {"pop", POP},
    {"dup", DUP},
    {"cond", COND},
    {"enq", ENQ},
    {"deq", DEQ},
    {"save", SAVE},
    {"load", LOAD},
    {"end", END},
};

int const OPERATION_COUNT = sizeof(OPERATIONS) / sizeof(Operation);

/** @name token_to_operation_id(std::string token)
 * @brief Maps token strings to ther corresponding operation IDs, if
 * possible.
 * @pre None
 * @post If the input token corresponds to a valid string representation
 * for an operation, the corresponding OpId value is returned. If
 * no such matching exists, OpId::BAD is returned instead
 * @param std::string token
 */
OpId token_to_operation_id(std::string token) {
    for (int i = 0; i < OPERATION_COUNT; i++) {
        if (OPERATIONS[i].name == token) {
            return OPERATIONS[i].id;
        }
    }
    return OpId::BAD;
}

/** @name welcome()
 * @brief prints a welcome message and displays the commands
 * @pre None
 * @post displays commands
 * @return None
 */
void welcome() {
    std::cout << "RPN [Reverse Polish Notation] Calculator!\n\n";
    std::cout << "*** COMMANDS ***\n\n"
              << "[add]  -> [Add A + B]\n"
              << "[sub]  -> [Subtract A - B]\n"
              << "[mul]  -> [Multiply A * B]\n"
              << "[div]  -> [Divide A / B] \n"
              << "[top]  -> [Prints]\n"
              << "[pop]  -> [Pop] \n"
              << "[dup]  -> [Duplicate]\n"
              << "[cond] -> [Condition] \n"
              << "[enq]  -> [Enqueue] \n"
              << "[deq]  -> [Dequeue]\n"
              << "[save] -> [Overwrite the save stack/queue]\n"
              << "[load] -> [Overwrite the active stack/queue]\n"
              << "[end]  -> [Quit]\n\n";
}

/** @name goodbye()
 * @brief Prints goodbye message
 */
void goodbye() {
    std::cout << std::endl << "Goodbye!" << std::endl << std::endl;
}

/** @name is_numeric(std::string token)
 * @brief Returns true if and only if the input string represents a non-empty
 * string consisting only of roman numerals.
 * @pre None
 * @post None, aside from description
 */
bool is_numeric(std::string token) {
    int size = token.size();
    if (size == 0) {
        return false;
    }
    for (int i = 0; i < size; i++) {
        if (token[i] < '0' || token[i] > '9') {
            return false;
        }
    }
    return true;
}

/** @name evaluate(Stack &active_stack, Queue &active_queue, Stack &save_stack, Queue &save_queue, std::string token)
 * @brief This function evaluates the tokens (numbers and arithmetic operations) in the input string and performs the
 * corresponding operations. It takes as arguments four objects
 * @param active_sack
 * @param active_queue
 * @param save_stack
 * @param save_queue
 * @param token
 * @return None
 * @pre all of the objects and the strign which are passed as parameters have to exist
 * @post makes changes on the stack or queue with the corresponding operation listed in the enum
 */
void evaluate(Stack &active_stack, Queue &active_queue, Stack &save_stack, Queue &save_queue, std::string token) {

    /// @note std::cerr is the standard way to report errors rather than cout

    if (is_numeric(token)) {
        int value = stoi(token);
        active_stack.push(value); // pushes value without a token
    } else {
        // Handle operations

        switch (token_to_operation_id(token)) {

            /** @brief
             * Pop the top-most value of the stack, B
             * and the next-top-most value of the stack A,
             * and push the value A+B onto the stack.
             */
        case OpId::ADD: { //[W]
            int size = active_stack.get_size();
            if (size < 2) {
                std::cerr << "Less than 2 elements for add operation\n";
            } else {
                int rhs = active_stack.pop();
                int lhs = active_stack.pop();
                active_stack.push(lhs + rhs);
            }
            break;
        }

            /** @brief
             * Pop the top-most value of the stack B
             * and the next-top-most value of the stack A
             * and push the value A-B onto the stack.
             */
        case OpId::SUB: { //[W]
            int size = active_stack.get_size();
            if (size < 2) {
                std::cerr << "Less than 2 elements for the subtract operation\n";
            } else {
                int rhs = active_stack.pop();
                int lhs = active_stack.pop();
                active_stack.push(lhs - rhs);
            }
            break;
        }

        /** @brief
         * Pop the top-most value of the stack B
         * and the next-top-most value of the stack A
         * and push the value A*B onto the stack.
         */
        case OpId::MUL: { //[W]
            int size = active_stack.get_size();
            if (size < 2) {
                std::cerr << "Less than 2 elements for the multiplication operation\n";
            } else {
                int rhs = active_stack.pop();
                int lhs = active_stack.pop();
                active_stack.push(lhs * rhs);
            }
            break;
        }

        /** @brief
         * Pop the top-most value of the stack B
         * and the next-top-most value of the stack A
         * and push the value A/B onto the stack.
         * If B is zero instead of attempting to divide by zero
         * the program simply removes B, reports a divide-by-zero error
         * and continues to evaluate input.
         */
        case OpId::DIV: { //[W]
            int size = active_stack.get_size();
            if (size < 2) {
                std::cerr << "Less than 2 elements for the division operation\n";
            } else {
                int rhs = active_stack.pop();
                if (rhs == 0) {
                    std::cerr << "Floating point exception";
                    active_stack.push(rhs);
                } else {
                    int lhs = active_stack.pop();
                    active_stack.push(lhs / rhs);
                }
            }
            break;
        }

        /** @brief
         * Print the top-most value of the stack, followed by a newline
         * This operation preserves the printed value at the top of the stack.
         */
        case OpId::TOP: { //[W]
            int size = active_stack.get_size();
            if (size == 0) {
                std::cerr << "Stack is empty";
            } else {
                std::cout << active_stack.get_data()[size - 1] << "\n";
            } // could also pop, store the val, print and then push back
            break;
        }

        /** @brief
         * Pop the top-most value of the stack.
         */
        case OpId::POP: { //[W]
            int size = active_stack.get_size();
            if (size == 0) {
                std::cerr << "Stack is empty\n"; // or throw std::length_error("Stack is empty")
            } else {
                active_stack.pop();
            }
            break;
        }

        /** @brief
         * Copy the top-most value of the stack
         * placing the copy on top of the original value on the stack.
         */
        case OpId::DUP: { //[W]
            int size = active_stack.get_size();
            if (size == 0) {
                std::cerr << "Stack is empty\n";
            } else {
                int value     = active_stack.pop(); // pop the top value
                int new_value = value * 2;          // did it the long way for debugging purposes
                active_stack.push(new_value);
            }
            break;
        }

        /** @brief
         * Pop the three top-most values in the stack, C, B, and A
         * (shown here from top-most to bottom-most)
         * then place A on the top of the stack
         * if C is non-zero or place B on the top of the stack if C is exactly zero.
         */
        case OpId::COND: { //[W]
            int size = active_stack.get_size();
            if (size < 3) {
                std::cerr << "Less than 3 elements for conditional operation\n";
                // std::cerr << "Error: stack has less than two elements for conditional operation\n";
            } else {
                int val_c = active_stack.pop(); // stack representation [bottom] [A], [B], [C] [top]
                int val_b = active_stack.pop();
                int val_a = active_stack.pop();

                if (val_c != 0) {
                    active_stack.push(val_c);
                    active_stack.push(val_b);
                    active_stack.push(val_a); // A on top
                } else if (val_c == 0) {
                    active_stack.push(val_c);
                    active_stack.push(val_a);
                    active_stack.push(val_b); // B on top
                }
            }
            break;
        }

        case OpId::ENQ: { //[W]
            int value = active_stack.pop();
            active_queue.enqueue(value);
            break;
        }

        /** @brief
         * Dequeue the front-most value of the queue and push it onto the stack.
         */
        case OpId::DEQ: { //[W]
            int value = active_queue.dequeue();
            active_stack.push(value);

            // catch
            break;
        }

        /** @brief
         * Overwrite the save stack/queue with the contents of the active stack/queue.
         * Immediately after this operation, the integer sequences contained by the save stack/queue
         * must have no observable differences in ordering
         * value or count relative to the active stack/queue.
         */
        case OpId::SAVE: {             //[W]
            save_stack = active_stack; // using the assigemnt operator
            save_queue = active_queue;
        }

        /** @brief
         * Overwrite the active stack/queue with the contents of the save stack/queue.
         * Operations that occur after this operation is performed should behave
         * as though the operations that occurred since the previous save never happened.
         */
        case OpId::LOAD: { //[W]
            active_stack = save_stack;
            active_queue = save_queue;
            break;
        }

        /** @brief
         * Ends the program
         */
        case OpId::END: {
            goodbye();
            exit(EXIT_SUCCESS);
            break;
        }

        default: {
            std::cerr << "Error: unknown operation " << token << "\n";
            break;
        }
        }
    }
}

/** @name main()
 * @brief main function of the program
 * @pre None
 * @post Makes the program run by calling the evaluate() function in a while loop
 * @param None
 * @return EXIT_SUCESS which is the same as 0 upon sucessful execution
 */
int main() {
    ///@note active
    Stack active_stack;
    Queue active_queue;

    ///@note save
    Stack save_stack;
    Queue save_queue;
    welcome();
    while (true) {
        std::string token;
        std::cin >> token;
        evaluate(active_stack, active_queue, save_stack, save_queue, token);
    }
    return EXIT_SUCCESS;
}

