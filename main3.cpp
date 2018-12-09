#include <iostream>
#include<stdexcept>
#include<deque>

template <typename tip>
class Red{
   std::deque <tip> red;
   public:
   Red() =default;
   Red(const Red<tip>& r){
       for(auto x : r.red)
       red.emplace_back(x);
   }
   Red<tip>& operator = (const Red<tip>& r){
       if(this == &r) return *this;
       for (auto x : r.red)
       red.emplace_back(x);
       return *this;
   }
   void brisi(){ red.clear(); }
   void stavi(const tip& el) { red.emplace_back(el); }
   tip skini(){
       if(!red.size()) throw "Izuzetak";
       tip novi = red.front();
       red.pop_front();
       return novi;
   }
   tip& celo(){
       if( !red.size()) throw "Izuzetak";
       return red.front();
   }
   int brojElemenata() { return red.size(); }
};


int main() {
  int brel;
Red<int> r;
for (int i(1); i<=5; i++)
	r.stavi(i);
{
        // Konstruktor kopije
	Red<int> r2(r);
	Red<int> r3;
        // Operator dodjele
	(r3=r).brojElemenata();
        // Destruktivna samododjela
        (r=r).brojElemenata();

	r.skini();
	brel = r2.brojElemenata();
	for (int i(0); i<brel; i++)
		std::cout << r2.skini() << " ";
	brel = r3.brojElemenata();
	for (int i(0); i<brel; i++)
		std::cout << r3.skini() << " ";
}
brel = r.brojElemenata();
for (int i(0); i<brel; i++)
	std::cout << r.skini() << " ";
}