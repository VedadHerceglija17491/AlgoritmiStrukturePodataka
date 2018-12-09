#include <iostream>
#include<utility>
#include<string>
#include<vector>
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


   template <typename TipKljuca, typename TipVrijednosti>
    class BinStabloMapa : public Mapa<TipKljuca, TipVrijednosti>{
    
    struct Cvor{
        TipVrijednosti vrijednost;
        TipKljuca kljuc;
        Cvor* lijevo;
        Cvor* desno;
        Cvor* roditelj;// atributi i konstruktor
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
    
    void umetni (Cvor*& ko, TipKljuca klj, Cvor* r){ //koristimo referencuu
         //nasli smo mjesto gdje treba umetnuti cvor
         if(ko == nullptr){
             
      
             
             if(brojEl == 0){   // provjeravamo je li prvi element
                 ko = new Cvor(TipVrijednosti(), klj, nullptr, nullptr,nullptr);
                 return;
             } 
             else
              
              ko = new Cvor(TipVrijednosti(), klj, nullptr, nullptr,r);
               brojEl++;
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
                } else korijen=nullptr; //zbog ovoga 8 test pado
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
        
    Cvor* rekurzija(Cvor* c, const TipKljuca &k){
// Terminiranje rekurzije - ovdje nema trazenog kljuca
	if (c==0) return 0; 

	// Ako je cvor veci ili jednak k, rjesenje je sigurno u lijevom podstablu
	if (c->kljuc >= k)
		return rekurzija(c->lijevo, k);

	// Ako je manji, postoje dvije mogucnosti:
	// 1. rjesenje je u desnom podstablu
	// 2. c je rjesenje
	Cvor* rez = rekurzija(c->desno, k);
	// Ako je rez=0, nije pronadjen nijedan cvor manji od k
	if (rez==0) return c;
	return rez;
    }
        
    TipVrijednosti prviManji(TipKljuca kljuc){
    
  // Pomocna funkcija "rekurzija" vraca 0 ako ne postoji kljuc manji od datog
	Cvor* rez = rekurzija(korijen, kljuc);

	if (rez==0) // Ovo niste morali uraditi na ispitu
		throw "Argument je manji ili jednak najmanjem kljucu u stablu";
	return rez->vrijednost;
    
    }
    void pom(Cvor* c, vector<TipKljuca> &v, int n){
        if(c == nullptr) return;
        
        if(n == 1)
        {
            v.push_back(c->kljuc);
            return;
        }
        pom(c->desno, v, n-1);
        pom(c->lijevo, v, n-1);
    }
    int zad2(){
        int n(1);
        vector<TipKljuca> v;
        for(;;)
        {
            vector<TipKljuca> v1;
            pom(korijen, v1, n);
            if(v1.size() > v.size()) v= v1;
            n++;
            if(v1.size() == 0) break;
        }
        return v.size();
    }
        
    };
    
    int main(){
BinStabloMapa <int, int> m;
m[7] = 1;
m[25] = 2;
m[13] = 3;
m[1] = 4;
m[87] = 5;
m[12] = 6;
m[93] = 7;
m[45] = 8;
m[78] = 9;
m[3] = 10;
cout<<m.prviManji(46)<<endl;
cout<<m.zad2();
        return 0;
    }
    
    
    
    
    
    
    
    
    
    
    