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
const int TOTAL_SIZE = 10 + 2 + 2 * ALPHABET_SIZE;

template <typename V, u_long i>
bool nullArray(array<V, i> a)
{
    for (V ob : a)
    {
        if (!(ob == nullptr || ob == NULL))
            return false;
    }
    return true;
}
struct IndexException : public std::exception
{
    int index;
    IndexException(int i)
    {
        index = i;
    }
    const char *what() const throw()
    {
        return ("Cannot access index " + std::to_string(index)).c_str();
    }
};

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
                if (c >= 'A' && c <= 'Z')
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
            char c = (i >= 11 && i < 37) ? 'A' + (i - 11) : 'a' + (i - 37);
            if (isalpha(c))
            {
                return c;
            }
            cout << "Index \'" << i << "\' is not a mappable index" << endl;

            throw runtime_error("Invalid Char");
        }
    }
    struct IterInfo
    {
        TrieNode<T> *node;
        int searchIndex;
        IterInfo(TrieNode<T> *n, int i) : node(n), searchIndex(i){};
        IterInfo(){};
    };
    struct IncrementEndException : public std::exception
    {
        const char *what() const throw()
        {
            return "Can't increment an end trie iterator";
        }
    };
    class TrieIterator
    {

    public:
        // vector<IterInfo> stack = *(new vector<IterInfo>());
        IterInfo *stack;
        int lastStackIndex = -1;
        string currString = ""s;
        TrieNode<T> *trieRoot;
        TrieIterator(Trie<T> t)
        {
            TrieNode<T> *currentNode = t.root;
            stack = new IterInfo[t.height + 1];
            trieRoot = t.root;
            stack[++lastStackIndex] = {trieRoot, -1};
            // stack.push_back({trieRoot, -1});
            next();
        }
        TrieIterator()
        {
            stack = new IterInfo[0];
        }
        void operator++() { next(); }
        void next()
        {
            //The iterator "cares about" parents; only potential or confirmed parents are stored in the stack
            if (lastStackIndex < 0)
            {
                throw IncrementEndException();
            }

            // currString.pop_back();
            // stack.pop_back();

            //Retrieve the active parent
            IterInfo* currentNode = &stack[lastStackIndex];

            //Begin checking the parent's next child

            // TrieNode<T> *curr;
            do
            {
                // cout<<"Checking node '"<<currString<<"' at index "<<currentNode->searchIndex<<std::endl;
                for (currentNode->searchIndex++; currentNode->searchIndex < TOTAL_SIZE; currentNode->searchIndex++)
                {
                    if (currentNode->node->children[currentNode->searchIndex])
                        break;
                }
                // cout<<"Index is now "<<currentNode->searchIndex<<std::endl;

                if (currentNode->searchIndex < TOTAL_SIZE)
                {
                    // cout<<"The last sIndex for '"<<currString<<"' was "<<currentNode->searchIndex<<" @"<<currentNode<<std::endl;
                    currString += (toChar(currentNode->searchIndex));
                    stack[++lastStackIndex] = IterInfo(currentNode->node->children[currentNode->searchIndex], -1);
                    currentNode = &stack[lastStackIndex];
                    if (currentNode->node->assigned)
                        return;
                    continue;
                }

                while (currentNode->searchIndex >= TOTAL_SIZE)
                {

                    currString.pop_back();
                    // cout << "Popping, index was "<<lastStackIndex;
                    lastStackIndex--;
                    // stack.pop_back();
                    if (lastStackIndex < 0)
                        return;
                    // cout << " and is now "<<lastStackIndex<<std::endl;

                    currentNode = &stack[lastStackIndex];
                    // cout<<"Current node is now @"<<currentNode<<std::endl;
                    // cout<<"Current node index is now @"<<currentNode->searchIndex<<std::endl;

                    // currentNode->searchIndex++;
                    // cout<<"changing "<<currentNode->searchIndex<<std::endl;
                }
            }while (!currentNode->node->assigned);
        }
        T& get()
        {
            IterInfo c = stack[lastStackIndex];
            if (lastStackIndex>-1&&c.node->assigned)
                return c.node->data;
            throw IncrementEndException();
        }
        T& operator*()
        {
            return get();
        }
        bool operator!=(TrieIterator &t)
        {

            if (this->lastStackIndex< 0 && t.lastStackIndex < 0)
            {
                return false;
            }
            if (this->lastStackIndex != t.lastStackIndex)
            {
                return true;
            }
            IterInfo a = this->stack[this->lastStackIndex];
            IterInfo b = t.stack[t.lastStackIndex];
            bool nodes = a.node == b.node;
            bool ints = a.searchIndex == b.searchIndex;
            return !(nodes && ints);
        }
        static TrieIterator END()
        {
            return TrieIterator();
        }
    };
    TrieNode<T> *root;
    int height;

    // Returns new trie node (initialized to nullptrs)
    Trie()
    {
        root = TrieNode<T>::getNode();
    }

    // If not present, inserts key into trie
    // If the key is prefix of trie node, just
    // marks leaf node
    void insert(const char *key, T data)
    {
        TrieNode<T> *currentNode = root;
        string keyString = string(key);
        int l = keyString.length();
        for (int i = 0; i < l; i++)
        {
            int index = toIndex(keyString[i]);
            if (!currentNode->children[index])
                currentNode->children[index] = TrieNode<T>::getNode();
            currentNode = currentNode->children[index];
        }

        // mark last node as leaf
        currentNode->data = data;
        currentNode->assigned = true;
        if (height < l)
            height = l;
    }

    // Returns true if key presents in trie, else
    // false
    T& search(const char *key)
    {
        TrieNode<T> *currentNode = root;
        string keyString = string(key);

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

        if (currentNode != nullptr && currentNode->assigned)
        {
            return currentNode->data;
        }
        throw std::invalid_argument("Key \"" + keyString + "\" is not present in the trie");
    }
    bool has(const char *key)
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
    T& operator[](const char *key)
    {
        return search(key);
    }
    TrieIterator begin()
    {
        // return TrieIterator(*this);
        TrieIterator t = TrieIterator(*this);
        return t;
    }
    Trie<T>::TrieIterator end()
    {
        return TrieIterator::END();
    }
};