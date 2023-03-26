/** DOCUMENTATION
 * @file queue.cpp
 * @author Jakob Balkovec
 * @brief implementation file for the Queue class for P5.
 * This file defines the queue class methods
 * @path: /home/st/jbalkovec/1430CPSC/Projects/p5/queue.cpp
 */

#include "queue.h"
#include <iostream>

/** DOCUMENTATION
 * @brief Default constructor for the Queue class.
 * Initializes the Queue with an array of size 1, sets the front and rear indices to 0,
 * and sets the capacity of the Queue to 1.
 * @pre Creates an object
 * @post None
 */
Queue::Queue() {
    data     = new int[1];
    front    = -1;
    rear     = -1;
    capacity = 1;
}

/**
 * @brief Copy constructor for the Queue class.
 * Creates a new Queue object and initializes its member variables to be the same as the
 * member variables of the Queue object passed as an argument.
 * It also allocates a new dynamic array
 * for the new Queue object and copies the elements of the dynamic array of the original Queue object
 * to the new dynamic array using a for loop.
 * @param other The Queue object to be copied.
 * @pre None
 * @post Creates a copy of an object
 */
Queue::Queue(Queue const &other) {
    data     = new int[other.capacity];
    front    = other.front;
    rear     = other.rear;
    capacity = other.capacity;
    for (int i = front; i < rear; i++) {
        data[i] = other.data[i];
    }
}

/** DOCUMENATION
 * @brief Destructor for the Queue class.
 * Deletes the dynamic array used to store the elements of the Queue.
 */
Queue::~Queue() {
    delete[] data;
}

/** DOCUMENATION
 * @brief Assignment operator overload for Queue class.
 * This function assigns the contents of one queue object
 * to another stack object using the "=" operator.
 * @param other Reference to the queue object to be copied from.
 */
void Queue::operator=(Queue const &other) {
    if (this != &other) {
        delete[] data;
        data     = new int[other.capacity];
        front    = other.front;
        rear     = other.rear;
        capacity = other.capacity;
        for (int i = front; i < rear; i++) {
            data[i] = other.data[i];
        }
    }
}

/** DOCUMENTATION
 * @brief Adds an element to the rear of the Queue.
 * This function takes an integer value as input and adds
 * it to the rear of the Queue. If there is no space
 * for the element, the function calls the resize()
 * function to increase the capacity of the Queue by a factor
 * of 2, and then adds the element to the rear of the Queue.
 * @param value The integer value to be added to the Queue.
 * @pre Queue has to exist and a value has to be passed as a parameter upon calling the method
 * @post enqueues an element
 */
void Queue::enqueue(int value) { // icludes resizing the array if necessary
    if (front == -1) {
        front = 0;
        rear  = 0;
    }
    if (rear == capacity) {
        int *new_data = new int[capacity * 2];
        int  j        = 0;
        for (int i = front; i < rear; i++) {
            new_data[j++] = data[i];
        }
        delete[] data;
        data  = new_data;
        front = 0;
        rear  = j;
        capacity *= 2; // From what I read online it is better than +1
    }
    data[rear++] = value;
}

/** DOCUMENTATION
 * @brief Removes the front element from the Queue.
 * This function removes the front element from the Queue and returns its integer value. If the Queue is
 * empty, the function throws a std::underflow_error with the message "Queue underflow".
 * @return The integer value of the front element that was removed from the Queue.
 * @throws std::underflow_error if the Queue is empty.
 */
int Queue::dequeue() {
    if (is_empty()) {                                // if empty, could also do if size == 0
        throw std::runtime_error("Queue underflow"); // would underflow_error be more appropriate?
    }
    int value = data[front++];
    if (front == rear) {
        front = -1;
        rear  = -1;
    }
    return value;
}

/** DOCUMENTATION
 * @brief prints the contents of the queue
 * @pre queue object has to exist/be created at some point
 * @post prints the queue
 */
void Queue::print() { // print the data
    for (int i = front; i < rear; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

/** DOCUMENTATION
 * @brief Checks if the queue is empty.
 *
 * @return true if the queue is empty, false otherwise.
 */
bool Queue::is_empty() {
    return front == -1 && rear == -1;
}
