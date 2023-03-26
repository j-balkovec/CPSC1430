/** DOCUMENTATION
 * @file queue.h -> @headerfile
 * @author Jakob Balkovec
 * @brief Header file for the Queue class for my P5.
 * This file defines the queue class
 * @path: /home/st/jbalkovec/1430CPSC/Projects/p5/queue.h
 */

#ifndef QUEUE_H
#define QUEUE_H

/// @class Queue
class Queue {
    private:
    int *data;
    int  front;
    int  rear;
    int  capacity;

    public:
    Queue();
    Queue(Queue const &other);
    ~Queue();
    void operator=(Queue const &other);
    void enqueue(int value);
    int  dequeue();
    void print();
    bool is_empty();
};

#endif // QUEUE_H
