#include<iostream>
#include<fstream>

using namespace std;

ifstream in("rmq.in");
ofstream out("rmq.out");

int minim(int a, int b){
    if(a < b){
        return a;
    } else {
        return b;
    }
}

void create(int vals[], int intTree[], int l, int h, int cp){
    // l = low, h = high, cp = current position
    if (l == h){
        intTree[cp] = vals[l];
        return;
    }

    int mid = (l + h) / 2;

    create(vals, intTree, l, mid, cp * 2);
    create(vals, intTree, mid + 1, h, (cp * 2) + 1);

    /*if (intTree[cp * 2] < intTree[(cp * 2) + 1]){
        intTree[cp] = intTree[cp * 2];
    } else {
        intTree[cp] = intTree[(cp * 2) + 1];
    }*/
    intTree[cp] = minim (intTree[cp * 2], intTree[(cp * 2) + 1]);
}

int getMin(int intTree[],int l, int h, int left, int right, int root) {
    if(l >= left && h <= right){
        return intTree[root];
    }

    int mid = (l + h) / 2;
    int minLeft = 100001, minRight = 100001;

    // Calculam minimul din subarborele stang
    if(mid >= left){
        minLeft = getMin(intTree, l, mid, left, right, root * 2);
    }
    // Calculam minimul din subarborele stang
    if(mid < right){
        minRight = getMin(intTree, mid + 1, h, left, right, (root * 2) + 1);
    }

    /*if (minLeft < minRight){
        return minLeft;
    } else {
        return minRight;
    }*/
    return minim(minLeft, minRight);
}


int main(){

    int nrElemente, nrIntrebari, st, dr, intTree[400004], vals[100001];
    in >> nrElemente >> nrIntrebari;
    for(int i = 1; i <= nrElemente; i++){
        in >> vals[i];
    }
    for(int i = 1; i < 400004; i++){
        intTree[i] = 100001;
    }

    create(vals, intTree, 1, nrElemente, 1);

    for(int i = 1; i <= nrIntrebari; i++){
        in >> st >> dr;
        out << getMin(intTree, 1, nrElemente, st, dr, 1) << endl;
    }
    return 0;
}
