#pragma once
#include <Modding/ModConfig.hpp>

class Mod
{
public:
    Mod(std::string modName);

    ModConfig config;
    std::string assetsFolderPath;
    std::string entityFolderPath;
    std::vector<std::string> entities;
};