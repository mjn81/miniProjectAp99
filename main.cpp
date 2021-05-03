#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#include <iostream>
#include <fstream>
using namespace std;


struct dict{
    string word;
    dict *nxt;
    dict *syn;
};

dict* createWord(const string&, dict *);

bool chekExist(dict *, dict *);

void addSyn(dict * , const string &syn);

int checkWord(const string &, const string &);

void sort(dict *&);

void add(dict *, dict *&);

dict* search(const string & , dict *&);

void dynamicDelete(dict *&);

void deleteWord(dict *, dict *&);

void deleteSyn(const string &, dict *& , dict *&);

void printWord(dict *);

void printWords(dict *&);

void changeWord(dict *,const string &);

void writeFileDict(dict *&);

void readFileDict(dict *&,const string &);

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

int checkWord(const string &a , const string &b){
    int al = a.length() , bl = b.length();
    int length = al<bl ? al : bl;

    for (int i = 0; i <length ; ++i) {
        if (a[i]>b[i]){
            return 1;
        }else if (a[i]<b[i]){
            return -1;
        }
    }
    if (al>bl){
        return 1;
    }else if (al<bl){
        return -1;
    }
    return 0;
}

void sort(dict *&head){
    dict *node , *temp;
    string word;
    bool flag = true;
    while (flag){
        node= head;
        flag = false;
        while (node->nxt!= nullptr){
            if (checkWord(node->word , node->nxt->word)==1){
                temp = node->syn;
                word= node->word;
                node->word = node->nxt->word;
                node->nxt->word = word;
                node->syn = node->nxt->syn;
                node->nxt->syn = temp;
                flag= true;
            }
            node = node->nxt;
        }
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

dict* search(const string &word , dict *&head){
    dict *temp = head;
    while (temp!= nullptr){
        if (temp->word == word){
            return temp;
        }
        temp = temp->nxt;
    }
    return nullptr;
}

void dynamicDelete(dict *&head){
    dict *temp , *Head=head;
    while (Head!= nullptr){
        temp = Head;
        Head = Head->nxt;
        delete temp;
    }
}

void deleteWord(dict *word , dict *&head){
    dict *current = head , *pre= nullptr;
    if (head == word && head->nxt== nullptr && chekExist(word , head)){
        head= nullptr;
        delete current;
        return;
    }
    else{
        while (current!= nullptr){
            if (chekExist(current , word)) {
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
        dynamicDelete(current->syn);
        delete current;
    }


}

void deleteSyn(const string &synWord , dict *&word , dict*&head){
    dict *temp = word->syn , *pre= nullptr;
    bool flag = false;
    if ( temp->word ==synWord && temp->nxt== nullptr){
        deleteWord(word,head);
        delete temp;
        return;
    }else{
        while (temp!= nullptr) {
            if (temp->word == synWord) {
                if (temp == word->syn) {
                    word->syn = temp->nxt;
                    flag = true;
                    break;
                } else if (temp->nxt == nullptr) {
                    pre->nxt = nullptr;
                    flag = true;
                    break;
                } else {
                    pre->nxt = temp->nxt;
                    flag = true;
                    break;
                }
            }
        pre = temp;
        temp = temp->nxt;
        }
        if (flag) {
            delete temp;
            return;
        }
    }
    cout<<"\nno such synonym exist!!\n\n";
}

void printWord(dict *word){
    dict *temp = word->syn;
    cout<<"word :"<<word->word<<"    "<<"synonyms :";
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

void writeFileDict(dict *&linkedList){
    ofstream writer;
    writer.open("outPut.txt");
    dict *node = linkedList;
    dict *syn;
    while (node!= nullptr){
        syn = node->syn;
        writer<<node->word<<"|";
        while (syn!= nullptr){
            writer<<syn->word<<"|";
            syn = syn->nxt;
        }
        node = node->nxt;
        writer<<"\n";
    }
}

void readFileDict(dict *&linkedList,const string &address){
    ifstream reader;
    reader.open("outPut.txt");
    dict *node = nullptr;
    string line , word;
    int c=0;
    while (!reader.eof()){
        getline(reader , line);
        c=0;
        for (auto x : line) {
            if (x == '|') {
                if (c==0) {
                    node = search(word , linkedList);
                    if (node== nullptr) {
                        node = createWord(word, nullptr);
                        add(node, linkedList);
                    }
                } else {
                    addSyn(node , word);
                }
                word = "";
                c++;
            } else {
                word += x;
            }
        }
        sort(node->syn);
    }
    sort(linkedList);
}

void mainMenu(){
    dict *head= nullptr;
    int inp , synNum;
    string word;
    do {
        cout<<"\n1-Add Word\n2-Add Synonym\n3-Find Word\n4-Delete Word\n5-Delete Synonym\n"
            <<"6-Print dictionary\n7-Change name\n8-Write in File\n9-Read From File\n10-Exit\n";
        cin>>inp;
        switch (inp) {
            case 1: {
                cout << "Enter Word :";
                cin >> word;
                cout << "Enter number of synonyms :";
                cin >> synNum;
                dict *node = createWord(word , nullptr);
                for (int i = 0; i < synNum; i++) {
                    cout<<"Enter synonym :";
                    cin>>word;
                    addSyn(node,word);
                }
                sort((node->syn) );
                add(node , head);
                sort(head);
                break;
            }
            case 2: {
                cout<<"Enter Word :";
                cin>>word;
                dict *temp = search(word , head);
                if (temp!= nullptr){
                    cout<<"Enter number of synonyms to add :";
                    cin>>synNum;
                    for (int i = 0; i < synNum; ++i) {
                        cout<<"Enter Synonym :";
                        cin>>word;
                        addSyn(temp , word);
                    }
                    sort(temp->syn);
                }else{
                    cout<<"no such word exist!!";
                }
                break;
            }
            case 3: {
                cout<<"Enter Word :";
                cin>>word;
                dict *temp = search(word , head);
                if (temp!= nullptr){
                    printWord(temp);
                }else{
                    cout<<"no such word exist!!";
                }
                break;
            }
            case 4: {
                cout<<"Enter Word :";
                cin>>word;
                dict *temp = search(word , head);
                if (temp!= nullptr){
                    deleteWord(temp , head);
                    cout<<"Word deleted!";
                }else{
                    cout<<"no such word exist!!";
                }
                break;
            }
            case 5: {
                cout<<"Enter Word :";
                cin>>word;
                dict *temp = search(word , head);
                if (temp!= nullptr){
                    cout<<"Enter synonym you want to delete :";
                    cin>>word;
                    deleteSyn(word , temp , head);
                    cout<<"Synonym deleted!!";
                }else{
                    cout<<"no such word exist!!";
                }
                break;
            }
            case 6: {
                printWords(head);
                break;
            }
            case 7: {
                cout<<"Enter Word you want to change dictation :";
                cin>>word;
                dict *temp = search(word ,head);
                if (temp!= nullptr) {
                    cout << "Enter new word to replace :";
                    cin >> word;
                    changeWord(temp , word);
                }else{
                    cout<<"no such word exist!!";
                }
                break;
            }
            case 8: {
                writeFileDict(head);
                cout<<"\nwriting successful!!\n";
                break;
            }
            case 9: {
                cout<<"Enter fileName :";
                cin>>word;
                readFileDict(head , word);
                printWords(head);
                break;
            }
            case 10: {
                cout<<"Do you want to save dictionary before you leave?(y/n)\n";
                cin>>word;
                if(word =="y"){
                    writeFileDict(head);
                }
                break;
            }
        }

    } while (inp!=10);
}