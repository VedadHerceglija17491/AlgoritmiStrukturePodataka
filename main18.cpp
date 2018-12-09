#include <iostream>
#include<vector>
#include <algorithm>
using namespace std;

bool je_li_list(int i, vector<int> &v){
    return i>= v.size()/2 && i<v.size();
}
int roditelj(int i){
    return (i-1)/2;
}
int lijevo_dijete(int i){
    return 2*i+1;
}
int desno_dijete(int i){
    return 2*i+2;
}
void popravi_dolje(vector<int> &v, int i, int velicina = -1){
    if(velicina == -1) velicina = v.size();
    while(! (i>= velicina/2 && i<velicina)){  //List nema djecu
        int veci(lijevo_dijete(i));
        int dd(desno_dijete(i));
        if(dd<velicina){   // provjera radi pristupa ne dozvoljenoj lokaciji
            if(v[dd]> v[veci])
            veci = dd;
        }
        if(v[i] > v[veci])
        return;
        else{
            swap(v[i], v[veci]);
            i = veci;
        }
    }
}
void stvoriGomilu(vector<int> &v){
    for(int i(v.size()/2); i>= 0; i--)
    popravi_dolje(v,i);
}
void popravi_gore (vector<int> &v, int i){
    if(i > 0)
    while( v[i] > v[roditelj(i)]){
        swap(v[i], v[roditelj(i)]);
        i = roditelj(i);
        if (i <= 0) break;
    }
    
}
void umetniUGomilu(vector<int> &v, int umetnuti, int &velicina){
    if(velicina<v.size())
    v[velicina] = umetnuti;
    else
    v.push_back(umetnuti);
    velicina++;
    popravi_gore(v,velicina-1);
}
int izbaciPrvi(vector<int> &v, int &velicina){
    if(velicina == 0) throw "izuzetak";
    velicina--;
    int x(v[velicina]);
    swap(v[0],v[velicina]);
    if(velicina > 0)
    popravi_dolje(v,0,velicina);
    return x;
}
void gomilaSort(vector<int> &a){
    int x(a.size());
    stvoriGomilu(a);
    for(int i(0); i<a.size()-1; i++)
    izbaciPrvi(a,x);
}

void radixSort(vector<int> &a){
    int baza (10);
    for(;;){
        vector<int> c(10,0);
        vector<int> b(a.size());
        //int osigurac(0);
        for(int i(0); i<a.size(); i++){
          //  if(double(a[i]%baza)/double(baza/10) > 0.00000001 and double(a[i]%baza)/double(baza/10) < 1) osigurac++;
            c[(a[i]%baza)/(baza/10)]++;
        } 
        if(c[0] == a.size()) break;
        for(int i(1); i<c.size(); i++)
        c[i] += c[i-1];
        for(int i (a.size()-1); i>=0; i--){
        c[(a[i]%baza)/(baza/10)]--;    
        b[c[(a[i]%baza)/(baza/10)]]= a[i];
        }
        a=b;
        baza*=10;
    }
}
int main() {
     vector<int> a;
    int velicina = 0;
    umetniUGomilu(a,546,velicina);
    umetniUGomilu(a,435435,velicina);
    umetniUGomilu(a,12,velicina);
    umetniUGomilu(a,546,velicina);
    umetniUGomilu(a,675767,velicina);
    umetniUGomilu(a,33,velicina);
    umetniUGomilu(a,555,velicina);
    umetniUGomilu(a,1,velicina);
    izbaciPrvi(a,velicina);
    izbaciPrvi(a,velicina);
    izbaciPrvi(a,velicina);
    izbaciPrvi(a,velicina);
    izbaciPrvi(a,velicina);
    izbaciPrvi(a,velicina);
    izbaciPrvi(a,velicina);
    izbaciPrvi(a,velicina);
    for(int i(0);i<a.size();i++){
        cout<<a[i]<<" "<<velicina<<" ";
    }    

}