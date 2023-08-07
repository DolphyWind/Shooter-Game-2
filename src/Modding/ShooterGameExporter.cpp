#include <Modding/ShooterGameExporter.hpp>
#include <Modding/LuaExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <Modding/Exporters/ColorExporter.hpp>
#include <Modding/Exporters/KeyboardExporter.hpp>
#include <Modding/Exporters/MouseExporter.hpp>
#include <Modding/Exporters/TransformExporter.hpp>

std::vector<LuaExporter> ShooterGameExporter::luaExporters = {
    Vector2Exporter::toLuaExporter(),
    ColorExporter::toLuaExporter(),
    KeyboardExporter::toLuaExporter(),
    MouseExporter::toLuaExporter(),
    TransformExporter::toLuaExporter(),
};

void ShooterGameExporter::exportTo(lua_State* L)
{
    for(auto& e : ShooterGameExporter::luaExporters)
    {
        e.exportToLuaState(L);
    }
}