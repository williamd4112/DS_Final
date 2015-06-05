#include "bikeheap.h"

BikeHeap::BikeHeap():
    heapsize(0) {
    // no use node
    heap.push_back(NULL);
}

BikeHeap::~BikeHeap() {

}

int BikeHeap::size() {
    return heapsize;
}

bool BikeHeap::empty() {
    return heapsize == 0;
}

BikePtr BikeHeap::top() {
    return heap[1];
}

BikePtr BikeHeap::pop() {
    if (heapsize != 0){
        // Copy last to first
        heap[1] = heap[heapsize--];

        // Pop back
        heap.pop_back();

        bubble_down(1, heap[1]);
    }
}

void BikeHeap::insert(BikePtr ptr) {
    if (ptr == NULL)
        throw NullpointerException();
    heap.push_back(ptr);
    bubble_up(++heapsize, ptr);
}

void BikeHeap::deletes(BikePtr bikeptr) {
    if (bikeptr == NULL)
        throw NullpointerException();

    int ti = find(bikeptr);
    if (!ti)
        throw LicenseNotFoundException(bikeptr->license);

    // Replace the element with
    heap[ti] = heap.back();
    heapsize--;

    // Pop out the last element
    heap.pop_back();

    // Larger than parent;
    if (ti > 1 && bikePtrCmp(heap[ti / 2], heap[ti])) 
        bubble_up(ti, heap[ti]);
    else 
        bubble_down(ti, heap[ti]);
}

BikeHeap::Iterator BikeHeap::begin() {
    return BikeHeap::Iterator(heap.begin() + 1);
}

BikeHeap::Iterator BikeHeap::end() {
    return BikeHeap::Iterator(heap.end());
}

int BikeHeap::find(BikePtr bikeptr) {
    for (int i = 1; i < heap.size(); i++)
        if (bikeptr == heap[i])
            return i;
        
    return 0;
}

void  BikeHeap::bubble_up(int currentnode, BikePtr e) {
    BikePtr parent_e;
    while (currentnode > 1 && bikePtrCmp((parent_e = heap[currentnode / 2]), e)) {
        heap[currentnode] = parent_e;
        currentnode /= 2;
    }
    heap[currentnode] = e;
}

void BikeHeap::bubble_down(int currentnode, BikePtr e) {
    int child = currentnode * 2;
    while (child <= heapsize) {
        if (child < heapsize && bikePtrCmp(heap[child], heap[child + 1]))
            child++;
        if (!bikePtrCmp(e, heap[child]))
            break;
        heap[currentnode] = heap[child];
        currentnode = child;
        child *= 2;
    }
    heap[currentnode] = e;
}

bool bikePtrCmp(const BikePtr a, const BikePtr b) {
    if (a != NULL && b != NULL)
        return a->getMile() < b->getMile();
    else
        throw NullpointerException();
}

void BikeHeap::dbg(){
    std::cout << "Heap:" << std::endl;
    for(int i = 1; i < heap.size(); i++){
        std::cout << heap[i]->license << std::endl;
    }
}