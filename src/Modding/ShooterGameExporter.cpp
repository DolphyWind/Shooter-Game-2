#include <Modding/ShooterGameExporter.hpp>
#include <Modding/LuaExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>

std::vector<LuaExporter> ShooterGameExporter::luaExporters = {
    Vector2Exporter::toLuaExporter(),
};

void ShooterGameExporter::exportTo(lua_State* L)
{
    for(auto& e : ShooterGameExporter::luaExporters)
    {
        e.exportToLuaState(L);
    }
}