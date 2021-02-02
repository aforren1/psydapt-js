#include <emscripten/bind.h>
#include <string>

#include "psydapt.hpp"
#include "staircase.hpp"

namespace em = emscripten;

EMSCRIPTEN_BINDINGS(psydapt)
{
    em::class_<EmStaircase>("Staircase")
        .constructor<em::val>()
        .function("update", em::select_overload<bool(int, double)>(&EmStaircase::update))
        .function("update", em::select_overload<bool(int)>(&EmStaircase::update))
        .function("next", &EmStaircase::next);
}