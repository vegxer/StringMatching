#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::vector;

const int ALPHABET_SIZE = 256;

struct vertex
{
    bool isTerminal;
    string str;
    vertex* child[ALPHABET_SIZE];
};

void initTrie(vertex*);
void insert(vertex*, string);
void printTrie(vertex*, vector<string>);
bool search(vertex*, string);
void deleteTrie(vertex*);
vertex* createVertex(bool, string);
vertex* pathToVertex(vertex*, string, int&, int&);
void copy(vertex*&, vertex*);
void childToNULL(vertex*);
void printVector(vector<string>);

int main()
{
    setlocale(LC_CTYPE, "rus");
    vertex* trie = new vertex();
    initTrie(trie);
    cout << "Сжатый бор:\n";
    printTrie(trie, {});
    string str;
    cout << "Введите строку для поиска: ";
    cin >> str;
    cout << (search(trie, str + '$') ? "Эта строка есть во множестве" : "Этой строки нет во множестве") << '\n';
    deleteTrie(trie);
    system("pause");
    return 0;
}

vertex* createVertex(bool isEnd, string word)
{
    vertex* newVertex = new vertex();
    newVertex->str = word;
    newVertex->isTerminal = isEnd;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        newVertex->child[i] = NULL;
    return newVertex;
}

vertex* pathToVertex(vertex* pointer, string word, int& i, int& j)
{
    while (word[i] != '$' && pointer->child[word[i]] != NULL)
    {
        j = 0;
        pointer = pointer->child[word[i]];
        while (j < pointer->str.length() && word[i] != '$' && pointer->str[j] == word[i])
            ++i, ++j;
    }
    return pointer;
}

void copy(vertex*& temp, vertex* pointer)
{
    temp->isTerminal = pointer->isTerminal;
    temp->str = pointer->str;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        temp->child[i] = pointer->child[i];
}

void childToNULL(vertex* pointer)
{
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        pointer->child[i] = NULL;
}

void insert(vertex* trie, string word)
{
    vertex* pointer = trie;
    int j = 0, i = 0;
    pointer = pathToVertex(pointer, word, i, j);
    if (pointer->str.length() == j)
        pointer->child[word[i]] = createVertex(true, word.substr(i, word.length() - i));
    else
    {
        vertex* temp = new vertex();
        copy(temp, pointer);
        pointer->str = pointer->str.substr(0, j);
        pointer->isTerminal = false;
        childToNULL(pointer);
        pointer->child[word[i]] = createVertex(true, word.substr(i, word.length() - i));
        temp->str.erase(0, j);
        pointer->child[temp->str[0]] = temp;
    }
}

bool search(vertex* trie, string pat)
{
    vertex* pointer = trie;
    int strLength = pat.length(), i;
    for (i = 0; i < strLength; )
    {
        /*если есть потомок для данного символа строки,
        то идём дальше, иначе вхождения уже не будет*/
        if (!pointer->child[pat[i]])
            return false;
        pointer = pointer->child[pat[i]];
        if (pointer->str != pat.substr(i, pointer->str.length()))
            return false;
        i += pointer->str.length();
    }
    /*если остановились в терминальной вершине
    и индекс совпавшей строки равен длине строки*/
    return pointer->isTerminal && i == strLength;
}

void printTrie(vertex* trie, vector<string> set)
{
    if (trie->isTerminal)
        printVector(set);
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        if (trie->child[i])
        {
            set.push_back(trie->child[i]->str);
            printTrie(trie->child[i], set);
            set.pop_back();
        }
}

void deleteTrie(vertex* trie)
{
    vertex* pointer = trie;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        if (pointer)
            deleteTrie(pointer->child[i]);
    delete pointer;
}

void initTrie(vertex* trie)
{
    int size;
    cout << "Введите мощность множества слов: ";
    cin >> size;
    string word;
    for (int i = 0; i < size; ++i)
    {
        cout << "Введите " << i + 1 << "-е слово: ";
        cin >> word;
        insert(trie, word + '$');
    }
}

void printVector(vector<string> v)
{
    int i;
    for (i = 0; i < v.size() - 1; ++i)
        cout << v[i];
    cout << v[i].substr(0, v[i].length() - 1);
    cout << '\n';
}
