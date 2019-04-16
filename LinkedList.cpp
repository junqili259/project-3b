//Jun Qi Li
//CSCI 235
//Project 3A
//Recursion on selective sorting a Singly linked list  
//  
//Implementation of Linked List class functions

#include "LinkedList.hpp"  // Header file
#include <cassert>
#include<iostream>


template<class T>
LinkedList<T>::LinkedList() : head_ptr_(nullptr), item_count_(0)
{
}  // end default constructor

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& a_list) : item_count_(a_list.item_count_)
{
   Node<T>* orig_chain_pointer = a_list.head_ptr_;  // Points to nodes in original chain

   if (orig_chain_pointer == nullptr)
      head_ptr_ = nullptr;  // Original list is empty
   else
   {
      // Copy first node
      head_ptr_ = new Node<T>();
      head_ptr_->setItem(orig_chain_pointer->getItem());

      // Copy remaining nodes
      Node<T>* new_chain_ptr = head_ptr_;      // Points to last node in new chain
      orig_chain_pointer = orig_chain_pointer->getNext();     // Advance original-chain pointer
      while (orig_chain_pointer != nullptr)
      {
         // Get next item from original chain
         T next_item = orig_chain_pointer->getItem();

         // Create a new node containing the next item
         Node<T>* new_node_ptr = new Node<T>(next_item);

         // Link new node to end of new chain
         new_chain_ptr->setNext(new_node_ptr);

         // Advance pointer to new last node
         new_chain_ptr = new_chain_ptr->getNext();

         // Advance original-chain pointer
         orig_chain_pointer = orig_chain_pointer->getNext();
      }  // end while

      new_chain_ptr->setNext(nullptr);              // Flag end of chain
   }  // end if
}  // end copy constructor

template<class T>
LinkedList<T>::~LinkedList()
{
   clear();
}  // end destructor

template<class T>
bool LinkedList<T>::isEmpty() const
{
   return item_count_ == 0;
}  // end isEmpty

template<class T>
int LinkedList<T>::getLength() const
{
   return item_count_;
}  // end getLength

template<class T>
bool LinkedList<T>::insert(int new_position, const T& new_entry)
{
   bool able_to_insert = (new_position >= 1) && (new_position <= item_count_ + 1);
   if (able_to_insert)
   {
      // Create a new node containing the new entry
      Node<T>* new_node_ptr = new Node<T>(new_entry);

      // Attach new node to chain
      if (new_position == 1)
      {
         // Insert new node at beginning of chain
         new_node_ptr->setNext(head_ptr_);
         head_ptr_ = new_node_ptr;
      }
      else
      {
         // Find node that will be before new node
         Node<T>* prev_ptr = getNodeAt(new_position - 1);

         // Insert new node after node to which prev_ptr points
         new_node_ptr->setNext(prev_ptr->getNext());
         prev_ptr->setNext(new_node_ptr);
      }  // end if

      item_count_++;  // Increase count of entries
   }  // end if

   return able_to_insert;
}  // end insert

template<class T>
bool LinkedList<T>::remove(int position)
{
   bool able_to_remove = (position >= 1) && (position <= item_count_);
   if (able_to_remove)
   {
      Node<T>* cur_ptr = nullptr;
      if (position == 1)
      {
         // Remove the first node in the chain
         cur_ptr = head_ptr_; // Save pointer to node
         head_ptr_ = head_ptr_->getNext();
      }
      else
      {
         // Find node that is before the one to delete
         Node<T>* prev_ptr = getNodeAt(position - 1);

         // Point to node to delete
         cur_ptr = prev_ptr->getNext();

         // Disconnect indicated node from chain by connecting the
         // prior node with the one after
         prev_ptr->setNext(cur_ptr->getNext());
      }  // end if

      // Return node to system
      cur_ptr->setNext(nullptr);
      delete cur_ptr;
      cur_ptr = nullptr;

      item_count_--;  // Decrease count of entries
   }  // end if

   return able_to_remove;
}  // end remove

template<class T>
void LinkedList<T>::clear()
{
   while (!isEmpty())
      remove(1);
}  // end clear

template<class T>
T LinkedList<T>::getEntry(int position) const
{
    T dummy;
   // Check precondition
   bool able_to_get = (position >= 1) && (position <= item_count_);
   if (able_to_get)
   {
      Node<T>* nodePtr = getNodeAt(position);
      return nodePtr->getItem();
   }
    else
        return dummy; //PROBLEM!!!! may return uninitialized object - will fix later with Exception Handling

}  // end getEntry



/************* PROJECT-SPECIFIC PUBLIC METHODS ************/

//wrapper function that calls the recursive Selection sort function
template<class T>
void LinkedList<T>::selectionSort(){

   if (isEmpty())//if list is empty do nothing
   {
      return;
   }
   else
   {
      Node<T>* first_ptr = head_ptr_;

      //Start the recursion by passing what the head pointer is pointing to
      Node<T>* min = recursiveSelectionSort(first_ptr);
      head_ptr_ = min;//repoint head pointer to beginning of sorted list
   }
}



/************* PRIVATE ************/



template<class T>
Node<T>* LinkedList<T>::getNodeAt(int position) const
{
   // Debugging check of precondition
   assert( (position >= 1) && (position <= item_count_) );

   // Count from the beginning of the chain
   Node<T>* cur_ptr = head_ptr_;
   for (int skip = 1; skip < position; skip++)
      cur_ptr = cur_ptr->getNext();

   return cur_ptr;
}  // end getNodeAt



       /***************** PROJECT-SPECIFIC PRIVATE METHODS ****************/

   //recursive selection sort, used for safe programming to avoid
   //exposing pointers to list in public methods
   //To sort the list, it relies on re-linking the chain rather than copying data items
   // @post the contents of the list are sorted in increasing order such that
   // the item at position 1 <= the item at at position 2 <= ...
   // <= item at position item_count_-1


//current_first_ptr is the determining line between unsorted and sorted
template<class T> 
Node<T>* LinkedList<T>::recursiveSelectionSort(Node<T>* current_first_ptr){

   //Base case of the function and returns the a pointer to the last unsorted node
   if (current_first_ptr->getNext() == nullptr)
   {
      return current_first_ptr;
   }
   //If length of list is 1, it's already sorted so do nothing and just return head pointer
   else if (getLength() == 1)
   {
      return head_ptr_;
   }
   else
   {
      //declaring all the needed pointers to perform the recursion
      Node<T>* current_first_next_ptr = current_first_ptr->getNext();

      //pointer to smaller value in the unsorted sublist
      Node<T>* min_ptr = searchMininum(current_first_ptr, current_first_next_ptr);
      Node<T>* min_next = min_ptr->getNext();
      
      //Don't swap anything, proceed to find next smallest value in unsorted sublist by looking ahead
      if (min_ptr == current_first_ptr)
      {
         //look ahead to connect the chain to next sorted node
         min_ptr->setNext(recursiveSelectionSort(min_ptr->getNext()));
         return min_ptr;
      }
      //in case if that min previous is current_first_ptr  
      else if (current_first_ptr->getNext() == min_ptr)
      {
         //swapping the nodes of min_ptr and current_first_ptr
         min_ptr->setNext(current_first_ptr);
         current_first_ptr->setNext(min_next);

         //look ahead to connect the chain to next sorted node
         min_ptr->setNext(recursiveSelectionSort(min_ptr->getNext()));
         return min_ptr;

      }
      else
      {
         //If all the special exceptions don't occur, just swap nodes and reconnect chain normaly
         Node<T>* min_prev = searchMinPrevious(current_first_ptr, min_ptr);
         min_ptr->setNext(current_first_next_ptr);//disconnects min_ptr and min_next
         current_first_ptr->setNext(min_next);
         min_prev->setNext(current_first_ptr);
         
         min_ptr->setNext(recursiveSelectionSort(min_ptr->getNext()));
         return min_ptr;
      }
   }
}//end recursiveSelectionSort


//passes current_first_ptr and min_ptr
//returns a pointer to the node before the min_ptr
template<class T>
Node<T>* LinkedList<T>::searchMinPrevious(Node<T>* first_ptr,const Node<T>* min_ptr) const{
   //look ahead and compare next ptr with min ptr and return if equal
   if (first_ptr->getNext() == min_ptr)
   {
      return first_ptr;
   }
   else
   {
      //recursively traverse through the list
      first_ptr = first_ptr->getNext();
      searchMinPrevious(first_ptr, min_ptr);
   }

}

//finds and returns a pointer to the smallest value in the unsorted sublist
template<class T>
Node<T>* LinkedList<T>::searchMininum(Node<T>* first_ptr, Node<T>* second_ptr) const{
   if (second_ptr == nullptr)//reached end of list
   {
      return first_ptr;//returns pointer to last node in list
   }

   //if second_ptr greater than first_ptr, second_ptr moves to next node and calls function again
   else if (first_ptr->getItem() < second_ptr->getItem())
   {  
      
      second_ptr = second_ptr->getNext();
      searchMininum(first_ptr, second_ptr);
   }

   //reassign pointer if item at second_ptr is smaller than first_ptr
   else if (first_ptr->getItem() > second_ptr->getItem())
   {
      first_ptr = second_ptr;
      second_ptr = second_ptr->getNext();
      searchMininum(first_ptr, second_ptr);
   }
   //Case handling if both nodes contain items of small value
   else if (first_ptr->getItem() == second_ptr->getItem())
   {
      second_ptr = second_ptr->getNext();
      searchMininum(first_ptr, second_ptr);
   }

}

//  End of implementation file.