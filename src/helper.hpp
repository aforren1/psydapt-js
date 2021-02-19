#ifndef PSYDAPTJS_HELPER_HPP
#define PSYDAPTJS_HELPER_HPP

#include <type_traits>
#include <vector>
#include <string>

#include <emscripten.h>
#include <emscripten/bind.h>

namespace em = emscripten;
template <typename T>
struct is_vector : public std::false_type
{
};

template <typename T, typename A>
struct is_vector<std::vector<T, A>> : public std::true_type
{
};

template <typename T>
void convert(T &out, em::val input)
{
    if constexpr (std::is_arithmetic_v<T>)
    {
        if (input.isNumber())
        {
            out = input.as<T>();

            return;
        }
        else if (input.isTrue() || input.isFalse())
        {
            out = input.as<T>();
            return;
        }
    }
    if constexpr (std::is_enum_v<T>)
    {
        if (input.typeOf().as<std::string>() == "object" && input["value"].isNumber())
        {
            out = static_cast<T>(input["value"].as<int>());
            return;
        }
    }
    if constexpr (is_vector<T>::value)
    {
        if (input.isArray())
        {
            out = em::convertJSArrayToNumberVector<typename T::value_type>(input);
            return;
        }
    }
}

#endif
