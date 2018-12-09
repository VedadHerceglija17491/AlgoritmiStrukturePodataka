#include <iostream>
#include<iostream>
#define VELICINA_NIZA 1000


template<typename Tip>
class Lista {
  public:
  Lista(){}
  virtual ~Lista(){}
  virtual int brojElemenata() const=0;
  virtual Tip& operator [] (int i) =0;
  virtual const Tip& operator [] (int i) const=0;
  virtual Tip& trenutni () =0;
  virtual Tip trenutni () const=0;
  virtual bool prethodni()=0;
  virtual bool sljedeci()=0;
  virtual void pocetak()=0;
  virtual void kraj()=0;
  virtual void obrisi()=0;
  virtual void dodajIspred(const Tip& el)=0;
  virtual void dodajIza(const Tip& el)=0;
  virtual void ispisUnazad()=0;
};
template <typename Tip>
class JednostrukaLista: public Lista<Tip>{
    struct Cvor{
        Tip el;
        Cvor* sljedeci;
    };
    Cvor* prvi, *posljednji, *t;
    int brojEl;
    public:
    JednostrukaLista(): Lista<Tip>(), prvi(0), posljednji(0), t(0), brojEl(0){}
    ~JednostrukaLista(){
        while(prvi != 0){
            t = prvi; 
            prvi = prvi->sljedeci;
            delete t;
        }
    }
    void ispisUnazad(){
       Tip el1 (trenutni());
       if (!sljedeci()) std::cout<<el1;
       else
       ispisUnazad();
    }

    JednostrukaLista(const JednostrukaLista<Tip>& l){
        Cvor* tmp (l.prvi), tmp2(0);
        while(tmp != 0){
            Cvor* novi =new Cvor;
            novi->el = tmp -> el;
            if (tmp2 == 0){
               prvi = novi; 
            } else {
                tmp2->sljedeci = novi;
            }
            tmp2 = novi;
            if( tmp == l.t){
                t=novi;
            }
            tmp=tmp->sljedeci;
        }
        posljednji = tmp2;
        brojEl = l.brojEl;
    }
    JednostrukaLista<Tip>& operator =(const JednostrukaLista<Tip>& l){
       if(this == &l) return *this;
      while(prvi != 0){
            t = prvi; 
            prvi = prvi->sljedeci;
            delete t;
        }
        Cvor* tmp (l.prvi), tmp2(0);
        while(tmp != 0){
            Cvor* novi =new Cvor;
            novi->el = tmp -> el;
            if (tmp2 == 0){
               prvi = novi; 
            } else {
                tmp2->sljedeci = novi;
            }
            tmp2 = novi;
            if( tmp == l.t){
                t=novi;
            }
            tmp=tmp->sljedeci;
        }
        posljednji = tmp2;
        brojEl = l.brojEl;
    return *this;
    }
    int brojElemenata() const { return brojEl; }
  virtual Tip& operator [] (int i){
      if(i<0 || i>= brojEl) throw "Izuzetak";
      Cvor* tmp(prvi);
      for(int j(0); j<i; j++)
         tmp=tmp->sljedeci;
         return tmp->el;
  }
  virtual const Tip& operator [] (int i) const {
      if(i<0 || i>= brojEl) throw "Izuzetak";
      Cvor* tmp(prvi);
      for(int j(0); j<i; j++)
         tmp=tmp->sljedeci;
         return tmp->el;
  }
  virtual Tip& trenutni () {
      if(prvi==0) throw "Izuzetak";
      return t->el;
  }
  virtual Tip trenutni () const{
      if(prvi==0) throw "Izuzetak";
      return t->el;
  }
  virtual bool prethodni(){
      if(prvi == 0) throw "Izuzetak";
      if(t == prvi) return false;
       Cvor* tmp(prvi);
      while(tmp->sljedeci != t)
         tmp = tmp->sljedeci;
      t = tmp;
      return true;
  }
  virtual bool sljedeci(){
      if(prvi == 0) throw "Izuzetak";
      if(t->sljedeci == 0) return false;
      t = t->sljedeci;
      return true;
  }
  virtual void pocetak(){
       if(prvi == 0) throw "Izuzetak";
       t=prvi;
  }
  virtual void kraj(){
       if(prvi == 0) throw "Izuzetak";
       t=posljednji;
  }
  virtual void obrisi(){
      if(prvi == 0) throw "Izuzetak";
      brojEl--;
      if(t == prvi){
          prvi=prvi->sljedeci;
          delete t;
          t = prvi;
          if (brojEl == 0) posljednji=0;
      } else {
       Cvor* tmp(prvi);
      while(tmp->sljedeci != t)
         tmp = tmp->sljedeci;
         tmp->sljedeci=t->sljedeci;
         delete t;
         t=tmp->sljedeci;
         if( t == 0)
         posljednji = t = tmp;
           }
  }
  virtual void dodajIspred(const Tip& el){
      Cvor* novi =new Cvor;
      novi->el= el;
      brojEl++;
     if(prvi == 0) {
          prvi = posljednji = t = novi;
          novi->sljedeci=0;
          }  else if( t== prvi){
          novi->sljedeci = prvi;
          prvi=novi;
          }else {
          Cvor* tmp(prvi);
      while(tmp->sljedeci != t)
         tmp = tmp->sljedeci;
         novi->sljedeci = tmp->sljedeci;
         tmp->sljedeci=novi;
       }  
       
    }
  virtual void dodajIza(const Tip& el){
      Cvor* novi =new Cvor;
      novi->el= el;
      brojEl++;
      if(prvi == 0) {
          prvi = posljednji = t = novi;
          novi->sljedeci=0;
      } else {
         novi->sljedeci = t->sljedeci;
         t->sljedeci=novi;
         if(posljednji == t)
         posljednji=novi;
      }
  }
  
};

    

int main() {
      Lista<int>* l;
      l = new JednostrukaLista<int>;
      for(int i(0); i<100; i++)
      l->dodajIza(i+1);
      l->ispisUnazad();
   
}