#include <iostream>

using namespace std;


struct dict{
    string word;
    dict *nxt;
    dict *syn;
};
dict* createWord(const string&, dict *);

bool chekExist(dict *, dict *);

void addSyn(dict *);

void add(dict *, dict *&);


int main() {

    dict *head= nullptr;
    dict *word1 = createWord("w1" , nullptr);
    dict *w2 = createWord("w2" , nullptr);
    dict *w3 = createWord("w3" , nullptr);

    return 0;
}

dict* createWord(const string &word , dict *syn){
    dict *node = new dict{word , nullptr , syn};
    return node;
}

bool chekExist(dict *node, dict *addNode){
    if (node->word == addNode->word){
        return true;
    }
    return false;
}
void addSyn(dict *node , const string &syn){
    dict *temp = node->syn;
    if (node->syn== nullptr)
        node->syn->word = syn;
    else{
        while (temp->nxt != nullptr){
            temp = temp->nxt;
        }
        temp->word = syn;
    }
}

void add(dict *addNode , dict *&head){
    dict *node = head;
    if (node== nullptr)
        head= addNode;
    else {
        while (node->nxt != nullptr) {
            if (chekExist(node,addNode)){
                if (node->syn== nullptr)
                    node->syn = addNode->syn;
                else {
                    dict *syn = node->syn;
                    while (syn->nxt != nullptr) {
                        syn = syn->nxt;
                    }
                    syn->nxt = addNode->syn;
                }
                return;
            }
            node = node->nxt;
        }
        node->nxt = addNode;
    }
}


