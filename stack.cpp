// Name: Ben Wilfong
// File Name: stack.cpp
// Date: 31 Oct, 2014
// Program Description: This file contains
// the template-implemented member functions 
// of the stack ADT.

#ifndef STACK_CPP 
#define STACK_CPP

template <class T>
Stack<T>::Stack()
{
    top = NULL;
    count = 0;        
}

template <class T>
bool Stack<T>:: push(T dataIn)
{
    Node<T>* pNew = new Node<T>;
    
    if (pNew == NULL)
        return false;
        
    pNew->data = dataIn;
    pNew->next = top;
    top = pNew;
    
    count++;
    
    return true;
}

template <class T>
bool Stack<T>::pop(T& dataOut)
{
    if (top == NULL)
        return false;
    
    dataOut = top->data;
    
    Node<T>* temp = top;
    top = top->next;
    count--;
    
    delete temp;
    
    return true;
}

template <class T>
bool Stack<T>::isEmpty()
{
    return (top == NULL);
}

template <class T>
bool Stack<T>::clear()
{
    T dummy;
    while(pop(dummy));
}     

template <class T>
Stack<T>::~Stack()
{
    T dummy;
    while(pop(dummy));
}

#endif
