#include <Modding/ShooterGameExporter.hpp>
#include <Modding/LuaExporter.hpp>
#include <Modding/Exporters/Vector2Exporter.hpp>
#include <Modding/Exporters/ColorExporter.hpp>
#include <Modding/Exporters/KeyboardExporter.hpp>
#include <Modding/Exporters/MouseExporter.hpp>
#include <Modding/Exporters/TransformExporter.hpp>
#include <Modding/Exporters/StopwatchExporter.hpp>
#include <Modding/Exporters/JoystickExporter.hpp>
#include <Modding/Exporters/FloatRectExporter.hpp>
#include <Modding/Exporters/IntRectExporter.hpp>
#include <Modding/Exporters/ImageExporter.hpp>
#include <Modding/Exporters/GlyphExporter.hpp>
#include <Modding/Exporters/FontExporter.hpp>
#include <Modding/Exporters/RenderWindowExporter.hpp>

std::vector<LuaExporter> ShooterGameExporter::luaExporters = {
    Vector2Exporter::toLuaExporter(),
    ColorExporter::toLuaExporter(),
    KeyboardExporter::toLuaExporter(),
    MouseExporter::toLuaExporter(),
    TransformExporter::toLuaExporter(),
    StopwatchExporter::toLuaExporter(),
    JoystickExporter::toLuaExporter(),
    FloatRectExporter::toLuaExporter(),
    IntRectExporter::toLuaExporter(),
    ImageExporter::toLuaExporter(),
    GlyphExporter::toLuaExporter(),
    FontExporter::toLuaExporter(),
    RenderWindowExporter::toLuaExporter(),
};

void ShooterGameExporter::exportTo(lua_State* L)
{
    for(auto& e : ShooterGameExporter::luaExporters)
    {
        e.exportToLuaState(L);
    }
}