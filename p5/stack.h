/** DOCUMENTATION
 * @file stack.h -> @headerfile
 * @author Jakob Balkovec
 * @brief Header file for the Stack class for my P5.
 * This file defines the stack class,
 * @path: /home/st/jbalkovec/1430CPSC/Projects/p5/stack.h
 */

#ifndef STACK_H
#define STACK_H

///@class Stack
class Stack {
    private:
    int *data;
    int  size;

    public:
    Stack();
    Stack(Stack const &other);
    ~Stack();
    void operator=(Stack const &other);
    void push(int value);
    int  pop();
    void print() const;
    int  get_size();
    bool is_empty();
    int *get_data();
};

#endif // STACK_H