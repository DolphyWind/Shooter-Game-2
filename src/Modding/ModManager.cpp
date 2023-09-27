#include <Modding/ModManager.hpp>
#include <InGame/GameManager.hpp>
#include <InGame/Entity.hpp>
#include <Global.hpp>

ModManager::ModManager(const fs::path& modsFolder):
    m_mods(), m_modsFolder(modsFolder)
{
    for(auto& entry : fs::directory_iterator(modsFolder))
    {
        if(!entry.is_directory()) continue;
        try
        {
            loadMod(entry.path());
        }
        catch (const std::runtime_error& re)
        {
            std::cerr << fmt::format("Unable to load {}: {}", entry.path().filename().c_str(), re.what()) << std::endl;
        }
    }
}

bool ModManager::isLoaded(const std::string& modName)
{
    for(auto& mod : m_mods)
    {
        if(modName == mod.config.getModName()) return true;
    }

    return false;
}

void ModManager::loadMod(const fs::path& modPath, std::vector<std::string> dependencyStack)
{
    Mod currentMod;
    currentMod.load(modPath);

    if(modPath.filename() != currentMod.config.getModName())
    {
        throw std::runtime_error(fmt::format("Mod name should be same as the directory name!"));
    }

    for(auto& dependencyName : currentMod.config.getDependencies())
    {
        if(isLoaded(dependencyName)) break;

        fs::path dependencyPath = m_modsFolder / dependencyName;
        if(fs::exists(dependencyPath) && fs::is_directory(dependencyPath))
        {
            if(std::find(dependencyStack.begin(), dependencyStack.end(), dependencyName) != dependencyStack.end())
            {
                throw std::runtime_error("Circular dependency detected!");
            }
            dependencyStack.push_back(dependencyName);
            loadMod(dependencyPath, dependencyStack);
        }
        else
        {
            throw std::runtime_error(fmt::format("Unable to find dependency {}", dependencyName));
        }
    }

    m_mods.push_back(currentMod);
}

const std::vector<Mod>& ModManager::getMods()
{
    return m_mods;
}

std::optional<std::pair<Mod, EntityData>> ModManager::getEntityData(const std::string& modName, const std::string& entityName)
{
    for(auto& mod : m_mods)
    {
        if(mod.config.getModName() == modName)
        {
            for(auto& entity : mod.config.getEntities())
            {
                if(entity.name == entityName)
                    return std::pair{mod, entity};
            }
        }
    }

    return std::nullopt;
}

Entity* ModManager::spawnEntity(const std::string& modName, const std::string& entityName)
{
    std::optional<std::pair<Mod, EntityData>> entityData = getEntityData(modName, entityName);
    if(!entityData.has_value())
    {
        return nullptr;
    }

    return Global::defaultGameManager.spawnEntity(entityData.value());
}