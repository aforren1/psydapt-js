#include <emscripten.h>
#include <emscripten/bind.h>
#include <string>

#include "psydapt.hpp"
#include "staircase/staircase.hpp"
#include "questplus/weibull.hpp"
#include "questplus/norm_cdf.hpp"
#include "questplus/csf.hpp"

namespace em = emscripten;
namespace psy = psydapt;
namespace s = staircase;
namespace q = questplus;

EMSCRIPTEN_BINDINGS(psydapt)
{
    em::enum_<psy::Scale>("Scale")
        .value("Linear", psy::Scale::Linear)
        .value("dB", psy::Scale::dB)
        .value("Log10", psy::Scale::Log10);

    em::class_<s::EmStaircase>("staircase.Staircase")
        .constructor<em::val>()
        .function("update", em::select_overload<bool(int, double)>(&s::EmStaircase::update))
        .function("update", em::select_overload<bool(int)>(&s::EmStaircase::update))
        .function("next", &s::EmStaircase::next);

    em::enum_<psy::questplus::StimSelectionMethod>("qpStimSelectionMethod")
        .value("MinEntropy", psy::questplus::StimSelectionMethod::MinEntropy)
        .value("MinNEntropy", psy::questplus::StimSelectionMethod::MinNEntropy);

    em::enum_<psy::questplus::ParamEstimationMethod>("qpParamEstimationMethod")
        .value("Mean", psy::questplus::ParamEstimationMethod::Mean)
        .value("Median", psy::questplus::ParamEstimationMethod::Median)
        .value("Mode", psy::questplus::ParamEstimationMethod::Mode);

    em::class_<q::EmWeibull>("questplus.Weibull")
        .constructor<em::val>()
        .function("update", em::select_overload<bool(int, double)>(&q::EmWeibull::update))
        .function("update", em::select_overload<bool(int)>(&q::EmWeibull::update))
        .function("next", &q::EmWeibull::next);

    em::class_<q::EmNormCDF>("questplus.NormCDF")
        .constructor<em::val>()
        .function("update", em::select_overload<bool(int, double)>(&q::EmNormCDF::update))
        .function("update", em::select_overload<bool(int)>(&q::EmNormCDF::update))
        .function("next", &q::EmNormCDF::next);

    em::class_<q::EmCSF>("questplus.CSF")
        .constructor<em::val>()
        .function("update", em::select_overload<bool(int, em::val)>(&q::EmCSF::update2))
        .function("update", em::select_overload<bool(int)>(&q::EmCSF::update))
        .function("next", &q::EmCSF::next2);

    // set up namespaces
    EM_ASM({
        Module['staircase'] = {};
        Module['staircase']['Staircase'] = Module['staircase$Staircase'];
        delete Module['staircase$Staircase'];

        // TODO: enums don't follow the same pattern as classes re: how '.' is parsed
        Module['questplus'] = {};
        Module['questplus']['StimSelectionMethod'] = Module['qpStimSelectionMethod'];
        delete Module['qpStimSelectionMethod'];

        Module['questplus']['ParamEstimationMethod'] = Module['qpParamEstimationMethod'];
        delete Module['qpParamEstimationMethod'];

        Module['questplus']['Weibull'] = Module['questplus$Weibull'];
        delete Module['questplus$Weibull'];

        Module['questplus']['NormCDF'] = Module['questplus$NormCDF'];
        delete Module['questplus$NormCDF'];

        Module['questplus']['CSF'] = Module['questplus$CSF'];
        delete Module['questplus$CSF'];
    });
}