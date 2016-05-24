// Name: Ben Wilfong
// File Name: stack.h
// Date: 31 Oct, 2014
// Program Description: This file contains
// the declaration of the position structure,
// the node structure, and the declaration of
// the Stack ADT

#ifndef STACK_H
#define STACK_H

struct Position
{
    int row;
    int column;
};

template <class T>
struct Node
{
    Node<T>* next;
    T data;
};

template <class T>
class Stack
{           
    private:
        Node<T>* top;

    public:
        Stack();
        ~Stack();
        bool clear();
        bool push(T dataIn);
        bool pop(T& dataOut);
        bool isEmpty();
        int  count;//Made public to verify there are n-queens   
};

#include "stack.cpp"

#endif

