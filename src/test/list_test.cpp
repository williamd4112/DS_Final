#include <iostream>
#include <list>

using namespace std;

int main(){
    
    list<int> li;
    li.push_back(1);
    //li.push_back(1);
    
    int a = 1;
    int& ar = a;
    
    cout << "Remove 1: " << li.remove(ar) << endl;
    //cout << "Remove 2: " << li.remove(b) << endl;
    
    return 0;
}