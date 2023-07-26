#include <Modding/LuaExporter.hpp>

LuaExporter::LuaExporter(const std::string& name, lua_CFunction constructor, const std::unordered_map<std::string, lua_CFunction>& functions, const std::unordered_map<std::string, lua_CFunction>& metafunctions):
    m_name(name), m_constructor(constructor), m_functions(functions), m_metafunctions(metafunctions)
{
}

LuaExporter::~LuaExporter()
{
    for(auto&[name, userdataInfo] : m_userdatas)
    {
        operator delete(userdataInfo.data);
    }
}

LuaExporter::LuaExporter(const LuaExporter& otherLuaExporter)
{
    // During copy, we copy otherExporter's userdatas to a new location to prevent double deletion in the destructor.
    // We copy everything else using their copy constructors.

    this->m_name = otherLuaExporter.m_name;
    this->m_constructor = otherLuaExporter.m_constructor;

    this->m_functions = otherLuaExporter.m_functions;
    this->m_metafunctions = otherLuaExporter.m_metafunctions;

    // This is where the fun begins
    for(auto&[name, userdataInfo] : m_userdatas)
    {
        operator delete(userdataInfo.data);
    }
    m_userdatas.clear();
    
    for(auto&[name, userdataInfo] : otherLuaExporter.m_userdatas)
    {
        UserdataInfo newDataInfo;
        newDataInfo.data = operator new (userdataInfo.size);
        newDataInfo.size = userdataInfo.size;
        newDataInfo.metatable_name = userdataInfo.metatable_name;
        std::memcpy(newDataInfo.data, userdataInfo.data, userdataInfo.size);
        m_userdatas[name] = newDataInfo;
    }

    m_integers = otherLuaExporter.m_integers;
    m_numbers = otherLuaExporter.m_numbers;
    m_booleans = otherLuaExporter.m_booleans;
    m_strings = otherLuaExporter.m_strings;
}

LuaExporter::LuaExporter(LuaExporter&& otherLuaExporter)
{
    // During move, we copy otherExporter's userdatas to a new location and delete the otherExporter's userdatas.
    // We do move everything else using their move constructors..

    this->m_name = std::move(otherLuaExporter.m_name);
    this->m_constructor = std::move(otherLuaExporter.m_constructor);

    this->m_functions = std::move(otherLuaExporter.m_functions);
    this->m_metafunctions = std::move(otherLuaExporter.m_metafunctions);

    // This is where the fun begins
    for(auto&[name, userdataInfo] : m_userdatas)
    {
        operator delete(userdataInfo.data);
    }
    m_userdatas.clear();
    
    for(auto&[name, userdataInfo] : otherLuaExporter.m_userdatas)
    {
        UserdataInfo newDataInfo;
        newDataInfo.data = operator new (userdataInfo.size);
        newDataInfo.size = userdataInfo.size;
        newDataInfo.metatable_name = userdataInfo.metatable_name;
        std::memcpy(newDataInfo.data, userdataInfo.data, userdataInfo.size);
        m_userdatas[name] = newDataInfo;
        operator delete(userdataInfo.data);
    }
    otherLuaExporter.m_userdatas.clear();

    m_integers = std::move(otherLuaExporter.m_integers);
    m_numbers = std::move(otherLuaExporter.m_numbers);
    m_booleans = std::move(otherLuaExporter.m_booleans);
    m_strings = std::move(otherLuaExporter.m_strings);
}

void LuaExporter::addFunction(const std::string& name, lua_CFunction func)
{
    m_functions[name] = func;
}

void LuaExporter::addMetaFunction(const std::string& name, lua_CFunction func)
{
    m_functions[name] = func;
}

void LuaExporter::addUserdata(const std::string& name, void* data, std::size_t size, const std::string& metatable_name)
{
    void* tmp = operator new (size);
    if(!tmp)
    {
        throw std::bad_alloc();
    }
    std::memcpy(tmp, data, size);
    m_userdatas[name] = {tmp, size, metatable_name};
}

void LuaExporter::addInteger(const std::string& name, lua_Integer integer)
{
    m_integers[name] = integer;
}

void LuaExporter::addNumber(const std::string& name, lua_Number number)
{
    m_numbers[name] = number;
}

void LuaExporter::addBoolean(const std::string& name, bool boolean)
{
    m_booleans[name] = boolean;
}

void LuaExporter::addString(const std::string& name, const std::string& str)
{
    m_strings[name] = str;
}

void LuaExporter::exportToLuaState(lua_State* L)
{
    if(!L) return;
    std::string metatableName = m_name + "_metatable";
    luaL_newmetatable(L, metatableName.c_str());
    int metatableIndex = lua_gettop(L);

    for(auto&[name, func] : m_metafunctions)
    {
        lua_pushstring(L, name.c_str());
        lua_pushcfunction(L, func);
        lua_settable(L, metatableIndex);
    }
    lua_remove(L, metatableIndex);

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

    for(auto&[name, userdataInfo] : m_userdatas)
    {
        void* tmp = lua_newuserdata(L, userdataInfo.size);
        std::memcpy(tmp, userdataInfo.data, userdataInfo.size);
        
        if(!userdataInfo.metatable_name.empty())
        {
            luaL_setmetatable(L, userdataInfo.metatable_name.c_str());
        }
        lua_setfield(L, tableIndex, name.c_str());
    }

    for(auto&[name, integer] : m_integers)
    {
        lua_pushinteger(L, integer);
        lua_setfield(L, tableIndex, name.c_str());
    }

    for(auto&[name, number] : m_numbers)
    {
        lua_pushnumber(L, number);
        lua_setfield(L, tableIndex, name.c_str());
    }

    for(auto&[name, boolean] : m_booleans)
    {
        lua_pushboolean(L, boolean);
        lua_setfield(L, tableIndex, name.c_str());
    }

    for(auto&[name, str] : m_strings)
    {
        lua_pushstring(L, str.c_str());
        lua_setfield(L, tableIndex, name.c_str());
    }

    lua_pop(L, 1);
}

const std::string& LuaExporter::getName() const
{
    return m_name;
}