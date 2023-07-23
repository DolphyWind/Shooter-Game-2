#pragma once
#include <lua.hpp>
#include <functional>
#include <iostream>
#include <Modding/LuaHelper.hpp>

class LuaFunction
{
public:
    LuaFunction();
    void load(lua_State* L, const std::string& funcName, int numberOfArgs, int numberOfReturns);
    ~LuaFunction();

    bool isEmpty() const;


    template<typename T, typename... Args>
    void operator()(T&& val, Args&&... args);

    template<typename T>
    void operator()(T&& val);

    void operator()();
private:
    std::function<void(void)> m_func;
    bool m_isEmtpy;

    lua_State* m_currentLuaState;
    int m_numberOfArguments;
    int m_numberOfReturns;
};

template<typename T, typename... Args>
void LuaFunction::operator()(T&& val, Args&&... args)
{
    if(m_isEmtpy) return;

    (*this)(val);
    (*this)(std::forward<Args&&...>(args...));
}

template<typename T>
void LuaFunction::operator()(T&& val)
{
    if(m_isEmtpy) return;

    LuaHelper::push(m_currentLuaState, val);
    if(lua_gettop(m_currentLuaState) == m_numberOfArguments) m_func();
}