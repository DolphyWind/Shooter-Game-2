#include <Modding/LuaFunction.hpp>

std::function<void(void)> LuaFunction::empty_function = [](){};

LuaFunction::LuaFunction():
    m_func(LuaFunction::empty_function), m_isLoaded(false), m_currentLuaState(nullptr), m_numberOfArguments(0), m_numberOfReturns(0)
{
}

void LuaFunction::load(lua_State* L, const std::string& funcName, int numberOfArgs, int numberOfReturns)
{
    lua_getglobal(L, funcName.c_str());

    // If the function is absent do nothing and set the function as empty
    // Maybe throwing an exception can be implemented in the future but istead of throwing an exception I recommend checking
    // the return value of LuaFunction::isLoaded after calling this function
    if(lua_isnil(L, -1))
    {
        m_isLoaded = false;
        m_func = LuaFunction::empty_function;
        m_currentLuaState = nullptr;
        m_numberOfArguments = 0;
        m_numberOfReturns = 0;
        lua_pop(L, 1);
        return;
    }

    // Cache function to acces it faster in the future
    int func_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    m_func = [numberOfArgs, numberOfReturns, func_ref, L](){
        lua_rawgeti(L, LUA_REGISTRYINDEX, func_ref);
        lua_insert(L, 1);
        int x = lua_pcall(L, numberOfArgs, numberOfReturns, 0);
        if(x != LUA_OK) throw std::runtime_error(lua_tostring(L, -1));
    };

    m_currentLuaState = L;
    m_isLoaded = true;
    m_numberOfArguments = numberOfArgs;
    m_numberOfReturns = numberOfReturns;
}

bool LuaFunction::isLoaded() const
{
    return m_isLoaded;
}

std::vector<LuaHelper::LuaVariable> LuaFunction::operator()()
{
    if(!m_isLoaded) return std::vector<LuaHelper::LuaVariable>();
    m_func();

    std::vector<LuaHelper::LuaVariable> result;
    result.reserve(m_numberOfReturns);

    for(int i = 0; i < m_numberOfReturns; ++i)
    {
        int idx = -m_numberOfReturns + i;
        LuaHelper::LuaVariable lua_var;
        if(lua_isinteger(m_currentLuaState, idx))
        {
            lua_Integer val = lua_tointeger(m_currentLuaState, idx);
            lua_var.integer = val;
        }
        else if(lua_isnumber(m_currentLuaState, idx))
        {
            lua_Number val = lua_tonumber(m_currentLuaState, idx);
            lua_var.number = val;
        }
        else if(lua_iscfunction(m_currentLuaState, idx))
        {
            lua_CFunction val = lua_tocfunction(m_currentLuaState, idx);
            lua_var.cfunction = val;
        }
        else if(lua_isboolean(m_currentLuaState, i))
        {
            bool val = lua_toboolean(m_currentLuaState, idx);
            lua_var.boolean = val;
        }
        else if(lua_isstring(m_currentLuaState, idx))
        {
            const char* val = lua_tostring(m_currentLuaState, idx);
            lua_var.string = val;
        }
        else if(lua_touserdata(m_currentLuaState, idx))
        {
            void* val = lua_touserdata(m_currentLuaState, idx);
            lua_var.userdata = val;
        }

        result.push_back(lua_var);
        lua_remove(m_currentLuaState, idx);
    }

    return result;
}
