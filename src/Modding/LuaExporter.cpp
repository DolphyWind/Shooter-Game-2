#include <Modding/LuaExporter.hpp>

LuaExporter::LuaExporter(const std::string& name, lua_CFunction constructor, const std::unordered_map<std::string, lua_CFunction>& functions, const std::unordered_map<std::string, lua_CFunction>& metafunctions):
    m_name(name), m_constructor(constructor), m_functions(functions), m_metafunctions(metafunctions)
{
}

void LuaExporter::addSubClass(LuaExporter* exporter)
{
    if(!exporter) return;

    m_subclasses.push_back(exporter);
}

void LuaExporter::addFunction(const std::string& name, lua_CFunction func)
{
    m_functions[name] = func;
}

void LuaExporter::addMetaFunction(const std::string& name, lua_CFunction func)
{
    m_functions[name] = func;
}

void LuaExporter::exportToLuaState(lua_State* L)
{
    if(!L) return;

    std::string metatableName = m_name + "_metatable";

    lua_newtable(L);
    int tableIndex = lua_gettop(L);
    lua_pushvalue(L, tableIndex);
    lua_setglobal(L, m_name.c_str());

    if(m_constructor)
    {
        lua_pushcfunction(L, m_constructor);
        lua_setfield(L, tableIndex, "new");
    }

    for(auto&[name, func] : m_functions)
    {
        lua_pushcfunction(L, func);
        lua_setfield(L, tableIndex, name.c_str());
    }

    for(auto& subclass : m_subclasses)
    {
        subclass->exportToLuaState(L);
        lua_getglobal(L, subclass->getName().c_str());
        lua_setfield(L, tableIndex, subclass->getName().c_str());
        lua_pushnil(L);
        lua_setglobal(L, subclass->getName().c_str());
    }
    lua_pop(L, 1);

    luaL_newmetatable(L, metatableName.c_str());
    int metatableIndex = lua_gettop(L);

    for(auto&[name, func] : m_metafunctions)
    {
        lua_pushstring(L, name.c_str());
        lua_pushcfunction(L, func);
        lua_settable(L, metatableIndex);
    }

    lua_remove(L, metatableIndex);
}

const std::string& LuaExporter::getName() const
{
    return m_name;
}