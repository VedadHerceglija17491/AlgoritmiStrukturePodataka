#include <iostream>
int nzd (int x, int y){
    int z ( x % y);
    if (z == 0) return y;
    return nzd(y,z);
}

int fib2_0 (int n, int rezultat = 0, int pretprosli = 1, int prosli = 1, int brojac = 2){
    if (n<=2) return n; 
   if (brojac == n) return rezultat;
  /* rezultat = pretprosli+prosli;
   pretprosli = prosli;
   prosli = rezultat;
   brojac++;*/
   return fib2_0(n, pretprosli+prosli, prosli, pretprosli+prosli, brojac+1);
} 
int main() {
   std::cout<< nzd(15,1)<<std::en
   dl;
   std::cout<<" Fibonaci za  n=2 je jednak "<<fib2_0(3)<<std::endl;
   return 0;
}