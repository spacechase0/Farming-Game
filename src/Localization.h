#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <iostream>
#include <map>

class Localization
{
    static std::map<std::string, std::string> entries;

    public:
    static void load(std::string);
    static std::string get(std::string);
};

typedef Localization Loc;

#endif
