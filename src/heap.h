#ifndef _HEAP_H_
#define _HEAP_H_

#include "standard.h"

template <typename T>
class Heap {
public:
    Heap(int capacity) {
        size = 0;
        data = new T[capacity + 1];
    }

    ~Heap() {
        delete [] data;
    }
    
    /*
        push(e):
        push an element at the bottom of the heap, and bubble up this element
    */
    void push(T e) {
        int currentnode = ++size;
        bubble_up(currentnode, e);
    }
    
    /*
        pop():
        pop an element at the heap, if no elements in this heap, ignore 
    */
    void pop() {
        if (size == 0)
            return;
            
        T last_e = data[size--];
        bubble_down(1, last_e);
    }
    
    /*
        remove(t):
        remove element in the heap
        
        return: true when success, false when failed to find element
    */
    bool remove(T t) {
        // Find element
        int ti = 0;
        for (int i = 1; i <= size; i++)
            if (data[i] == t) {
                ti = i;
                break;
            }

        if(ti == 0)
            return false;

        // Replace the element with
        data[ti] = data[size--];

        // Larger than parent
        (data[ti / 2] < data[ti]) ? bubble_up(ti, data[ti]) : bubble_down(ti, data[ti]);
        
        return true;
    }
    
    /*
        top():
        return the top element
    */
    T& top() {
        if(empty())
            throw EmptyContainerException();
        return data[1];
    }

    bool empty() {
        return (size == 0);
    }

private:
    
    /* Heapsize */
    int size;
    
    /* Heap data array */
    T *data;
    
    /*
        bubble_up(int currentnode, T e):
        bubble up in this heap start at currentnode with value e
    */
    void bubble_up(int currentnode, T e) {
        T parent_e;
        while ((parent_e = data[currentnode / 2]) < e && currentnode != 1) {
            data[currentnode] = parent_e;
            currentnode /= 2;
        }
        data[currentnode] = e;
    }
    
    /*
        bubble_down(int currentnode, T e):
        bubble down in this heap start at currentnode with value e
    */
    void bubble_down(int currentnode, T e) {
        int child = currentnode * 2;
        while (child <= size) {
            
            // if child < heapsize, choose the larger child
            // if two child equal, choose smaller one
            if (child < size && data[child] < data[child + 1])
                child++;
                
            // if all child are smaller than parent, break
            if (!(e < data[child]))
                break;
                
            data[currentnode] = data[child];
            currentnode = child;
            child *= 2;
        }
        data[currentnode] = e;
    }
};

#endif