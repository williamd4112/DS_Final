#include <iostream>
#include <vector>
#include <algorithm>
#include "heap.h"

using namespace std;

bool cmp(const int a, const int b){
    return a < b;
}

int main(){
    
    int myints[] = {10,20,30,5,15};
    Heap<int> h(5, cmp);
    
    return 0;
}