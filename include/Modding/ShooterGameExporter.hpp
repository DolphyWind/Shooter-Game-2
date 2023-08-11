#pragma once
#include <iostream>
#include <SFEX/Numeric/Vector2.hpp>
#include <lua.hpp>
#include <cassert>
#include <vector>
#define ASSETSPATH_VARNAME "ASSETS_FOLDER_PATH"

class LuaExporter;
class ShooterGameExporter
{
public:
    ShooterGameExporter() = delete;
    static void exportTo(lua_State* L);
private:
    static std::vector<LuaExporter> luaExporters;
};
