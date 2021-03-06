#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct NodeTree {
    int key;
    NodeTree *Left;
    NodeTree *Right;
};

struct Tree {
    NodeTree *Top;
};


void CreateTree(Tree &t) {
    t.Top = nullptr;
}

bool FindNode(Tree &t, int k) {
    NodeTree *current;
    current = t.Top;
    while (current != nullptr) {
        if (k == current->key) {
            return true;
        }
        if (k < current->key) {
            current = current->Left;
            continue;
        }
        if (k > current->key) {
            current = current->Right;
        }
    }
    return false;
}

void AddNode(Tree &t, int k) {
    if (FindNode(t, k)) {
        return;
    }
    NodeTree *node;
    node = new NodeTree;
    node->Left = nullptr;
    node->Right = nullptr;
    node->key = k;
    if (t.Top == nullptr) {
        t.Top = node;
    } else {
        NodeTree *current;
        current = t.Top;
        NodeTree *prev;
        prev = nullptr;
        while (current != nullptr) {
            prev = current;
            if (k < current->key) {
                current = current->Left;
                continue;
            }
            if (k > current->key) {
                current = current->Right;
            }
        }
        if ((prev != nullptr) and (k < prev->key)) {
            prev->Left = node;
        }
        if ((prev != nullptr) and (k > prev->key)) {
            prev->Right = node;
        }
    }
}


void DeleteNode(Tree &t, int k) {
    NodeTree *current;
    current = t.Top;
    NodeTree *prev;
    prev = nullptr;
    while ((current != nullptr) and (current->key != k)) {
        prev = current;
        if (k < current->key) {
            current = current->Left;
            continue;
        }
        if (k > current->key) {
            current = current->Right;
        }
    }
    if (current == nullptr) {
        return;
    }
    if ((current->Left == nullptr) and (current->Right == nullptr)) {
        if (k == t.Top->key) {
            t.Top = nullptr;
        }
        delete current;
        if ((prev != nullptr) and (k < prev->key)) {
            prev->Left = nullptr;
        }
        if ((prev != nullptr) and (k > prev->key)) {
            prev->Right = nullptr;
        }
        return;
    }
    if ((current->Left != nullptr) and (current->Right == nullptr)) {
        if (k == t.Top->key) {
            t.Top = current->Left;
        }
        if ((prev != nullptr) and (k < prev->key)) {
            prev->Left = current->Left;
        }
        if ((prev != nullptr) and (k > prev->key)) {
            prev->Right = current->Left;
        }
        delete current;
        return;
    }
    if ((current->Left == nullptr) and (current->Right != nullptr)) {
        if (k == t.Top->key) {
            t.Top = current->Right;
        }
        if ((prev != nullptr) and (k < prev->key)) {
            prev->Left = current->Right;
        }
        if ((prev != nullptr) and (k > prev->key)) {
            prev->Right = current->Right;
        }
        delete current;
        return;
    }
    if ((current->Left != nullptr) and (current->Right != nullptr)) {
        NodeTree *instead;
        int instead_key;
        instead = current->Right;
        while (instead->Left != nullptr) {
            instead = instead->Left;
        }
        instead_key = instead->key;
        DeleteNode(t, instead_key);
        current->key = instead_key;
        return;
    }
}

bool IsTreeEmpty(Tree &t) {
    return (t.Top == nullptr);
}

void DirectTravel(NodeTree *node, int l = 1) {
    if (node != nullptr) {
        DirectTravel(node->Right, l + 1);
        for (int i = 0; i < l; i++)
            cout << "    ";
        cout << node->key << endl;
        DirectTravel(node->Left, l + 1);
    }
}

void PrintTree(Tree &t) {
    DirectTravel(t.Top);
}

void ReverseTravel(NodeTree *node) {
    if (node == nullptr) {
        return;
    }
    ReverseTravel(node->Left);
    ReverseTravel(node->Right);
    cout << node->key << " ";
}


void SymmetricTravel(NodeTree *node) {
    if (node == nullptr) {
        return;
    }
    ReverseTravel(node->Left);
    cout << node->key << " ";
    ReverseTravel(node->Right);
}

double SummTree(NodeTree *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->key + SummTree(node->Left) + SummTree(node->Right);
}

//void DeleteTree(Tree &t) {
//    //!!! void DeleteTree(????) + ????????
//    while (!IsTreeEmpty(t)) {
//        DeleteNode(t, t.Top->key);
//    }
//}

void DeleteTree(NodeTree *node) {
    if (node!= nullptr) {
        DeleteTree(node->Left);
        DeleteTree(node->Right);

        free(&node->key);
        free(node);
    }

}

int main() {
    setlocale(LC_ALL, "Rus");
    Tree tr{};
    CreateTree(tr);
    int num = 0;
    int quant = 0;
    int select = 0;
    while ((select < 1) or (select > 3)) {
        cout << "1 - ????" << endl << "2 - ?????? ???????" << endl << "3 - ????????? ?????????? ???????" << endl
             << "????????=";
        cin >> select;
        cout << endl;
    }
    if (select == 1) {
        ifstream FileIn("File.txt", ios_base::in);
        while (FileIn >> num) {
            AddNode(tr, num);
            quant++;
        }
        FileIn.close();
    }
    if (select == 2) {
        cout << "??????? ???-??" << endl;
        cin >> quant;
        cout << "????????" << endl;
        for (int count = 1; count <= quant; count++) {
            cin >> num;
            AddNode(tr, num);

        }
    }
    if (select == 3) {
        while ((quant < 1)) {
            cout << "??????? ???-??" << endl;
            cin >> quant;
            srand(time(nullptr));
            for (int count = 1; count <= quant; count++) {
                AddNode(tr, rand() % 1000 + 1);
            }
        }
    }
    cout << "?????? : " << endl;
    PrintTree(tr);
    cout << endl;

    cout << "?????? ??????? : " << SummTree(tr.Top) / quant << endl;
    DeleteTree(tr.Top);

}
