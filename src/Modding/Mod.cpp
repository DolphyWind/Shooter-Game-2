#include <Modding/Mod.hpp>

Mod::Mod()
{
}

void Mod::load(const fs::path& modPath)
{
    fs::path configPath = modPath / "config.json";
    decltype(assetsFolderPath) _assetsFolderPath = modPath / "assets";
    decltype(entitiesFolderPath) _entitiesFolderPath = modPath / "entities";
    decltype(config) _config;

    if(!fs::exists(configPath) || !fs::exists(_assetsFolderPath) || !fs::exists(_entitiesFolderPath))
    {
        throw std::runtime_error(fmt::format("Mod structure in {} is invalid!", modPath.c_str()));
    }

    try
    {
        _config.loadFromFile(configPath);
    }
    catch (const VersionParsingException& vpe)
    {
        throw std::runtime_error("VersionParsingException: Unable to parse mod version.");
    }
    catch (const InvalidFieldException& ife)
    {
        throw std::runtime_error(fmt::format("InvalidFieldException: {}", ife.what()));
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error(fmt::format("Unexpected Error: {}", e.what()));
    }

    for (EntityData& e : _config.getEntities())
    {
        fs::path entityPath = _entitiesFolderPath / e.file;
        if(!fs::exists(entityPath))
        {
            throw std::runtime_error(fmt::format("The file {} does not exists!", entityPath.c_str()));
        }
    }

    // Do this to only load mod if every test passes
    config = _config;
    assetsFolderPath = _assetsFolderPath;
    entitiesFolderPath = _entitiesFolderPath;
}