/** DOCUMENTATION
 * @file list.cpp
 * @author Jakob Balkovec
 * @brief source file for my ToDo list in my [p4]
 */

#include "list.h"
#include <iostream>
#include <string>

//list.cpp PATH: /home/st/jbalkovec/1430CPSC/Projects/p4/list.cpp
//list.h PATH: /home/st/jbalkovec/1430CPSC/Projects/p4/list.h
//p4.cpp PATH: /home/st/jbalkovec/1430CPSC/Projects/p4/p4.cpp

std::string const EMPTY = "[ ] ";
std::string const CHECKED = "[X] ";

/** DOCUMENTATION
 * @brief Constructor for the TodoList class.
 * This constructor initializes the head member variable of the TodoList class to a null pointer,
 * indicating that the list is initially empty.
 * @param None
 * @post creates an object
 * @return None
 */
TodoList::TodoList() {
  head = nullptr; //default parameters
}

/** DOCUMENTATION
 * @brief Copy constructor for the TodoList class.
 *
 * This constructor creates a new TodoList object that is a copy of an existing TodoList object, `other`.
 * It initializes the `head` member variable to a null pointer and then iterates over each entry in `other`,
 * adding each entry to the new TodoList object using the `add_entry` function.
 *
 * @param other A reference to the TodoList object to be copied.
 * @return None
 */
TodoList::TodoList(const TodoList& other) {
  head = nullptr;
  EntryNode *current = other.head;
  while (current != nullptr) {
    add_entry(current->text);
    current = current->next;
  }
}

//! FIX
// having free_list() metod allows to reset the linked list to an "empty state"
// without calling the destructor and destroying the object

// TodoList::~TodoList() { //destructor
//   EntryNode *current = head;
//   while (current != nullptr) {
//     EntryNode *next = current->next;
//     delete current;
//     current = next;
//   }
//   head = nullptr;
// }
//! FIX

/** DOCUMENTATION
 * @brief Destructor for the TodoList class.
 * This function deallocates all memory used by the TodoList, including
 * all EntryNodes and their associated TodoItems. It calls the free_list()
 * function to handle deallocating the memory.
 * @pre memory has to be allocated prior to calling the destructor
 * @post deallocates memory by calling free_list()
 * @return None
 */
TodoList::~TodoList() { //destructor separated
  free_list();
}

/** DOCUMENTATION
 * @brief Frees all EntryNodes in the TodoList.
 * This function deallocates all EntryNodes and their associated TodoItems
 * in the TodoList. It uses a loop to iterate through all EntryNodes in the
 * list, freeing each one and updating the head pointer to null.
 * @pre memory has to be allocated prior to calling the destructor
 * @post deallocates memory by calling free_list()
 * @invariant This function assumes that the head pointer is correctly set. //!should I avoid that
 * @return None
 */
void TodoList::free_list() {
  EntryNode *current = head;
  while (current != nullptr) {
    EntryNode *next = current->next;
    delete current;
    current = next;
  }
  head = nullptr;
}

/** DOCUMENTATION
 * @brief Adds a new entry to the TodoList.
 * Creates a new EntryNode and sets its text to the given text parameter. Sets its checked flag to false.
 * If the head node of the list is nullptr, the new node's next pointer is set to nullptr. Otherwise,
 * the new node's next pointer is set to the current head node's next pointer. Finally, sets the head
 * pointer to the new node, making it the new head of the list.
 * @param text The text of the new entry to be added to the list.
 * @return None
 * @bug endless loop
 */
void TodoList::add_entry(std::string text) {
  EntryNode *new_node = new EntryNode;
  new_node->text = text;
  new_node->checked = false;
  
  if (head == nullptr) {
    // The list is empty...set the new node next pointer to nullptr
    new_node->next = nullptr;
    head = new_node;
    tail = new_node;
  } else {
    // Set the new node next pointer to the current head node next pointer
    new_node->next = head->next;
    head = new_node;
    tail -> next = new_node;
    tail = new_node;
  }
}

/** DOCUMENTATION
 * @brief Removes an entry from the todo list.
 * This function removes the entry with the provided text from the list. If multiple entries with the same text
 * exist, all of them will be removed.
 * @param text The text of the entry to be removed.
 * @return None.
 */
void TodoList::remove_entry(std::string text) {
  EntryNode *current = head;
  EntryNode *previous = nullptr;
  while (current != nullptr) {
    if (current->text == text) {
      EntryNode *to_delete = current;
      if (previous == nullptr) {
        head = current->next;
      } else {
        previous->next = current->next;
      }
      current = current->next;
      delete to_delete;
    } else {
      previous = current;
      current = current->next;
    }
  }
}

/** DOCUMENTATION
 * @brief Raises an entry in the todo list.
 * This function moves the entry with the provided text up one position in the list. If the entry is already
 * at the top of the list or does not exist, nothing is done.
 * @param text The text of the entry to be raised.
 * @return None.
 */
void TodoList::raise(std::string text) {
  EntryNode *current = head;
  EntryNode *previous = nullptr;
  while (current != nullptr) {
    if (current->text == text) {
      if (previous != nullptr) {
        previous->next = current->next;
        current->next = previous->next->next;
        previous->next->next = current;
      }
      return;
    }
    previous = current;
    current = current->next;
  }
}

/** DOCUMENTATION
 * @brief Lowers an entry in the todo list.
 * This function moves the entry with the provided text down one position in the list. If the entry is already
 * at the bottom of the list or does not exist, nothing is done.
 * @param text The text of the entry to be lowered.
 * @return None.
 */
void TodoList::lower(std::string text) {
  EntryNode* current = this->head;
  EntryNode* prev = nullptr;
  
  while (current != nullptr && current->text != text) {
    prev = current;
    current = current->next;
    }
  
  if (current == nullptr) {
    return;
  }
  
  if (current->next == nullptr) {
    // Node is already at the bottom of the list or there is only one node in the list
    return;
  }
  
  EntryNode* next = current->next;
  current->next = next->next;
  
  if (prev == nullptr) {
    // Moving head
    next->next = this->head;
    this->head = next;
  } else {
    next->next = current;
    prev->next = next;
  }
}

/** DOCUMENTATION
 * @brief Marks an entry as checked in the todo list.
 * This function sets the 'checked' flag to true for the entry with the provided text. If the entry does not exist
 * in the list, nothing is done.
 * @param text The text of the entry to be checked.
 * @return None.
 */
void TodoList::check(std::string text) {
  EntryNode *current = head;
  while (current != nullptr) {
    if (current->text == text) {
      current->checked = true;
    }
    current = current->next;
  }
}

/** DOCUMENTATION
 * @brief Marks an entry as unchecked in the todo list.
 * This function sets the 'checked' flag to false for the entry with the provided text. If the entry does not exist
 * in the list, nothing is done.
 * @param text The text of the entry to be unchecked.
 * @return None.
 */
void TodoList::uncheck(std::string text) {
  EntryNode *current = head;
  while (current != nullptr) {
    if (current->text == text) {
      current->checked = false;
    }
    current = current->next;
  }
}

/** DOCUMENTATION
 * @brief Prints the contents of the todo list to the console.
 * This function iterates through the linked list and prints each entry to the console. Each entry is prefixed with
 * either a CHECKED or an EMPTY symbol to indicate whether it has been checked off.
 * @return None.
 * @post prints the todo list
 * @bug only prints a single entry
 * @bug head is not nullptr
 */ 
void TodoList::show() {
  EntryNode* current = this->head;
  
  while (current != nullptr) {
    if (current->checked) {
      std::cout << CHECKED;
    } else {
      std::cout << EMPTY;
    }
    std::cout << current->text << std::endl;
    // Update the current pointer to the next node
    current = current->next;    
  }
}
