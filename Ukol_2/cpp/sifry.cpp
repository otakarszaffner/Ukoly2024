#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;
// funkce pro otevreni souboru
string otevri_soubor(const string &jmeno_souboru)
{
  string text;
  char tmp;
  // otevru soubor
  ifstream f(jmeno_souboru, ifstream::in);

// kontrola jestli se soubor otevrel
  if (!f.is_open()){
    cerr << "Soubor " << jmeno_souboru << " se nepodarilo otevrit." << endl; // kdyz se soubor neotevre, kod ukoncim a vypisu chybovou spravu
    exit(1);
  }
// nacteni souboru do stringu
  while(f.get(tmp)){
    text += tmp;
  }
  // zavru soubor
  f.close();
  return text;
}
// Caesarova šifra
string caesar_sifra(const string &text, int posun, bool sifrovat)
{
  string upravenytext = text;
  // sifruju
  if(sifrovat == true){
    for(int i = 0; i < text.length(); i++){
      // pokud bych posunutim vysel z range pismen v ascii, odectu 26, abych v nem zustal
      if(isalpha(text[i] + posun)){
        upravenytext[i] = text[i] + posun;
      }else{
        upravenytext[i] = text[i] + posun - 26;
      }
    }

  // desifruju
  }else{
    for(int i = 0; i < text.length(); ++i){
      // stejne jako u sifrovani, akorat pricitam 26
      if(isalpha(text[i] - posun)){
        upravenytext[i] = text[i] - posun;
      }else{
        upravenytext[i] = text[i] - posun + 26;
      }
    }
  }
  return upravenytext;
}
// Vigenerova šifra
string vigener_sifra(const string &text, const string &klic, bool sifrovat)
{
  string upravenytext = text;
  int posun = 0;

  // sifruju
  if(sifrovat == true){
    for(int i = 0; i < text.length(); i++){
      if(isupper(klic[i])){
        posun = klic[i] - 65;
      }else{  
        posun = klic[i] - 97;
      }
      if(isalpha(text[i] + posun)){
        upravenytext[i] = text[i] + posun;
      }else{
        upravenytext[i] = text[i] + posun - 26;
      }
    }

  // desifruju
  }else{
    for(int i = 0; i < text.length(); i++){
      if(isupper(klic[i])){
        posun = klic[i] - 65;
      }else{  
        posun = klic[i] - 97;
      }
      if(isalpha(text[i] - posun)){
        upravenytext[i] = text[i] - posun;
      }else{
        upravenytext[i] = text[i] - posun + 26;
      }
    }
  }
  return upravenytext;
}
// XOR šifra
string xor_sifra(const string &text, const string &klic, bool sifrovat)
{
  string upravenytext = text;

  for(int i = 0; i < text.length(); ++i){
    upravenytext[i] = text[i] ^ klic[i % klic.length()]; // ^ operator pro binarni XOR
  }

  return upravenytext;
}

// Funkce pro uložení řetězce do souboru
void uloz_do_souboru(const string &jmeno_souboru, const string &obsah)
{
  // otevru soubor pro zapisovani, pokud neexistuje tak ho vytvorim
  ofstream MyFile(jmeno_souboru);

  // zapisu do souboru
  MyFile << obsah;

  // zavru soubor
  MyFile.close();
}

#ifndef __TEST__ // Add this preprocessor guard
int main(){
  // Načtení vstupního souboru
  string vstupni_text = otevri_soubor("vstup.txt");

  // Šifrování textu pomocí Caesarovy šifry
  string sifrovany_text_caesar = caesar_sifra(vstupni_text, 3, true);
  cout << sifrovany_text_caesar << endl;

  // Šifrování textu pomocí Vigenerovy šifry
  string sifrovany_text_vigener = vigener_sifra(vstupni_text, "MNOPQRSTUVWZABCDEFGHIJKLabcdefghijklmnoprqrstuwz", true);
  cout << sifrovany_text_vigener << endl;

  // Šifrování textu pomocí XOR šifry
  string sifrovany_text_xor = xor_sifra(vstupni_text, "heslo", true);
  cout << sifrovany_text_xor << endl;

  // Uložení šifrovaných textů do souborů
  uloz_do_souboru("sifrovany_caesar.txt", sifrovany_text_caesar);
  uloz_do_souboru("sifrovany_vigener.txt", sifrovany_text_vigener);
  uloz_do_souboru("sifrovany_xor.txt", sifrovany_text_xor);

  // Dešifrování textů
  cout << "Dešifrovany text pomocí Caesarovy šifry: " << caesar_sifra(otevri_soubor("sifrovany_caesar.txt"), 3, false) << endl;
  cout << "Dešifrovany text pomocí Vigenerovy šifry: " << vigener_sifra(otevri_soubor("sifrovany_vigener.txt"), "MNOPQRSTUVWZABCDEFGHIJKLabcdefghijklmnoprqrstuwz", false) << endl;
  cout << "Dešifrovany text pomocí XOR šifry: " << xor_sifra(otevri_soubor("sifrovany_xor.txt"), "heslo", false) << endl;

  return 0;
} 
#endif // __TEST__
