#include <iostream>

using namespace std;


struct dict{
    string word;
    dict *nxt;
    dict *syn;
};
dict* createWord(const string&, dict *);

bool chekExist(dict *, dict *);

void addSyn(dict * , const string &syn);

void add(dict *, dict *&);

dict* search(const string & , dict *);

void deleteWord(dict *, dict *&);

void deleteSyn(const string &, dict *);

int main() {


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

dict* search(const string &word , dict *head){
    while (head!= nullptr){
        if (head->word == word){
            return head;
        }
        head = head->nxt;
    }
    cout<<"no such word exist!!";
    return nullptr;
}

void deleteWord(dict *word , dict *&head){
    dict *current = head , *pre;
    if (head == word && head->nxt== nullptr){
        delete head;
        return;
    }
    else{
        while (current->nxt!= nullptr){
            if (current->word == word->word) {
                if (current == head){
                    head = head->nxt;
                    break;
                }
                else if (current->nxt== nullptr){
                    pre->nxt= nullptr;
                    break;
                }
                else{
                    pre->nxt = current->nxt;
                    break;
                }
            }
            pre = current;
            current = current->nxt;
        }
        delete current;
    }


}

void deleteSyn(const string &synWord , dict *&word){
    dict *temp = word->syn , *pre = nullptr;

    if (temp->word ==synWord && temp->nxt== nullptr){
        word->syn = nullptr;
        delete temp;
        return;
    }else{
        while (temp->nxt!= nullptr) {
            if (temp->word == synWord) {
                if (temp == word) {
                    word->syn = temp->nxt;
                    break;
                } else if (temp->nxt == nullptr) {
                    pre->nxt = nullptr;
                    break;
                } else {
                    pre->nxt = temp->nxt;
                    break;
                }
            }
        pre = temp;
        temp = temp->nxt;
        }
        delete temp;
    }


}

