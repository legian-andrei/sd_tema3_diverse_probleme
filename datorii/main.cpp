#include<iostream>
#include<fstream>

using namespace std;

ifstream in("datorii.in");
ofstream out("datorii.out");

void create(int vals[], int intTree[], int l, int h, int cp){
    // low = l, h = high, cp = current position
    if (l == h){
        intTree[cp] = vals[l];
        return;
    }

    int mid = (l + h) / 2;

    create(vals, intTree, l, mid, cp * 2);
    create(vals, intTree, mid + 1, h, (cp * 2) + 1);

    intTree[cp]= intTree[cp * 2] + intTree[(cp * 2) + 1];
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
    intTree[root]= intTree[root * 2] + intTree[(root * 2) + 1];
}

int getSum(int intTree[],int l, int h, int left, int right, int root) {
    // low = l, h = high, left = left margin, right = right margin
    if (left <= l && h <= right){
        return intTree[root];
    }

    int mid = (l + h) / 2, leftSum = 0, rightSum = 0;

    // Calculam suma pe subarborele stang
    if (mid >= left){
        leftSum = getSum(intTree, l, mid, left, right, root * 2);
    }

    // Calculam suma pe subarborele drept
    if (mid < right){
        rightSum = getSum(intTree, mid + 1, h, left, right, (root * 2) + 1);
    }

    return leftSum + rightSum;
}


int main(){
    int nrComenzi, nrOperatii, operatie;
    int intTree[400004], vals[100001];
    for (int i=1;i<400004;i++){
        intTree[i]=0;
    }

    in >> nrComenzi >> nrOperatii;
    for (int i = 1; i <= nrComenzi; i++){
        in >> vals[i];
    }
    create(vals, intTree, 1, nrComenzi, 1);

    for (int i = 1; i <= nrOperatii; i++){
        int par1, par2;
        in >> operatie >> par1 >> par2;

        if (!operatie) {
            vals[par1] -= par2;
            update(intTree, 1, nrComenzi, 1, par1, vals[par1]);
        } else {
            out << getSum(intTree, 1, nrComenzi, par1, par2, 1) << endl;
        }
    }
    return 0;
}
