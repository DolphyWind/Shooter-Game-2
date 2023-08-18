#pragma once
#include <Version.hpp>
#include <vector>
#include <string>
#include <SFEX/General/Multitype.hpp>

class Mod
{
public:
    sfex::Multitype toJSON();

    Version version;
    std::vector<std::string> authors;
    std::string title;
    std::string description;
    std::vector<std::string> dependencies;
    std::string underlyingName;
    std::vector<sfex::Multitype> entities;
};