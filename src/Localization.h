#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <iostream>
#include <map>

class Localization
{
    static std::map<std::string, std::string> entries;

    public:
    static void load(const std::string&);
    static std::string get(const std::string&);
};

typedef Localization Loc;

#endif
