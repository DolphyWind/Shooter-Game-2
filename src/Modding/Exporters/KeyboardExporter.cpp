#include <Modding/Exporters/KeyboardExporter.hpp>
#include <Modding/LuaExporter.hpp>
#include <SFEX/General/Keyboard.hpp>

int KeyboardExporter::getKey(lua_State *L)
{
    lua_Integer key = luaL_checkinteger(L, 1);
    bool keyState = sfex::Keyboard::getKey(static_cast<sfex::Keyboard::Key>(key));
    lua_pushboolean(L, keyState);
    return 1;
}

int KeyboardExporter::getKeyDown(lua_State *L)
{
    lua_Integer key = luaL_checkinteger(L, 1);
    bool keyState = sfex::Keyboard::getKeyDown(static_cast<sfex::Keyboard::Key>(key));
    lua_pushboolean(L, keyState);
    return 1;
}

int KeyboardExporter::getKeyUp(lua_State *L)
{
    lua_Integer key = luaL_checkinteger(L, 1);
    bool keyState = sfex::Keyboard::getKeyUp(static_cast<sfex::Keyboard::Key>(key));
    lua_pushboolean(L, keyState);
    return 1;
}

LuaExporter KeyboardExporter::toLuaExporter()
{
    LuaExporter keyboardExporter(LUA_KEYBOARD_CLASSNAME,
    nullptr,
    {
        {"getKey", KeyboardExporter::getKey},
        {"getKeyDown", KeyboardExporter::getKeyDown},
        {"getKeyUp", KeyboardExporter::getKeyUp},
    },
    {}
    );

    keyboardExporter.addInteger("A", sfex::Keyboard::Key::A);
    keyboardExporter.addInteger("B", sfex::Keyboard::Key::B);
    keyboardExporter.addInteger("C", sfex::Keyboard::Key::C);
    keyboardExporter.addInteger("D", sfex::Keyboard::Key::D);
    keyboardExporter.addInteger("E", sfex::Keyboard::Key::E);
    keyboardExporter.addInteger("F", sfex::Keyboard::Key::F);
    keyboardExporter.addInteger("G", sfex::Keyboard::Key::G);
    keyboardExporter.addInteger("H", sfex::Keyboard::Key::H);
    keyboardExporter.addInteger("I", sfex::Keyboard::Key::I);
    keyboardExporter.addInteger("J", sfex::Keyboard::Key::J);
    keyboardExporter.addInteger("K", sfex::Keyboard::Key::K);
    keyboardExporter.addInteger("L", sfex::Keyboard::Key::L);
    keyboardExporter.addInteger("M", sfex::Keyboard::Key::M);
    keyboardExporter.addInteger("N", sfex::Keyboard::Key::N);
    keyboardExporter.addInteger("O", sfex::Keyboard::Key::O);
    keyboardExporter.addInteger("P", sfex::Keyboard::Key::P);
    keyboardExporter.addInteger("Q", sfex::Keyboard::Key::Q);
    keyboardExporter.addInteger("R", sfex::Keyboard::Key::R);
    keyboardExporter.addInteger("S", sfex::Keyboard::Key::S);
    keyboardExporter.addInteger("T", sfex::Keyboard::Key::T);
    keyboardExporter.addInteger("U", sfex::Keyboard::Key::U);
    keyboardExporter.addInteger("V", sfex::Keyboard::Key::V);
    keyboardExporter.addInteger("W", sfex::Keyboard::Key::W);
    keyboardExporter.addInteger("X", sfex::Keyboard::Key::X);
    keyboardExporter.addInteger("Y", sfex::Keyboard::Key::Y);
    keyboardExporter.addInteger("Z", sfex::Keyboard::Key::Z);
    keyboardExporter.addInteger("Num0", sfex::Keyboard::Key::Num0);
    keyboardExporter.addInteger("Num1", sfex::Keyboard::Key::Num1);
    keyboardExporter.addInteger("Num2", sfex::Keyboard::Key::Num2);
    keyboardExporter.addInteger("Num3", sfex::Keyboard::Key::Num3);
    keyboardExporter.addInteger("Num4", sfex::Keyboard::Key::Num4);
    keyboardExporter.addInteger("Num5", sfex::Keyboard::Key::Num5);
    keyboardExporter.addInteger("Num6", sfex::Keyboard::Key::Num6);
    keyboardExporter.addInteger("Num7", sfex::Keyboard::Key::Num7);
    keyboardExporter.addInteger("Num8", sfex::Keyboard::Key::Num8);
    keyboardExporter.addInteger("Num9", sfex::Keyboard::Key::Num9);
    keyboardExporter.addInteger("Escape", sfex::Keyboard::Key::Escape);
    keyboardExporter.addInteger("LControl", sfex::Keyboard::Key::LControl);
    keyboardExporter.addInteger("LShift", sfex::Keyboard::Key::LShift);
    keyboardExporter.addInteger("LAlt", sfex::Keyboard::Key::LAlt);
    keyboardExporter.addInteger("LSystem", sfex::Keyboard::Key::LSystem);
    keyboardExporter.addInteger("RControl", sfex::Keyboard::Key::RControl);
    keyboardExporter.addInteger("RShift", sfex::Keyboard::Key::RShift);
    keyboardExporter.addInteger("RAlt", sfex::Keyboard::Key::RAlt);
    keyboardExporter.addInteger("RSystem", sfex::Keyboard::Key::RSystem);
    keyboardExporter.addInteger("Menu", sfex::Keyboard::Key::Menu);
    keyboardExporter.addInteger("LBracket", sfex::Keyboard::Key::LBracket);
    keyboardExporter.addInteger("RBracket", sfex::Keyboard::Key::RBracket);
    keyboardExporter.addInteger("Semicolon", sfex::Keyboard::Key::Semicolon);
    keyboardExporter.addInteger("Comma", sfex::Keyboard::Key::Comma);
    keyboardExporter.addInteger("Period", sfex::Keyboard::Key::Period);
    keyboardExporter.addInteger("Quote", sfex::Keyboard::Key::Quote);
    keyboardExporter.addInteger("Slash", sfex::Keyboard::Key::Slash);
    keyboardExporter.addInteger("Backslash", sfex::Keyboard::Key::Backslash);
    keyboardExporter.addInteger("Tilde", sfex::Keyboard::Key::Tilde);
    keyboardExporter.addInteger("Equal", sfex::Keyboard::Key::Equal);
    keyboardExporter.addInteger("Hyphen", sfex::Keyboard::Key::Hyphen);
    keyboardExporter.addInteger("Space", sfex::Keyboard::Key::Space);
    keyboardExporter.addInteger("Enter", sfex::Keyboard::Key::Enter);
    keyboardExporter.addInteger("Backspace", sfex::Keyboard::Key::Backspace);
    keyboardExporter.addInteger("Tab", sfex::Keyboard::Key::Tab);
    keyboardExporter.addInteger("PageUp", sfex::Keyboard::Key::PageUp);
    keyboardExporter.addInteger("PageDown", sfex::Keyboard::Key::PageDown);
    keyboardExporter.addInteger("End", sfex::Keyboard::Key::End);
    keyboardExporter.addInteger("Home", sfex::Keyboard::Key::Home);
    keyboardExporter.addInteger("Insert", sfex::Keyboard::Key::Insert);
    keyboardExporter.addInteger("Delete", sfex::Keyboard::Key::Delete);
    keyboardExporter.addInteger("Add", sfex::Keyboard::Key::Add);
    keyboardExporter.addInteger("Subtract", sfex::Keyboard::Key::Subtract);
    keyboardExporter.addInteger("Multiply", sfex::Keyboard::Key::Multiply);
    keyboardExporter.addInteger("Divide", sfex::Keyboard::Key::Divide);
    keyboardExporter.addInteger("Left", sfex::Keyboard::Key::Left);
    keyboardExporter.addInteger("Right", sfex::Keyboard::Key::Right);
    keyboardExporter.addInteger("Up", sfex::Keyboard::Key::Up);
    keyboardExporter.addInteger("Down", sfex::Keyboard::Key::Down);
    keyboardExporter.addInteger("Numpad0", sfex::Keyboard::Key::Numpad0);
    keyboardExporter.addInteger("Numpad1", sfex::Keyboard::Key::Numpad1);
    keyboardExporter.addInteger("Numpad2", sfex::Keyboard::Key::Numpad2);
    keyboardExporter.addInteger("Numpad3", sfex::Keyboard::Key::Numpad3);
    keyboardExporter.addInteger("Numpad4", sfex::Keyboard::Key::Numpad4);
    keyboardExporter.addInteger("Numpad5", sfex::Keyboard::Key::Numpad5);
    keyboardExporter.addInteger("Numpad6", sfex::Keyboard::Key::Numpad6);
    keyboardExporter.addInteger("Numpad7", sfex::Keyboard::Key::Numpad7);
    keyboardExporter.addInteger("Numpad8", sfex::Keyboard::Key::Numpad8);
    keyboardExporter.addInteger("Numpad9", sfex::Keyboard::Key::Numpad9);
    keyboardExporter.addInteger("F1", sfex::Keyboard::Key::F1);
    keyboardExporter.addInteger("F2", sfex::Keyboard::Key::F2);
    keyboardExporter.addInteger("F3", sfex::Keyboard::Key::F3);
    keyboardExporter.addInteger("F4", sfex::Keyboard::Key::F4);
    keyboardExporter.addInteger("F5", sfex::Keyboard::Key::F5);
    keyboardExporter.addInteger("F6", sfex::Keyboard::Key::F6);
    keyboardExporter.addInteger("F7", sfex::Keyboard::Key::F7);
    keyboardExporter.addInteger("F8", sfex::Keyboard::Key::F8);
    keyboardExporter.addInteger("F9", sfex::Keyboard::Key::F9);
    keyboardExporter.addInteger("F10", sfex::Keyboard::Key::F10);
    keyboardExporter.addInteger("F11", sfex::Keyboard::Key::F11);
    keyboardExporter.addInteger("F12", sfex::Keyboard::Key::F12);
    keyboardExporter.addInteger("F13", sfex::Keyboard::Key::F13);
    keyboardExporter.addInteger("F14", sfex::Keyboard::Key::F14);
    keyboardExporter.addInteger("F15", sfex::Keyboard::Key::F15);
    keyboardExporter.addInteger("Pause", sfex::Keyboard::Key::Pause);

    return keyboardExporter;
}