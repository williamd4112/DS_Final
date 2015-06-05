#include "bikeheap.h"

BikeHeap::BikeHeap(){
    
}

BikeHeap::~BikeHeap(){
    
}

int BikeHeap::size(){
    return heap.size();
}

bool BikeHeap::empty(){
    return heap.size() == 0;
}

BikePtr BikeHeap::top(){
    return heap.front();
}

BikePtr BikeHeap::pop(){
    std::pop_heap(heap.begin(), heap.end(), bikePtrCmp);
    heap.pop_back();
    
}

void BikeHeap::insert(BikePtr ptr){
    if(ptr == NULL)
        throw NullpointerException();
    heap.push_back(ptr); 
    std::push_heap(heap.begin(), heap.end(), bikePtrCmp);
}

void BikeHeap::deletes(BikePtr bikeptr){
    if(bikeptr == NULL)
        throw NullpointerException();
    std::vector<BikePtr>::iterator it = std::find(heap.begin(), heap.end(), bikeptr);
    if(it == heap.end())
        throw LicenseNotFoundException(bikeptr->license);
    
    // Replace the delete node with last node
    *it = heap.back();
    
    // Pop out the last node
    heap.pop_back();
    std::make_heap(heap.begin(), heap.end(), bikePtrCmp);
}

BikeHeap::Iterator BikeHeap::begin(){
    return BikeHeap::Iterator(heap.begin());
}

BikeHeap::Iterator BikeHeap::end(){
    return BikeHeap::Iterator(heap.end());
}

void BikeHeap::update(){
    // Re-assign the cursor to each bike
    for(BikeHeapCursor it = heap.begin(); it != heap.end(); it++)
        (*it)->setCursor(it);
}

bool bikePtrCmp(const BikePtr a, const BikePtr b){
	if(a != NULL && b != NULL)
		return a->getMile() <= b->getMile();
	else
		throw NullpointerException();
}