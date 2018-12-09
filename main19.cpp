#include <iostream>
#include<utility>
#include<string>
#include<functional>
using namespace std;

template<typename TipKljuca, typename TipVrijednosti>
class Mapa{
  public:
  Mapa(){}
  virtual ~Mapa(){}
  virtual TipVrijednosti& operator [] (TipKljuca i) =0;
  virtual const TipVrijednosti operator [] (TipKljuca i) const=0;
  virtual int brojElemenata() const=0;
  virtual void obrisi()=0;
  virtual void obrisi(const TipKljuca& kljuc) =0;
  };

    template<typename TipKljuca, typename TipVrijednosti>
    class NizMapa : public Mapa<TipKljuca, TipVrijednosti>{
    std::pair<TipKljuca, TipVrijednosti>** niz;
    int kap, brojEl;
     void povecaj(){   
        if(brojEl == kap){
        kap*=2;
        std::pair<TipKljuca,TipVrijednosti>** niz2 =new std::pair<TipKljuca,TipVrijednosti>*[kap];
        for(int i(0); i<brojEl; i++)
           niz2[i]=niz[i];
           for(int i(brojEl); i<kap; i++)
           niz2[i] = nullptr;
        delete[] niz;
        niz=niz2;
                  }
     }
     public:
     NizMapa(): Mapa<TipKljuca,TipVrijednosti>(), niz(new std::pair<TipKljuca,TipVrijednosti>*[100]), kap(100), brojEl(0){
         for(int i(0); i<kap; i++)
         niz[i] = nullptr;
     }
    ~NizMapa(){
        for (int i(0); i<brojEl; i++)
            delete niz[i];
        delete[] niz;
    }
    NizMapa(const NizMapa<TipKljuca,TipVrijednosti> &l){
        kap=l.kap;
        brojEl=l.brojEl;
        niz=new std::pair<TipKljuca,TipVrijednosti>* [l.kap];
        for(int i(0); i<l.brojEl; i++)
        niz[i]=new std::pair<TipKljuca,TipVrijednosti> (*l.niz[i]);
        for(int i(l.brojEl); i<l.kap; i++)
        niz[i] = nullptr;
    }
     NizMapa<TipKljuca,TipVrijednosti>& operator= (const NizMapa<TipKljuca,TipVrijednosti>& n){
       if(this == &n) return *this;
       for (int i(0); i<brojEl; i++)
            delete niz[i];
        delete[] niz;
        kap=n.kap;
        brojEl=n.brojEl;
        niz=new std::pair<TipKljuca,TipVrijednosti>*[n.kap];
        for(int i(0); i<n.brojEl; i++)
        niz[i]=new std::pair<TipKljuca,TipVrijednosti> (*n.niz[i]);
        for(int i(n.brojEl); i<n.kap; i++)
        niz[i] = nullptr;
        return *this;
    }
     int brojElemenata() const{
      return brojEl;
  }
  
   TipVrijednosti& operator [] (TipKljuca a) {
     for(int i(0); i<brojEl; i++){
       if(niz[i]->first == a) return niz[i]->second;
     }
     brojEl++;
     povecaj();
     niz[brojEl-1] = new std::pair<TipKljuca, TipVrijednosti> (std::make_pair(a, TipVrijednosti()));
     return niz[brojEl-1]->second;
   }
     const TipVrijednosti operator [] (TipKljuca a) const{
     
       for(int i(0); i<brojEl; i++){
       if(niz[i]->first == a) return niz[i]->second;
     }
     return TipVrijednosti();
   }

      void obrisi(){
      if(brojEl == 0) return;
       for (int i(0); i<brojEl; i++){
            delete niz[i];
            niz[i] = nullptr;
       }
        brojEl = 0;
     }
    void obrisi(const TipKljuca& kljuc) {
      if(brojEl == 0) return;
        for(int i(0); i<brojEl; i++){
       if(niz[i]->first == kljuc){
      brojEl--;
      delete niz[i];
      niz[i] = nullptr;
      for(int j(i); j<brojEl; j++)
      niz[j]=niz[j+1];
      niz[brojEl] = nullptr;
      break;
    }
            }
       return;
    }
    };
   
    template <typename TipKljuca, typename TipVrijednosti>
    class BinStabloMapa : public Mapa<TipKljuca, TipVrijednosti>{
    struct Cvor{
        TipVrijednosti vrijednost;
        TipKljuca kljuc;
        Cvor* lijevo;
        Cvor* desno;
        Cvor* roditelj;
        Cvor(TipVrijednosti v,TipKljuca k, Cvor* l, Cvor* d, Cvor* r):
        vrijednost(v), kljuc(k), lijevo(l), desno(d), roditelj(r){}
    };
    Cvor* korijen;
    int brojEl;
    
    Cvor * trazi(Cvor* ko, TipKljuca klj){
         if(ko == nullptr) return nullptr; // da ne bi porgram krahirao
        if( klj == ko->kljuc) // ako smo nasli ili dosli do nullptr
        return ko;
        if(ko->kljuc > klj) return trazi(ko->lijevo, klj);
        else return trazi(ko->desno, klj);
    }
      Cvor* traziconst (Cvor* ko, TipKljuca klj) const{ 
         if(ko == nullptr) return nullptr; // da ne bi porgram krahirao
        if( klj == ko->kljuc) // ako smo nasli ili dosli do nullptr
        return ko;
        if(ko->kljuc > klj) return traziconst(ko->lijevo, klj);
        else return traziconst(ko->desno, klj);
    }
    
    void umetni (Cvor*& ko, TipKljuca klj, Cvor* r){
         //nasli smo mjesto gdje treba umetnuti cvor
         if(ko == nullptr){
             brojEl++;
             if(brojEl == 0){   // provjeravamo je li prvi element
                 ko = new Cvor(TipVrijednosti(), klj, nullptr, nullptr,nullptr);
                 return;
             } 
             else
              ko = new Cvor(TipVrijednosti(), klj, nullptr, nullptr,r);
              return;
              }
        if( klj == ko->kljuc) // ako postoji cvor  tim
        return;
        if(ko->kljuc > klj) return umetni(ko->lijevo, klj,ko);
        else return umetni(ko->desno, klj, ko);
    }
       void obrisiSve(Cvor *c){
            if(c == nullptr) return;
             obrisiSve(c->lijevo);
             obrisiSve(c->desno);
             delete c;
             brojEl--;
         
        }
         void obrisiPom(Cvor* c){
                   if(c == nullptr) return; // ako je nullptr da ne bi slucajno krahiro
            if(c->lijevo == nullptr && c->desno== nullptr){ // slucaj kada nema djece
                if(c->roditelj != nullptr){ // ako ima roditelja
                
                
                if(c == c->roditelj->lijevo)// ako je lijevo dijete
                c->roditelj->lijevo = nullptr;
                else
                c->roditelj->desno = nullptr;
                }
                delete c;
                brojEl--;
            }
            else if(c->lijevo != nullptr && c->desno != nullptr){ // ako ima i lijevo i desno podstablo
               Cvor* tmp = c->lijevo;//idemo u lijevo pod stablo
               
               while( tmp->desno != nullptr) // tmp je najdesniji cvor u lijevom pod stablu
               tmp = tmp->desno;
                
                c->kljuc = tmp->kljuc; //mjenjamo kljuc i vrijednost cvorova
                c->vrijednost = tmp->vrijednost;
                obrisiPom(tmp); // brisemo sada cvor
                
            } else { // cvor ima jedno dijete ne znamo koje
                Cvor* dijete = c->lijevo; // predpostavimo da je lijevvo
                if(dijete == nullptr) dijete = c->desno; // ako nije lijevo onda je desno
               
                 if(c->roditelj != nullptr){ // ako ima roditelja
               
               
                 if(c == c->roditelj->lijevo) // ako je c lijevo dijete
                c->roditelj->lijevo = dijete; 
                else
                c->roditelj->desno = dijete;
                 } else korijen = dijete;
                 
                 
                dijete->roditelj = c->roditelj; // preusmjeravo covo dijete da mu je roditelj njegov "dedo"
                delete c;
                brojEl--;
            }
         }
         
        void kopiraj(Cvor*& cOvaj, Cvor* cDrugi, Cvor* roditelj){ // cOvaj u koji se kopira 
        if(cDrugi == nullptr) return;  //ako se nema sta kopirat  
        cOvaj = new Cvor(cDrugi->vrijednost, cDrugi->kljuc, nullptr, nullptr, roditelj);   
        kopiraj(cOvaj->lijevo,cDrugi->lijevo, cOvaj);
        kopiraj(cOvaj->desno,cDrugi->desno, cOvaj);
        brojEl++;    
        }   
      TipVrijednosti& pom1 (Cvor*& ko, TipKljuca klj, Cvor* r){
        if(ko == nullptr){
              ko= new Cvor(TipVrijednosti(),klj,nullptr,nullptr,r);
              brojEl++;
        }
        if( klj == ko->kljuc) // ako smo nasli ili dosli do nullptr
        return ko->vrijednost;
        if(ko->kljuc > klj) return pom1(ko->lijevo, klj,ko);
        else return pom1(ko->desno, klj,ko);
    } 
     
     
         
         
         public:
         BinStabloMapa(): Mapa<TipKljuca,TipVrijednosti>(), korijen(nullptr), brojEl(0){}   // konstruktor
         
          ~BinStabloMapa(){ //destruktor sve dealocira
           obrisiSve(korijen);    
           }
           
        BinStabloMapa(const BinStabloMapa<TipKljuca,TipVrijednosti>& m){ // kopirajuci konstruktor
        korijen=nullptr;
        brojEl=0;
        kopiraj(korijen,m.korijen, nullptr);
        }     
         
        BinStabloMapa<TipKljuca, TipVrijednosti>& operator =(const BinStabloMapa<TipKljuca,TipVrijednosti>& m){ //operator dodjele
            if(this == &m) return *this;// zastita od destrukticne samododjele
            obrisiSve(korijen);
            korijen = nullptr;
            kopiraj(korijen,m.korijen, nullptr);
            return *this;
        }  
         int brojElemenata() const{ return brojEl; }
     
              TipVrijednosti& operator []( TipKljuca kljuc){
              return pom1(korijen,kljuc,nullptr);
              }
        
        
        
        const TipVrijednosti operator []( TipKljuca kljuc) const {
            Cvor* c = traziconst(korijen,kljuc);
            if(c == nullptr){
                return TipVrijednosti();
            }else{
                return c->vrijednost;
            }
        }
         void obrisi(){
            obrisiSve(korijen);
            korijen= nullptr;
            brojEl=0;
        }
           void obrisi(const TipKljuca& kljuc){
            Cvor* c= trazi(korijen, kljuc);
            if(c==nullptr) return;
            obrisiPom(c);
        }
        
        
        
        
    };
    
    
    template<typename TipKljuca, typename TipVrijednosti>
    class  HashMapa : public Mapa<TipKljuca, TipVrijednosti>{
    std::pair<TipKljuca, TipVrijednosti>** niz;
    
    unsigned int kap, brojEl;
   
    function <unsigned int(TipKljuca, unsigned int)> f;
    
    std::pair<TipKljuca, TipVrijednosti> prazan;
    
     void povecaj(){   
        if(brojEl >= kap *0.66){
        unsigned int starikap(kap);
        kap*=2;
        std::pair<TipKljuca,TipVrijednosti>** niz2 =new std::pair<TipKljuca,TipVrijednosti>*[kap];
        for(int i(0); i<starikap; i++)
           niz2[i]=niz[i];
           for(int i(starikap); i<kap; i++)
           niz2[i] = nullptr;
        delete[] niz;
        niz=niz2;
                  }
     }
    
     unsigned int HashUmetni(TipKljuca k){
         unsigned int i(0);
         unsigned int j (f(k,kap));
         while(i < kap){
             j+=i;
             if(j == kap) j=j-kap;
              if(j>= kap || j<0) return 0;
               if(niz[j] == nullptr) return j;
               if(niz[j] == &prazan) return j;

               i++;
         }
         return 256;
     }
      unsigned int HashTrazi( TipKljuca k) const {
         unsigned int i(0);
         unsigned int j(f(k,kap));
         while(i<kap){
             j+=i;
             if(j == kap) j=j-kap;
             if(j>= kap || j<0) return 0;
             if(niz[j] == nullptr) return j;
             if(niz[j]->first == k) return j;
             i++;
         }
         return 256; 
     }
     
     public:
      HashMapa():  Mapa<TipKljuca,TipVrijednosti>(), niz(new std::pair<TipKljuca,TipVrijednosti>*[1000000]), kap(1000000), brojEl(0), f(nullptr) {
          prazan.first=TipKljuca();
          prazan.second= TipVrijednosti();
         for(int i(0); i<kap; i++)
         niz[i] = nullptr;
     }
      
      ~HashMapa(){
        for (int i(0); i<kap; i++)
            delete niz[i];
        delete[] niz;
      }
      
        HashMapa(const HashMapa<TipKljuca,TipVrijednosti> &l){
             prazan.first=TipKljuca();
          prazan.second= TipVrijednosti();
        kap=l.kap;
        brojEl=l.brojEl;
        f=l.f;
        niz=new std::pair<TipKljuca,TipVrijednosti>* [l.kap];
        for(int i(0); i<l.kap; i++){
        if(l.niz[i] == nullptr)
          niz[i] = nullptr;
          else
         niz[i]=new std::pair<TipKljuca,TipVrijednosti> (*l.niz[i]);
        }
    }
     HashMapa<TipKljuca,TipVrijednosti>& operator= (const HashMapa<TipKljuca,TipVrijednosti>& n){
       if(this == &n) return *this; //samododjela
       for (int i(0); i<kap; i++)
            delete niz[i];
        delete[] niz;
        
        prazan.first=TipKljuca();
        prazan.second= TipVrijednosti();
        kap=n.kap;
        brojEl=n.brojEl;
        f=n.f;
        niz=new std::pair<TipKljuca,TipVrijednosti>* [n.kap];
        for(int i(0); i<n.kap; i++){
        if(n.niz[i] == nullptr)
          niz[i] = nullptr;
          else
         niz[i]=new std::pair<TipKljuca,TipVrijednosti> (*n.niz[i]);
        }
        return *this;
    }
      int brojElemenata() const{
      return brojEl;
  }
  void definisiHashFunkciju ( function <unsigned int(TipKljuca, unsigned int)> f1){
      f=f1;
      }
    
     
TipVrijednosti& operator [] (TipKljuca a) {
     if(f == nullptr) throw "Izuzetak";
     unsigned int j(HashTrazi(a));
    if( niz[j] != nullptr) return niz[j] ->second;
    else {
     brojEl++;
     povecaj();
     j=HashUmetni(a);
     niz[j] = new std::pair<TipKljuca, TipVrijednosti> (std::make_pair(a, TipVrijednosti()));
     return niz[j]->second;
    }
   }
    const TipVrijednosti operator [] (TipKljuca a) const{
         if(f == nullptr) throw "Izuzetak";
       unsigned int j (HashTrazi(a));
       if(niz[j] != nullptr/* && niz[j] != &prazan*/)  return niz[j]->second;
      
     return TipVrijednosti();
   }
     void obrisi(){
      if(brojEl == 0) return;
      int brojac(0);
       for (int i(0); i<kap; i++){
           if(niz[i] != nullptr && niz[i] != &prazan){
             brojac++;
            delete niz[i];
            niz[i] = nullptr;
           }
           if(niz[i] == &prazan)
           niz[i] = nullptr;
           if (brojac == brojEl) break;
       }
        brojEl = 0;
     }
       void obrisi(const TipKljuca& kljuc) {
      if(brojEl == 0) return;
      unsigned int j(HashTrazi(kljuc));
        if(niz[j] != nullptr){
       brojEl--;
      delete niz[j];
      niz[j] = &prazan;
        }
     return;
    }
    };

int main() {
 



NizMapa<std::string,std::string> m;
m["Sarajevo"] = "BiH";
m["Zagreb"] = "Hrvatska";
{
        // Konstruktor kopije
	NizMapa<std::string,std::string> m2(m);
        // Operator dodjele
	NizMapa<std::string,std::string> m3;
	m3["Kiseljak"] = "BiH";
	cout << (m3=m).brojElemenata() << " "; // 2
        // Destruktivna samododjela
	cout << (m=m).brojElemenata() << " "; // 2

        // Plitka kopija
	m.obrisi("Sarajevo");
	cout << m2.brojElemenata() << " "; // 2
        cout << m2["Sarajevo"] << " "; // BiH
        cout << m3.brojElemenata() << " "; // 2
        cout << m3["Sarajevo"] << " "; // BiH
}
cout << m.brojElemenata(); // 1
cout << " '" << m["Sarajevo"] << "' "; // ''
m.obrisi();
cout << m.brojElemenata(); // 0
cout << " '" << m["Zagreb"] << "'"; // ''
}