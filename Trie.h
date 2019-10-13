#pragma once
// C++ implementation of search and insert
// operations on Trie
/*
b ClargParse::getArgList
r -first 1 -second 2 -third 3

*/
#include <string>
#include <array>
#include <vector>
#include <iostream>
using namespace std;

const int ALPHABET_SIZE = 26;
const int TOTAL_SIZE = 11 + 2* ALPHABET_SIZE;

template <typename T>
    class TrieNode
    {
    public:
        array<TrieNode<T> *, TOTAL_SIZE> children = new array<TrieNode<T> *, TOTAL_SIZE>();
        T data;
        bool assigned = false;
        static TrieNode<T> *getNode()
        {
            TrieNode<T> *t = (TrieNode<T> *)malloc(sizeof(TrieNode<T>));
            t->children.fill(nullptr);
            return t;
        }
        TrieNode()
        {
        }
    };
// trie node
template <typename T>
class Trie
{
public:
    static int toIndex(char c)
    {
        switch (c)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return c - '0';
        case '_':
            return 10;
        default:
            if (isalpha(c))
            {
                if(c>='A'&&c<='Z')
                    return 11 + c - 'A';
                else
                    return 37 + c - 'a';
            }
            cout << "Character \'" << c << "\' is not a valid argument character" << endl;

            throw runtime_error("Invalid Char");
        }
    }
    static char toChar(int i)
    {
        if (i < 0 || i >= TOTAL_SIZE)
        {
            throw runtime_error("Invalid Index");
        }
        switch (i)
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            return '0' + i;
        case 10:
            return '_';
        default:
            char c = (i>=11 && i<37)?'A' + (i - 11):'a' + (i-37);
            if (isalpha(c))
            {
                return c;
            }
            cout << "Index \'" << i << "\' is not a mappable index" << endl;

            throw runtime_error("Invalid Char");
        }
    }
    class TrieIterator
    {
        //Parent, pos

        //END = (stack[0] == {root, ALPH_SIZE})

        //To check
    public:
        vector<pair<TrieNode<T> *, int>> stack = *(new vector<pair<TrieNode<T> *, int>>());
        string currString = ""s;
        TrieIterator(Trie<T> t)
        {
            TrieNode<T> *currentNode = t.root;
            int i;
            cout << "Building the iterator " << endl;

            while (currentNode != nullptr)
            {
                cout << "CurrString: " << currString << endl;

                i = 0;
                while (i < TOTAL_SIZE && !currentNode->children[i])
                {

                    i++;
                }
                if (i >= TOTAL_SIZE)
                {
                    cout << "An empty row!" << endl;
                    break;
                }
                cout << "Index: " << i << endl;
                currString += toChar(i);
                stack.push_back({currentNode, i});
                currentNode = currentNode->children[i];
            }
            cout << "Total size: " << stack.size() << endl;
        }
        TrieIterator()
        {
        }
        void operator++()
        {
            cout<<"Moving to next"<<endl;
        top:
            pair<TrieNode<T> *, int> &c = stack.back();
            if (c.second+1 < TOTAL_SIZE)
            {
                c.second++;
            }
            else
            {
                stack.pop_back();
                goto top;
            }
        }
        T get()
        {
            pair<TrieNode<T> *, int> &c = stack.back();
            cout<<"Current char "<<toChar(i)<<endl;
            if (c.second < TOTAL_SIZE)
                return c.first->children[c.second]->data;
            throw std::out_of_range("Can't increment an end trie iterator");
        }
        T operator*()
        {
            return get();
        }
        bool operator!=(TrieIterator &t)
        {
            
            if (this->stack.empty() && t.stack.empty())
            {
                return false;
            }
            if (this->stack.size() != t.stack.size())
            {
                return true;
            }
            pair<TrieNode<T> *, int> a = this->stack.back();
            pair<TrieNode<T> *, int> b = t.stack.back();
            bool nodes = a.first == b.first;
            bool ints = a.second == b.second;
            return !(nodes && ints);
        }
        static TrieIterator END()
        {
            return TrieIterator();
        }
    };
    TrieNode<T> *root;

    // Returns new trie node (initialized to nullptrs)
    Trie()
    {
        root = TrieNode<T>::getNode();
        // cout << "Root " << currentNode->data << endl;
    }

    // If not present, inserts key into trie
    // If the key is prefix of trie node, just
    // marks leaf node
    void insert(const char * key, T data)
    {
        TrieNode<T> *currentNode = root;
        string keyString = string(key);

        for (int i = 0; i < keyString.length(); i++)
        {
            int index = toIndex(keyString[i]);
            if (!currentNode->children[index])
                currentNode->children[index] = TrieNode<T>::getNode();

            currentNode = currentNode->children[index];
        }

        // mark last node as leaf
        currentNode->data = data;
        currentNode->assigned = true;
        cout << "Node: " << currentNode << " Key: " << key << " Data: " << currentNode->data << endl;
    }

    // Returns true if key presents in trie, else
    // false
    T search(const char* key)
    {
        TrieNode<T> *currentNode = root;
                string keyString = string(key);

        cout << "KEY:" << keyString << endl;
        int n = keyString.length();
        for (int i = 0; i < n; i++)
        {
            int index = toIndex(keyString[i]);
            if (currentNode != nullptr)
            {
                if (currentNode->children[index] == nullptr)
                    throw std::invalid_argument("Key \"" + keyString + "\" is not present in the trie");
                currentNode = currentNode->children[index];
            }
        }
        
        if (currentNode != nullptr && currentNode->assigned){
            cout << "Found value " << currentNode->data<<endl;;
            return currentNode->data;    
        }
        throw std::invalid_argument("Key \"" + keyString + "\" is not present in the trie");
    }
    bool has(const char* key)
    {
        TrieNode<T> *currentNode = root;
                string keyString = string(key);

        for (int i = 0, n = keyString.length(); i < n; i++)
        {
            int index = toIndex(keyString[i]);
            if (!currentNode->children[index])
                return false;
            currentNode = currentNode->children[index];
        }

        if (currentNode != nullptr)
            return (currentNode->assigned);
        return false;
    }
    T operator[](const char *key)
    {
        return search(key);
    }
    TrieIterator begin()
    {
        return TrieIterator(*this);
    }
    Trie<T>::TrieIterator end()
    {
        return TrieIterator::END();
    }
};