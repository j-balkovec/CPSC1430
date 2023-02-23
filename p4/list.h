/** DOCUMENTATION
 * @file list.h -> @headerfile
 * @author Jakob Balkovec
 * @brief Header file for the TodoList class.
 * This file defines the list class,
 * which represents a ToDo list (a linked list) in project 4.
 */

#ifndef LIST_H
#define LIST_H

#include <string>

struct EntryNode {
    bool checked;
    std::string text;
    EntryNode *next;
};

class TodoList {
private:
    EntryNode *head;
    EntryNode *tail; //probs not necessary
    void free_list(); //private to deal with memory

public:
    TodoList();
    TodoList(const TodoList& other);
    ~TodoList();
    void add_entry(std::string text);
    void remove_entry(std::string text);
    void raise(std::string text);
    void lower(std::string text);
    void check(std::string text);
    void uncheck(std::string text);
    void show();
};
#endif //LIST_H
