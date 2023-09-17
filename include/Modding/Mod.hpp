#pragma once
#include <Modding/ModConfig.hpp>
#include <fmt/format.h>
#include <filesystem>
namespace fs = std::filesystem;

class Mod
{
public:
    Mod();

    /// Loads the mod from a path
    /// \param modPath Path of the mod to load
    /// \throw std::runtime_error If the mod config or structure is invalid
    void load(const fs::path& modPath);

    ModConfig config;
    fs::path assetsFolderPath;
    fs::path entitiesFolderPath;
};