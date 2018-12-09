#include <iostream>
int pow ( int a, unsinged int n){
    if(n == 1) return a;
    int b=pow(a, n/2);
    if(n%2) return b*b;
    else return b*b;
}
int main() {
    std::cout << pow(2,3);
    return 0;
}