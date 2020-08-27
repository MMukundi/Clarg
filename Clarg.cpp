#include <iostream>
#include "Clarg.h"
Arg::Arg(const char *n)
{
    if (std::string(n).size() > 1 && isalnum(n[0]))
    {
        printf("create Error: Flags can only be one alphanumeric character\n");
        exit(1);
    }
    name = n;
    this->val.flag = false;
}
Arg::Arg(const char *n, int q)
{
    name = n;
    if (q > 0)
    {
        for (auto a : std::string(n))
            if (!(isalnum(a) || a == '_'))
            {
                printf("create Error: Arguments can only comprise of alphanumeric characters and underscores\n");
                exit(1);
            }

        this->val.strings = (char **)malloc(sizeof(const char *) * q);
    }
    else
    {
        if (std::string(n).size() > 1 && isalnum(n[0]))
        {
            printf("create Error: Flags can only be one alphanumeric character\n");
            exit(1);
        }
    }
}

bool Arg::operator==(Arg *a)
{
    return string(name) == string(a->name);
}

std::ostream &operator<<(std::ostream &os, Arg const &a)
{
    return os << "Name " << a.name;
}

ParseResult::ParseResult(std::unordered_map<const char *, bool> flags_,
                         std::unordered_map<const char *, const char **> arguments_,
                         std::vector<const char *> inputs_)
{
    flags = flags_;
    arguments = arguments_;
    inputs = inputs_;
}

ClargParse::ClargParse()
{
}
void ClargParse::addArg(const char *arg, int args)
{
    if (arguments.has(arg))
    { //TODO:ADD INPUT
        std::cout << "Overwritting arg " << arg << std::endl;
    }
    arguments.insert(arg, Arg(arg, args));
}
void ClargParse::addArg(const char *arg, Arg a)
{
    if (arguments.has(arg))
    { //TODO:ADD INPUT
        std::cout << "Overwritting arg " << arg << std::endl;
    }
    arguments.insert(arg, a);
};
ClargParse::ArgumentList ClargParse::getArgList(const char *name)
{
    try
    {
        Arg a = arguments[name];
        cout << "ARG " << name << " returned " << string(a.val.strings[0]) << endl;
        return a.val.strings;
    }
    catch (std::exception &e)
    {
        printf("Argument %s is not present\n", name);
        exit(1);
    }
}
ClargParse::Flag ClargParse::getFlag(const char *name)
{
    try
    {
        Arg a = arguments[name];
        cout << "ARG " << name << " returned " << a.val.flag << endl;
        return a.val.flag;
    }
    catch (std::exception &e)
    {
        printf("Argument %s is not present\n", name);
        exit(1);
    }
}

// template<typename R>
// R operator[]({const char *name})
// {
//     return this->getArg<R>(name); //getArg(name);;
// }

void ClargParse::parse(char **args, int argc)
{
    cout << "Parsing!" << endl;
    for (int a = 1; a < argc; a++)
    {

        cout << "Parsing: " << args[a] << endl;
        if (args[a][0] == '-')
        {
            try
            {
                std::string arg = args[a];
                int pos;
                if (args[a][1] == '_')
                {
                    arg = arg.substr(2);
                }
                else
                {
                    arg = arg.substr(1);
                }
                cout << "Current Argument: " << arg << endl;
                //TODO:ONCE TRIE IS IMPLEMENTED, BUILD A VECTOR OF SMALLER SUB-WORDS, AND THEN CHECK FOR THEM LARGEST TO SMALLEST (DEPTH-FIRST SEARCH)
                for (auto n : arguments)
                {
                    std::string name = n.name;
                    cout << "Testing if argument " << name << " matches supplied argument " << arg << endl;
                    if ((pos = arg.find(name)) == 0)
                    {
                        arg = arg.substr(name.size());
                        if (arg.size() > 0)
                        {
                        }
                        else if (a < argc - 1)
                        {
                            arg = string(args[++a]);
                        }
                        else
                        {
                            throw printf("create Error: option \"%s\" requires an argument\n", n.name);
                        }
                    }
                }
            }
            catch (std::out_of_range &e)
            {
                printf("Invalid syntax, please follow something after '-'\n");
            }
        }
    }
}
