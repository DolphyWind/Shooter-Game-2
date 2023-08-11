#pragma once
#include <lua.hpp>
#include <string>
#include <cstring>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <memory>
#include <new>
#define ASSETSPATH_VARNAME "ASSETS_FOLDER_PATH"

/// @brief Exports a class to lua using tables and metatables.
class LuaExporter
{
public:
    struct UserdataInfo
    {
        void* data;
        std::size_t size;
        std::string metatable_name;
    };

    /// @brief Construct a new Lua Exporter object
    /// @param name The name of the class
    /// @param constructor Constructor function of the class. Can be set to null. The first thing it pushes to the lua stack should be a userdata.
    /// Unfortunately, you also have to set metatable of the class in the constructor manually because there is no way to convert the modified
    /// function back to lua_CFunction. But the name of the metatable always would be (name) + "_metatable".
    /// @param functions Functions of the class
    /// @param metafunctions Meta functions of the class
    LuaExporter(
        const std::string& name,
        lua_CFunction constructor,
        const std::unordered_map<std::string, lua_CFunction>& functions={},
        const std::unordered_map<std::string, lua_CFunction>& metafunctions={}
    );

    /// @brief Copy constructor
    LuaExporter(const LuaExporter& otherLuaExporter);

    /// @brief Move constructor
    LuaExporter(LuaExporter&& otherLuaExporter);

    /// @brief Destroy the Lua Exporter object
    ~LuaExporter();

    /// @brief Adds a function to current class
    /// @param name Name of the function
    /// @param func The function you want to add
    void addFunction(const std::string& name, lua_CFunction func);

    /// @brief Adds a metafunction to metatable of the current class
    /// @param name Name of the metafunction
    /// @param func The metafunction you want to add
    void addMetaFunction(const std::string& name, lua_CFunction func);

    /// @brief Adds a userdata to the class. Copies the given userdata so nothing bad happens even if the original memory gets deleted.
    /// @param name Name of the userdata
    /// @param data Userdata you want to add
    /// @param size Size of the userdata
    /// @param metatable_name Metatable of the userdata. Left it empty to make it plain userdata. 
    void addUserdata(const std::string& name, void* data, std::size_t size, const std::string& metatable_name="");

    /// @brief Adds an integer to the class
    /// @param name Name of the integer
    /// @param integer Integer you want to add
    void addInteger(const std::string& name, lua_Integer integer);

    /// @brief Adds a number to the class
    /// @param name Name of the number
    /// @param number Number you want to add.
    void addNumber(const std::string& name, lua_Number number);

    /// @brief Adds a boolean to the class
    /// @param name Name of the boolean
    /// @param boolean Boolean you want to add
    void addBoolean(const std::string& name, bool boolean);

    /// @brief Adds a string to the class
    /// @param name Name of the string
    /// @param str String you want to add
    void addString(const std::string& name, const std::string& str);

    /// @brief Exports the current API to lua
    /// @param L Lua state you want to export to
    void exportToLuaState(lua_State* L);

    /// @brief Get the name of the current class
    /// @return Name of the current class
    const std::string& getName() const;
private:
    std::string m_name;
    lua_CFunction m_constructor;
    
    std::unordered_map<std::string, lua_CFunction> m_functions;
    std::unordered_map<std::string, lua_CFunction> m_metafunctions;

    std::unordered_map<std::string, UserdataInfo> m_userdatas;
    std::unordered_map<std::string, lua_Integer> m_integers;
    std::unordered_map<std::string, lua_Number> m_numbers;
    std::unordered_map<std::string, bool> m_booleans;
    std::unordered_map<std::string, std::string> m_strings;
};