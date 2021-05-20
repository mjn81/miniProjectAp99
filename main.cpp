#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

#include <iostream>
#include <fstream>

using namespace std;

struct dict {
    string word;
    dict *nxt;
    dict *syn;
};

//prototypes
dict *createWord(const string &, dict *);

bool chekExist(dict *, dict *);

void addSyn(dict *, const string &syn);

int checkWord(const string &, const string &);

void sort(dict *&);

void add(dict *, dict *&);

dict *search(const string &, dict *&);

void dynamicDelete(dict *&);

void deleteWord(dict *, dict *&);

void deleteSyn(const string &, dict *&, dict *&);

void printWord(dict *);

void printWords(dict *&);

void changeWord(dict *, const string &);

void writeFileDict(dict *&);

void readFileDict(dict *&, const string &);

void mainMenu();

int main() {

    mainMenu();

    return 0;
}

dict *createWord(const string &word, dict *syn) {
    dict *node = new dict{word, nullptr, syn};
    return node;
}

//if word_ptr exists returns true else returns false (only for words)
bool chekExist(dict *node, dict *addNode) {
    if (node->word == addNode->word) {
        return true;
    }
    return false;
}

//adds a synonym(no existence checking)
void addSyn(dict *node, const string &syn) {
    dict *temp = node->syn, *s = new dict{syn, nullptr, nullptr};
    //if it doesnt have a syn
    if (node->syn == nullptr)
        node->syn = s;
    else {
        //it has a list of syn
        while (temp->nxt != nullptr) {
            temp = temp->nxt;
        }
        temp->nxt = s;
    }
}

//compares 2 word if 1st bigger returns 1 if equal 0 else -1 (const ref for efficiency)
int checkWord(const string &a, const string &b) {
    int al = a.length(), bl = b.length();//a length , b length
    int length = al < bl ? al : bl;

    // if length a is bigger returns 1 , else -1
    if (al > bl) {
        return 1;
    } else if (al < bl) {
        return -1;
    }
    // check words char by char
    for (int i = 0; i < length; ++i) {
        if (a[i] > b[i]) {
            return 1;
        } else if (a[i] < b[i]) {
            return -1;
        }
    }

    return 0;
}

//sorts any head of any part (both syn & word)
void sort(dict *&head) {
    dict *node, *temp;
    string word;
    bool flag = true;
    //bubble sorting
    while (flag) {
        node = head;
        flag = false;
        while (node->nxt != nullptr) {
            if (checkWord(node->word, node->nxt->word) == 1) {
                temp = node->syn;
                word = node->word;
                node->word = node->nxt->word;
                node->nxt->word = word;
                node->syn = node->nxt->syn;
                node->nxt->syn = temp;
                flag = true;
            }
            node = node->nxt;
        }
    }
}

//adds word(no existence checking)
void add(dict *addNode, dict *&head) {
    dict *node = head;
    if (node == nullptr)
        head = addNode;
    else {
        while (node->nxt != nullptr) {
            node = node->nxt;
        }
        node->nxt = addNode;
    }
}

//finds any word in any head(both syn & words)
dict *search(const string &word, dict *&head) {
    dict *temp = head;
    while (temp != nullptr) {
        if (temp->word == word) {
            return temp;
        }
        temp = temp->nxt;
    }
    return nullptr;
}

//deletes all syn nodes
void dynamicDelete(dict *&head) {
    dict *temp, *Head = head;
    while (Head != nullptr) {
        temp = Head;
        Head = Head->nxt;
        delete temp;
    }
}

//deletes words
void deleteWord(dict *word, dict *&head) {
    dict *current = head, *pre = nullptr;
    if (head == word && head->nxt == nullptr && chekExist(word, head)) {//only head exists & matches with input_word
        head = nullptr;
        delete current;
        return;
    } else {
        while (current != nullptr) {
            if (chekExist(current, word)) {//if word is 1st node
                if (current == head) {
                    head = head->nxt;
                } else if (current->nxt == nullptr) {//if middle node
                    pre->nxt = nullptr;
                } else {//if end node
                    pre->nxt = current->nxt;
                }
                break;
            }
            pre = current;
            current = current->nxt;
        }
        // deletes syn node
        dynamicDelete(current->syn);
        delete current;
    }


}

//deletes syn by input_word(no existence checking)
void deleteSyn(const string &synWord, dict *&word, dict *&head) {
    dict *temp = word->syn, *pre = nullptr;//temp = head of syn linked list
    bool flag = false;
    if (temp->word == synWord && temp->nxt == nullptr) {//if only head and head equals deletes the word itself
        deleteWord(word, head);
        delete temp;
        return;
    } else {
        while (temp != nullptr) {
            if (temp->word == synWord) {
                if (temp == word->syn) {//if node is 1st
                    word->syn = temp->nxt;
                } else if (temp->nxt == nullptr) {//if node is end
                    pre->nxt = nullptr;
                } else {//if node is middle
                    pre->nxt = temp->nxt;
                }
                flag = true;
                break;
            }
            pre = temp;
            temp = temp->nxt;
        }//flag to stop printing not exist message
        if (flag) {
            delete temp;
            return;
        }
    }
    cout << "\nno such synonym exist!!\n\n";
}

//print one
void printWord(dict *word) {
    dict *temp = word->syn;
    cout << "word :" << word->word << "    " << "synonyms :";
    while (temp != nullptr) {
        cout << temp->word << "  ";
        temp = temp->nxt;
    }
    cout << endl;
}

//print all
void printWords(dict *&head) {
    dict *temp = head;
    while (temp != nullptr) {
        printWord(temp);
        temp = temp->nxt;
    }
}

//change word_dictation
void changeWord(dict *word, const string &chw) {
    word->word = chw;
}

void writeFileDict(dict *&linkedList) {
    ofstream writer;
    writer.open("outPut.txt");
    dict *node = linkedList;
    dict *syn;
    while (node != nullptr) {
        syn = node->syn;
        writer << node->word << "|";
        while (syn != nullptr) {
            writer << syn->word << "|";
            syn = syn->nxt;
        }
        node = node->nxt;
        writer << "\n";
    }
}

void readFileDict(dict *&linkedList, const string &address) {
    ifstream reader;
    reader.open(address);
    dict *node = nullptr, *syn;
    string line, word;
    int c = 0;
    while (!reader.eof()) {
        getline(reader, line);
        c = 0;
        for (auto x : line) {
            if (x == '|') {
                if (c == 0) {
                    node = search(word, linkedList);
                    if (node == nullptr) {
                        node = createWord(word, nullptr);
                        add(node, linkedList);
                    }
                } else {
                    syn = search(word, node->syn);
                    if (syn == nullptr) {
                        addSyn(node, word);
                    }
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

//// main menu for printing messages and so....

void mainMenu() {
    dict *head = nullptr, *syn;
    int inp, synNum;
    string word;
    do {
        cout << "\n1-Add Word\n2-Add Synonym\n3-Find Word\n4-Delete Word\n5-Delete Synonym\n"
             << "6-Print dictionary\n7-Change name\n8-Write in File\n9-Read From File\n10-Exit\n";
        cin >> inp;
        switch (inp) {
            case 1: {
                cout << "Enter Word :";
                cin >> word;
                cout << "Enter number of synonyms :";
                cin >> synNum;
                if (synNum == 0) {
                    break;
                }
                dict *node = search(word, head);
                if (node == nullptr) {
                    node = createWord(word, nullptr);
                    add(node, head);
                }
                for (int i = 0; i < synNum; i++) {
                    cout << "Enter synonym :";
                    cin >> word;
                    syn = search(word, node->syn);
                    if (syn == nullptr) {
                        addSyn(node, word);
                    }
                }
                sort((node->syn));
                sort(head);
                break;
            }
            case 2: {
                cout << "Enter Word :";
                cin >> word;
                dict *temp = search(word, head);
                if (temp != nullptr) {
                    cout << "Enter number of synonyms to add :";
                    cin >> synNum;
                    for (int i = 0; i < synNum; ++i) {
                        cout << "Enter Synonym :";
                        cin >> word;
                        syn = search(word, temp->syn);
                        if (syn == nullptr) {
                            addSyn(temp, word);
                        }
                    }
                    sort(temp->syn);
                } else {
                    cout << "no such word exist!!";
                }
                break;
            }
            case 3: {
                cout << "Enter Word :";
                cin >> word;
                dict *temp = search(word, head);
                if (temp != nullptr) {
                    printWord(temp);
                } else {
                    cout << "no such word exist!!";
                }
                break;
            }
            case 4: {
                cout << "Enter Word :";
                cin >> word;
                dict *temp = search(word, head);
                if (temp != nullptr) {
                    deleteWord(temp, head);
                    cout << "Word deleted!";
                } else {
                    cout << "no such word exist!!";
                }
                break;
            }
            case 5: {
                cout << "Enter Word :";
                cin >> word;
                dict *temp = search(word, head);
                if (temp != nullptr) {
                    cout << "Enter synonym you want to delete :";
                    cin >> word;
                    deleteSyn(word, temp, head);
                    cout << "Synonym deleted!!";
                } else {
                    cout << "no such word exist!!";
                }
                break;
            }
            case 6: {
                printWords(head);
                break;
            }
            case 7: {
                cout << "Enter Word you want to change dictation :";
                cin >> word;
                dict *temp = search(word, head);
                if (temp != nullptr) {
                    cout << "Enter new word to replace :";
                    cin >> word;
                    changeWord(temp, word);
                    cout << "Changing successful";
                } else {
                    cout << "no such word exist!!";
                }
                break;
            }
            case 8: {
                writeFileDict(head);
                cout << "\nwriting successful!!\n";
                break;
            }
            case 9: {
                cout << "Enter fileName :";
                cin >> word;
                readFileDict(head, word);
                printWords(head);
                break;
            }
            case 10: {
                cout << "Do you want to save dictionary before you leave?(y/n)\n";
                cin >> word;
                if (word == "y") {
                    writeFileDict(head);
                }
                break;
            }
        }

    } while (inp != 10);
}