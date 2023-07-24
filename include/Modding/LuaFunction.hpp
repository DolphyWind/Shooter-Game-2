#pragma once
#include <lua.hpp>
#include <functional>
#include <stdexcept>
#include <vector>
#include <cassert>
#include <Modding/LuaHelper.hpp>

class LuaFunction
{
public:

    /// @brief Construct a new Lua Function object. By default, every Lua Function object is considered unloaded when you first create them.
    LuaFunction();

    /// @brief Load a new lua function from a lua state
    /// @param L Lua state to load from
    /// @param funcName Name of the lua function
    /// @param numberOfArgs Number of arguments the function takes
    /// @param numberOfReturns Number of return values it has
    void load(lua_State* L, const std::string& funcName, int numberOfArgs, int numberOfReturns);
    
    /// @brief Destroy the Lua Function object
    ~LuaFunction() = default;

    /// @brief Check whether the function is successfully loaded or not.
    /// @return True if the function is successfullt loaded. False otherwise.
    bool isLoaded() const;

    /// @brief Calls the underlying lua function with given arguments and returns its return values as a std::vector<LuaHelver::LuaVariable>
    /// @return The return values of the underlying lua function as a std::vector<LuaHelper::LuaVariable>
    template<typename T, typename... Args>
    [[maybe_unused]] std::vector<LuaHelper::LuaVariable> operator()(T&& val, Args&&... args);

    /// @brief Calls the underlying lua function with one argument and returns its return values as a std::vector<LuaHelver::LuaVariable>
    /// @return The return values of the underlying lua function as a std::vector<LuaHelper::LuaVariable>
    template<typename T, typename... Args>
    [[maybe_unused]] std::vector<LuaHelper::LuaVariable> operator()(T&& val);

    /// @brief Calls the underlying lua function with no arguments and returns its return values as a std::vector<LuaHelver::LuaVariable>
    /// @return The return values of the underlying lua function as a std::vector<LuaHelper::LuaVariable>
    [[maybe_unused]] std::vector<LuaHelper::LuaVariable> operator()();

    /// @brief A std::function object that does absolutely nothing
    static std::function<void(void)> empty_function;
private:
    std::function<void(void)> m_func;
    bool m_isLoaded;

    lua_State* m_currentLuaState;
    int m_numberOfArguments;
    int m_numberOfReturns;
};

template<typename T, typename... Args>
std::vector<LuaHelper::LuaVariable> LuaFunction::operator()(T&& val, Args&&... args)
{
    if(!m_isLoaded) return std::vector<LuaHelper::LuaVariable>();

    LuaHelper::push(m_currentLuaState, val);
    return (*this)(std::forward<Args&&...>(args...));
}

template<typename T, typename... Args>
std::vector<LuaHelper::LuaVariable> LuaFunction::operator()(T&& val)
{
    if(!m_isLoaded) return std::vector<LuaHelper::LuaVariable>();

    LuaHelper::push(m_currentLuaState, val);
    return (*this)();
}
