#include <iostream>
#include <fstream>
#include <vector>
//#include <algorithm>

using namespace std;

ifstream in("hashuri.in");
ofstream out("hashuri.out");

bool gasit(vector<vector<int>> myHash, int nr){
    for(int j = 0; j < myHash[nr % 214163].size(); j++){
        if(myHash[nr % 214163][j] == nr)
            return true;
    }
    return false;
}

void add(vector<vector<int>>& myHash, int deAdaugat){
    myHash[deAdaugat % 214163].push_back(deAdaugat);
}

void del(vector<vector<int>>& myHash, int deSters){
    for(int j = 0; j < myHash[deSters % 214163].size(); j++){
        if(myHash[deSters % 214163][j] == deSters){
            swap(myHash[deSters % 214163][j], myHash[deSters % 214163][myHash[deSters % 214163].size() - 1]);
            myHash[deSters % 214163].pop_back();
        }
    }
}

int main()
{
    int nrOperatii, tipOperatie, parametru;

    /// Numerele pot fi maxim 2*10^9. Ln(nrMaxim) = 21.4164...
    /// Cel mai apropiat numar prim de acel ln * 10000 este 214163, asa ca vom folosi acest numar ca hash key
    vector<vector<int>> myHash;
    myHash.resize(214163);

    in >> nrOperatii;
    for(int i = 0; i < nrOperatii; i++){
        in >> tipOperatie >> parametru;
        switch(tipOperatie){
            case 1:
                if(!gasit(myHash, parametru)){
                    add(myHash, parametru);
                }
                break;
            case 2:
                if(gasit(myHash, parametru)){
                    del(myHash, parametru);
                }
                break;
            case 3:
                if(gasit(myHash, parametru)){
                    out << '1' << endl;
                } else {
                    out << '0' << endl;
                }
                break;
        }
    }

    return 0;
}
