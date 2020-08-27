#include "Clarg.h"
#include <iostream>
#include <queue>

int main(int argc, char **args)
{
    ClargParse parse;
    // cout << "Creted" << endl;
    parse.addArg("name", 1);
    // cout << "0 Added" << endl;
    parse.addArg("car", 1);
    // cout << "1 added" << endl;
    parse.addArg("birds", 2);

    for (auto n : parse.arguments)
    {
        cout<<n.name<<endl;
        cout << "-------------------" << n.name << "-------------------"<< endl;
    }
    cout << "2 added" << endl;
    parse.parse(args, argc);
    // cout << "Parsed" << endl;
    // Input keys (use only 'a' through 'z'
    // and lower case)
    // pair<ClargParse::ArgumentList, int> keys[] = {{parse.getArgList("na"), 0}, {parse.getArgList("second"), 1}, {parse.getArgList("third"), 2}};
    // int n = sizeof(keys) / sizeof(keys[0]);

    // Construct trie
    // for (int i = 0; i < n; i++) 
    //     cout << keys[i].first[keys[i].second] << std::endl;
    auto bs = parse.getArgList("birds");
    printf("%s got out of their %s and saw a %s fighting a %s!\n",parse.getArgList("name")[0],parse.getArgList("car")[0],bs[0],bs[1]);


    return 0;
}
