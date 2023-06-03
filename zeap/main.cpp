#include <fstream>
#include <set>
#include <string>
#include <limits.h>
#include <iterator>

using namespace std;

ifstream in("zeap.in");
ofstream out("zeap.out");

set<int> zeap;
/// minDif are diferenta minima din zeap drept first si valorile din care este obtinut ca pereche in second
pair<int, pair<int, int>> minDif;

void insereaza(int toBeInserted) {
    if (zeap.find(toBeInserted) == zeap.end()) {
        zeap.insert(toBeInserted);

        /// Daca zeap-ul are doar 2 elemente, inseamna ca diferenta minima dintre elementele zeap-ului e chiar diferenta dintre cele 2 elemente
        if(zeap.size() == 2) {
            minDif = make_pair(*(zeap.rbegin()) - *(zeap.begin()), make_pair(*(zeap.rbegin()), *(zeap.begin())));
        } else if (zeap.size() > 2) {
            /// Daca zeap-ul contine mai mult de 2 elemente, atunci diferenta minima se poate afla doar intre
            /// numarul introdus si urmatorul sau numarul intodus si precedentul
            auto poz = zeap.find(toBeInserted);
            auto nextPoz = next(poz);
            auto prevPoz = prev(poz);
            if (poz != zeap.begin() && *poz - *prevPoz < minDif.first) {
                minDif = make_pair(*poz - *prevPoz, make_pair(*prevPoz, *poz));
            }
            if (nextPoz != zeap.end() && *nextPoz - *poz < minDif.first) {
                minDif = make_pair(*nextPoz - *poz, make_pair(*poz, *nextPoz));
            }
        }
    }
}

string sterge(int toBeDeleted) {
    if (zeap.find(toBeDeleted) == zeap.end()) {
        return "-1";
    } else if (minDif.second.first == toBeDeleted || minDif.second.second == toBeDeleted) {
        /// Daca elementul sters face parte din minDif, inlocuim minDif cu valoarea "default"
        minDif = make_pair(INT_MAX, make_pair(0,0));
        zeap.erase(toBeDeleted);
    }


    return "";
}

int cauta(int searchNum) {
    if (zeap.find(searchNum) == zeap.end()) {
        return 0;
    } else {
        return 1;
    }
}

int max_dif(){
    if (zeap.size() < 2) {
        return -1;
    } else {
        /// Elementele dintr-un set fiind sortate crescator, cea mai mare diferenta va fi intre primul si ultimul element
        return *(zeap.rbegin()) - *(zeap.begin());
    }
}

int min_dif(){
    if (zeap.size() < 2) {
        return -1;
    } else if (minDif.first == INT_MAX) {
        /// Daca valoarea minDif este cea "default", atunci recalculam diferenta minima
        for (auto curr = zeap.begin(); curr != zeap.end(); curr++){
            if (curr != zeap.begin()) {
                auto left = prev(curr);
                if (*curr - *left < minDif.first){
                    minDif = make_pair(*curr - *left, make_pair(*curr, *left));
                }
            }
        }
    }

    return minDif.first;
}

int main()
{

    minDif = make_pair(INT_MAX, make_pair(0,0));
    string option;
    int param;
    while (in >> option) {
        if (option == "I") {
            in >> param;
            insereaza(param);
        } else if (option == "S") {
            in >> param;
            string rez = sterge(param);
            if (!rez.empty()) {
                out << rez << endl;
            }
        } else if (option == "C") {
            in >> param;
            out << cauta(param) << endl;
        } else if (option == "MAX") {
            out << max_dif() << endl;
        } else if (option == "MIN") {
            out << min_dif() << endl;
        }
    }
    return 0;
}
