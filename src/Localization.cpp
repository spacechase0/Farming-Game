#include "Localization.h"

#include <fstream>

namespace
{
	std::string getKey(const std::string& entry)
	{
		return entry.substr(0, entry.find('='));
	}

	std::string getValue(const std::string& entry)
	{
		return entry.substr(entry.find('=') + 1);
	}
}

std::map<std::string, std::string> Localization::entries;

void Localization::load(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    std::string entry;
    while (std::getline(file, entry))
    {
        entries.insert(std::make_pair(getKey(entry), getValue(entry)));
    }
    file.close();
}

std::string Localization::get(const std::string& key)
{
    return entries[key];
}
