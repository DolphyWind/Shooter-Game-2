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
#include <Modding/Exporters/ViewExporter.hpp>
#include <Modding/Exporters/EventExporter.hpp>
#include <Modding/Exporters/VideoModeExporter.hpp>
#include <Modding/Exporters/ContextSettingsExporter.hpp>
#include <Modding/Exporters/CursorExporter.hpp>
#include <Modding/Exporters/TextureExporter.hpp>
#include <Modding/Exporters/SpriteExporter.hpp>
#include <Modding/Exporters/RenderWindowExporter.hpp>
#include <Modding/Exporters/RectangleShapeExporter.hpp>
#include <Modding/Exporters/CircleShapeExporter.hpp>
#include <Modding/Exporters/ConvexShapeExporter.hpp>
#include <Modding/Exporters/SoundBufferExporter.hpp>
#include <Modding/Exporters/SoundExporter.hpp>
#include <Modding/Exporters/MusicExporter.hpp>
#include <Modding/Exporters/TextExporter.hpp>
#include <Modding/Exporters/EntityExporter.hpp>

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
    ViewExporter::toLuaExporter(),
    EventExporter::toLuaExporter(),
    VideoModeExporter::toLuaExporter(),
    ContextSettingsExporter::toLuaExporter(),
    CursorExporter::toLuaExporter(),
    TextureExporter::toLuaExporter(),
    SpriteExporter::toLuaExporter(),
    RenderWindowExporter::toLuaExporter(),
    RectangleShapeExporter::toLuaExporter(),
    CircleShapeExporter::toLuaExporter(),
    ConvexShapeExporter::toLuaExporter(),
    SoundBufferExporter::toLuaExporter(),
    SoundExporter::toLuaExporter(),
    MusicExporter::toLuaExporter(),
    TextExporter::toLuaExporter(),
    EntityExporter::toLuaExporter(),
};

void ShooterGameExporter::exportTo(lua_State* L)
{
    for(auto& e : ShooterGameExporter::luaExporters)
    {
        e.exportToLuaState(L);
    }
}