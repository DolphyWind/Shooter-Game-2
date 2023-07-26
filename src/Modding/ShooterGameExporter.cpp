#include <Modding/ShooterGameExporter.hpp>
#include <Modding/LuaExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>

std::vector<LuaExporter> ShooterGameExporter::subExporters = {
    Vector2Exporter::toLuaExporter(),
};

LuaExporter ShooterGameExporter::sg_exporter(
    "sg",
    NULL,
    {},
    {}
);

void ShooterGameExporter::init()
{
    for(auto& subclass : ShooterGameExporter::subExporters)
    {
        sg_exporter.addSubClass(&subclass);
    }
}

void ShooterGameExporter::exportTo(lua_State* L)
{
    sg_exporter.exportToLuaState(L);
}