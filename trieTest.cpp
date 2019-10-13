#include "Trie.h"
using namespace std;

class A
{
public:
    int a;
    A(int a_)
    {
        a = a_;
    }
};
ostream &operator<<(ostream &os, A const &m)
{
    return os << m.a;
}

template <typename T>
void printTrie(TrieNode<T> *t, string indent = "");

int main()
{
    Trie<A> t;

    t.insert("Marcel", A(17));
    t.insert("Caleb", A(18));
    t.insert("Malcolm", A(17));
    t.insert("Erika", A(18));
    t.insert("Erica", A(15));
    printTrie(t.root);

    return 0;
}

template <typename T>
void printTrie(TrieNode<T> *t, string indent)
{
    for (int i = 0; i < TOTAL_SIZE; i++)
    {
        if (t->children[i] != nullptr)
        {
            TrieNode<T> *node = t->children[i];
            std::cout << indent << Trie<T>::toChar(i);
            if (node->assigned)
            {
                std::cout << " - ";
                cout << node->data;
            }
            std::cout << std::endl;
            printTrie(t->children[i], indent + "  ");
        }
    }
}