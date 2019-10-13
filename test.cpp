#include "Clarg.h"
#include <iostream>
#include <queue>
using namespace std;

int main(int argc, char **args)
{
    ClargParse parse;
    // cout << "Creted" << endl;
    parse.addArg("first", 1);
    // cout << "0 Added" << endl;
    parse.addArg("second", 1);
    // cout << "1 added" << endl;
    parse.addArg("third", 1);
    cout << "Testing args" << endl;

    for (auto n : parse.arguments)
    {
        cout<<n.name<<endl;
        cout << "-------------------" << n.name << "-------------------"<< endl;
    }
    // cout << "2 added" << endl;
    parse.parse(args, argc);
    // cout << "Parsed" << endl;
    // Input keys (use only 'a' through 'z'
    // and lower case)
    pair<string, int> keys[] = {{parse.getArgList("first")[0], 1}, {parse.getArgList("second")[0], 2}, {parse.getArgList("third")[0], 0}};
    int n = sizeof(keys) / sizeof(keys[0]);

    // Construct trie
    for (int i = 0; i < n; i++)
        cout << keys[i].first << ": " << keys[i].second << endl;

    return 0;
}
