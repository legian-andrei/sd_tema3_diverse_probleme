#include<iostream>
#include<fstream>

using namespace std;

ifstream in("farfurii.in");
ofstream out("farfurii.out");

int main(){

    long long nrFarfurii, nrTacamuri, maxAsezari, nrFarfurii2;
    in >> nrFarfurii >> nrTacamuri;
    nrFarfurii2 = nrFarfurii;

    maxAsezari = (nrFarfurii - 1) * nrFarfurii / 2;
    if (maxAsezari == nrTacamuri){
        for (long long i = nrFarfurii; i >= 1; i--){
            out << i << " ";
        }
    } else {
        while ((nrFarfurii2 - 2) * (nrFarfurii2 - 1) / 2 > nrTacamuri && nrFarfurii2 > 2){
            nrFarfurii2--;
        }

        for (int i = 1; i <= nrFarfurii - nrFarfurii2; i++){
            out << i << " ";
        }

        long long aux = nrFarfurii - (nrFarfurii2 - 1) * nrFarfurii2 / 2 + nrTacamuri;
        out << aux << " ";

        for (long long i = nrFarfurii; i > nrFarfurii - nrFarfurii2; i--){
            if(i != aux){
                out << i << " ";
            }
        }
    }

    return 0;
}
