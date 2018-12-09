#include <iostream>
#include<fstream>
#include<string>
#include <stdio.h>
#include<ctime>
#include <stdlib.h>   
template<typename Tip>
void selection_sort(Tip* niz, int vel ){
    for(int i=0; i<vel-1; i++){
        int min(i);
        for(int j=i+1; j<vel; j++)
        if(niz[j]<niz[min]) min=j;
        Tip tmp(niz[min]);
        niz[min]=niz[i];
        niz[i] = tmp;
    }
}
template<typename Tip>
void bubble_sort(Tip* niz, int vel){
    for(int i=vel-1; i>0; i--)
    for(int j=0; j<i; j++)
        if(niz[j]>niz[j+1]){
            Tip tmp(niz[j]);
            niz[j]=niz[j+1];
            niz[j+1]=tmp; 
        }
    }

template <typename Tip>
void merge_sort_pom(Tip* niz, int l, int u);

template <typename Tip>
void merge_sort_pom2(Tip* niz,int l, int p, int q, int u);

template <typename Tip>
void merge_sort(Tip* niz, int vel){
  merge_sort_pom(niz, 0, vel-1); 
}

template <typename Tip>
void merge_sort_pom(Tip* niz, int l, int u){
    if(u > l){
        int p((l+u-1)/2);
        int q (p+1);
        merge_sort_pom(niz, l, p);
        merge_sort_pom(niz, q, u);
        merge_sort_pom2(niz, l, p, q, u);        
}
}
template <typename Tip>
void merge_sort_pom2(Tip* niz,int l, int p, int q, int u){
     int i=0, j=q-l, k=l;
     Tip *niz2 = new Tip [u-l+1]; //dinamicki alociramo novi niz
     for(int m(0); m < u-l+1; m++){//prepisujemo elemente u novi niz
     niz2 [m] = niz[l+m];
     //std::cout<<niz[m]<<" ";
     }
     //std::cout<<std::endl;
     while(i <= p-l and j <= u-l ){ //uzimamo  manji element 
         if(niz2[i]<niz2[j]){
             niz[k] = niz2[i];
             i++;
         }else{
             niz[k] = niz2[j];
             j++;
         }
         k++;
     }// ispraznili smo jedan dio niza sada samo nadopunjujemo drugim djelom niza
     while(i<= p-l){
         niz[k++]= niz2[i++];
     }
     while(j<= u-l){
         niz[k++]= niz2[j++];
     }//brisemo pomocni niz
     delete[] niz2;
 }

 template<typename Tip>
void qucik_sort_pom(Tip*niz, int p, int q);

 
 template<typename Tip>
 void quick_sort(Tip* niz, int vel){
    qucik_sort_pom(niz,0,vel-1);
}

template<typename Tip>
void  qucik_sort_pom(Tip*niz, int p, int q){
        if(p<q){
         int i(p);
         Tip x(niz[p]);
         for(int j(p+1); j <= q; j++){
             if(niz[j]<x){
                 i++;
                 Tip tmp(niz[i]);
                 niz[i] = niz[j];
                 niz[j] = tmp;
             }
         }
         Tip tmp(niz[i]);
         niz[i] = niz[p];
         niz[p] = tmp;
         qucik_sort_pom(niz,p,i-1);
         qucik_sort_pom(niz,i+1,q);
        }
}
 
 void ucitaj(std::string filename, int*& niz, int &vel){
     std::ifstream ulazni_tok;
     ulazni_tok.open(filename);
     if(ulazni_tok.fail()){
     std::cout<<"Otvaranje datoteke nije uspjelo!\n";
    exit(1); 
     }
     else{
     int br_elemenata=0;
     int broj;
     //char znak;
     while(ulazni_tok>>broj){
         br_elemenata++;
     }
     vel=br_elemenata;
     niz = new int [br_elemenata];
     ulazni_tok.close();
     ulazni_tok.open(filename);
     int i=0;
     while(ulazni_tok>>broj){
         niz[i] = broj;
         i++;
     }
     ulazni_tok.close();
     }
        
 }
void generisi(std::string filename, int vel){
    std::ofstream izlazni_tok;
     izlazni_tok.open(filename);
     if(izlazni_tok.fail()){
     std::cout<<"Otvaranje datoteke nije uspjelo!\n";
    exit(1); 
     }
     else{
         
  srand (time(NULL));
         for(int i(0); i<vel; i++){
             izlazni_tok<< rand()%100<<" ";
         }
        izlazni_tok.close(); 
     }
}

int main() {
int* niz;
int vel = 0;
    int x;
   generisi("autotest.txt", 3000);
   ucitaj("autotest.txt", niz, vel);
    for(;;){
    std::cout<<"Unesite 1 za selection_sort, 2 za bubble_sort, 3 merge_sort, 4 qucik_sort ";
    std::cin>>x;
    if(x>=1 and x<=4) break;
    }
  if(x==1){
    clock_t vrijeme1 = clock();
  selection_sort(niz,3000);
clock_t vrijeme2 = clock();
int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
}
    if(x==2){
    clock_t vrijeme1 = clock();
  bubble_sort(niz,3000);
clock_t vrijeme2 = clock();
int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
}
 if(x==3){
    clock_t vrijeme1 = clock();
  merge_sort(niz,3000);
clock_t vrijeme2 = clock();
int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
}
 if(x==4){
    clock_t vrijeme1 = clock();
  quick_sort(niz,3000);
clock_t vrijeme2 = clock();
int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
}
std::ofstream izlazni_tok("brojevi.TXT");
if(!izlazni_tok) std::cout<<"kreiranje datoteke nije uspjelo";
 for(int i(0); i<vel-1; i++){
 izlazni_tok<<niz[i]<<" ";
 if(!izlazni_tok){
     std::cout<<"Nesto nije u redu sa datotekom";
     break;
 }
    if(niz[i] > niz[i+1]) {
       std:: cout << "NOT ";
        break;
    }
 }
std::cout << "OK";
delete[] niz;

}