#pragma once
#include <Modding/Mod.hpp>
#include <optional>

class Entity;
class ModManager
{
public:
    ModManager(const fs::path& modsFolder);

    const std::vector<Mod>& getMods();
    bool isLoaded(const std::string& modName);
    std::optional<std::pair<Mod, EntityData>> getEntityData(const std::string& modName, const std::string& entityName);
    Entity* spawnEntity(const std::string& modName, const std::string& entityName);
private:
    void loadMod(const fs::path& modPath, std::vector<std::string> dependencyStack={});

    std::vector<Mod> m_mods;
    fs::path m_modsFolder;
};