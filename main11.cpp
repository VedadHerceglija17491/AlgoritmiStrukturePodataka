#include <iostream>
template<typename tip>
int binarna_p(tip* niz, int poc, int kraj, tip element){
    if(niz+poc <= niz+kraj){
    int m=(poc+kraj)/2;
    if(niz[m] == element) return m;
    else if( niz[m] > element) return binarna_p(niz,0,m-1,element);
    else if(niz [m] < element) return binarna_p(niz,m+1,kraj,element);
    else return -1;
    }
    else return -1;
}
template <typename tip>
int binarna_pretraga(tip* niz, int n, tip element){
    return binarna_p(niz,0,n-1,element);
}
int main() {
    int niz [] {1,2,3,4,5};
    int index;
    index = binarna_pretraga(niz,5,7);
    std::cout<<index;
    return 0;
}