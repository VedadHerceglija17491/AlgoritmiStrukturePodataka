#include <iostream>
#include<utility>
#include<string>
#include<vector>
#include<iomanip>
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
    class AVLStabloMapa : public Mapa<TipKljuca, TipVrijednosti>{
    
    struct Cvor{
        TipVrijednosti vrijednost;
        TipKljuca kljuc;
        Cvor* lijevo; 
        Cvor* desno;
        Cvor* roditelj;// atributi i konstruktor
        int balans;
        Cvor(TipVrijednosti v,TipKljuca k, Cvor* l, Cvor* d, Cvor* r):
        vrijednost(v), kljuc(k), lijevo(l), desno(d), roditelj(r), balans(0){}
            
    };
    
    void provjeri(Cvor* trenutni){
     if(trenutni->roditelj == nullptr){
         
     } 
     
     else if(trenutni->roditelj->lijvo != nullptr && trenutni->roditelj->desno != nullptr) //ako ima brata ili sestru      
     {trenutni->roditelj->balans = 0;}
     else 
     azurirajBalans(trenutni);
    }
    void azurirajBalans(Cvor* trenutni){
          if(trenutni->roditelj == nullptr) return;
          
          if(trenutni->roditelj->lijevo == trenutni)
             trenutni->roditelj.balans++;
          
             else
             trenutni->roditelj.balans--;
          
             if(trenutni->roditelj.balans < -1 || trenutni->roditelj.balans > 1){
             
             if((trenutni->roditelj.balans > 1 && trenutni.balans >0) || (trenutni->roditelj.balans < -1 && trenutni.balans < 0)) // naginju u jednu stranu 
             {
                 if(trenutni->roditelj.balans < -1 && trenutni.balans < 0){ // naginju u desnu jednostruka lijevo
                  Cvor* pom(trenutni->roditelj);
                 
                  trenutni->roditelj = pom->roditelj;
                 
                  pom->desno = trenutni->lijevo;
                  
                  if(pom->desno != nullptr)
                  pom->desno->roditelj = pom;
                 
                  trenutni->lijevo = pom;
                  if(pom->roditelje->lijevo == pom)
                  pom->roditelj->lijevo = trenutni;
                  else
                  pom->roditelj->desno = trenutni;
                  
                  pom->roditelj=trenutni;
            //      pom.balans=0;
              //    trenutni.balans=0;
               
                }
                else
                {//jednostruka desno
                Cvor* pom(trenutni->roditelj);
                 
                  trenutni->roditelj = pom->roditelj;
                 
                  pom->lijevo = trenutni->desno;
                  
                  if(pom->lijvo != nullptr)
                  pom->lijevo->roditelj = pom;
                 
                  trenutni->desno = pom;
                  if(pom->roditelje->lijevo == pom)
                  pom->roditelj->lijevo = trenutni;
                  else
                  pom->roditelj->desno = trenutni;
                 
                  pom->roditelj=trenutni;
                  /*
                  pom.balans=0;
                  trenutni.balans=0;*/
                }
              // return azurirajBalans(trenutni->roditelj);                     
             }
             else
             {
                 if(trenutni.balans>0){ //jednostruka desno
                     Cvor* tren2(trenutni->lijevo);
                     Cvor* pom2(trenutni);
                           
                  tren2->roditelj = pom2->roditelj;
                 
                  pom2->lijevo = tren2->desno;
                  
                  if(pom2->lijvo != nullptr)
                  pom2->lijevo->roditelj = pom2;
                 
                  tren2->desno = pom2;
                  if(pom2->roditelje->lijevo == pom2)
                  pom2->roditelj->lijevo = tren2;
                  else
                  pom2->roditelj->desno = tren2;
                 
                  pom2->roditelj=tren2;
                 //jednostruka lijevo
                  Cvor* pom(trenutni->roditelj);
                   
                   trenutni->roditelj = pom->roditelj;
                 
                  pom->desno = trenutni->lijevo;
                  
                  if(pom->desno != nullptr)
                  pom->desno->roditelj = pom;
                 
                  trenutni->lijevo = pom;
                  if(pom->roditelje->lijevo == pom)
                  pom->roditelj->lijevo = trenutni;
                  else
                  pom->roditelj->desno = trenutni;
                  
                  pom->roditelj=trenutni;
                     
      //               trenutni->lijevo.balans=0;
        //             trenutni.balans = 0;
          //           trenutni->roditelj.balans=0;
                 }
                 else{                              //jednostruka lijevo
                      Cvor* tren2(trenutni->desno);
                      Cvor* pom2(trenutni);
                      
                 tren2->roditelj = pom2->roditelj;
                 
                  pom2->desno = tren2->lijevo;
                  
                  if(pom2->desno != nullptr)
                  pom2->desno->roditelj = pom2;
                 
                  trenutni->lijevo = pom2;
                  if(pom2->roditelje->lijevo == pom2)
                  pom2->roditelj->lijevo = tren2;
                  else
                  pom2->roditelj->desno = tren2;
                  
                  pom2->roditelj=tren2;
                  
                   Cvor* pom(trenutni->roditelj); //jednostruka desno
                   trenutni->roditelj = pom->roditelj;
                 
                  pom->lijevo = trenutni->desno;
                  
                  if(pom->lijvo != nullptr)
                  pom->lijevo->roditelj = pom;
                 
                  trenutni->desno = pom;
                  if(pom->roditelje->lijevo == pom)
                  pom->roditelj->lijevo = trenutni;
                  else
                  pom->roditelj->desno = trenutni;
                 
                  pom->roditelj=trenutni;
                    /*trenutni->desno.balans=0;
                     trenutni.balans = 0;
                     trenutni->roditelj.balans=0;
                  */
                 }
             }
             }
              azurirajBalans(trenutni->roditelj);
    }
    
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
                 provjeri(ko);
                 return;
             } 
             else{
              ko = new Cvor(TipVrijednosti(), klj, nullptr, nullptr,r);
              provjeri(ko);
             }
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
                } else korijen=nullptr; //zbog ovoga  test pado
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
         AVLStabloMapa(): Mapa<TipKljuca,TipVrijednosti>(), korijen(nullptr), brojEl(0){}   // konstruktor
         
          ~AVLStabloMapa(){ //destruktor sve dealocira
           obrisiSve(korijen);    
           }
           
        AVLStabloMapa(const AVLStabloMapa<TipKljuca,TipVrijednosti>& m){ // kopirajuci konstruktor
        korijen=nullptr;
        brojEl=0;
        kopiraj(korijen,m.korijen, nullptr);
        }     
         
        AVLStabloMapa<TipKljuca, TipVrijednosti>& operator =(const AVLStabloMapa<TipKljuca,TipVrijednosti>& m){ //operator dodjele
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
        
        
        TipVrijednosti Korijen(){
            return korijen->vrijednost;
        }
        
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
        
        
        
        
    };
    int main(){
{
  BinStabloMapa <int, int> bm;
clock_t vrijeme1 = clock();
    for (int i (0); i<10000; i++)
    bm[i]=i;
    for(int i(0); i<10000; i=i+23)
    bm.obrisi(i);
    for(int i(0); i<10000; i= i+49)
    bm[i];
 clock_t vrijeme2 = clock();
int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
std::cout << "Vrijeme izvrsenja binstablo mape: " << ukvrijeme << " ms." << std::endl;
}
{
  AVLStabloMapa <int, int> bm;
clock_t vrijeme1 = clock();
    for (int i (0); i<10000; i++)
    bm[i]=i;
    for(int i(0); i<10000; i=i+23)
    bm.obrisi(i);
    for(int i(0); i<10000; i= i+49)
    bm[i];
 clock_t vrijeme2 = clock();
int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
std::cout << "Vrijeme izvrsenja avl mape: " << ukvrijeme << " ms." << std::endl;
}
//IAKO AVLSTABLO NIJE DOBRO IMPLEMENTIRANO U POTPUNOSTI ono je ipak brze od obicnog stabla

    }
    
    
    
    
    
    
    
    
    
    
    