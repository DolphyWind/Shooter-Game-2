#pragma once
#include <Modding/Mod.hpp>

class ModLoader
{
public:
    ModLoader(const fs::path& modsFolder);

    const std::vector<Mod>& getMods();
    bool isLoaded(const std::string& modName);
private:
    void loadMod(const fs::path& modPath);

    std::vector<Mod> m_mods;
    fs::path m_modsFolder;
};