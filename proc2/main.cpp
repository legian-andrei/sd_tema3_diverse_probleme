#include <fstream>
#include <queue>

using namespace std;

ifstream in("proc2.in");
ofstream out("proc2.out");

int main()
{
    int nrProcesoare, nrProcese, inceputProces, durataProces;

    /// procesoareDisponibile contine indexul fiecarui procesor disponibil in ordine crescatoare
    priority_queue<int, vector<int>, greater<int>> procesoareDisponibile;

    /// proceseInExecutie contine perechi de tipul <timpFinalExecutie, indexProcesorAsignat>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> proceseInExecutie;

    in >> nrProcesoare >> nrProcese;

    /// Initial toate procesoarele sunt disponibile
    for(int i = 1; i <= nrProcesoare; i++){
        procesoareDisponibile.push(i);
    }

    for(int i = 0; i < nrProcese; i++){
        in >> inceputProces >> durataProces;

        /// Scot din proceseInExecutie toate procesoarele care si-au terminat executia si sunt disponibile pentru noi task-uri
        while(!proceseInExecutie.empty() && proceseInExecutie.top().first < inceputProces){
            procesoareDisponibile.push(proceseInExecutie.top().second);
            proceseInExecutie.pop();
        }

        /// Introduc in proceseInExecutie momentul de final al procesului citit impreuna cu indexul procesorului din varful pq-ului
        /// si afisez procesorul asignat taskului curent
        proceseInExecutie.push({inceputProces + durataProces - 1, procesoareDisponibile.top()});
        out << procesoareDisponibile.top() << endl;
        procesoareDisponibile.pop();

    }
    return 0;
}
