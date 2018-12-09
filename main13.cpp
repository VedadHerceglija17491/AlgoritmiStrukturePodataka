#include <iostream>
template<typename Tip>
void insertionSort(Tip* niz, int vel){
    for(int i=1; i<vel; i++){
     Tip tmp(niz[i]);
     int j=i-1;
    
    while(j>=0  && niz[j]>tmp){   
        niz[j+1] = niz [j];
        j--;
    }
    niz[j+1] = tmp;
    }
}
int main() {
    int niz[]{5,1,3,4,2};
    insertionSort(niz,5);
    for(int x: niz) std::cout<<x<<" ";
    //std::cout << "Tutorijal 6, Zadatak 2";
    return 0;
}