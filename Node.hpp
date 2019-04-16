//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
//  Modified by Tiziana Ligorio for Hunter College CSCI 235

/** @file Node.hpp
    Node for Singly Linked List*/

#ifndef NODE_
#define NODE_

template<class T>
class Node
{
private:
   T        item_; // A data item_
   Node<T>* next_; // Pointer to next_ node

public:
   Node();
   Node(const T& an_item);
   Node(const T& an_item, Node<T>* next_node_ptr);
   void setItem(const T& an_item);
   void setNext(Node<T>* next_node_ptr);
   T getItem() const ;
   Node<T>* getNext() const ;
}; // end Node

#include "Node.cpp"
#endif
