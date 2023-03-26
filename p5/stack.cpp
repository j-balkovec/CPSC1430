/** DOCUMENTATION
 * @file stack.cpp
 * @author Jakob Balkovec
 * @brief source file for my stack
 * @path: /home/st/jbalkovec/1430CPSC/Projects/p5/stack.cpp
 */
#include "stack.h"
#include <exception>
#include <iostream>

/** DOCUMENTATION
 * @typedef Constructor of the Stack class
 * @brief creates a new stack
 * @pre None
 * @post A new object is created
 */
Stack::Stack() {
    data = new int[0];
    size = 0;
}

/** DOCUMENTATION
 * @typedef Destructor of the Stack class
 * @brief handles memory for the stack (kills the existing object)
 * @pre An object type Stack has to exist
 * @post Deallocates te memory used by the object
 */
Stack::~Stack() {
    delete[] data;
}

/** DOCUMENTATION
 * @brief Copy constructor that creates a new
 * object that is a copy of another object (type Stack).
 * @param other The Stack object to copy.
 * @pre None
 * @post None
 */
Stack::Stack(Stack const &other) {
    // for loop for data
    size = other.size;
    data = new int[other.size]; // should it be zero?
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

/** DOCUMENTATION
 * @brief Assignment operator overload for Stack class.
 * This function assigns the contents of one stack object
 * to another stack object using the "=" operator.
 * @param other Reference to the Stack object to be copied from.
 */
void Stack::operator=(Stack const &other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new int[other.size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
}

/** DOCUMENTATION
 * @brief Pushes a value onto the top of the Stack.
 * This function adds an integer value to the top of the Stack.
 * It first creates a new array with size increased by 1.
 * Then it copies the elements of the current data array
 * to the new array and deletes the current data array.
 * Finally, it assigns the new array to data and updates the size variable.
 * @param value The integer value to be added to the top of the Stack.
 * @invariant the push method always only ads one element
 * @pre user has to provide a value
 * @post adds an element to the stack
 */
void Stack::push(int value) { // includes resizing the array
    int  new_size = size + 1;
    int *new_data = new int[new_size];
    for (int i = 0; i < size && i < new_size && size != new_size; i++) {
        new_data[i] = data[i];
    }
    new_data[size] = value;
    delete[] data;
    data = new_data;
    size = new_size;
}

/** DOCUMENTATION
 * @brief Removes and returns the top element of the Stack.
 * This function removes and returns the top element of the Stack.
 * If the Stack is empty, it throws an error.
 * @return The integer value of the top element of the Stack.
 * @throw "stack underflow" If the Stack is empty
 * @pre None
 * @post removes an element
 */
int Stack::pop() {
    if (size == 0) {
        throw std::runtime_error("stack underflow"); // would underflow error be more appropriate?
    }
    return data[--size];
}

/** DOCUMENTATION
 * @brief Prints the contents of the stack
 * @pre None
 * @post The contents of the Stack are printed
 */
void Stack::print() const {
    std::cout << "Stack contents: ";
    for (int i = size - 1; i >= 0; i--) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

/** DOCUMENATION
 * @brief Returns the size of the given stack.
 * @return The size of the stack.
 */
int Stack::get_size() {
    return size;
}

/** DOCUMENTATION
 * @brief Checks if the stack is empty.
 * @return true if the stack is empty, false otherwise.
 */
bool Stack::is_empty() {
    if (size == 0) {
        return true;
    }
    return false;
}

/** DOCUMENTATION
 * @brief Returns a pointer to the data in the give stack.
 * @return pointer to the data variable.
 */
int *Stack::get_data() {
    return data;
}