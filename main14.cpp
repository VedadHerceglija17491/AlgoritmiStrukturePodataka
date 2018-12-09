#include <iostream>
/*Implementirati funkciju:
shellSort(Tip* niz, int vel, int* h, int hVel);
Koja će sortirati niz veličine vel pomoću shell sort algoritma. Funkcija prima i niz h koji predstavlja
niz razmaka koji se koriste u algoritmu. Testirati ulazni niz za različit niz h
*/
template<typename Tip>
void shellSort(Tip* niz, int vel, int* h, int hVel){
    for(int i(1); i<hVel; i++){
    
    for(int H=h[i]; H<vel ; H+=h[i]){
     Tip tmp(niz[H]);
     int j=H-h[i];
    
    while(j>=0  && niz[j]>tmp){
        niz[j+h[i]] = niz [j];
        j-=h[i];
    }
    niz[j+h[i]] = tmp;
    
    }
 

}
}
int main() {
     int niz[]{28,25,24,7,26,13,8,9,6,10,18,5,3,1,2};
     int niz2[]{5,3,1};
    shellSort(niz,15,niz2,3);
    for(int x: niz) std::cout<<x<<" ";
    //std::cout << "Tutorijal 6, Zadatak 2";
    return 0;
}