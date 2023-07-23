#include <Modding/LuaFunction.hpp>

LuaFunction::LuaFunction():
    m_isEmtpy(true), m_currentLuaState(nullptr)
{

}

LuaFunction::~LuaFunction()
{

}

void LuaFunction::load(lua_State* L, const std::string& funcName, int numberOfArgs, int numberOfReturns)
{
    lua_getglobal(L, funcName.c_str());

    if(lua_isnil(L, -1))
    {
        m_isEmtpy = true;
        lua_pop(L, 1);
        return;
    }

    int func_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    auto callLuaFunc = [numberOfArgs, numberOfReturns, func_ref, L](){
        lua_rawgeti(L, LUA_REGISTRYINDEX, func_ref);
        lua_insert(L, 1);
        int x = lua_pcall(L, numberOfArgs, numberOfReturns, 0);
        if(x != LUA_OK) throw std::runtime_error(lua_tostring(L, -1));
    };

    m_func = callLuaFunc;
    m_currentLuaState = L;
    m_isEmtpy = false;
    m_numberOfArguments = numberOfArgs;
    m_numberOfReturns = numberOfReturns;
}


void LuaFunction::operator()()
{
    if(m_isEmtpy) return;

    m_func();
}

bool LuaFunction::isEmpty() const
{
    return m_isEmtpy;
}