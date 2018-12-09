/*Implementirati funkciju:
countingSort(Tip* a, int vel, int* bNiz, int k);
Koja će u bNiz veličine vel premjestiti sortiran niz a pomoću counting sort algoritma
*/

#include <iostream>
template<typename Tip>
void countingSort(Tip* a, int vel, int* bNiz, int k){
    int* c = new int [k+1];
    for(int i=0; i<=k; i++) 
    c[i] = 0;
    for(int i(0); i<vel; i++)//broji i zapisuje u niz c koliko kojih  elemenata ima u nizu a
    c[a[i]]= c[a[i]]+1;
    for(int i(1); i<=k; i++)//koliko je vecih ili jednakih elemenata od i u nizu c
    c[i] = c[i] + c[i-1];
    for(int i (vel-1); i>=0; i--){//element iz niza a upisujemo na odgovarajucu poziciju u niz b
        c[a[i]]= c[a[i]]-1;
        bNiz[c[a[i]]] = a[i];
        
    }
    delete [] c;
}
int main() {
    int b[]{1,2,3,4,5};
    int niz[]{1,3,3,2,8};
    countingSort(niz,5,b,8);
    for(int i(0); i<5; i++) std::cout<<b[i]<<" ";
    return 0;
}