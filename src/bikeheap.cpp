#include "bikeheap.h"

BikeHeap::BikeHeap():
heapsize(0){
    // No use node
    heap.push_back(new Bike(LicenseType("")));
}

BikeHeap::~BikeHeap(){

}

int BikeHeap::size(){
    return heapsize;
}

bool BikeHeap::empty(){
    return heapsize == 0;
}

BikePtr BikeHeap::top(){
    if(empty())
        throw EmptyContainerException();
    else if(heap[1] == NULL)
        throw NullpointerException();
    return heap[1];
}

void BikeHeap::pop(){
    if (heapsize == 0)
        return;
    bubble_down(1, heap[heapsize--]);
}

void BikeHeap::insert(BikePtr ptr){
    if(ptr == NULL)
        throw NullpointerException();
    std::cout << "Insert : " << ptr->license << std::endl;
    bubble_up(++heapsize, ptr);
    std::cout << "size: " << heap.size() << std::endl;
}

void BikeHeap::deletes(BikePtr bikeptr){
    if(bikeptr == NULL)
        throw NullpointerException();
    
    for(std::vector<BikePtr>::iterator it = heap.begin(); it != heap.end(); it++){
        if(*it == NULL) continue;
        std::cout << "size: " << heap.size() << std::endl;
        std::cout << "Comapre: " << (*it)->license << " with " << bikeptr->license << std::endl;
        if(*it != NULL && *it == bikeptr){
            std::cout << "Found" << std::endl;
            int ti = it - heap.begin();

            // Replace the element with
            heap[ti] = heap[heapsize--];
        
            // Larger than parent
            (bikePtrCmp(heap[ti / 2], heap[ti])) ? bubble_up(ti, heap[ti]) : bubble_down(ti, heap[ti]);
            return;
        }
    }
    
    throw LicenseNotFoundException(bikeptr->license);
}

void BikeHeap::bubble_up(int currentnode, BikePtr e){
    BikePtr parent_e;
    while (currentnode != 1 && currentnode != 0) {
        if(bikePtrCmp((parent_e = heap[currentnode / 2]), e)){
            heap[currentnode] = parent_e;
            currentnode /= 2;
        }
        else
            break;
    }
    heap[currentnode] = e;
}

void BikeHeap::bubble_down(int currentnode, BikePtr e){
    int child = currentnode * 2;
    while (child <= heapsize) {
        if (child < heapsize && bikePtrCmp(heap[child], heap[child + 1]))
            child++;
                
        if (!(bikePtrCmp(e, heap[child])))
            break;
                
        heap[currentnode] = heap[child];
        currentnode = child;
        child *= 2;
    }
    heap[currentnode] = e; 
}

BikeHeap::Iterator BikeHeap::begin(){
    return BikeHeap::Iterator(heap.begin() + 1);
}

BikeHeap::Iterator BikeHeap::end(){
    return BikeHeap::Iterator(heap.begin() + 1 + heapsize);
}

//bikePtrCmp()
bool bikePtrCmp(const BikePtr a, const BikePtr b){
	if(a != NULL && b != NULL)
		return a->getMile() < b->getMile();
	else
		throw NullpointerException();
}