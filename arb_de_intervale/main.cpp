#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;

ifstream in("arbint.in");
ofstream out("arbint.out");

void create(int vals[], int intTree[], int l, int h, int cp){
    // low = l, h = high, cp = current position
    if (l == h){
        intTree[cp] = vals[l];
        return;
    }

    int mid = (l + h) / 2;

    create(vals, intTree, l, mid, cp * 2);
    create(vals, intTree, mid + 1, h, (cp * 2) + 1);

    intTree[cp] = max(intTree[cp * 2], intTree[(cp * 2) + 1]);
}

void update(int intTree[], int l, int h, int root, int p, int valoare){
    // low = l, h = high, p = position to be updated
    if (l == h){
        intTree[root] = valoare;
        return;
    }

    int mid = (l + h) / 2;

    // Parcurgem arborele pana la pozitia cautata
    if (p > mid){
        update(intTree, mid + 1, h, (root * 2) + 1, p, valoare);
    } else {
        update(intTree, l, mid, root * 2, p, valoare);
    }

    // Actualizam restul arborelui la intoarcere
    intTree[root] = max(intTree[root * 2], intTree[(root * 2) + 1]);
}

int getMax(int intTree[],int l, int h, int left, int right, int root) {
    // l = low, h = high, left = left margin, right = right margin
    if (left <= l && h <= right){
        return intTree[root];
    }

    int mid = (l + h) / 2, leftMax = 0, rightMax = 0;

    // Calculam max pe subarborele stang
    if (mid >= left){
        leftMax = getMax(intTree, l, mid, left, right, root * 2);
    }

    // Calculam max pe subarborele drept
    if (mid < right){
        rightMax = getMax(intTree, mid + 1, h, left, right, (root * 2) + 1);
    }

    return max(leftMax, rightMax);
}


int main(){
    int nrElemente, nrOperatii, alegere, par1,par2;
    int intTree[400004], vals[100001];
    in >> nrElemente >> nrOperatii;
    for(int i = 1; i <= nrElemente; i++){
        in >> vals[i];
    }
    for(int i = 1; i < 400004; i++){
        intTree[i] = -1;
    }

    create(vals, intTree, 1, nrElemente, 1);

    for(int i = 1; i <= nrOperatii; i++){
        in >> alegere >> par1 >> par2;
        if(!alegere) {
            out << getMax(intTree, 1, nrElemente, par1, par2, 1)<<"\n";
        } else {
            update(intTree, 1, nrElemente, 1, par1, par2);
            vals[par1]=par2;
        }
    }
    return 0;
}
