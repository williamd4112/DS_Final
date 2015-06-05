#include <iostream>
#include <cstdio>
#include <ctype.h>

using namespace std;

int h(const char *license_number, int i){
    return isalpha(license_number[i]) ? (license_number[i] - 'A' + 10) : license_number[i] - '0';
}

int toHash(char* license){
    int s[5];
    s[0] = h(license, 0);
    for(int i = 1; i < 5; i++){
        s[i] = s[i - 1] * 31 + h(license, i);
        printf("s[%d] = %d\n",i,s[i]);
    }
    printf("0x%x\n",s[4]);
    return (s[4] >> 10) & 0x000000ff;
}

int main(){
    
    char l[] = "NTHU0";
    cout << "Hashcode: " << toHash(l) << endl;
    
    return 0;
}