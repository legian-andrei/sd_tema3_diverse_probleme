#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

ifstream in("branza.in");
ofstream out("branza.out");

int main()
{
    long long nrSaptamani, pretSaptamana, termenValabilitate, costTotal = 0, cantitate;
    in >> nrSaptamani >> pretSaptamana >> termenValabilitate;

    long long costProducere[nrSaptamani];
    for(int i = 0; i < nrSaptamani; i++){
        costProducere[i] = 0;
    }
    deque <long long> stocBranza;

    for(int saptamanaActuala = 0; saptamanaActuala < nrSaptamani; saptamanaActuala++){
        in >> costProducere[saptamanaActuala] >> cantitate;

        /// Daca branza pe care o avem deja in depozit a expirat, o aruncam
        while(!stocBranza.empty() && stocBranza.front() < saptamanaActuala - termenValabilitate){
            stocBranza.pop_front();
        }
        /// Daca branza pe care o avem deja in depozit e mai scumpa de tinut decat sa producem una proaspata o aruncam
        while(!stocBranza.empty() && costProducere[stocBranza.back()] + (saptamanaActuala - stocBranza.back()) * pretSaptamana > costProducere[saptamanaActuala]){
            stocBranza.pop_back();
        }
        stocBranza.push_back(saptamanaActuala);
        /// La costul total adaugam pretul producerii branzei din saptamana curenta
        costTotal += (costProducere[stocBranza.front()] + (saptamanaActuala - stocBranza.front()) * pretSaptamana) * cantitate;
    }

    out << costTotal;
    return 0;
}
