#include <unordered_map>

class ClargParse
{
    std::unordered_map<char *, Arg> arguments;

public:
    ClargParse();
    void addArg(char *arg, int a);
};

class Arg
{
    char *name;
};
