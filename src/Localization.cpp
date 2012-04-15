#include "Localization.h"

#include <fstream>

std::string getKey(std::string entry)
{
    return entry.substr(0, entry.find('='));
}

std::string getValue(std::string entry)
{
    return entry.substr(entry.find('='));
}

std::map<std::string, std::string> Localization::entries;

void Localization::load(std::string filename)
{
    std::ifstream file(filename.c_str());
    std::string entry;
    while (std::getline(file, entry))
    {
        entries.insert(std::make_pair(getKey(entry), getValue(entry)));
    }
    file.close();
}

std::string Localization::get(std::string key)
{
    entries[key];
}
