//Jun Qi Li
//CSCI 235
//Project 3B
//Selection Sort on a Singly Linked List
//
//This is the hpp file for the Linked List class
#ifndef LINKED_LIST_
#define LINKED_LIST_

#include "Node.hpp"

template<class T>
class LinkedList
{

public:
   LinkedList();
   LinkedList(const LinkedList<T>& a_list);
   virtual ~LinkedList();

   bool isEmpty() const;
   int getLength() const;
   bool insert(int new_position, const T& new_entry);
   bool remove(int position);
   void clear();
   T getEntry(int position) const;


   /***************** PROJECT-SPECIFIC PUBLIC METHODS ****************/

   void selectionSort();


private:
    Node<T>* head_ptr_; // Pointer to first node in the chain;
    // (contains the first entry in the list)
    int item_count_;           // Current count of list items

    // Locates a specified node in this linked list.
    // @pre  position is the number of the desired node;
    //       position >= 1 and position <= item_count_.
    // @post  The node is found and a pointer to it is returned.
    // @param position  The number of the node to locate.
    // @return  A pointer to the node at the given position.
    Node<T>* getNodeAt(int position) const;


       /***************** PROJECT-SPECIFIC PRIVATE METHODS ****************/
    //void connectSublists(Node<T>* new_min_ptr);


	//recursive selection sort, used for safe programming to avoid
	//exposing pointers to list in public methods
	//To sort the list, it relies on re-linking the chain rather than copying data items
	// @post the contents of the list are sorted in increasing order such that
	// the item at position 1 <= the item at at position 2 <= ...
	// <= item at position item_count_-1
	Node<T>* recursiveSelectionSort(Node<T>* current_first_ptr); 

  //returns a pointer to smallest value in the unsorted sublist
	Node<T>* searchMininum(Node<T>* first_ptr, Node<T>* second_ptr) const;

  //returns a pointer to the node before the smallest value in the sublist
  Node<T>* searchMinPrevious(Node<T>* first_ptr,const Node<T>* min_ptr) const;

 

}; // end LinkedList

#include "LinkedList.cpp"
#endif
