#include <iostream>
#include <fstream>
#include <string>
#include <deque>

using namespace std;

ifstream in("alibaba.in");
ofstream out("alibaba.out");

int main()
{
    int nrCifre, deTaiat, cifreTaiate = 0;
    in >> nrCifre >> deTaiat;
    string numarInitial;
    getline(in, numarInitial);
    getline(in, numarInitial);
    deque<int> numarFinal;

    for(int i = 0; i < nrCifre; i++){
        /// Pe masura ce parcurg numarul initial, sterg cifrele mai mici decat cifra actuala din coada numarului final
        while(!numarFinal.empty() && cifreTaiate < deTaiat && numarInitial[i] - '0' > numarFinal.back()){
            numarFinal.pop_back();
            cifreTaiate++;
        }
        numarFinal.push_back(numarInitial[i] - '0');
    }

    /// Daca totusi mai am de sters, o fac din capatul numarului final
    while(cifreTaiate < deTaiat){
        numarFinal.pop_back();
        cifreTaiate++;
    }

    for(int cifra: numarFinal){
        out << cifra;
    }
    return 0;
}
