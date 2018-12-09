#include<iostream>
#define vel 1000
template <typename tip>
class Stek {
    public:
  Stek () {}
 virtual ~Stek(){}
 // Stek(const Stek& ) = delete;
 // Stek& operator = (const Stek&) = delete;
 virtual void brisi () = 0;
 virtual void stavi(const tip &el) = 0;
 virtual tip skini() = 0;
 virtual tip& vrh() = 0;
 virtual int BrojElemenata() const = 0;
 };
template <typename tip>
class NizStek : public Stek<tip> {
tip* niz;
int trn;
int kap;
void povecaj (){
    if(trn + 1 == kap  ){
    kap *= 2;
    tip* tmp = new tip [kap];
    for(int i(0); i<trn+1; i++)
    tmp[i] = niz[i];
    delete [] niz;
    niz = tmp;
    }
}
public:
NizStek (): Stek<tip>(), niz(new tip[vel]), trn(-1), kap(vel) {}
~NizStek() { delete [] niz; }
  NizStek(const NizStek<tip>& ) = delete;
  NizStek<tip>& operator = (const NizStek&) = delete;
  void brisi () { trn=-1; }
  void stavi(const tip &el) {
     povecaj();
     niz[++trn]=el;
 }
  tip skini() {
 if( trn == -1) throw "Izuzetak";
 tip el(niz[trn--]);
 return el;    
 }
  tip& vrh() {
     if(trn == -1) throw "Izuzetak";
     return niz[trn];
 }
  int BrojElemenata() const{ return trn+1; }
};


template <typename tip>

class LStek : public Stek<tip> {

 struct Cvor{
  tip vrijednost;
  Cvor* sljedeci;
 };

 int brojEl;
 Cvor* VRH;

    public:
  LStek () : Stek<tip>(), brojEl(0), VRH(0) {}

  ~LStek(){ brisi(); }
  LStek(const LStek<tip> &l ){
   Cvor* tmp (l.VRH);
   Cvor* tmp2 (0);
   
        while(tmp != 0){
            
            Cvor* novi =new Cvor;
            novi->vrijednost = tmp->vrijednost;
           novi->sljedeci = 0;
            
            if (tmp2 == 0){
               VRH = novi; 
            } else {
                tmp2->sljedeci = novi;
            }
            
            tmp2 = novi;
            tmp=tmp->sljedeci;
        }
       //if(brojEl != 0) tmp2->sljedeci = 0;
        brojEl = l.brojEl;
    }
  LStek& operator = (const LStek<tip> &l){
    brisi();
    Cvor* tmp (l.VRH);
    Cvor* tmp2(0);
   
        while(tmp != 0){
            
            Cvor* novi =new Cvor;
            novi->vrijednost = tmp->vrijednost;
            novi->sljedeci = 0;
            
            if (tmp2 == 0){
               VRH = novi; 
            } else {
                tmp2->sljedeci = novi;
            }
            
            tmp2 = novi;
            tmp=tmp->sljedeci;
        }
        //tmp2->sljedeci = 0;
        brojEl = l.brojEl;
        return *this;
    }
  
  void brisi () {
  while (brojEl > 0) 
  skini();
 }
  void stavi(const tip &el) {
  if( brojEl == 0){
   Cvor* novi (new Cvor);
   novi->vrijednost = el;
   novi->sljedeci = 0;
   brojEl++;
   VRH = novi;
   return;
  }
  Cvor* novi (new Cvor);
  novi->vrijednost = el;
  novi->sljedeci= VRH;
  VRH = novi;
  brojEl++;
  return;
 }
 tip skini() {
  if( brojEl == 0) throw "Izuzetak";
  if(brojEl == 1) {
   tip tmp (VRH->vrijednost);
   delete [] VRH;
   VRH = 0;
   brojEl--;
   return tmp;
  }
  Cvor* tmp (VRH->sljedeci);
  tip p_vrijednost (VRH->vrijednost);
  delete [] VRH;
  VRH = tmp;
  brojEl--;
  return p_vrijednost;
 }
  tip& vrh() {
   if (brojEl == 0) throw "Izuzetak";
  return VRH->vrijednost;
 }
  int BrojElemenata() const {
  return brojEl;
 }
 };
 
 bool provjeri_zagrade(std::string tekst){
LStek<char> s;
for(int i(0); i<tekst.length(); i++){
if( tekst[i] == '[' || tekst[i] == '{' || tekst[i] == '(' ){
    s.stavi(tekst[i]);
   }
   if( tekst[i] == ']'){
    if(s.vrh() == '[')
       s.skini();
    else
        return false;
   }
   if( tekst[i] == '}'){
    if(s.vrh() == '{')
       s.skini();
    else
        return false;
   }
   if( tekst[i] == ')'){
    if(s.vrh() == '(')
       s.skini();
    else
        return false;
   }
}
if(s.BrojElemenata() != 0) return false;
return true;
}
 
  int main () {
   std::string tekst( "{}[");
   if(provjeri_zagrade(tekst))
   std::cout<<"ok";
   else
   std::cout<<"ne valja";
   return 0;
  }  
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    