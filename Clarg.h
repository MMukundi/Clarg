
#pragma once
#include <iostream>
#include <unordered_map>
#include <functional>
#include <variant>
#include <vector>
#include <string>
#include "Trie.h"

class Arg{
  public:
    const char *name;
    int argCount = 0;
    enum ValueType{
        Strings,
        String,
        Flag,
        None
    } type = None;
    bool set = false;
    union Val {
        char **strings;
        bool flag;
    } val;
    Arg(const char* n);  
    Arg(const char *n, int count);

    void initFlag(const char* n);

    char* getArg(int i=0);
    char** getArgs();
    bool getFlag();
    bool operator==(Arg *a);
    
};
std::ostream &operator<<(std::ostream &os, Arg const &a);

class ParseResult{
public:
    std::unordered_map<const char *, bool> flags;
    std::unordered_map<const char *, const char **> arguments;
    std::vector<const char *> inputs;
    ParseResult(std::unordered_map<const char *, bool> flags_,
                std::unordered_map<const char *, const char **> arguments_,
                std::vector<const char *> inputs_);
};
class ClargParse{
public:
    typedef bool Flag;
    typedef char **ArgumentList;

    Trie<Arg> arguments;
    std::vector<const char *> inputs;
    ClargParse();
    void addArg(const char *arg, int args = 0);
    void addArg(const char *arg, Arg a);
    ArgumentList getArgList(const char *name);
    Flag getFlag(const char *name);
    void parse(char **args, int argc);

};

//Full Defs?
