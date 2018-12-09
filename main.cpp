#include <iostream>
#include<cmath>
#include<typeinfo>

template<typename tip>
class Iterator;

template<typename Tip>
class Lista {
  public:
  Lista(){}
  virtual ~Lista(){}
  virtual int brojElemenata() const=0;
  virtual Tip& operator [] (int i) =0;
  virtual Tip& operator [] (int i) const=0;
  virtual Tip& trenutni () =0;
  virtual Tip trenutni () const=0;
  virtual bool prethodni()=0;
  virtual bool sljedeci()=0;
  virtual void pocetak()=0;
  virtual void kraj()=0;
  virtual void obrisi()=0;
  virtual void dodajIspred(const Tip& el)=0;
  virtual void dodajIza(const Tip& el)=0;
};

template<typename tip>
class DvostrukaLista : public Lista<tip>{
  
  struct Cvor{
    tip vrijednost;
    Cvor* slj;
    Cvor* pr;
  };
  int index;
  int brojEl;
  Cvor* poc;
  Cvor* krajnji;
  Cvor* tren;
  
  public:
  
    DvostrukaLista() : Lista<tip>(), index(-1), brojEl(0) {
      poc = new Cvor;
      krajnji = new Cvor;
      tren = poc;
      poc->slj = krajnji;
      poc->pr = nullptr;
      poc->vrijednost = tip();
      krajnji->slj = nullptr; 
      krajnji->pr = poc;
      krajnji->vrijednost = tip();
    }
  
  virtual ~DvostrukaLista(){
    while(poc != nullptr){
      tren = poc;
      poc = poc->slj;
      delete tren;
    }
    }
      DvostrukaLista(const DvostrukaLista<tip> &l){
      Cvor* tmp(l.poc);
      Cvor* tmp2(nullptr);
      while(tmp != nullptr){
        Cvor* novi (new Cvor);
        novi->slj = nullptr;
        novi->pr = nullptr;
        novi->vrijednost = tip();
        if(tmp == l.poc ){
          poc = novi;
          tmp2 = novi;
        }
        else{
          tmp2->slj = novi;
          if(tmp != l.krajnji)
          novi->vrijednost = tmp->vrijednost;
          novi->pr = tmp2;
          tmp2 = novi;
          }
          if (tmp == l.tren) tren = novi;
          tmp = tmp ->slj;
    }
    krajnji = tmp2;
    brojEl = l.brojEl;
    index = l.index;
      }
       DvostrukaLista<tip>& operator= (const DvostrukaLista<tip>& l){
       if(this == &l) return *this;
        while(poc != nullptr){
      tren = poc;
      poc = poc->slj;
      delete tren;
    }
    Cvor* tmp(l.poc);
      Cvor* tmp2(nullptr);
      while(tmp != nullptr){
        Cvor* novi (new Cvor);
        novi->slj = nullptr;
        novi->pr = nullptr;
        novi->vrijednost = tip();
        if(tmp == l.poc ){
          poc = novi;
          tmp2 = novi;
        }
        else{
          tmp2->slj = novi;
          if(tmp != l.krajnji)
          novi->vrijednost = tmp->vrijednost;
          novi->pr = tmp2;
          tmp2 = novi;
          }
          if (tmp == l.tren) tren = novi;
          tmp = tmp ->slj;
    }
    krajnji = tmp2;
    brojEl = l.brojEl;
    index = l.index;
        return *this;
    }
  int brojElemenata() const{ return brojEl;}
  
  tip& operator [] (int i){
      if (i >= brojEl || i < 0) throw "Izuzetak";
  Cvor* tmp(tren);
  if(i - 0 < brojEl - i && i - 0 < std::fabs(index - i)){
   tmp = poc;
  for(int j(-1); j<i; j++)
  tmp = tmp->slj;
  }
  else if (brojEl - i > std::fabs(index - i)){
    tmp = krajnji;
    for(int j (brojEl); j > i; j--)
    tmp = tmp->pr;
  }
  else{
  if(index < i){
    for(int j (index); j < i; j++)
    tmp = tmp->slj;
  }
  if(index > i)
    for(int j(index); j > i; j--)
      tmp = tmp ->pr;
  }
  //tren = tmp;
  //index = i;
  return tmp->vrijednost;
  }
  
  tip& operator [] (int i) const {
    
  if (i >= brojEl || i < 0) throw "Izuzetak";
  Cvor* tmp(tren);
  if(i - 0 < brojEl - i && i - 0 < std::fabs(index - i)){
   tmp = poc;
  for(int j(-1); j<i; j++)
  tmp = tmp->slj;
  }
  else if (brojEl - i > std::fabs(index - i)){
    tmp = krajnji;
    for(int j (brojEl); j > i; j--)
    tmp = tmp->pr;
  }
  else{
  if(index < i){
    for(int j (index); j < i; j++)
    tmp = tmp->slj;
  }
  if(index > i)
  for(int j(index); j > i; j--)
  tmp = tmp ->pr;
  }
  //tren = tmp;
  //index = i;
  return tmp->vrijednost;
}

   tip& trenutni () {
    if(brojEl == 0) throw "Izuzetak";
    return tren->vrijednost;
  }
   tip trenutni () const{
    if(brojEl == 0) throw "Izuzetak";
    return tren->vrijednost;
   }
bool prethodni(){
     if (brojEl == 0) throw "Izuzetak";
     if (tren->pr == poc) return false;
     tren = tren->pr;
     index--;
     return true;
  }
  bool sljedeci(){
    if (brojEl == 0) throw "Izuzetak";
    if (tren->slj == krajnji) return false;
    tren = tren->slj;
    index++;
    return true;
    }
  void pocetak(){
    if(brojEl == 0) throw "Izuzetak";
    tren = poc->slj;
    index = 0;
  }
  void kraj(){
    if(brojEl == 0) throw "Izuzetak";
    tren = krajnji->pr;
    index = brojEl - 1;
  }
  void obrisi(){
  if(brojEl == 0) throw "Izuzetak";
  brojEl--;
  Cvor* tmp (tren);
  (tren->pr)->slj = tren->slj;
  (tren->slj)->pr = tren->pr;
  if(tren->slj == krajnji){
  tren = tren->pr;
  index--;
  }
  else
  tren = tren->slj;
  delete tmp;
  }
  void dodajIspred(const tip& el){
    Cvor* novi(new Cvor);
    novi->vrijednost = el;
     if(brojEl == 0){
      novi->slj = krajnji;
      novi->pr = poc;
      poc->slj = novi;
      krajnji->pr = novi;
      tren = novi;
    }else{
      novi->slj = tren;
      novi->pr = tren->pr;
      (tren->pr)->slj = novi;
      tren->pr = novi;
    }
    brojEl++;
    index++;
  }
   void dodajIza(const tip& el){
    Cvor* novi(new Cvor);
    novi->vrijednost = el;
    if(brojEl == 0){
      novi->slj = krajnji;
      novi->pr = poc;
      poc->slj = novi;
      krajnji->pr = novi;
      tren = novi;
      index++;
   }
   else{
      novi->slj = tren->slj;
      novi->pr = tren;
      (tren->slj)->pr= novi;
      tren->slj = novi;
   }
   brojEl++;
   }
   friend class Iterator<tip>;
}; 
template <typename tip>
class Iterator{
  const DvostrukaLista<tip>* d;
  typename DvostrukaLista<tip>::Cvor* tren;
  public:
    Iterator(const Lista<tip>& l){
    if(typeid(l) == typeid(DvostrukaLista<tip>)){
      d = (const DvostrukaLista<tip>*)&l;
      tren = d->tren;
    }
  }
  Iterator (const DvostrukaLista<tip> &dvostrukalista) : d(&dvostrukalista), tren(d->tren) {}

   bool sljedeci(){
    if (d->brojEl == 0) throw "Izuzetak";
    if (tren->slj == d->krajnji) return false;
    tren = tren->slj;
    return true;
    }
   bool prethodni(){
     if (d->brojEl == 0) throw "Izuzetak";
     if (tren->pr == d->poc) return false;
     tren = tren->pr;
     return true;
  }
   void pocetak(){
     if(d->brojEl == 0) throw "Izuzetak";
     tren = d->poc->slj;
   
   }
   void kraj(){
     if(d->brojEl == 0) throw "Izuzetak";
    tren = d->krajnji->pr;
   }
   tip& trenutni () {
    if(d->brojEl == 0) throw "Izuzetak";
    return tren->vrijednost;
  }
   
};

template <typename uporedivtip>
uporedivtip dajMaksimum (const Lista<uporedivtip> &l){
  Iterator<uporedivtip> i(l);
  i.pocetak();
//  std::cout<<"u funkciji"<<std::cout<<i.trenutni()<<std::endl;
  uporedivtip maks =i.trenutni();
  for(int j(1); j<=l.brojElemenata(); j++){
   //  std::cout<<"u funkciji"<<std::cout<<i.trenutni()<<std::endl;
    if(i.trenutni() > maks) maks = i.trenutni();
    i.sljedeci();
  }
  return maks;
}





int main() {
   DvostrukaLista<int> lista;
for (int i(1); i<=5; i++)
	lista.dodajIspred(i);

    // Konstruktor kopije
    DvostrukaLista<int> lista2(lista);
  //  DvostrukaLista<int> lista3;
    // Operator dodjele
    //(lista3=lista).brojElemenata();
    // Destruktivna samododjela
    //(lista=lista).brojElemenata();

    //lista.obrisi();
   // std::cout << lista2.brojElemenata() << " " << lista2[2];
    //std::cout << " " << lista3.brojElemenata() << " " << lista3[2] << " ";

std::cout << lista2.brojElemenata() << " " << lista[2] << " " << dajMaksimum(lista);
return 0;
}