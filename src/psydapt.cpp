#include <emscripten/bind.h>
#include <string>

#include "psydapt.hpp"
#include "staircase.hpp"
#include "questplus_weibull.hpp"

namespace em = emscripten;

EMSCRIPTEN_BINDINGS(psydapt)
{
    em::class_<EmStaircase>("Staircase")
        .constructor<em::val>()
        .function("update", em::select_overload<bool(int, double)>(&EmStaircase::update))
        .function("update", em::select_overload<bool(int)>(&EmStaircase::update))
        .function("next", &EmStaircase::next);

    // TODO: figure out namespaces
    em::class_<EmWeibull>("QuestPlusWeibull")
        .constructor<em::val>()
        .function("update", em::select_overload<bool(int, double)>(&EmWeibull::update))
        .function("update", em::select_overload<bool(int)>(&EmWeibull::update))
        .function("next", &EmWeibull::next);
}