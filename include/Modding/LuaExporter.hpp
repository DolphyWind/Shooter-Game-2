#pragma once
#include <lua.hpp>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

/// @brief Exports a class to lua using tables and metatables
class LuaExporter
{
public:
    /// @brief Construct a new Lua Exporter object
    /// @param name The name of the class
    /// @param constructor Constructor function of the class. Can be set to null. The first thing it pushes to the lua stack should be a userdata.
    /// Unfortunately, you also have to set metatable of the class in the constructor manually because there is no way to convert the modified
    /// function back to lua_CFunction. But the name of the metatable would be name + "_metatable".
    /// @param functions Functions of the class
    /// @param metafunctions Meta functions of the class
    LuaExporter(const std::string& name, lua_CFunction constructor, const std::unordered_map<std::string, lua_CFunction>& functions={}, const std::unordered_map<std::string, lua_CFunction>& metafunctions={});

    /// @brief Adds a sub class to lua to implement a namespace-like behaviour
    /// @param luaExporter The exporter you want to add as a subclass
    void addSubClass(LuaExporter* luaExporter);

    /// @brief Add a function to current class
    /// @param name Name of the function
    /// @param func The function you want to add
    void addFunction(const std::string& name, lua_CFunction func);

    /// @brief Add a metafunction to current class
    /// @param name Name of the metafunction
    /// @param func The metafunction you want to add
    void addMetaFunction(const std::string& name, lua_CFunction func);

    /// @brief Exports the current API to lua
    /// @param L Lua state you want to export to
    void exportToLuaState(lua_State* L);

    /// @brief Get the name of the current class
    /// @return Name of the current class
    const std::string& getName() const;
private:
    std::string m_name;
    lua_CFunction m_constructor;
    
    std::vector<LuaExporter*> m_subclasses;
    std::unordered_map<std::string, lua_CFunction> m_functions;
    std::unordered_map<std::string, lua_CFunction> m_metafunctions;
};