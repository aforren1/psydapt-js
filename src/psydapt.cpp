#include <emscripten/bind.h>
#include <string>

#include "psydapt.hpp"
#include "staircase.hpp"
#include "questplus_weibull.hpp"
#include "questplus_normcdf.hpp"

namespace em = emscripten;
namespace psy = psydapt;

EMSCRIPTEN_BINDINGS(psydapt)
{
    em::enum_<psy::Scale>("Scale")
        .value("Linear", psy::Scale::Linear)
        .value("dB", psy::Scale::dB)
        .value("Log10", psy::Scale::Log10);
    em::class_<EmStaircase>("staircase.Staircase")
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

    em::class_<EmNormCDF>("QuestPlusNormCDF")
        .constructor<em::val>()
        .function("update", em::select_overload<bool(int, double)>(&EmNormCDF::update))
        .function("update", em::select_overload<bool(int)>(&EmNormCDF::update))
        .function("next", &EmNormCDF::next);

    // EM_ASM({
    //     Module['staircase']['Staircase'] = Module['staircase.Staircase'];
    //     delete Module['staircase.Staircase'];
    // });
}