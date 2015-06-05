#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const int a, const int b){
    return a > b;
}

void p(vector<int>& v){
    for(vector<int>::iterator it = v.begin(); it != v.end(); it++){
        cout << *it << " ";   
    }
    cout << endl;
}

void pu(vector<int>& v, int val){
    v.push_back(val);
    push_heap(v.begin(), v.end(), cmp);
}

void d(vector<int>& v, vector<int>::iterator cursor){
    *cursor = v.back();
     v.pop_back(); 
     make_heap(v.begin(), v.end(), cmp);
}

int* gp(vector<int>& v, int val){
    vector<int>::iterator it = find(v.begin(), v.end(), val);
    if(it == v.end())
        cerr << "Not found" << endl;
    int& int_ref = *it;
    
    return &int_ref;
}

int main(){
    
    int myints[] = {10,20,30,5,15};
    vector<int> v(myints, myints+5);
    
    cout << "Return: " << *gp(v, 15) << endl;
    
    // make_heap(v.begin(), v.end(), cmp);
    // p(v);
    
    // pu(v, 16);
    // p(v);
    
    // vector<int>::iterator it = v.begin() + 1;
    // d(v, v.begin() + 1);
    // p(v);
    // cout << *v.end() << endl;
    
    return 0;
}