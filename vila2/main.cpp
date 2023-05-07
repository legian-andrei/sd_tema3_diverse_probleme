#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

ifstream in("vila2.in");
ofstream out("vila2.out");

int main()
{
    int nrVecini, distantaMax, difVarstaMax = 0;
    in >> nrVecini >> distantaMax;

    int varste[nrVecini];
    for(int i = 0; i < nrVecini; i++){
        varste[i] = 0;
    }
    deque<int> minime, maxime;

    for(int i = 0; i < nrVecini; i++){
        in >> varste[i];

        /// Verific daca vecinul de pe prima pozitie din minime si maxime e prea departe de
        /// solarianul actual
        if(!minime.empty() && minime.front() == i - distantaMax - 1){
            minime.pop_front();
        }
        if(!maxime.empty() && maxime.front() == i - distantaMax - 1){
            maxime.pop_front();
        }

        /// In minime pastrez doar vecinii mai tineri decat solarianul actual, astfel incat
        /// pe prima pozitie se va afla mereu solarianul cu varsta minima din intervalul dat
        while(!minime.empty() && varste[minime.back()] >= varste[i]){
            minime.pop_back();
        }

        /// In maxime pastrez doar vecinii mai batrani decat solarianul actual, astfel incat
        /// pe prima pozitie se va afla mereu solarianul cu varsta maxima din intervalul dat
        while(!maxime.empty() && varste[maxime.back()] <= varste[i]){
            maxime.pop_back();
        }

        minime.push_back(i); maxime.push_back(i);

        /// Calculez si retin maximul modulului diferentei de varsta dintre vecini
        if(i >= distantaMax && difVarstaMax < varste[maxime.front()] - varste[minime.front()]){
            difVarstaMax = varste[maxime.front()] - varste[minime.front()];
        }
    }
    out << difVarstaMax;
    return 0;
}
