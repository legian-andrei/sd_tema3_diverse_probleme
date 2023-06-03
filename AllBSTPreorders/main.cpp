#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int value;
    Node* left; Node* right;
};

Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

vector <Node*> BSTgenerator(int leftMargin, int rightMargin){
    /// bsts va fi utilizat pentru a stoca toti arborii de cautare binara generati
    vector<Node*> bsts;

    /// Verificam cazul de baza. Daca leftMargin > rightMargin, inseamna ca nu avem elemente intre acesti 2 indici,
    /// deci se va returna nullptr. Aceasta conditie reprezinta recursivitatea care se intoarce si construieste arborele
    /// in sus.
    if (leftMargin > rightMargin) {
        bsts.push_back(nullptr);
        return bsts;
    }

    /// Luam pe rand fiecare valoare de la leftMargin la rightMargin si construim arborii care au respectiva valoare ca radacina.
    for(int root = leftMargin; root <= rightMargin; root++){
        /// Apelam recursiv functia BSTgenerator pentru a construi subarborii stangi si subarborii drepti.
        vector<Node*> leftSubTree = BSTgenerator(leftMargin, root - 1);
        vector<Node*> rightSubTree = BSTgenerator(root + 1, rightMargin);

        /// Pentru fiecare combinatie de subarbori stangi cu subarbori drepti se creaza arborul avand radacina cu valoarea root
        for (int lst = 0; lst < leftSubTree.size(); lst++) {
            Node* leftTree = leftSubTree[lst];
            for (int rst = 0; rst < rightSubTree.size(); rst++) {
                Node* rightTree = rightSubTree[rst];

                Node* rootNode = createNode(root);
                rootNode->left = leftTree;
                rootNode->right = rightTree;
                bsts.push_back(rootNode);
            }
        }
    }

    return bsts;
}

void preOrder(Node* root) {
    if (!root){
        return;
    }

    cout << root->value << " ";
    preOrder(root->left);
    preOrder(root->right);
}

int main()
{
    int n;
    cin >> n;
    vector<Node*> allTreesFrom1ToN = BSTgenerator(1, n);
    for (auto tree: allTreesFrom1ToN) {
        preOrder(tree);
        cout << endl;
    }
    return 0;
}
