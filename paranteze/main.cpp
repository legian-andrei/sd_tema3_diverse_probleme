#include <fstream>
#include <iostream>
using namespace std;
ifstream in("paranteze.in");
ofstream out("paranteze.out");

bool inchidere(char last, char current){
    if(last == '(' && current == ')'){
        return true;
    } else if(last == '[' && current == ']'){
        return true;
    } else if(last == '{' && current == '}'){
        return true;
    }
    return false;
}

int main()
{
    int n, pozStiva, lungMax = 0, lungimeCurenta = 0;
    in >> n;
    char* stivaParanteze = new char[n + 1];

    /// In vectorul poz retinem pozitia fiecarei paranteze din sirul initial aferente parantelor
    /// din stivaParanteze
    int* poz = new int[n + 1];

    /// In vectorul de booluri valid retinem pozitiile pe care s-au aflat paranteze inchise corect.
    /// Ulterior, pe baza vectorului valid vom calcula secventa de lungime maxima
    bool* valid = new bool[n + 1];
    for(int i = 0; i <= n; i++){
        valid[i] = false;
    }

    /// Punem - pe prima pozitie din vector pentru a nu iesi din stiva in momentul unei comparari
    /// in cazul in care stiva e goala
    stivaParanteze[0] = '-'; poz[0] = 0; pozStiva = 0;

    for(int i = 1; i <= n; i++){
        char parantezaCurenta;
        in >> parantezaCurenta;

        /// Daca ultima paranteza introdusa si paranteza din varful stivei formeaza o inchidere,
        /// atunci marcam in vectorul valid acest lucru si scadem varful stivei. Altfel adaugam
        /// paranteza curenta in varful stivei
        if(inchidere(stivaParanteze[pozStiva], parantezaCurenta)){
            valid[i] = true; valid[poz[pozStiva]] = true;
            pozStiva--;
        }
        else {
            pozStiva++;
            stivaParanteze[pozStiva] = parantezaCurenta;
            poz[pozStiva] = i;
        }
    }

    for(int i = 1; i <= n; i++){
        if(valid[i]){
            lungimeCurenta++;
            if(lungimeCurenta > lungMax)
            {
                lungMax = lungimeCurenta;
            }
        } else {
            lungimeCurenta = 0;
        }
    }
    out << lungMax;
}
