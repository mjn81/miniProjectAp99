#include <iostream>
#include <iomanip>
using namespace std;


struct dict{
    string word;
    dict *nxt;
    dict *syn;
};

dict* createWord(const string&, dict *);

bool chekExist(dict *, dict *);

void addSyn(dict * , const string &syn);

void sort(dict *&);

void add(dict *, dict *&);

dict* search(const string & , dict *&);

void deleteWord(dict *, dict *&);

void deleteSyn(const string &, dict *&);

void printWord(dict *);

void printWords(dict *&);

void changeWord(dict *,const string &);

void mainMenu();


int main() {

    mainMenu();

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
    dict *temp = node->syn , *s = new dict{syn , nullptr , nullptr};
    if (node->syn== nullptr)
        node->syn = s;
    else{
        while (temp->nxt != nullptr){
            temp = temp->nxt;
        }
        temp->nxt = s;
    }
}

void sort(dict *&head){}

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

dict* search(const string &word , dict *&head){
    dict *temp = head;
    while (temp!= nullptr){
        if (temp->word == word){
            return temp;
        }
        temp = temp->nxt;
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

void printWord(dict *word){
    dict *temp = word->syn;
    cout<<"word :"<<word->word<<"\t"<<"synonyms :";
    while (temp!= nullptr){
        cout<<temp->word<<"  ";
        temp = temp->nxt;
    }
    cout<<endl;
}

void printWords(dict *&head){
    dict *temp = head;
    while (temp!= nullptr){
        printWord(temp);
        temp = temp->nxt;
    }
}

void changeWord(dict *word , const string &chw){
    word->word = chw;
}

void mainMenu(){
    dict *head= nullptr;
    int inp , synNum;
    string word;
    do {
        cout<<"1-Add Word\n2-Add Synonym\n3-Find Word\n4-Delete Word\n5-Delete Synonym\n"
            <<"6-Print dictionary\n7-Change name\n8-Write in File\n9-Read From File\n10-Exit\n";
        cin>>inp;
        switch (inp) {
            case 1: {
                cout << "Enter Word :";
                cin >> word;
                cout << "Enter numeber of synonyms :";
                cin >> synNum;
                dict *node = createWord(word , nullptr);
                for (int i = 0; i < synNum; i++) {
                    cout<<"Enter synonym :";
                    cin>>word;
                    addSyn(node,word);
                }
                add(node , head);
            }
                break;
            case 2:
                break;
            case 3:{

            }
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:{
                printWords(head);
            }
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
        }





    } while (inp!=10);







}